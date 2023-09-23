#include "MemoryManager.h"
#include <vector>
#include <list>
#include <limits>
#include <stdlib.h>
#include <fstream>
#include <fcntl.h>
#include <string>
#include <unistd.h>

using namespace std;

memChunk::memChunk(int offset, bool hole, int size, memChunk* prev, memChunk* next) {
    this->offset = offset;
    this->size = size;
    this->hole = hole;
    this->prev = prev;
    this->next = next;
} //Done
int memChunk::getOffset() {
    return this->offset;
}
int memChunk::getSize() {
    return this->size;
}
bool memChunk::isHole() {
    return this->hole;
}
memChunk* memChunk::getPrev() {
    return this->prev;
}
memChunk* memChunk::getNext() {
    return this->next;
}
void memChunk::setPrev(memChunk* prev) {
    this->prev = prev;
}
void memChunk::setNext(memChunk* next) {
    this->next = next;
}
void memChunk::setOffset(int offset) {
    this->offset = offset;
}
void memChunk::setSize(int size) {
    this->size = size;
}
void memChunk::setHole(bool hole) {
    this->hole = hole;
}



MemoryManager::MemoryManager(unsigned wordSize, std::function<int(int, void*)> allocator) {
    this->allocator = allocator;
    this->wordSize = wordSize;
}


MemoryManager::~MemoryManager() {
    shutdown();
    //delete storedList;
    //delete storedBitMap;
}

void MemoryManager::initialize(size_t sizeInWords) {
    if (sizeInWords < 65536) {
        this->totalWords = sizeInWords;
    }

    totalBytes = totalWords * wordSize;

    if (startOfMem) {
        shutdown();
    }

    startOfMem = new uint8_t[sizeInWords * totalWords];

    this->head = new memChunk(0, false, 0, nullptr, nullptr); //dummyNode to hold the head
}

void MemoryManager::shutdown() {
    delete[] startOfMem;
    startOfMem = nullptr;

    memChunk* curr = this->head;
    memChunk* nextPlaceholder;

    while (curr) {
        nextPlaceholder = curr->getNext();
        delete curr;
        curr = nextPlaceholder;
    }

    //delete this->head;
    this->head = nullptr;

}

void* MemoryManager::allocate(size_t sizeInBytes) {
    if (!head->getNext()) {
        memChunk* initialHole = new memChunk(0, true, totalWords, head, nullptr); //create initialHole before any memory is allocated
        this->head->setNext(initialHole);
    }


    int numberofWords = ceil((float)sizeInBytes / wordSize);
    int offset = allocator(numberofWords, (void*)getList());

    delete this->storedList;

    if (offset == -1) {
        return nullptr;
    }
    memChunk* curr = this->head->getNext(); //points to first real node in linkedlist

    while (curr && curr->getOffset() != offset) {
        curr = curr->getNext();
    }

    if (curr->getSize() == numberofWords) { //if allocated mem fits into existing hole perfectly, just flip isHole
        curr->setHole(false);
    }
    else { // else break up the hole into newly allocated and whats left of the previous, larger hole
        memChunk* newlyAllocated = new memChunk(offset, false, numberofWords, curr->getPrev(), curr);
        curr->getPrev()->setNext(newlyAllocated);
        curr->setPrev(newlyAllocated);
        curr->setOffset(curr->getOffset() + numberofWords);
        curr->setSize(curr->getSize() - numberofWords);
    }

    return this->startOfMem + offset * wordSize;
}

void MemoryManager::free(void* address) {
    int offset = ceil(((uint8_t*)address - this->startOfMem) / wordSize);
    memChunk* curr = head->getNext();

    while (curr) {
        if (curr->getOffset() == offset) {
            curr->setHole(true);
            break;
        }
        curr = curr->getNext();
    }
    combineHoles(curr);
}

void MemoryManager::setAllocator(std::function<int(int, void*)> allocator) {
    this->allocator = allocator;
}

int MemoryManager::dumpMemoryMap(char* filename) {

    int file = open(filename, O_CREAT | O_WRONLY, 0600);

    auto* holeList = static_cast<uint16_t*>(getList());
    //uint16_t length = *holeList++;
    //cout << length << " : " << holeList[0] << endl;
    int length = holeList[0];

    if (file < 0) {
        return -1;
    }

    string message;

    for (int i = 1; i < length * 2 + 1; i += 2) {
        if (i == 1) {
            message += "[" + to_string(holeList[i]) + ", " + to_string(holeList[i + 1]) + "]";
        }
        else {
            message += " - [" + to_string(holeList[i]) + ", " + to_string(holeList[i + 1]) + "]";
        }
    }
    //cout << message << endl;
    //message.push_back('\0');
    write(file, message.c_str(), message.size());
    close(file);

    delete[] this->storedList;

    return 0;
}

void* MemoryManager::getList() {
    //updateList();
    if (!head->getNext()) return nullptr;

    memChunk* curr = head->getNext();

    vector<uint16_t> holeVector;

    while (curr) {
        if (curr->isHole()) {
            holeVector.push_back(curr->getOffset());
            holeVector.push_back(curr->getSize());
        }

        curr = curr->getNext();
    }
    int numHoles = holeVector.size() / 2;
    this->storedList = new uint16_t[holeVector.size() + 1];
    this->storedList[0] = numHoles;

    for (int i = 0; i < holeVector.size(); i++) {
        this->storedList[i + 1] = holeVector[i];
    }

    return this->storedList;
}

void* MemoryManager::getBitmap() {
    int numBytes = ceil((float)totalWords / 8);

    this->storedBitMap = new uint8_t[numBytes + 2];

    memChunk* curr = this->head->getNext();

    vector<bool> holeList = {};
    while (curr != nullptr) {
        for (int i = 0; i < curr->getSize(); i++) {
            holeList.push_back(!curr->isHole());
        }

        curr = curr->getNext();
    }
    int afterBitMapSize = 2;
    uint8_t temp = 0;
    for (int i = 0; i < holeList.size(); i++) {
        temp |= (holeList[i] << (i % 8));
        if ((i + 1) % 8 == 0) {
            storedBitMap[afterBitMapSize++] = temp;
            temp = 0;
        }
    }
    if (holeList.size() % 8 != 0) {
        storedBitMap[afterBitMapSize] = temp;
    }

    storedBitMap[0] = numBytes & 0xFF;
    storedBitMap[1] = (numBytes >> 8) & 0xFF;

    return this->storedBitMap;
}

unsigned MemoryManager::getWordSize() {
    return wordSize;
}

void* MemoryManager::getMemoryStart() {
    return startOfMem;
}
unsigned MemoryManager::getMemoryLimit() {
    return totalBytes;
}

int bestFit(int sizeInWords, void* list) {
    int fragment = INT16_MAX;
    int offset = -1;

    auto* holeList = static_cast<uint16_t*>(list);
    uint16_t numHoles = holeList[0];
    int length = numHoles * 2 + 1;


    for (int i = 1; i < length; i += 2) {
        if ((holeList[i + 1] - sizeInWords >= 0) && (holeList[i + 1] - sizeInWords < fragment)) {
            offset = holeList[i];
            fragment = holeList[i + 1] - sizeInWords;
        }
    }
    return offset;
}

int worstFit(int sizeInWords, void* list) {
    int fragment = -1;
    int offset = -1;

    auto* holeList = static_cast<uint16_t*>(list);
    int numHoles = holeList[0];
    int length = numHoles * 2 + 1;

    for (int i = 1; i < length; i += 2) {
        if ((holeList[i + 1] - sizeInWords >= 0) && (holeList[i + 1] - sizeInWords > fragment)) {
            offset = holeList[i];
            fragment = holeList[i + 1] - sizeInWords;
        }
    }
    return offset;
}

void MemoryManager::combineHoles(memChunk* justFreed) {
    memChunk* freedChunk = justFreed;
    memChunk* startCombine = freedChunk;
    if (freedChunk->getPrev()->isHole()) {
        startCombine = freedChunk->getPrev();
    }

    while (startCombine->getNext() != nullptr && startCombine->getNext()->isHole()) {
        memChunk* nextPlaceholder = startCombine->getNext();
        startCombine->setSize(startCombine->getSize() + startCombine->getNext()->getSize());
        startCombine->setNext(startCombine->getNext()->getNext());
        if (startCombine->getNext()) {
            startCombine->getNext()->setPrev(startCombine);
        }

        delete nextPlaceholder;
    }


}
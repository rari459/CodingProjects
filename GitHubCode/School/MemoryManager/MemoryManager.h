#include <functional>
#include <fstream>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

class memChunk {
public:
    memChunk(int offset, bool free, int size, memChunk* prev, memChunk* next);
    int getOffset();
    int getSize();
    bool isHole();
    void setOffset(int);
    void setSize(int);
    void setHole(bool);
    memChunk* getPrev();
    memChunk* getNext();
    void setPrev(memChunk* prev);
    void setNext(memChunk* next);

private:
    int offset;
    int size;
    bool hole;
    memChunk* prev;
    memChunk* next;
};

class MemoryManager {
public:
    MemoryManager(unsigned wordSize, std::function<int(int, void*)> allocator);
    ~MemoryManager();
    void initialize(size_t sizeInWords);
    void shutdown();
    void* allocate(size_t sizeInBytes);
    void free(void* address);
    void setAllocator(std::function<int(int, void*)> allocator);
    int dumpMemoryMap(char* filename);
    void* getList();
    void* getBitmap();
    unsigned getWordSize();
    void* getMemoryStart();
    unsigned getMemoryLimit();
    void combineHoles(memChunk* justFreed);

private:
    std::function<int(int, void*)> allocator;

    memChunk* head = nullptr;

    uint8_t* startOfMem = nullptr;
    uint16_t* storedList = nullptr;
    uint8_t* storedBitMap = nullptr;

    unsigned wordSize;

    size_t totalWords;

    unsigned int totalBytes;

};
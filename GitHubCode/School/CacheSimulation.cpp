#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <deque>
#include <math.h>
#include <fstream>
#include <sstream>
#include <list>
using namespace std;

string HexToBin(string hexdec)
{
    long int i = 0;
    string output = "";
    while (hexdec[i]) {

        switch (hexdec[i]) {
        case '0':
            output +=  "0000";
            break;
        case '1':
            output += "0001";
            break;
        case '2':
            output += "0010";
            break;
        case '3':
            output += "0011";
            break;
        case '4':
            output += "0100";
            break;
        case '5':
            output += "0101";
            break;
        case '6':
            output += "0110";
            break;
        case '7':
            output += "0111";
            break;
        case '8':
            output += "1000";
            break;
        case '9':
            output += "1001";
            break;
        case 'A':
        case 'a':
            output += "1010";
            break;
        case 'B':
        case 'b':
            output += "1011";
            break;
        case 'C':
        case 'c':
            output += "1100";
            break;
        case 'D':
        case 'd':
            output += "1101";
            break;
        case 'E':
        case 'e':
            output += "1110";
            break;
        case 'F':
        case 'f':
            output += "1111";
            break;
        default:
            cout << "\nInvalid hexadecimal digit "
                << hexdec[i];
        }
        i++;
    }
    return output;
}

class DirectMap {
private:
	int noBlocks;
    int blockSize;
    map<string, string> cache; //args are lineNO, tag
    int noRequests;
    int noHits;

public:
    DirectMap(int lineSize, int noLines) {
        blockSize = lineSize;
        noBlocks = noLines;
        noRequests = 0;
        noHits = 0;
    }
    string getBlockNo(string address) {
        string binary = HexToBin(address);
        string binline = binary.substr(32- log2(noBlocks)-log2(blockSize), log2(noBlocks));
        return binline;
    }
    string getTag(string address) {
        string binary = HexToBin(address);
        string bintag = binary.substr(0, 32-log2(noBlocks)-log2(blockSize));
        return bintag;
    }

    string getOffset(string address) {
        string binary = HexToBin(address);
        string binoffset = binary.substr(32-log2(blockSize), log2(blockSize));
        return binoffset;
    }

    void load(string address) {
        string addy = HexToBin(address);
        string tag = getTag(address);
        string line = getBlockNo(address);
        noRequests++;
        auto it = cache.find(line);
        if (it != cache.end() && cache[line] == tag) {
            noHits++;
        }
        else {
            cache[line] = tag;  //this is where we will process a miss, just replace the value
        }
    }
    float hitRatio() {
        return (float)noHits / (float)noRequests;
    }

    map<string, string> returnMap(){
        return cache;
    }

    void display() {
        for (auto i : cache) {
            cout << i.first << ": " << i.second << endl;
        }
    }

};

class fAssociative{ 
private:
    int blockSize;
    int noBlocks; //number of lines in the cache
    deque<string> tagQ; //holds tags of all memory addresses that have been stored in sequential order for FIFO
    list<string> LRU; //holds tags for LRU
    int noRequests;
    int noHits;
public:
    fAssociative(int lineSize, int noLines) {
        blockSize = lineSize;
        noBlocks = noLines;
        noRequests = 0;
        noHits = 0;
    }

    string getTag(string address) {
        string binary = HexToBin(address);
        string bintag = binary.substr(0, 32 - log2(blockSize));
        return bintag;
    }

    string getOffset(string address) {
        string binary = HexToBin(address);
        string binoffset = binary.substr(32-log2(blockSize), log2(blockSize));
        return binoffset;
    }

    void FIFOload(string address) {
        string tag = getTag(address);
        noRequests++;
        if (find(tagQ.begin(), tagQ.end(), tag) != tagQ.end()) {
            noHits++;
        }
        else {
            tagQ.push_front(tag);
            if (tagQ.size() > noBlocks) {
                tagQ.pop_back();
            } 
        }
    }

    void LRUload(string address) {
        string tag = getTag(address);
        noRequests++;
        auto it = find(LRU.begin(), LRU.end(), tag);
        if (it != LRU.end()) {
            noHits++;
            auto rb = std::next(it);
            auto re = LRU.end();
            LRU.splice(it, LRU, rb, re);
        }
        else {
            LRU.push_back(tag);
            if (LRU.size() > noBlocks) {
                LRU.pop_front();
            }  
        }
    }
    
    float hitRatio() {
        return (float)noHits / (float)noRequests;
    }

    deque<string> returnQ() {
        return tagQ;
    }

};

class sAssociative {
private:
    int noSet;
    int associativity;
    int blockSize;
    map<string, deque<string>> cache; //args are setNo, tag
    map<string, list<string>> LRUcache;
    int noRequests;
    int noHits;

public:
    sAssociative(int lineSize, int noLines, int way) {
        blockSize = lineSize;
        noSet = noLines;
        noRequests = 0;
        noHits = 0;
        associativity = way;
    }
    string getBlockNo(string address) {
        string binary = HexToBin(address);
        string binline = binary.substr(32-log2(noSet)-log2(blockSize), log2(noSet));
        return binline;
    }
    string getTag(string address) {
        string binary = HexToBin(address);
        string bintag = binary.substr(0, 32-log(noSet) - log2(blockSize));
        return bintag;
    }

    string getOffset(string address) {
        string binary = HexToBin(address);
        string binoffset = binary.substr(32-log2(blockSize), log2(blockSize));
        return binoffset;
    }

    void FIFOload(string address) {
        string tag = getTag(address);
        string line = getBlockNo(address);
        noRequests++;
        auto it = cache.find(line);
        if (it != cache.end() && find(cache[line].begin(), cache[line].end(), tag) != cache[line].end()) {
            noHits++;
        }
        else {
            cache[line].push_front(tag);
            if (cache[line].size() > associativity) {
                cache[line].pop_back();
            } //this is where we will process a miss, just replace the value
        }
    }


    void LRUload(string address) {
        string tag = getTag(address);
        string line = getBlockNo(address);
        noRequests++;
        auto iter = LRUcache.find(line);
        if (iter != LRUcache.end()) {
            auto it = find(LRUcache[line].begin(), LRUcache[line].end(), tag);
            if (it != LRUcache[line].end()) {
                noHits++;
                auto rb = std::next(it);
                auto re = LRUcache[line].end();
                LRUcache[line].splice(it, LRUcache[line], rb, re);
            }
        }
        
        else {
            LRUcache[line].push_back(tag);
            if (LRUcache[line].size() > associativity) {
                LRUcache[line].pop_front(); //CHECK WHICH IS BEING POPPED
            } 
        }
    }

    float hitRatio() {
        return (float)noHits / (float)noRequests;
    }

    map<string, deque<string>> returnMap() {
        return cache;
    }

};


int main()
{
    ifstream myFile("swim.trace");
    string line;

    DirectMap DM = DirectMap(32, 2);
    fAssociative FALRU = fAssociative(32, 2);
    sAssociative SALRU = sAssociative(32, 1, 2);
    fAssociative FAFIFO = fAssociative(32, 2);
    sAssociative SAFIFO = sAssociative(32, 1, 2);


    while (getline(myFile, line))
    {
        istringstream ss(line);
    
        string command; //getline of commands based on number of instructions and break into command and input values
        getline(ss, command, ' ');
        string address;
        getline(ss, address, ' ');
        string secondval;
        getline(ss, secondval, ' ');
        address.erase(address.begin(), address.begin() + 2);
        if (command == "l" || command == "s") {
            DM.load(address);
            FALRU.LRUload(address);
            SALRU.LRUload(address);
            FAFIFO.FIFOload(address);
            SAFIFO.FIFOload(address);
        }
    }
    
    cout << "Hit Ratios by Cache: " << endl;
    cout << "DM: " << DM.hitRatio() << endl;
    cout << "FASSOC LRU: " << FALRU.hitRatio() << endl;
    cout << "SASSOC LRU: " << SALRU.hitRatio() << endl;
    cout << "FASSOC FIFO: " << FAFIFO.hitRatio() << endl;
    cout << "SASSOC FIFO: " << SAFIFO.hitRatio() << endl;



};




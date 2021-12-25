#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <string>
#include <cstring>
#include <utility>
#include <typeinfo>
using namespace std;

unsigned int hashFunction(char const* key, int table_size) {
    unsigned int code = 0;
    unsigned int b = 0;
    for (int i = 0; i < strlen(key); i++) {
        if (i % 2 == 0) {
            b = (code << 7) ^ key[i] ^ (code >> 3);
        }
        else {
            b = (code << 11) ^ key[i] ^ (code >> 5);
            b = ~b;
        }
        code = code ^ b;
    }
    code |= 1UL << 30;
    code = code % table_size;
    return code;
}
struct Node {
    Node* next;
    string ID;
    string name;
};

class Bucket {
private:
    Node* head;
public:
    Bucket() {
        head = nullptr;
    }
    ~Bucket() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* temp = curr->next;
            delete curr;
            curr = temp;
        }
        head = nullptr;
    }

    void push(string id, string name) {
        Node* insert = new Node();
        insert->ID = id;
        insert->name = name;
        insert->next = nullptr;

        if (head == nullptr) {
            head = insert;
        }
        else {
            insert->next = head;
            head = insert;
        }
    }

    void remove(Node* node, string id) {
        if (node == nullptr) {
            return;
        }
        while (node->next != nullptr) {
            if (node->next->ID == id) {
                Node* temp = node->next;
                if (node->next->next != nullptr) {
                    node->next = node->next->next;
                    delete temp;
                }
                else {
                    node->next = nullptr;
                    delete temp;
                }

            }
        }
    }
    string& search(Node* head, string id) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->ID == id) {
                return curr->name;
            }
            curr = curr->next;
        }
    }

    bool exists(Node* head, string id) {
        Node* curr = head;
        if (curr == nullptr) {
            false;
        }
        while (curr != nullptr) {
            if (curr->ID == id) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
    Node* getHead() {
        return head;
    }
};
class UnorderedMap
{
    int bucketCount;
    unsigned int keyNo;
    double mapLF;
    vector<Bucket*> table;
public:
    class Iterator;
    UnorderedMap(unsigned int bucketCount, double loadFactor);
    ~UnorderedMap();
    Iterator begin() const;
    Iterator end() const;
    std::string& operator[] (std::string const& key);
    void rehash();
    void remove(std::string const& key);
    unsigned int size();
    double loadFactor();
    vector<Bucket*> getTable();
    void nullBuckets(int);

    class Iterator
    {
    private:
        Node* pointer;
        const UnorderedMap* obj;
        int index;

    public:
        //this constructor does not need to be a default constructor;
        //the parameters for this constructor are up to your discretion.
        //hint: you may need to pass in an UnorderedMap object.
        Iterator(const UnorderedMap* obj, Node* pointer, int index) {
            this->obj = obj;
            this->pointer = pointer;
            this->index = index;
        }

        Iterator& operator=(Iterator const& rhs) {
            this->pointer = rhs.pointer;
            this->obj = rhs.obj;
            this->index = rhs.index;

            return *this;
        }
        Iterator& operator++() {
            if (pointer->next != nullptr) {
                pointer = pointer->next;
                return *this;
            }
            else {
                for (int i = index + 1; i < obj->table.size(); i++) {
                    Node* temp = obj->table[i]->getHead();
                    if (temp != nullptr) {
                        pointer = temp;
                        index = i;
                        return *this;
                    }
                }
                Iterator end = obj->end();
                return end;
            }
        }

        bool operator!=(Iterator const& rhs) {
            return this->pointer != rhs.pointer;
        }
        bool operator==(Iterator const& rhs) {
            return this->pointer == rhs.pointer;
        }
        std::pair<std::string, std::string> operator*() const {
            pair<string, string> pair1;
            pair1.first = this->pointer->ID;
            pair1.second = this->pointer->name;
            return pair1;
        }
        friend class UnorderedMap;
    };
};

UnorderedMap::UnorderedMap(unsigned int bucketCount, double loadFactor)
{
    this->bucketCount = bucketCount;
    keyNo = 0;
    this->mapLF = loadFactor;

    vector<Bucket*> table(bucketCount);
    this->table = table;
    this->nullBuckets(bucketCount);
}

UnorderedMap::~UnorderedMap()
{
    table.clear();
}

void UnorderedMap::nullBuckets(int buckets) {
    for (int i = 0; i < buckets; i++) {
        table[i] = new Bucket();
    }
}

UnorderedMap::Iterator UnorderedMap::begin() const
{
    if (keyNo < 1) {
        return this->end(); 
    }
    for (int i = 0; i < bucketCount; i++) {
        if (table[i]->getHead() != nullptr) {
            return Iterator(this, table[i]->getHead(), i);
        }
    }
}

UnorderedMap::Iterator UnorderedMap::end() const
{
    for (int i = bucketCount - 1; i >= 0; i--) {
        if (table[i]->getHead() != nullptr) {
            Node* temp = table[i]->getHead();
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            return Iterator(this, temp->next, i);
        }
    }
}

std::string& UnorderedMap::operator[] (std::string const& key)
{
    const char* convertedKey = key.c_str();
    unsigned int index = hashFunction(convertedKey, bucketCount);

    bool exists = table[index]->exists(table[index]->getHead(), key);
    if (exists == true) {
        string& name = table[index]->search(table[index]->getHead(), key);
        return name;
    }
    else {
        keyNo++;
        table[index]->push(key, "");
        string& name = table[index]->search(table[index]->getHead(), key);

        if (this->loadFactor() >= mapLF) {
            this->rehash();
        }
        return name;
    }
}

void UnorderedMap::rehash()
{
    vector<Bucket*> temp = table;
    vector<Node*> curr;
    bucketCount = bucketCount * 2;

    for (int i = 0; i < temp.size(); i++) {
        if (temp[i] != nullptr) {
            Node* holder = temp[i]->getHead();
            while (holder != nullptr) {
                curr.push_back(holder);
                holder = holder->next;
            }
        }
    }
    table.clear();
    table.resize(bucketCount);
    this->nullBuckets(bucketCount);


    for (int j = 0; j < curr.size(); j++) {
        Node* var = curr[j];
        const char* convertedKey = var->ID.c_str();
        unsigned int index = hashFunction(convertedKey, bucketCount);
        table[index]->push(var->ID, var->name);
    }

}

void UnorderedMap::remove(std::string const& key)
{
    const char* convertedKey = key.c_str();
    unsigned int index = hashFunction(convertedKey, bucketCount);

    table[index]->remove(table[index]->getHead(), key);
    keyNo--;
}

unsigned int UnorderedMap::size()
{
    return keyNo;
}

double UnorderedMap::loadFactor()
{
    return (double)(keyNo / (double)bucketCount);
}

vector<Bucket*> UnorderedMap::getTable() {
    return this->table;
}


//implement other operators in Iterator class

//Do not change main() 
int main()
{
    int lines = 0, buckets = 0;
    double maxLoadFactor = 0.0;
    std::string command = "", ufid = "", name = "", key = "";
    std::cin >> lines >> buckets >> maxLoadFactor;
    UnorderedMap myMap = UnorderedMap(buckets, maxLoadFactor);
    while (lines--)
    {
        std::cin >> command;
        if (command == "hash")
        {
            std::cin >> key;
            const char* convertedKey = key.c_str();
            std::cout << hashFunction(convertedKey, buckets) << "\n";
        }
        else if (command == "insert")
        {
            std::cin >> ufid >> name;
            myMap[ufid] = name;
        }
        else if (command == "size")
        {
            std::cout << myMap.size() << "\n";
        }
        else if (command == "load")
        {
            std::cout << std::fixed << std::setprecision(2) << myMap.loadFactor() << "\n";
        }
        else if (command == "search")
        {
            std::cin >> ufid;
            std::cout << myMap[ufid] << "\n";
        }
        else if (command == "traverse")
        {
            for (UnorderedMap::Iterator iter = myMap.begin(); iter != myMap.end(); ++iter)
            {
                std::cout << (*iter).first << " " << (*iter).second << "\n";
            }


            /* This should also work
                for (auto tableEntry: myMap)
                {
                    std::cout << tableEntry.first << " " << tableEntry.second << "\n";
                }
            */
        }
        else if (command == "remove")
        {
            std::cin >> ufid;
            myMap.remove(ufid);
        }
    }

    return 0;
}
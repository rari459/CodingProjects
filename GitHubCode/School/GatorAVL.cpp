#include <iostream>
#include <string>
#include <sstream>
#include <queue>
using namespace std;

class TreeNode {
public:
    int studentID = 0;
    string studentName;
    int height;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x, string studentName) :studentID(x), left(NULL), right(NULL), height(1), studentName(studentName) {}
};

class AVLTree {
public:
    TreeNode* root = NULL;

    void insert(int key, string name) {
        this->root = helperInsert(this->root, key, name); //calls helper insert fucntion to prevent memory access
    }

    void remove(int key) {
        bool success = false;
        this->root = helperremove(key, this->root, success); //calls helper remove fucntion to prevent memory access
        if (success) { //prints success if the bool passed to the helper function is true
            cout << "successful" << endl;
        }
        else { cout << "unsuccessful" << endl; }
    }

    void inorder() {
        string list;
        helperinorder(this->root, list); //calls helper inorder fucntion to prevent memory access
        list.erase(list.size() - 2, 2); //gets rid of space and comma at the end of the string before outputting
        cout << list << endl;
    }
    void preorder() {
        string list;
        helperpreorder(this->root, list); //calls helper preorder fucntion to prevent memory access
        list.erase(list.size() - 2, 2);
        cout << list << endl;
    }
    void postorder() {
        string list;
        helperpostorder(this->root, list); //calls helper postorder fucntion to prevent memory access
        list.erase(list.size() - 2, 2);
        cout << list << endl;
    }

    void IDSearch(int Id) {
        helperIDSearch(Id, this->root);
    }

    void nameSearch(string name) {
        bool success = false;
        helpernameSearch(name, this->root, success);
        if (success == false) { cout << "unsuccessful" << endl; }
    }

    void removeNth(int index) {
        TreeNode* head = this->root;
        vector <int> arr; //create int array
        inorderArray(head, arr); //store inorder student ids
        int removeID = arr[index]; //find id of student to remove
        remove(removeID);
    }

    void printLevelCount() {
        TreeNode* root = this->root; //use level order traversal and increment level by 1 everytime the for loop is done executing
        int level = 0;
        queue<TreeNode*> nodeQ;
        nodeQ.push(root);
        while (!nodeQ.empty()) {
            int size = nodeQ.size();
            level++;
            for (int i = 0; i < size; i++) {
                TreeNode* temp = nodeQ.front();
                nodeQ.pop();
                if (temp->left != NULL)
                    nodeQ.push(temp->left);

                if (temp->right != NULL)
                    nodeQ.push(temp->right);
            }
        }
        cout << level << endl;
    }

    void inorderArray(TreeNode* head, vector <int>& arr) { //creates an inorder array of student ids
        if (head == NULL)cout << "";
        else {
            inorderArray(head->left, arr);
            arr.push_back(head->studentID);
            inorderArray(head->right, arr);
        }
    }

private:
    int nodeHeight(TreeNode* root) { //returns height of each node
        if (root == NULL) {
            return 0;
        }
        else {
            return root->height;
        }
    }

    TreeNode* rotateLeft(TreeNode* node) {   //used given rotation code to balance trees
        TreeNode* right = node->right;
        TreeNode* rightLeft = right->left;
        right->left = node;
        node->right = rightLeft;


        node->height = max(nodeHeight(node->left), nodeHeight(node->right)) + 1; //using height function to retrieve and set heights
        right->height = max(nodeHeight(right->left), nodeHeight(right->right)) + 1;
        return right;
    }

    TreeNode* rotateRight(TreeNode* node) {
        TreeNode* left = node->left;
        TreeNode* leftRight = left->right;
        left->right = node;
        node->left = leftRight;

        node->height = max(nodeHeight(node->left), nodeHeight(node->right)) + 1;
        left->height = max(nodeHeight(left->left), nodeHeight(left->right)) + 1;
        return left;
    }

    TreeNode* helperInsert(TreeNode* helpRoot, int ID, string name) {
        if (helpRoot == nullptr) //first implement BST insert
            return new TreeNode(ID, name);
        else if (ID < helpRoot->studentID)
            helpRoot->left = helperInsert(helpRoot->left, ID, name);
        else
            helpRoot->right = helperInsert(helpRoot->right, ID, name);


        helpRoot->height = 1 + max(nodeHeight(helpRoot->right), nodeHeight(helpRoot->left));
        int balanceFactor = nodeHeight(helpRoot->left) - nodeHeight(helpRoot->right); //if-else conditional to see if rotations are required

        if (balanceFactor < -1 && ID > helpRoot->right->studentID) {
            return rotateLeft(helpRoot);
        }
        else if (balanceFactor > 1 && ID < helpRoot->left->studentID) {
            return rotateRight(helpRoot);
        }
        else if (balanceFactor > 1 && ID > helpRoot->left->studentID) {
            helpRoot->left = rotateLeft(helpRoot->left);
            return rotateRight(helpRoot);
        }
        else if (balanceFactor < -1 && ID < helpRoot->right->studentID) {
            helpRoot->right = rotateRight(helpRoot->right);
            return rotateLeft(helpRoot);
        }
        return helpRoot;
    }

    TreeNode* helperremove(int Id, TreeNode* head, bool& success) {
        if (head == nullptr) { //BST removal of node
            success = false;
            return head;
        }
        else {
            success = true;
        }
        if (head->studentID > Id) {
            head->left = helperremove(Id, head->left, success);
        }
        else if (head->studentID < Id) {
            head->right = helperremove(Id, head->right, success);
        }
        else {
            if (head->left == NULL && head->right == NULL) {
                return NULL;
            }
            else if (head->left == NULL) {
                TreeNode* temp = head->right;
                delete head;
                return temp;
            }
            else if (head->right == NULL) {
                TreeNode* temp = head->left;
                delete head;
                return temp;
            }
            else if (head->right != NULL && head->left != NULL) {
                TreeNode* temp = inorderSuccessor(head->right);
                head->studentID = temp->studentID;
                head->studentName = temp->studentName;
                head->right = helperremove(temp->studentID, head->right, success);
            }


        }
        return head;

    }


    TreeNode* inorderSuccessor(TreeNode* root) { //finds the smallest left node, call on the right subtree of the node which is being deleted
        TreeNode* temp = root;
        while (temp != NULL && temp->left != NULL) {
            temp = temp->left;
        }
        return temp;
    }

    void helperinorder(TreeNode* head, string& print) {
        if (head == NULL)cout << "";
        else {
            helperinorder(head->left, print);
            print = print + head->studentName + ", ";
            helperinorder(head->right, print);
        }
    }

    void helperpreorder(TreeNode* head, string& print) {
        if (head == NULL)cout << "";
        else {
            print = print + head->studentName + ", ";
            helperpreorder(head->left, print);
            helperpreorder(head->right, print);
        }
    }

    void helperpostorder(TreeNode* head, string& print) {
        if (head == NULL)cout << "";
        else {
            helperpostorder(head->left, print);
            helperpostorder(head->right, print);
            print = print + head->studentName + ", ";
        }
    }



    void helperIDSearch(int Id, TreeNode* head) {
        if (head == nullptr) { //use BST search implementation
            cout << "unsuccessful" << endl;
            return;
        }
        else if (head->studentID == Id) {
            cout << head->studentName << endl;
        }
        else if (head->studentID > Id) {
            helperIDSearch(Id, head->left);
        }
        else if (head->studentID < Id) {
            helperIDSearch(Id, head->right);
        }
    }

    void helpernameSearch(string name, TreeNode* head, bool& success) {
        if (head == nullptr) { //if name does not exist, success is false and public fucntion will print unsuccessful
            return;
        }

        else {
            if (head->studentName == name) { //use preorder traversal to find name
                cout << head->studentID << endl;
                success = true;

            }
            helpernameSearch(name, head->left, success);
            helpernameSearch(name, head->right, success);
        }

    }
};

int main()
{
    AVLTree tree;

    string input;
    cin >> input;

    int instrucCount = stoi(input);
    for (unsigned int i = 0; i <= instrucCount + 1; i++) {
        string response;
        getline(cin, response);

        istringstream ss(response);

        string command; //getline of commands based on number of instructions and break into command and input values
        getline(ss, command, ' ');
        string firstval;
        getline(ss, firstval, ' ');
        string secondval;
        getline(ss, secondval, ' ');

        if (command == "search") {
            if (firstval[0] == '\"') {
                string name = firstval;
                name.erase(0, 1);
                name.erase(name.size() - 1, 1);
                tree.nameSearch(name);
            }
            else {
                int id = stoi(firstval);
                tree.IDSearch(id);
            }
        }
        if (command == "insert") {
            string name = firstval;
            int id = stoi(secondval);
            name.erase(0, 1);
            name.erase(name.size() - 1, 1);
            tree.insert(id, name);
            cout << "successful" << endl;
        }
        if (command == "remove") {
            int id = stoi(firstval);
            tree.remove(id);
        }
        if (command == "removeInorder") {
            int index = stoi(firstval);
            tree.removeNth(index);
        }
        if (command == "printInorder") {
            tree.inorder();
        }
        if (command == "printPreorder") {
            tree.preorder();
        }
        if (command == "printPostorder") {
            tree.postorder();
        }
        if (command == "printLevelCount") {
            tree.printLevelCount();
        }
    }
}
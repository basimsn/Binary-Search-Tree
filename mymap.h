//mymap.h allows for users to put nodes in a Binary Search Tree. From this BST, users can 
//insert, copy, and retrieve all sorts of information. The function put allows the BST to
//be created in order using single threading which has each leaf having a right node pointing 
//to the pointer. To copy BSTs the user can use the equal operator when declaring the my map or
//in the next line. By using functions get, the breacket operator we can retrieve the value and 
//for functions like contain we can see if a key is there using a bool.

#pragma once
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
 private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

    
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    
    struct iterator {
     private:
        NODE* curr;  // points to current in-order node for begin/end

     public:
        iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        iterator operator++() {
            if(curr == nullptr){ //If null retruns null
                return iterator(nullptr);
            }
            if(curr->isThreaded){ //Checks if threaded and returns parent
                curr = curr->right;
                return iterator(curr);
            }
            else{ //If not threaded moves right
                curr = curr->right;
                if(curr == nullptr){ 
                    return iterator (nullptr);
                }
                while(curr->left){ //Moves as left as possible
                    curr = curr->left;
                }
                return iterator(curr);
            }
    
        }
    };

 public:

    mymap() { //Default Constructor
        root = nullptr;
        size = 0;
    }
//-------------------------------------------------------
    mymap(const mymap& other) { //Copy Constructor
        NODE* temp = other.root;
        NODE* nBST = nullptr;
        nBST = clone(temp); //Clones other BST
        root = nBST;
    }
//-------------------------------------------------------
    NODE* clone(NODE* curr){ //Function clones a BST
        if(curr == nullptr){ //Checks if null
            return curr;
        }
        NODE* nCurr = new NODE; //Creates a New Node
        nCurr->nL = 0;
        nCurr->nR = 0;
        nCurr->isThreaded = false;
        nCurr->left = nullptr;
        nCurr->right = nullptr;
        nCurr->key = curr->key;
        nCurr->value = curr->value;
        size++; 

        nCurr->left = clone(curr->left); //Preorder Traversal for copying a BST
        nCurr->right = clone(curr->right);

        return nCurr; //Returns BST
    }
//-------------------------------------------------------
    mymap& operator=(const mymap& other) { //Function makes this BST = other BST
        this->clear(); //Clears the BST
        NODE* temp = other.root; 
        NODE* nBST = nullptr;
        nBST = clone(temp); //Clones the other BST into nBST
        root = nBST; //Puts the cloned BST into this BST

        return *this; 
    }
//-------------------------------------------------------
    void clearHelper(NODE* node){ //Clear Helper Function
        if(node != nullptr){
            clearHelper(node->left); //PostOrder Traversal for deleting Nodes
            clearHelper(node->right);
            (size)--; //Subtracts the size
            delete node;
        }
        else{
            return;
        }
    }
//-------------------------------------------------------
    void clear() { //Clears BST
        NODE* temp = root;
        clearHelper(temp); 
        root = nullptr;
    }
//-------------------------------------------------------
    ~mymap() { //Destructor
        clear();
    }
//-------------------------------------------------------
    void put(keyType key, valueType value) { //Adds nodes into the BST in correct order with threading
        NODE* tRoot = root;
        NODE* prev = nullptr;
        NODE* pParent = nullptr;
        while(tRoot != nullptr){ //Loops through the BST until key is in the place it is supposed to be
            if(key == tRoot->key){ 
                prev = tRoot;
                tRoot->value = value;
                return; //Returns because the value is just supposed to update and nothing else
            }
            else if(key < tRoot->key){ 
                pParent = tRoot; //The Parent is stored for later
                prev = tRoot;
                tRoot = tRoot->left;
            }
            else{
                prev = tRoot;
                tRoot = (tRoot->isThreaded) ? nullptr: tRoot->right; //Given
            }
        }

        NODE* nCurr = new NODE; //Creates New Node 
        nCurr->key = key;
        nCurr->value = value;
        nCurr->left = nullptr;
        nCurr->right = nullptr;
        nCurr->nL = 0;
        nCurr->nR = 0;
        nCurr->isThreaded = false;
        
        if(prev == nullptr){ //If parent is null, root is the node given
            root = nCurr;
        }
        else if(key > prev->key){  //Finds where the node should be stored
            prev->right = nCurr;
        }
        else if(key < prev->key){
            prev->left = nCurr;
        }
        else if(pParent != nullptr){ //Threading 
            pParent->isThreaded = false; //Parent is no longer a leaf so threading is false
            nCurr->right = pParent; //The leaf's right points to next value
            nCurr->isThreaded = true;
        }

        size++; //Adds size
    }
//-------------------------------------------------------
    bool contains(keyType key) { //Bool Function to determine if a key exists in the BST
        NODE* nFind = root;
        while(nFind != nullptr){ //Loops through the BST
            if(nFind->key == key){
                return true;
            }
            else{
                if(nFind->isThreaded){ //Returns false because it has reached a leaf without being equal
                    return false; //This if statement prevents infinite loop
                }
                if(nFind->key < key){
                    nFind = nFind->right;
                }
                else{
                    nFind = nFind->left;
                }
            }
        }
        return false;
    }
//-------------------------------------------------------
    valueType get(keyType key) {  //Gets the Value of a given key
        NODE* nFind = root;
        while(nFind != nullptr){ //Loops through the BST
            if(nFind->key == key){
                return nFind->value; //Returns value of given key
            }
            else{
                if(nFind->isThreaded == true){
                    break; //Breaks out of while loop if the node reaches a leaf
                }
                if(nFind->key < key){
                    nFind = nFind->right;
                }
                else{
                    nFind = nFind->left;
                }
            }
        }
        return valueType(); //Returns valuetype if key is not found within the BST
    }
//-------------------------------------------------------
    valueType operator[](keyType key) { //Bracket Operator returning the key's value and inserting a key and its valuetype if not found
        NODE* nFind = root; 
        while(nFind != nullptr){ //Loops through BST
            if(nFind->key == key){
                return nFind->value;
            }
            else{
                if(nFind->isThreaded == true){ //Breaks out of while loop when it reaches a leaf
                    break;
                }
                if(nFind->key < key){
                    nFind = nFind->right;
                }
                else{
                    nFind = nFind->left;
                }
            }
        }
        put(key, valueType()); //Inserts key and valuetype if key is not found in the BST
        return valueType(); //Returns Valuetype
    }
//-------------------------------------------------------
    int Size() { //Returns Size
        return size;
    }
//-------------------------------------------------------
    iterator begin() { //Returns the leftest Node
        NODE* minVal = root;
        while(minVal->left != nullptr){
            minVal = minVal->left;
        }
        return iterator(minVal);
    }
//-------------------------------------------------------
    iterator end() { //Returns null
        return iterator(nullptr);
    }
//-------------------------------------------------------
    void buildString(NODE* node, ostream& output){ //toString Helper Function
        if(node != nullptr){ 
            buildString(node->left, output); //InOrder Traversal for inorder output
            output<<"key: "<<node->key<<" value: "<<node->value<<"\n"; //Builds on to the ostream output
            if(node->isThreaded == false){ //Stops when a leaf is reached
                buildString(node->right, output);
            }
        }
        else{
            return;
        }
    }
//-------------------------------------------------------
    string toString() { //Prints out all the keys and values in order using stringstream
        string str;
        if(root == nullptr){
            str="";
            return str; //Returns empty string if BST is empty
        }
        else{
            stringstream ss;
            buildString(root, ss);
            str = ss.str();
            return str; //Returns string of all keys and values of the BST
        }
    }
//-------------------------------------------------------
  void toVectorHelper(NODE* node, vector<pair<keyType, valueType>> &v1){
    if(node != nullptr){
      toVectorHelper(node->left, v1); //InOrder Traversal for copying
      v1.push_back(make_pair(node->key, node->value)); //Push back the pair into the vector
      if(node->isThreaded == false){
        toVectorHelper(node->right, v1);
      }
      
    }
  }
//-------------------------------------------------------
  vector<pair<keyType, valueType> > toVector() { //Vector filled with key and value
    vector<pair<keyType, valueType>> v1; //Create
    toVectorHelper(root, v1);
    return v1;
  }
//-------------------------------------------------------
    void checkHelper(NODE* node, ostream& output){ //toString Helper Function
        if(node != nullptr){ 
            checkHelper(node->left, output); //InOrder Traversal for inorder output
            output<<"key: "<<node->key<<" nL: "<<node->nL<<" nR: "<<node->nR<<"\n"; //Builds on to the ostream output
            if(node->isThreaded == false){ //Stops when a leaf is reached
                checkHelper(node->right, output);
            }
        }
        else{
            return;
        }
    }
//-------------------------------------------------------
    string checkBalance() { //Returns a string of the key, the nL, and the nR
        string str;
        if(root == nullptr){
            str="";
            return str; //Returns empty string if BST is empty
        }
        else{
            stringstream ss;
            checkHelper(root, ss);
            str = ss.str();
            return str; //Returns string of all keys and values of the BST
        }
    }
//-------------------------------------------------------
};

#include <iostream>
#include <fstream>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

struct node {
    int* keys;
    node** childptr;
    bool leaf;
    int size;

    node(int degree){
        keys = new int[degree];
        childptr = new node*[degree+1];
        leaf = true;
        size = 0;

        for(int i = 0; i < degree; i++){
            keys[i] = -1;
        }
        for(int i = 0; i < degree+1; i++){
            childptr[i] = nullptr;
        }
    }
};

class btree{
private:
    node* root;
    int degree;
public:
    btree(int d){
        root = nullptr;
        degree = d;
    }

    void insert(int data){
        if(dupCheck(root, data)){
            return;
        }
        if(root == nullptr){
            root = new node(degree);
            root->keys[0] = data;
            root->size = 1;
        }
        else{
            addAtLeaf(nullptr, root, data);
        }
    }

    void addAtLeaf(node* parent, node* n, int data){
        if(n->leaf){
            int i = n->size;
            while(i != 0 && n->keys[i-1] > data){
                n->keys[i] = n->keys[i-1];
                i--;
            }
            n->keys[i] = data;
            n->size+=1;
        }
        else{
            int i = 0;
            while(i < n->size && data > n->keys[i]){
                i++;
            }
            addAtLeaf(n, n->childptr[i], data);
        }

        if(n->size == degree){
            if(n == root){
                node* temp = new node(degree);
                temp->leaf = false;
                temp->childptr[0] = n;
                splitChild(temp, n);
                root = temp;
            }
            else{
                splitChild(parent, n);
            }
        }
    }

    void splitChild(node* parent, node* leftNode){
        node* rightNode = new node(degree);
        rightNode->leaf = leftNode->leaf;
        int mid = (degree-1)/2;
        int num = leftNode->keys[mid];
        /*
        for(int i = 0; i < leftNode->size; i++){
            cout << leftNode->keys[i] << " ";
        }
        cout << endl;
        */
        int ri = 0;
        int ls = leftNode->size;
        //copy half of left node to right node
        for(int i = mid+1; i < ls; i++){
            rightNode->keys[ri] = leftNode->keys[i];
            leftNode->keys[i] = -1;
            ri++;
            rightNode->size+=1;
            leftNode->size-=1;
        }
        leftNode->size-=1;
        leftNode->keys[mid] = -1;
        // copy half the pointer of the left node to right node
        ri = 0;
        int start = (degree+1)/2;
        if(!leftNode->leaf){
            for(int i = start; i < degree+1; i++){
                rightNode->childptr[ri] = leftNode->childptr[i];
                leftNode->childptr[i] = nullptr;
                ri++;
            }
        }
        
        // find the correct position to add the new array
        int index;
        for (index = parent->size; index > 0 && num < parent->keys[index - 1]; index--) {
            parent->keys[index] = parent->keys[index - 1];
            parent->childptr[index + 1] = parent->childptr[index];
        }
        //add the middle keys to the parent
        parent->childptr[index+1] = rightNode;
        parent->keys[index] = num;
        parent->size+=1;
    }
    
    node* getRoot(){ 
        return root;
    }
    
    int height(node* cu){
        while(cu != nullptr)
        {
          return height(cu->childptr[0]) + 1;
        }
        return 0;
    }

    bool dupCheck(node* cu, int val){   
        if(cu == nullptr){
          return false;
        }
        for(int x = 0; x < cu->size; x++){
          if(cu->keys[x] == val){
            return true;
          }
        }
        for(int x = 0; x < cu->size + 1; x++){
          if(dupCheck(cu->childptr[x], val)){
            return true;
          }
        }
        return false;
    }

    void print(node* cu, int level, ofstream& output){
        if(cu == nullptr){
          output << "Empty";
          return;
        }
        if(level > height(root)){
          output << "Empty";
          return;
        }
        if(level == 1){
          if(cu == nullptr){
            output << "Empty";
            return;
          }
          for(int x = 0; x < cu->size; x++){
            output << cu->keys[x] << " ";
          }
        } 
        else {
          for(int i = 0; i < cu->size + 1; i++){
            print(cu->childptr[i], level - 1, output);
          }
        }
      }
};

int main(int argc, char *argv[]) {
    /*
    ArgumentManager am(argc, argv);
    string inFile = am.get("input");
    string comFile = am.get("command");
    string outFile = am.get("output");
    ifstream input(inFile);
    ifstream commandFile(comFile);
    ofstream output(outFile);
    */
    
    ifstream input("input2.txt");
    ifstream commandFile("command2.txt");
    ofstream output("output2.txt");
    
    if(!input.is_open() || !commandFile.is_open()){
      exit(-1);
    }
    
    

    string temp;
    int degree;
    commandFile >> temp;
    temp = temp.substr(temp.find('=') + 1);
    temp.erase(remove(temp.begin(), temp.end(), '\n'), temp.end());
    temp.erase(remove(temp.begin(), temp.end(), '\r'), temp.end());
    temp.erase(remove(temp.begin(), temp.end(), '\t'), temp.end());
    cout << temp << endl;
    if(isdigit(temp[0])){
        degree = stoi(temp);
    }
    btree B(degree);
    string word = "";
    int num;
    int amount = 0;
    while(!input.eof()){
        input >> word;
        word.erase(remove(word.begin(), word.end(), '\n'), word.end());
        word.erase(remove(word.begin(), word.end(), '\r'), word.end());
        word.erase(remove(word.begin(), word.end(), '\t'), word.end());
        cout << word << endl;
        num = stoi(word);
        B.insert(num);
    }
    int level;
    output << "Height=" << B.height(B.getRoot()) << " " << endl;
    while(!commandFile.eof()){
        word = "";
        getline(commandFile, temp);
        temp.erase(remove(temp.begin(), temp.end(), '\n'), temp.end());
        temp.erase(remove(temp.begin(), temp.end(), '\r'), temp.end());
        temp.erase(remove(temp.begin(), temp.end(), '\t'), temp.end());
        if(temp == " " || temp == ""){
            continue;
        }
        word = temp.substr(temp.find(' ')+1);
        cout << word << endl;
        level = stoi(word);
        B.print(B.getRoot(),level, output);
        output << endl;
    }
}
#include <iostream>
#include "ArgumentManager.h"
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

template <typename t> struct node {
    t data;
    node<t> *next;
};

template <typename t> class ll {
private:
    node<t> *head;
    int size;

public:
    ll();
    ~ll();
    bool isEmpty() { return head == nullptr; }
    int getSize() { return size; }
    node<t>* getHead() { return head; }
    void addHead(t value);
    void addTail(t value);
    void removeHead();
    void removeTail();
    void print();

};

template <typename t> ll<t>::ll() {
    head = nullptr;
    size = 0;
}

template <typename t> ll<t>::~ll() {
    node<t>* cu = head;
    while (cu != nullptr) {
        node<t>* temp = cu;
        cu = cu->next;
        delete temp;
    }
}

template <typename t> void ll<t>::addHead(t value) {
    node<t>* temp = new node<t>();
    temp->data = value;
    temp->next = nullptr;

    node<t>* cu = head;
    if (cu == nullptr) {
        head = temp;
    }
    else {
        temp->next = head;
        head = temp;
    }
    size++;
}

template <typename t> void ll<t>::removeHead() {
    node<t>* cu = head;
    node<t>* temp = nullptr;
    if (cu == nullptr)
        return;
    else if (cu->next == nullptr) {
        head = nullptr;
    }
    else {
        temp = cu->next;
        delete cu;
        head = temp;
    }
    size--;
}

template <typename t> void ll<t>::addTail(t value) {
    node<t>* temp = new node<t>();
    temp->data = value;
    temp->next = nullptr;

    node<t>* cu = head;
    if (cu == nullptr) {
        head = temp;
    }
    else {
        while (cu->next != nullptr) {
            cu = cu->next;
        }
        cu->next = temp;
    }
    size++;
}

template <typename t> void ll<t>::removeTail() {
    node<t>* cu = head;
    node<t>* prev = nullptr;
    if (cu == nullptr)
        return;
    else if (cu->next == nullptr) {
        head = nullptr;
    }
    else {
        while (cu->next != nullptr) {
            prev = cu;
            cu = cu->next;
        }
        prev->next = nullptr;
        delete cu;
    }
    size--;
}

template <typename t> void ll<t>::print() {
    node<t>* cu = head;
    while (cu != nullptr) {
        if (cu->next == nullptr) {
            cout << cu->data;
        }
        else {
            cout << cu->data << " ";
        }
        cu = cu->next;
    }
}

int main(int argc, char *argv[]) {

    
    ArgumentManager am(argc, argv);
    ifstream ifs(am.get("input"));
    ofstream ofs(am.get("output"));
    
    /*
    ifstream ifs("input1.txt");
    ofstream ofs("output1.txt");
    */

    string type;
    getline(ifs, type);
    type.erase(remove(type.begin(), type.end(), '\n'), type.end());
    type.erase(remove(type.begin(), type.end(), '\r'), type.end());
    type.erase(remove(type.begin(), type.end(), ' '), type.end());
    string where;
    getline(ifs, where);
    where.erase(remove(where.begin(), where.end(), '\n'), where.end());
    where.erase(remove(where.begin(), where.end(), '\r'), where.end());
    where.erase(remove(where.begin(), where.end(), ' '), where.end());
    ll<string> list;
    if (where == "head") {
        string in = "";

        while (getline(ifs, in)) {
            // Clean up blank spaces, \n and \r, and skip blank lines
            in.erase(remove(in.begin(), in.end(), '\n'), in.end());
            in.erase(remove(in.begin(), in.end(), '\r'), in.end());
            in.erase(remove(in.begin(), in.end(), ' '), in.end());
            if (in == "removehead") {
                list.removeHead();
            }
            else if (in == "removetail") {
                list.removeTail();
            }
            else {
                list.addHead(in);
            }
        }
    }
    else {
        string in = "";

        while (getline(ifs, in)) {
            // Clean up blank spaces, \n and \r, and skip blank lines
            in.erase(remove(in.begin(), in.end(), '\n'), in.end());
            in.erase(remove(in.begin(), in.end(), '\r'), in.end());
            in.erase(remove(in.begin(), in.end(), ' '), in.end());
            if (in == "removehead") {
                list.removeHead();
            }
            else if (in == "removetail") {
                list.removeTail();
            }
            else {
                list.addTail(in);
            }
        }
    }

    node<string>* cu = list.getHead();
    while (cu != nullptr) {
        if (cu->next == nullptr) {
            ofs << cu->data;
        }
        else {
            ofs << cu->data << " ";
        }
        cu = cu->next;
    }
    list.print();
    
	return 0;
}
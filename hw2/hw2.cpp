#include <iostream>
#include "ArgumentManager.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

struct student {
    string id, username, score, grade;
    student* next;
};

class ll {
private:
    student* head;
    int size;

public:
    ll();
    ~ll();
    bool isEmpty() { return head == nullptr; }
    int getSize() { return size; }
    student* getHead() { return head; }
    void addend(string i, string u, string s, string g);
    void addpos(int pos, string i, string u, string s, string g);
    int findPosition(string _id) {
        student* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->id == _id) {
                return index;
            }
            index++;
            current = current->next;
        }
        return -1;
    }
    int findName(string _name) {
        student* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->username == _name) {
                return index;
            }
            index++;
            current = current->next;
        }
        return -1;
    }
    void removeid(string who);
    void removename(string who);
    void removescore(string what);
    void removegrade(string what);
    void sortid(student*, int);
    void sortname(student*, int);
    void sortscore(student*, int);
    void sortgrade(student*, int);
    student* swap(student* ptr1, student* ptr2){
        student* tmp = ptr2->next;
        ptr2->next = ptr1;
        ptr1->next = tmp;
        return ptr2;
    }
    void print();
};

ll::ll() {
    head = nullptr;
    size = 0;
}

ll::~ll() {
    student* cu = head;
    while (cu != nullptr) {
        student* temp = cu;
        cu = cu->next;
        delete temp;
    }
}

void ll::addend(string i, string u, string s, string g) {
    student* temp = new student();
    temp->id = i;
    temp->username = u;
    temp->score = s;
    temp->grade = g;
    temp->next = nullptr;

    student* cu = head;
    if (cu == nullptr) {
        head = temp;
    }

    else if(findName(u) == findPosition(i) && findName(u) != -1){
        int p = findPosition(i);
        while (p > 0) {
            cu = cu->next;
            p--;
        }
        cu->username = u;
        cu->score = s;
        cu->grade = g;
    }

    else if (findName(u) > -1) {
        return;
    }

    else if (findPosition(i) != -1) {
        int p = findPosition(i);
        while (p > 0) {
            cu = cu->next;
            p--;
        }
        cu->username = u;
        cu->score = s;
        cu->grade = g;
    }
    
    else {
        while (cu->next != nullptr) {
            cu = cu->next;
        }
        cu->next = temp;
    }
    size++;
}

void ll::addpos(int pos, string i, string u, string s, string g) {
    if (pos > getSize()) {
        return;
    }
    student* temp = new student();
    temp->id = i;
    temp->username = u;
    temp->score = s;
    temp->grade = g;
    temp->next = nullptr;
    int p = pos;

    student* cu = head;
    //cout << findPosition(i) << endl;
    //cout << findName(u) << endl;
    if (cu == nullptr) {
        head = temp;
    }

    else if(findName(u) == findPosition(i) && findName(u) != -1){
        int p = findPosition(i);
        while (p > 0) {
            cu = cu->next;
            p--;
        }
        cu->username = u;
        cu->score = s;
        cu->grade = g;
    }
    
    else if (findName(u) > -1) {
        return;
    }

    else if (findPosition(i) != -1) {
        p = findPosition(i);
        while (p > 0) {
            cu = cu->next;
            p--;
        }
        cu->username = u;
        cu->score = s;
        cu->grade = g;
    }
    
    else if (pos == 0) {
        temp->next = head;
        head = temp;
    }
    else if (pos == size) {
        while (cu->next != nullptr) {
            cu = cu->next;
        }
        cu->next = temp;
    }
    else {
        while (p>1) {
            cu = cu->next;
            p--;
        }
        temp->next = cu->next;
        cu->next = temp;
    }
    size++;
}

void ll::removeid(string who) {
    student* cu = head;
    student* prev = nullptr;
    if (cu == nullptr)
        return;
    else if(cu->id == who){
        head = cu->next;
        delete cu;
        size--;
    }
    else {
        while (cu->next != nullptr) {
            if(cu->id == who){
                student* temp = cu;
                prev->next = cu->next;
                cu = cu->next;
                delete temp;
                size--;
            }
            else {
                prev = cu;
                cu = cu->next;
            }
        }
    }
    if(cu->id == who){
        prev->next = nullptr;
        delete cu;
    }
}

void ll::removename(string who) {
    student* cu = head;
    student* prev = nullptr;
    if (cu == nullptr)
        return;
    else if(cu->username == who){
        head = cu->next;
        delete cu;
        size--;
    }
    else {
        while (cu->next != nullptr) {
            if (cu->username == who) {
                student* temp = cu;
                prev->next = cu->next;
                cu = cu->next;
                delete temp;
                size--;
            }
            else {
                prev = cu;
                cu = cu->next;
            }
        }
    }
    if(cu->username == who){
        prev->next = nullptr;
        delete cu;
    }
}

void ll::removescore(string who) {
    student* cu = head;
    student* prev = nullptr;
    if (cu == nullptr)
        return;
    else {
        while (cu->next != nullptr) {
            if(cu->score == who && cu == head){
                head = cu->next;
                delete cu;
                size--;
                cu = head;
            }
            else if (cu->score == who) {
                student* temp = cu;
                prev->next = cu->next;
                cu = cu->next;
                delete temp;
                size--;
            }
            else {
                prev = cu;
                cu = cu->next;
            }
        }
    }
    if(cu->score == who){
        prev->next = nullptr;
        delete cu;
    }
}

void ll::removegrade(string who) {
    student* cu = head;
    student* prev = nullptr;
    if (cu == nullptr)
        return;
    else {
        while (cu->next != nullptr) {
            if(cu->grade == who && cu == head){
                head = cu->next;
                delete cu;
                size--;
                cu = head;
            }
            else if (cu->grade == who) {
                student* temp = cu;
                prev->next = cu->next;
                cu = cu->next;
                delete temp;
                size--;
            }
            else {
                prev = cu;
                cu = cu->next;
            }
        }
    }
    if(cu->grade == who){
        prev->next = nullptr;
        delete cu;
    }
}

void ll::sortid(student* head, int count) {
    if(head == nullptr){
        return;
    }
    student* p1 = new student();
    student* p2 = new student();
    int swapped = 1;

    while (swapped)
    {
        swapped = 0;
        p1 = head;
        p2 = head->next;

        while (p2 != nullptr)
        {
            if (p1->id > p2->id)
            {
                /* update the link after swapping */
                string _id = p1->id;
                string _username = p1->username;
                string _score = p1->score;
                string _grade = p1->grade;
                p1->id = p2->id;
                p1->username = p2->username;
                p1->score = p2->score;
                p1->grade = p2->grade;
                p2->id = _id;
                p2->username = _username;
                p2->score = _score;
                p2->grade = _grade;

                swapped = 1;
            }
            p1 = p2;
            p2 = p2->next;
        }
    }
}

void ll::sortname(student* head, int count) {
    if(head == nullptr){
        return;
    }
    student* p1 = new student();
    student* p2 = new student();
    int swapped = 1;

    while (swapped)
    {
        swapped = 0;
        p1 = head;
        p2 = head->next;

        while (p2 != nullptr)
        {
            if (p1->username > p2->username)
            {
                /* update the link after swapping */
                string _id = p1->id;
                string _username = p1->username;
                string _score = p1->score;
                string _grade = p1->grade;
                p1->id = p2->id;
                p1->username = p2->username;
                p1->score = p2->score;
                p1->grade = p2->grade;
                p2->id = _id;
                p2->username = _username;
                p2->score = _score;
                p2->grade = _grade;

                swapped = 1;
            }
            p1 = p2;
            p2 = p2->next;
        }
    }
}

void ll::sortscore(student* head, int count) {
    if(head == nullptr){
        return;
    }
    student* p1 = new student();
    student* p2 = new student();
    int swapped = 1;

    while (swapped)
    {
        swapped = 0;
        p1 = head;
        p2 = head->next;

        while (p2 != nullptr)
        {
            if (p1->score < p2->score)
            {
                /* update the link after swapping */
                string _id = p1->id;
                string _username = p1->username;
                string _score = p1->score;
                string _grade = p1->grade;
                p1->id = p2->id;
                p1->username = p2->username;
                p1->score = p2->score;
                p1->grade = p2->grade;
                p2->id = _id;
                p2->username = _username;
                p2->score = _score;
                p2->grade = _grade;

                swapped = 1;
            }
            p1 = p2;
            p2 = p2->next;
        }
    }
}

void ll::sortgrade(student* head, int count) {
    if(head == nullptr){
        return;
    }
    student* p1 = new student();
    student* p2 = new student();
    int swapped = 1;

    while (swapped)
    {
        swapped = 0;
        p1 = head;
        p2 = head->next;

        while (p2 != nullptr)
        {
            if (p1->grade > p2->grade)
            {
                /* update the link after swapping */
                string _id = p1->id;
                string _username = p1->username;
                string _score = p1->score;
                string _grade = p1->grade;
                p1->id = p2->id;
                p1->username = p2->username;
                p1->score = p2->score;
                p1->grade = p2->grade;
                p2->id = _id;
                p2->username = _username;
                p2->score = _score;
                p2->grade = _grade;

                swapped = 1;
            }
            p1 = p2;
            p2 = p2->next;
        }
    }
}

void ll::print() {
    student* cu = head;
    while (cu != nullptr) {
        if (cu->next == nullptr) {
            cout << "[id:" << cu->id << ";username:" <<
                 cu->username << ";score:" << cu->score
                 << ";grade:" << cu->grade << "]";
        }
        else {
            cout << "[id:" << cu->id << ";username:" <<
                cu->username << ";score:" << cu->score
                << ";grade:" << cu->grade << "]" << endl;
        }
        cu = cu->next;
    }
}

int main(int argc, char *argv[]) {
    
    ArgumentManager am(argc, argv);
    
    ifstream ifs(am.get("input"));
    ifstream cfs(am.get("command"));
    ofstream ofs(am.get("output"));
    
    
    /*
    ifstream ifs("input9.txt");
    ifstream cfs("command9.txt");
    ofstream ofs("output9.txt");
    */
    ll list;
    
    string in = "";

    while (getline(ifs, in)) {
        // Clean up blank spaces, \n and \r, and skip blank lines
        in.erase(remove(in.begin(), in.end(), '\n'), in.end());
        in.erase(remove(in.begin(), in.end(), '\r'), in.end());
        in.erase(remove(in.begin(), in.end(), '['), in.end());
        in.erase(remove(in.begin(), in.end(), ']'), in.end());
        if (in.find("id") == string::npos || in.find("username") == string::npos || in.find("score") == string::npos || in.find("grade") == string::npos
            || in.find("id") > in.find("username") || in.find("username") > in.find("score") || in.find("score") > in.find("grade")){
            continue;
        }
        int pos = in.find(":", 0);
        int end = in.find(";", 0);
        string id = in.substr(pos+1, end - pos-1);
        pos = in.find(":", pos+1);
        end = in.find(";", end+1);
        string username = in.substr(pos+1, end - pos-1);
        pos = in.find(":", pos+1);
        end = in.find(";", end+1);
        string score = in.substr(pos+1, end - pos-1);
        pos = in.find(":", pos+1);
        end = in.find(";", end+1);
        string grade = in.substr(pos+1, end - pos-1);
        list.addend(id, username, score, grade);
    }

    //list.print();
    //cout << endl << endl;
    
    string cmd;

    while (getline(cfs, cmd)) {
        cmd.erase(remove(cmd.begin(), cmd.end(), '\n'), cmd.end());
        cmd.erase(remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
        stringstream ss;
        ss << cmd;
        string what = "";
        ss >> what;
        //cout << what << " ";
        if (what == "Add") {
            string where;
            ss >> where;
            where.erase(remove(where.begin(), where.end(), '('), where.end());
            where.erase(remove(where.begin(), where.end(), ')'), where.end());
            int w = stoi(where);
            //cout << where << " ";
            string stu;
            ss >> stu;
            stu.erase(remove(stu.begin(), stu.end(), '\n'), stu.end());
            stu.erase(remove(stu.begin(), stu.end(), '\r'), stu.end());
            stu.erase(remove(stu.begin(), stu.end(), '['), stu.end());
            stu.erase(remove(stu.begin(), stu.end(), ']'), stu.end());
            if (stu.find("id") == string::npos || stu.find("username") == string::npos || stu.find("score") == string::npos || stu.find("grade") == string::npos
                || stu.find("id") > stu.find("username") || stu.find("username") > stu.find("score") || stu.find("score") > stu.find("grade")) {
                continue;
            }
            int pos = stu.find(":", 0);
            int end = stu.find(";", 0);
            string id = stu.substr(pos+1, end - pos-1);
            //cout << id << " ";
            pos = stu.find(":", pos+1);
            end = stu.find(";", end+1);
            string username = stu.substr(pos+1, end - pos-1);
            //cout << username << " ";
            pos = stu.find(":", pos+1);
            end = stu.find(";", end+1);
            string score = stu.substr(pos+1, end - pos-1);
            //cout << score << " ";
            pos = stu.find(":", pos+1);
            end = stu.find(";", end+1);
            string grade = stu.substr(pos+1, end - pos-1);
            //cout << grade << endl;
            list.addpos(w, id, username, score, grade);
        }
        else if (what == "Remove") {
            ss >> what;
            what.erase(remove(what.begin(), what.end(), '('), what.end());
            what.erase(remove(what.begin(), what.end(), ')'), what.end());
            int colon = what.find(":");
            string key = what.substr(0, colon);
            string value = what.substr(colon + 1);
            //cout << key << " " << value << endl;
            if (key == "id") {
                list.removeid(value);
            }
            else if (key == "username") {
                list.removename(value);
            }
            else if (key == "score") {
                list.removescore(value);
            }
            else {
                list.removegrade(value);
            }
        }
        else {
            ss >> what;
            what.erase(remove(what.begin(), what.end(), '('), what.end());
            what.erase(remove(what.begin(), what.end(), ')'), what.end());
            //cout << what << endl;
            if (what == "id") {
                list.sortid(list.getHead(), list.getSize());
            }
            if (what == "username") {
                list.sortname(list.getHead(), list.getSize());
            }
            if (what == "score") {
                list.sortscore(list.getHead(), list.getSize());
            }
            if (what == "grade") {
                list.sortgrade(list.getHead(), list.getSize());
            }
        }
        list.print();
        cout << endl << endl;
    }
    
    //list.print();

    student* cu = list.getHead();
    while (cu != nullptr) {
            ofs << "[id:" << cu->id << ";username:" <<
                cu->username << ";score:" << cu->score
                << ";grade:" << cu->grade << "]" << endl;
        cu = cu->next;
    }

	return 0;
}
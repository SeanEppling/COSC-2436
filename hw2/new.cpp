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

class ll{
private:
    student* head;
    student* tail;
    int size;

public:
    ll() {
        head = nullptr;
        tail = head;
        size = 0;
    }
    bool empty() {return head == nullptr;}
    int getSize() {return size;}
    student* getHead() { return head;}
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
        while (current != nullptr) {
            if (current->username == _name) {
                return 1;
            }
            current = current->next;
        }
        return 0;
    }
    void addTail(string i, string u, string s, string g){
        student* temp = new student();
        temp->id = i;
        temp->username = u;
        temp->score = s;
        temp->grade = g;
        if(head == nullptr){
            head = temp;
            tail = head;
        }
        else if (findPosition(i) != -1) {
            student* cu = head;
            int p = findPosition(i);
            while (p > 0) {
                cu = cu->next;
                p--;
            }
            cu->username = u;
            cu->score = s;
            cu->grade = g;
        }
        else if (findName(u) == 1) {
            return;
        }
        else{
            tail->next = temp;
            tail = temp;
        }
        size++;
    }
    void addPos(string i, string u, string s, string g, int p){
        if(p > size){
            return;
        }
        else if (findPosition(i) != -1) {
            student* cu = head;
            int pos = findPosition(i);
            while (pos > 0) {
                cu = cu->next;
                pos--;
            }
            cu->username = u;
            cu->score = s;
            cu->grade = g;
        }
        else if (findName(u) == 1) {
            return;
        }
        student* temp = new student();
        temp->id = i;
        temp->username = u;
        temp->score = s;
        temp->grade = g;
        if(p == 0){
            temp->next = head;
            head = temp;  
        }
        else if(p == size){
            tail->next = temp;
            tail = temp;
        }
        else{
            int count = 0;
            student* cu = head;
            student* prev;
            while(count < p){
                prev = cu;
                cu = cu->next;
                count++;
            }
            temp->next = cu;
            prev->next = temp;
        }
    }
    void print(ofstream& output) {
        student* cu = head;
        while (cu != nullptr) {
            cout << "[id:" << cu->id << ";username:" <<
                cu->username << ";score:" << cu->score
                << ";grade:" << cu->grade << "]" << endl;
            output << "[id:" << cu->id << ";username:" <<
                cu->username << ";score:" << cu->score
                << ";grade:" << cu->grade << "]" << endl;
            cu = cu->next;
        }
    }

};

int main(int argc, char *argv[]) {
    
    ArgumentManager am(argc, argv);
    /*
    ifstream ifs(am.get("input"));
    ifstream cfs(am.get("command"));
    ofstream ofs(am.get("output"));
    */
    
    
    ifstream ifs("input1.txt");
    ifstream cfs("command1.txt");
    ofstream ofs("output1.txt");
    
    ll list;

    string in;
    while(getline(ifs, in)){
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
        //cout << id << endl;
        pos = in.find(":", pos+1);
        end = in.find(";", end+1);
        string username = in.substr(pos+1, end - pos-1);
        //cout << username << endl;
        pos = in.find(":", pos+1);
        end = in.find(";", end+1);
        string score = in.substr(pos+1, end - pos-1);
        //cout << score << endl;
        pos = in.find(":", pos+1);
        end = in.find(";", end+1);
        string grade = in.substr(pos+1, end - pos-1);
        //cout << grade << endl;
        list.addTail(id, username, score, grade);       
    }

    string cmd;
    while(getline(cfs, cmd)){
        cmd.erase(remove(cmd.begin(), cmd.end(), '\n'), cmd.end());
        cmd.erase(remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
        stringstream ss;
        ss << cmd;
        string what = "";
        ss >> what;
        //cout << what;
        if (what == "Add") {
            string where;
            ss >> where;
            where.erase(remove(where.begin(), where.end(), '('), where.end());
            where.erase(remove(where.begin(), where.end(), ')'), where.end());
            int w = stoi(where);
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
            pos = stu.find(":", pos+1);
            end = stu.find(";", end+1);
            string username = stu.substr(pos+1, end - pos-1);
            pos = stu.find(":", pos+1);
            end = stu.find(";", end+1);
            string score = stu.substr(pos+1, end - pos-1);
            pos = stu.find(":", pos+1);
            end = stu.find(";", end+1);
            string grade = stu.substr(pos+1, end - pos-1);
            list.addPos(id, username, score, grade, w);
        }
        else if (what == "Remove") {
            ss >> what;
            what.erase(remove(what.begin(), what.end(), '('), what.end());
            what.erase(remove(what.begin(), what.end(), ')'), what.end());
            int colon = what.find(":");
            string key = what.substr(0, colon);
            string value = what.substr(colon + 1);
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
            if (what == "id") {
                list.sortid(list.getHead(), list.getSize());
            }
        }
    }

    list.print(ofs);
}
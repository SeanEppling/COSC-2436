#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <sstream>
#include <vector>
#include "PQueue4.h"
#include "BST.h"
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char* argv[]) {

    //ArgumentManager am(argc, argv);
    //ifstream input(am.get("input"));
    //ofstream output(am.get("output"));

    ifstream input("input4.txt");
    ofstream output("output4.txt");

    PQueue pq;
    queue<string> q;
    bst t;
    string command, check;

    while (!input.eof()) {
        getline(input, check);
        if (check == "") {
            continue;
        }
        command = check;
        command.erase(remove(command.begin(), command.end(), '\n'), command.end());
        command.erase(remove(command.begin(), command.end(), '\r'), command.end());
        int colon = command.find(":");
        string function = command.substr(0, colon);
        //cout << function << " ";
        vector<string> vals;
        if (function == "REMOVE" || function == "DECODE") {
            string val = command.substr(colon + 2, command.find(']')-(colon+2));
            //cout << val << " ";
            vals.push_back(val);
        }
        else if (function == "REPLACE" || function == "ADD" || function == "SWAP") {
            string val = command.substr(colon + 2, 1);
            //cout << val << " ";
            vals.push_back(val);
            val = command.substr(colon + 4, 1);
            //cout << val << " ";
            vals.push_back(val);
        }
        if (function == "Inorder" || function == "Preorder" || function == "Postorder") {
            continue;
        }
        int priority = stoi(command.substr(command.find("(") + 1, 1));
        //cout << priority << endl;
        link* temp = new link();
        temp->func = function;
        temp->vals = vals;
        temp->prio = priority;
        pq.enq(temp);
    }

    while (!pq.empty()) {
        link* temp = pq.deq();
        cout << temp->func << endl;
        if (temp->func == "DECODE") {
            q.push(temp->vals[0]);
            cout << temp->vals[0] << endl;
        }
        else if (!q.empty()) {
            string str = q.front();
            q.pop();
            if (temp->func == "REPLACE") {
                string first = temp->vals[0];
                string second = temp->vals[1];
                for (int i = 0; i < str.length(); i++)
                    if (str[i] == first[0])
                        str[i] = second[0];
                q.push(str);
            }
            else if (temp->func == "ADD") {
                string first = temp->vals[0];
                string second = temp->vals[1];
                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == first[0])
                        str = str.substr(0, i+1) + second + str.substr(i+1);
                }
                q.push(str);
            }
            else if (temp->func == "REMOVE") {
                string first = temp->vals[0];
                str.erase(remove(str.begin(), str.end(), first[0]), str.end());
                q.push(str);
            }
            else if (temp->func == "SWAP") {
                string first = temp->vals[0];
                string second = temp->vals[1];
                for (int i = 0; i < str.length(); i++) {
                    if (str[i] == first[0]) {
                        str[i] = second[0];
                    }
                    else if (str[i] == second[0]) {
                        str[i] = first[0];
                    }
                }
                q.push(str);
            }
            else if (temp->func == "BST") {
                t.insert(str, t.getRoot(), t.getRoot());
            }
            cout << str << endl;
        }
    }

    if(t.empty()){
        cout << "Shit's empty" << endl;
    }

    if (command == "Inorder") {
        t.in(t.getRoot(), output);
    }
    if (command == "Preorder") {
        t.pre(t.getRoot(), output);
    }
    if (command == "Postorder") {
        t.post(t.getRoot(), output);
    }

	return 0;
}
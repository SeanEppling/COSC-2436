#include "ArgumentManager.h"
#include "PQueue.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream output(am.get("output"));

    //ifstream input("input1.txt");
    //ofstream output("output1.txt");

    PQueue pq;
    while (!input.eof()) {
        node* temp = new node();
        string task;
        string time;
        string in;
        getline(input, in);
        if (in.empty()) {
            continue;
        }
        int pos = in.find_last_of(" ");
        task = in.substr(0, pos);
        time = in.substr(pos + 1);
        //cout << task << " " << time << endl;
        temp->task = task;
        temp->time = stof(time);
        pq.enq(temp);
    }
    while (!pq.empty()) {
        node* temp = pq.deq();
        output << temp->task << endl;
        cout << temp->task << endl;
    }

    return 0;
}
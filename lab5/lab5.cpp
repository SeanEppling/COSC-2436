#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream output(am.get("output"));

    //ifstream input("input7.txt");
    //ofstream output("output7.txt");

    map<string, int> m;
    string line;
    
    while (getline(input, line)) {
        if (line.length() == 0) {
            continue;
        }
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), '.'), line.end());
        line.erase(remove(line.begin(), line.end(), ','), line.end());
        line.erase(remove(line.begin(), line.end(), ';'), line.end());
        line.erase(remove(line.begin(), line.end(), ':'), line.end());
        line.erase(remove(line.begin(), line.end(), '!'), line.end());
        line.erase(remove(line.begin(), line.end(), '?'), line.end());
        line.erase(remove(line.begin(), line.end(), '"'), line.end());
        stringstream ss;
        ss << line;
        string word;
        while (ss >> word) {
            for(int i = 0; i < word.length(); i++)
                word[i] = tolower(word[i]);
            //cout << word << " ";
            if (m.find(word) == m.end()) {
                m.insert(pair<string, int>(word, 1));
            }
            else {
                int num = m[word] + 1;
                //cout << num << " ";
                m.erase(word);
                m.insert(pair<string, int>(word, num));
            }
            //cout << m[word] << endl;
        }
    }

    std::vector<string> keys;
    for (auto it = m.begin(); it != m.end(); it++) {
        keys.push_back(it->first);
    }

    int bruh = 0;
    for (const auto& key : keys) {
        if (bruh == 0) {
            output << key << ": " << m[key];
            bruh++;
        }
        else
            output << endl << key << ": " << m[key];
        //cout << key << ": " << m[key] << endl;
    }

	return 0;
}
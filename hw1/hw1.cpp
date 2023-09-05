#include <iostream>
#include "ArgumentManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
int main(int argc, char *argv[]) // add the argc and *argv[] later :)
{
  
    ArgumentManager am(argc, argv);
    ifstream ifs(am.get("input"));
    ifstream cfs(am.get("command"));
    ofstream ofs(am.get("output"));
   
    /*
    ifstream ifs("input9.txt");
    ifstream cfs("command9.txt");
    ofstream ofs("output9.txt");
    */

    vector<string> ids;

    string in = "";

    while (getline(ifs, in)) {
        // Clean up blank spaces, \n and \r, and skip blank lines
        in.erase(remove(in.begin(), in.end(), '\n'), in.end());
        in.erase(remove(in.begin(), in.end(), '\r'), in.end());
        in.erase(remove(in.begin(), in.end(), ' '), in.end());
        if (in.size() == 0)
            continue;

        map<string, string> m;
        string text = in;
        //cout << text << endl;
        stringstream ss;
        ss << text;
        string part;
        while (!ss.eof()) {
            getline(ss, part, ';');
            int colon = part.find(":");
            m.insert({ part.substr(0, colon), part.substr(colon + 1) });
        }

        /*
        for (auto const& pair : m) {
            std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
        */

        if (m.find("id") == m.end()) {
            continue;
        }
        if (m.size() <= 1) {
            continue;
        }

        string id = m["id"];
        //cout << id;
        string ans = "";
        int count = 0;
        for (int i = 0; i < id.size(); i++) {
            string str = id.substr(i, 1);
            if (m.find(str) != m.end()) {
                ans = ans + m[str];
            }
            else if (str == "#") {
                int pos = ans.length() - count;
                if (pos >= 10)
                    count++;
                ans = ans + to_string(pos);
            }
            else {
                ans = ans + str;
            }
            //cout << ans << endl;
        }
        ids.push_back(ans);
    }
    
    /*
    for (string x : ids)
        cout << x << endl;
    */

    string cmd = "";
    vector<string> first;
    vector<string> last;

    while (getline(cfs, cmd)) {
        // Clean up blank spaces, \n and \r, and skip blank lines
        cmd.erase(remove(cmd.begin(), cmd.end(), '\n'), cmd.end());
        cmd.erase(remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
        cmd.erase(remove(cmd.begin(), cmd.end(), ' '), cmd.end());
        if (cmd.size() == 0)
            continue;
        
        int colon = cmd.find(":");
        string where = cmd.substr(0, colon);
        string what = cmd.substr(colon + 1);

        //cout << where << endl;
        //cout << what << endl;
        
        if (where == "first4") {
            first.push_back(what);
        }
        if (where == "last4") {
            last.push_back(what);
        }
    }
    
    /*
    for (string x : first)
        cout << x << endl;
    for (string x : last)
        cout << x << endl;
    */
    

    if (last.empty() && first.empty()) {
        for (string x : ids)
            ofs << x << endl;
    }
    else if (last.empty()) {
        for (string x : ids) {
            string f = x.substr(0, 4);
            if (find(first.begin(), first.end(), f) != first.end()) {
                ofs << x << endl;
            }
        }
    }
    else if (first.empty()) {
        for (string x : ids) {
            string l = x.substr(x.size()-4);
            if (find(last.begin(), last.end(), l) != last.end()) {
                ofs << x << endl;
            }
        }
    }
    else {
        for (string x : ids) {
            string f = x.substr(0, 4);
            string l = x.substr(x.size()-4);
            if (find(last.begin(), last.end(), l) != last.end() && find(first.begin(), first.end(), f) != first.end()) {
                ofs << x << endl;
            }
        }
    }
    

    return 0;
}

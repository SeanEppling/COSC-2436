#include <iostream>
#include "ArgumentManager.h"
#include <algorithm>
#include <stack>
#include <string>
#include <cctype>
#include <fstream>
#include <iomanip>
using namespace std;

int priority(char x) {
	if (x == '^')
		return 3;
	else if (x == '*' || x == '/')
		return 2;
	else if (x == '+' || x == '-')
		return 1;
	return 0;
}

int main(int argc, char *argv[]) {
	
	ArgumentManager am(argc, argv);
	ifstream ifs(am.get("input"));
	ofstream ofs(am.get("output"));
	
	/*
	ifstream ifs("input6.txt");
	ofstream ofs("output6.txt");
	*/
	string eq;
	getline(ifs, eq);
	eq.erase(remove(eq.begin(), eq.end(), '\n'), eq.end());
	eq.erase(remove(eq.begin(), eq.end(), '\r'), eq.end());
	eq.erase(remove(eq.begin(), eq.end(), ' '), eq.end());
	string math = eq.substr(0, eq.find('='));
	string sol = eq.substr(eq.find('=') + 1);

	stack<char> ops;
	string post = "";
	int parentheses = 0;

	/*
	* ------------------------------------------------
	* In-fix to Post-fix
	* ------------------------------------------------
	*/
	for (int i = 0; i < math.length(); i++) {
		char s = math[i];
		cout << s << endl;
		
		if (isdigit(s) > 0 || s == 'x') {
			post = post + s;
		}
		else if (s == '(') {
			ops.push(s);
			parentheses++;
		}
		else {
			if (parentheses > 0) {
				if (s == ')') {
					while (ops.top() != '(' && !ops.empty()) {
						post = post + ops.top();
						ops.pop();
					}
					ops.pop();
					parentheses--;
				}
				else if (ops.top() == '(')
					ops.push(s);
				else if (!ops.empty() && priority(ops.top()) < priority(s)) {
					ops.push(s);
				}
				else {
					while (!ops.empty() && priority(ops.top()) >= priority(s)) {
						post = post + ops.top();
						ops.pop();
					}
				}
			}
			else {
				if (ops.empty()) {
					ops.push(s);
				}
				else if (priority(ops.top()) < priority(s)) {
					ops.push(s);
				}
				else {
					while (!ops.empty() && priority(ops.top()) >= priority(s)) {
						post = post + ops.top();
						ops.pop();
					}
					ops.push(s);
				}
			}
		}
		cout << post << endl;
	}
	while (!ops.empty()) {
		post = post + ops.top();
		ops.pop();
	}

	cout << post << endl;

	stack<float> s;
	string ans = "";

	/*
	* ------------------------------------
	* Computing Post-fix
	* ------------------------------------
	*/ 
	for (int x = 0; x < post.length(); x++)
	{
		cout << isdigit(post[x]) << endl;
		if (isdigit(post[x]) > 0)
		{
			s.push((float)(post[x] - '0'));
		}
		else if (post.at(x) == 'x')
		{
			s.push(-1000);
		}
		else
		{

			float rightNum = s.top();
			s.pop();

			float leftNum = s.top();
			s.pop();

			if (rightNum > -1000 && leftNum > -1000)
			{
				switch (post.at(x))
				{
				case '+':
					s.push(leftNum + rightNum);
					break;
				case '-':
					s.push(leftNum - rightNum);
					break;
				case '*':
					s.push(leftNum * rightNum);
					break;
				case '/':
					s.push(leftNum / rightNum);
					break;
				}
			}
			else if (leftNum == -1000  || rightNum == -1000)
			{
				if (leftNum < 0)
				{
					ans += "x";
					(leftNum > -1000) ? (ans += to_string(leftNum)) : (ans += to_string(rightNum));
					ans += post.at(x);
				}
				else if (rightNum < 0)
				{
					(leftNum > -1000) ? (ans += to_string(leftNum)) : (ans += to_string(rightNum));
					ans += "x";
					ans += post.at(x);
				}
			}
		}
	}

	cout << ans << endl;

	int posx = ans.find('x');
	float x = 0;
	char op = ans[ans.length()-1];
	switch (op)
	{
	case '+':
		if (posx == 0) {
			string num = ans.substr(1, ans.length() - 2);
			x = (float)stof(sol) - (float)stof(num);
		}
		else {
			string num = ans.substr(0, posx);
			x = (float)stof(sol) - (float)stof(num);
		}
		break;
	case '-':
		if (posx == 0) {
			string num = ans.substr(1, ans.length() - 2);
			x = (float)stof(sol) + (float)stof(num);
		}
		else {
			string num = ans.substr(0, posx);
			x = ((float)stof(sol) - (float)stof(num)) * -1;
		}
		break;
	case '*':
		if (posx == 0) {
			string num = ans.substr(1, ans.length() - 2);
			x = (float)stof(sol) / (float)stof(num);
		}
		else {
			string num = ans.substr(0, posx);
			x = (float)stof(sol) / (float)stof(num);
		}
		break;
	case '/':
		if (posx == 0) {
			string num = ans.substr(1, ans.length() - 2);
			x = (float)stof(sol) * (float)stof(num);
		}
		else {
			string num = ans.substr(0, posx);
			x = (float)stof(num) / (float)stof(sol);
		}
		break;
	}
	
	cout << fixed << setprecision(2);
	cout << x << endl;
	
	ofs << fixed << setprecision(2);
	ofs << x;

	return 0;
}
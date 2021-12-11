#include"ReadFile.h"
#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::stack;
using std::string;

void readInput(vector<string> &ll)
{
	mhr::ReadFile inf("input.txt");
	string ln;
	int y = 0;
	while(inf.readLine(ln))
	{
		if(ln.size() > 0)
			ll.push_back(ln);
	}
	inf.close();
}

unsigned long long getScore(string &ss)
{
	unsigned long long tot = 0;
	for(char c : ss)
	{
		if(c == ')') { tot *= 5; tot++; }
		else if(c == ']') { tot *= 5; tot += 2; }
		else if(c == '}') { tot *= 5; tot += 3; }
		else if(c == '>') { tot *= 5; tot += 4; }
	}
	return tot;
}

/////

int main()
{
	vector<string> ll;
	readInput(ll);
	int tot = 0;
	for(std::vector<string>::reverse_iterator it = ll.rbegin() ; it != ll.rend(); ++it)
	{
		string ss = *it;
		stack<char> st;
		for(int i = 0; i < ss.length(); i++)
		{
			if(ss[i] == '<' || ss[i] == '[' || ss[i] == '{' || ss[i] == '(')
				st.push(ss[i]);
			else
			{
				char c = st.top();
				if(c == '<' && ss[i] == '>') st.pop();
				else if(c == '[' && ss[i] == ']') st.pop();
				else if(c == '{' && ss[i] == '}') st.pop();
				else if(c == '(' && ss[i] == ')') st.pop();
				else
				{
					if(ss[i] == ')') tot += 3;
					else if(ss[i] == ']') tot += 57;
					else if(ss[i] == '}') tot += 1197;
					else if(ss[i] == '>') tot += 25137;
					ll.erase(std::next(it).base());
					break;
				}
			}
		}
	}

	cout << "PART1 answer = " << tot << endl;

	/////

	vector<unsigned long long> scores;
	for(string s1 : ll)
	{
		string s2 = "";
		string add = "";

		while(true)
		{
			if(s1.length() == 0) break;

			int lc = s1.length() - 1;
			if(s1[lc] == '>')      { s2 = s1[lc] + s2; s1.pop_back(); }
			else if(s1[lc] == ']') { s2 = s1[lc] + s2; s1.pop_back(); }
			else if(s1[lc] == ')') { s2 = s1[lc] + s2; s1.pop_back(); }
			else if(s1[lc] == '}') { s2 = s1[lc] + s2; s1.pop_back(); }
			else
			{
				if(s1[lc] == '<' && s2[0] == '>')      { s1.pop_back(); s2.erase(0,1); }
				else if(s1[lc] == '[' && s2[0] == ']') { s1.pop_back(); s2.erase(0,1); }
				else if(s1[lc] == '(' && s2[0] == ')') { s1.pop_back(); s2.erase(0,1); }
				else if(s1[lc] == '{' && s2[0] == '}') { s1.pop_back(); s2.erase(0,1); }
				else
				{
					if(s1[lc] == '<') add += '>';
					else if(s1[lc] == '[') add += ']';
					else if(s1[lc] == '(') add += ')';
					else if(s1[lc] == '{') add += '}';
					s1.pop_back();
				}
			}
		}

		scores.push_back(getScore(add));
	}

	sort(scores.begin(), scores.end());
	cout << "PART2 answer = " << scores[scores.size() / 2] << endl;
}

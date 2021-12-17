#include"ReadFile.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;

void tokenize(string &str, string &delims, vector<string> &ll)
{
	string tok("");
	for(int i = 0; i < str.length(); i++)
	{
		string chr(1, str[i]);
		if(delims.find(chr) != string::npos)
		{
			if(tok.length() > 0)
			{
				ll.push_back(tok);
				tok = "";
			}
		}
		else
			tok += chr;
	}
	if(tok.length() > 0)
		ll.push_back(tok);
}

void readInput(vector<string> &lns)
{
	//mhr::ReadFile inf("sample_input.txt");
	mhr::ReadFile inf("input.txt");
	string ln;
	while(inf.readLine(ln))
	{
		if(ln.size() > 0)
			lns.push_back(ln);
	}
	inf.close();
}

/////

int main()
{
	unordered_map<string,unsigned long long> cnts;
	unordered_map<string,char> mp;

	vector<string> lns;
	readInput(lns);

	string inp = "";
	for(string ln : lns)
	{
		if(inp.empty())
			inp = ln;
		else
		{
			vector<string> ll;
			string delims = " ->";
			tokenize(ln, delims, ll);
			mp[ll[0]] = ll[1][0];
		}
	}
	lns.clear();

	//

	for(int i = 0; i < inp.length()-1; i++)
	{
		string ss = inp.substr(i,2);
		cnts[ss]++;
	}

	for(int i = 0; i < 40; i++)
	{
		//cout << "---" << endl;
		//cout << "STEP: " << i+1 << endl;

		unordered_map<string,unsigned long long> cnts2;

		for(auto it = mp.begin(); it != mp.end(); ++it)
		{
			string ky = it->first;
			if(cnts.count(ky) == 1)
			{
				string chr(1, it->second);
				string n1 = ky[0] + chr;
				string n2 = chr + ky[1];

				unsigned long long ccc = cnts[ky];
				cnts2[n1] += ccc;
				cnts2[n2] += ccc;
			}
		}

		//for(auto it = cnts2.begin(); it != cnts2.end(); ++it)
		//	cout << it->first << " = " << it->second << endl;
		cnts = cnts2;
	}

	//cout << "---------------" << endl;
	unordered_map<char,unsigned long long> totals;
	for(auto it = cnts.begin(); it != cnts.end(); ++it)
	{
		char c = it->first[0];
		if(totals.count(c) == 0) totals[c] = 0;
		totals[c] += it->second;
	}
	totals[inp.back()]++;
	unsigned long long max = 0;
	unsigned long long min = ULLONG_MAX;
	for(auto it = totals.begin(); it != totals.end(); ++it)
	{
		//cout << it->first << " = " << it->second << endl;
		if(it->second > max) max = it->second;
		if(it->second < min) min = it->second;
	}
	cout << "max    = " << max << endl;
	cout << "min    = " << min << endl;
	unsigned long long answer = max - min;
	cout << "answer = " << answer << endl;
}

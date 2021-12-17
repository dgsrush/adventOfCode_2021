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

unordered_map<string,char> mp;
unordered_map<char,unsigned long long> cnts;

char alpha[] = {
	'A','B','C','D','E','F','G','H','I','J','K','L','M',
	'N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

void initCnts()
{
	cnts.clear();
	for(char c : alpha)
		cnts[c] = 0;
}

void getMinMaxCnts(unsigned long long &min, unsigned long long &max)
{
	min = ULLONG_MAX;
	max = 0;
	for(char c : alpha)
	{
		unsigned long long v = cnts[c];
		if(v > max) max = v;
		if(v > 0 && v < min) min = v;
	}
}

void step(const vector<char> &inp, vector<char> &out)
{
	out.clear();
	unsigned long long len = inp.size() - 1;
	string key = "  ";
	for(unsigned long long i = 0; i < len; i++)
	{
		key[0] = inp[i];
		key[1] = inp[i+1];
		out.push_back(key[0]);
		if(mp.count(key) == 1)
			out.push_back(mp[key]);
	}
	out.push_back(inp[len]);
}

/////

int main()
{
	vector<string> lns;
	readInput(lns);

	string sss = "";
	for(string ln : lns)
	{
		if(sss.empty())
			sss = ln;
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

	vector<char> ss;
	vector<char> out;
	for(char c : sss)
		ss.push_back(c);

	for(int i = 0; i < 10; i += 2)
	{
		step(ss, out);
		cout << "step " << i + 1 << ": ";// << out;
		cout << "\tlength: " << out.size() << endl;

		step(out, ss);
		cout << "step " << i + 2 << ": ";// << out;
		cout << "\tlength: " << ss.size() << endl;
	}

	initCnts();
	for(char c : ss)
		cnts[c]++;

	unsigned long long min, max;
	getMinMaxCnts(min, max);
	cout << "min=" << min << endl;
	cout << "max=" << max << endl;

	cout << "PART1 answer = " << max - min << endl;
}

/*
Sample:
Template:     NNCB
After step 1: NCNBCHB
After step 2: NBCCNBBBCBHCB
After step 3: NBBBCNCCNBBNBNBBCHBHHBCHB
After step 4: NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB
After step 10: 1749 - 161 = 1588

Real data answer:
3535 - 588 = 2947
*/

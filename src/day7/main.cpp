#include"ReadFile.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<sstream>
#include<iterator>

using std::cout;
using std::endl;
using std::vector;
using std::string;

//////////////////////////////////////////////////

string to_string(char c)
{
	char buf[2];
	buf[0] = c;
	buf[1] = 0;
	string ss(buf);
	return ss;
}

void tokenize(string &str, string &delims, vector<unsigned long long> &ll)
{
	string tok("");
	for(int i = 0; i < (int)str.length(); i++)
	{
		string chr = to_string(str[i]);
		if(delims.find(chr) != string::npos)
		{
			if(tok.length() > 0)
			{
				ll.push_back(std::stoi(tok));
				tok = "";
			}
		}
		else
			tok += chr;
	}
	if(tok.length() > 0)
	{
		ll.push_back(std::stoi(tok));
	}
}

//////////////////////////////////////////////////

vector<unsigned long long> ll;
int hh = -1;
unsigned long long minv = ULLONG_MAX;

void readInput()
{
	mhr::ReadFile inf("input.txt");
	string delim = ",";
	string ln;
	inf.readLine(ln);
	tokenize(ln, delim, ll);
	inf.close();
}

int getMaxInputValue()
{
	int maxn = 0;
	for(int i : ll)
		if(i > maxn) maxn = i;
	return maxn;
}

void calc1(int h)
{
	unsigned long long cnt = 0;
	for(int i = 0; i < ll.size(); i++)
		cnt += abs(h - ll[i]);
	if(cnt < minv)
	{
		hh = h;
		minv = cnt;
	}
	//cout << "h = " << h << " fl = " << cnt << endl;
}

void calc2(int h)
{
	unsigned long long cnt = 0;
	for(int i = 0; i < ll.size(); i++)
	{
		unsigned long long ii = abs(h - ll[i]);
		for(unsigned long long j = 1; j <= ii; j++)
			cnt += j;
	}
	if(cnt < minv)
	{
		hh = h;
		minv = cnt;
	}
	//cout << "h = " << h << " fl = " << cnt << endl;
}

int main()
{
	readInput();
	int maxn = getMaxInputValue();
	cout << "maxn = " << maxn << endl;

	//////////

	for(int i = 0; i <= maxn; i++)
		calc1(i);
	cout << "PART1 hh = " << hh << " answer = " << minv << endl;

	//////////

	hh = -1;
	minv = ULLONG_MAX;

	for(int i = 0; i <= maxn; i++)
		calc2(i);
	cout << "PART2 hh = " << hh << " answer = " << minv << endl;

	return 0;
}

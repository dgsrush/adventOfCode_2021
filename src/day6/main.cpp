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

void tokenize(string &str, string &delims, vector<int> &ll)
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

vector<int> ll;

void readInput()
{
	mhr::ReadFile inf("input.txt");
	string delim = ",";
	string ln;
	inf.readLine(ln);
	tokenize(ln, delim, ll);
	inf.close();
}

void calc(int days)
{
	for(int day = 1; day <= days; day++)
	{
		unsigned long long cnt = ll.size();
		for(unsigned long long i = 0; i < cnt; i++)
		{
			if(ll[i] == 0)
			{
				ll[i] = 6;
				ll.push_back(8);
			}
			else
			{
				ll[i]--;
			}
		}
	}
}

int getCount(int ii)
{
	int cnt = 0;
	for(int i = 0; i < ll.size(); i++)
		if(ll[i] == ii) cnt++;
	return cnt;
}

unsigned long long runit(int rr)
{
	readInput();

	unsigned long long numOf1s = getCount(1);
	unsigned long long numOf2s = getCount(2);
	unsigned long long numOf3s = getCount(3);
	unsigned long long numOf4s = getCount(4);
	unsigned long long numOf5s = getCount(5);
	cout << "number of 1s: " << numOf1s << endl;
	cout << "number of 2s: " << numOf2s << endl;
	cout << "number of 3s: " << numOf3s << endl;
	cout << "number of 4s: " << numOf4s << endl;
	cout << "number of 5s: " << numOf5s << endl;

	ll.clear(); ll.push_back(1); calc(rr);
	cout << "1 = " << ll.size() << endl;
	numOf1s *= ll.size();

	ll.clear(); ll.push_back(2); calc(rr);
	cout << "2 = " << ll.size() << endl;
	numOf2s *= ll.size();

	ll.clear(); ll.push_back(3); calc(rr);
	cout << "3 = " << ll.size() << endl;
	numOf3s *= ll.size();

	ll.clear(); ll.push_back(4); calc(rr);
	cout << "4 = " << ll.size() << endl;
	numOf4s *= ll.size();

	ll.clear(); ll.push_back(5); calc(rr);
	cout << "5 = " << ll.size() << endl;
	numOf5s *= ll.size();

	unsigned long long total = numOf1s + numOf2s + numOf3s + numOf4s + numOf5s;
	return total;
}

int main()
{
	unsigned long long total = runit(80);
	cout << "PART1 total = " << total << endl;
	ll.clear();
	total = runit(256);
	cout << "PART2 total = " << total << endl;
	return 0;
}

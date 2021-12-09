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

void tokenize(string &str, string &delims, vector<string> &ll)
{
	string tok("");
	for(int i = 0; i < (int)str.length(); i++)
	{
		string chr = to_string(str[i]);
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
	{
		ll.push_back(tok);
	}
}

//////////////////////////////////////////////////

class Row
{
public:
	Row(string &ln)
	{
		string delim = " |";
		vector<string> xx;
		tokenize(ln, delim, xx);
		for(int i = 0; i < 10; i++)
		{
			signal[i] = xx[i];
			decode[i] = -1;
		}
		output[0] = xx[10];
		output[1] = xx[11];
		output[2] = xx[12];
		output[3] = xx[13];

		for(int i = 0; i < 10; i++)
			sort(signal[i].begin(), signal[i].end());
		for(int i = 0; i < 4; i++)
			sort(output[i].begin(), output[i].end());
	}

	void print()
	{
		for(int i = 0; i < 10; i++)
			cout << signal[i] << "=" << decode[i] << " ";
		cout << " *** " << endl;
		for(int i = 0; i < 4; i++)
			cout << output[i] << " ";
		cout << endl;
	}

	int cnt1478()
	{
		int cnt = 0;
		for(int i = 0; i < 4; i++)
		{
			if(output[i].size() == 2 || output[i].size() == 3 || output[i].size() == 4 ||output[i].size() == 7)
				cnt++;
		}
		return cnt;
	}

	bool containsOnes(string &ss)
	{
		if(ss.find(one[0]) != string::npos && ss.find(one[1]) != string::npos) return true;
		return false;
	}

	bool containsElementsOfFour(string &ss, int need)
	{
		int cnt = 0;
		for(int i = 0; i < 4; i++)
		{
			char c = four[i];
			if(ss.find(c) != string::npos) cnt++;
		}
		if(cnt == need) return true;
		return false;
	}

	int decodeIt()
	{
		for(int i = 0; i < 10; i++)
		{
			if(signal[i].size() == 2)
			{
				decode[i] = 1;
				one[0] = signal[i][0];
				one[1] = signal[i][1];
			}
			else if(signal[i].size() == 3)
				decode[i] = 7;
			else if(signal[i].size() == 4)
			{
				decode[i] = 4;
				four[0] = signal[i][0];
				four[1] = signal[i][1];
				four[2] = signal[i][2];
				four[3] = signal[i][3];
			}
			else if(signal[i].size() == 7)
				decode[i] = 8;
		}
		for(int i=0;i<10;i++)
		{
			if(signal[i].size() == 5 && containsOnes(signal[i]))
			{
				decode[i] = 3;
			}
			else if(signal[i].size() == 5 && containsElementsOfFour(signal[i], 2))
			{
				decode[i] = 2;
			}
			else if(signal[i].size() == 5 && containsElementsOfFour(signal[i], 3))
			{
				decode[i] = 5;
			}
			else if(signal[i].size() == 6 && !containsOnes(signal[i]))
			{
				decode[i] = 6;
			}
			else if(signal[i].size() == 6 && containsElementsOfFour(signal[i], 3))
			{
				decode[i] = 0;
			}
			else if(signal[i].size() == 6 && containsElementsOfFour(signal[i], 4))
			{
				decode[i] = 9;
			}
		}

		int total = 0;
		for(int i = 0; i < 10; i++)
		{
			if(signal[i] == output[0])
			{
				total += decode[i] * 1000;
				break;
			}
		}
		for(int i = 0; i < 10; i++)
		{
			if(signal[i] == output[1])
			{
				total += decode[i] * 100;
				break;
			}
		}
		for(int i = 0; i < 10; i++)
		{
			if(signal[i] == output[2])
			{
				total += decode[i] * 10;
				break;
			}
		}
		for(int i = 0; i < 10; i++)
		{
			if(signal[i] == output[3])
			{
				total += decode[i];
				break;
			}
		}
		return total;
	}

private:
	string signal[10];
	int decode[10];
	string output[4];

	char one[2]={' ',' '};
	char four[4]={' ',' ',' ',' '};
};

//////////////////////////////////////////////////

vector<Row *> ll;

void readInput()
{
	mhr::ReadFile inf("input.txt");
	string ln;
	while(inf.readLine(ln))
	{
		if(ln.size() > 0)
			ll.push_back(new Row(ln));
	}
	inf.close();
}

int main()
{
	readInput();

	int cnt = 0;
	for(Row *r : ll)
		cnt += r->cnt1478();
	cout << "PART1 answer = " << cnt << endl;

	////

	cnt = 0;
	for(Row *r : ll)
		cnt += r->decodeIt();
	cout << "PART2 answer = " << cnt << endl;

	////

	for(Row *r : ll)
		delete r;
	ll.clear();

	return 0;
}

#include"ReadFile.h"
#include<iostream>
#include<vector>

using std::cout;
using std::endl;

void readInput(std::vector<std::string> *v)
{
	mhr::ReadFile inf("input.txt");
	std::string ll;
	while(inf.readLine(ll))
	{
		if(ll.length() > 0)
		{
			v->push_back(ll);
		}
	}
	inf.close();
}

void part1()
{
	std::vector<std::string> ll;
	readInput(&ll);
	int cnt = ll.size();
	
	std::string gamma = "";
	std::string epsilon = "";
	
	for(int j = 0; j < 12; j++)
	{
		int cnt0 = 0;
		int cnt1 = 0;
		for(int i = 0; i < cnt; i++)
		{
			if(ll[i][j] == '0') cnt0++;
			else if(ll[i][j] == '1') cnt1++;
		}
		if(cnt0 > cnt1)
		{
			gamma += "0";
			epsilon += "1";
		}
		else
		{
			gamma += "1";
			epsilon += "0";
		}
	}
	
	
	cout << "PART1 gamma   = " << gamma << endl;
	cout << "PART1 epsilon = " << epsilon << endl;
	
	int gam = std::stoi(gamma, 0, 2);
	int eps = std::stoi(epsilon, 0, 2);
	
	cout << "PART1 gamma   = " << gam << endl;
	cout << "PART1 epsilon = " << eps << endl;
	cout << "PART1 answer  = " << gam * eps << endl;
}

void getCounts(int *cnt0, int *cnt1, std::vector<std::string> *inp, int column)
{
	for(int i = 0; i < inp->size(); i++)
	{
		if(inp->at(i)[column] == '0')
			(*cnt0)++;
		else if(inp->at(i)[column] == '1')
			(*cnt1)++;
	}
}

void updateList(std::vector<std::string> *ll, char c, int column)
{
	std::vector<std::string> tmp;
	for(int i = 0; i < ll->size(); i++)
	{
		if(ll->at(i)[column] == c)
			tmp.push_back(ll->at(i));
	}
	ll->clear();
	ll->swap(tmp);
}

void part2()
{
	std::vector<std::string> ll;
	readInput(&ll);
	
	std::string oxy = "";
	std::string co2 = "";
		
	for(int j = 0; j < 12; j++)
	{
		int cnt0 = 0;
		int cnt1 = 0;		
		getCounts(&cnt0, &cnt1, &ll, j);
		
		bool keep0;
		if(cnt0 > cnt1)
			keep0 = true;
		else
			keep0 = false;
				
		if(keep0)
			updateList(&ll, '0', j);
		else
			updateList(&ll, '1', j);
				
		if(ll.size()==1)
		{
			oxy = ll[0];
			break;
		}
	}
	
	ll.clear();
	readInput(&ll);

	for(int j = 0; j < 12; j++)
	{
		int cnt0 = 0;
		int cnt1 = 0;		
		getCounts(&cnt0, &cnt1, &ll, j);
		
		bool keep0;
		if(cnt0 > cnt1)
			keep0 = false;
		else
			keep0 = true;
				
		if(keep0)
			updateList(&ll, '0', j);
		else
			updateList(&ll, '1', j);
				
		if(ll.size()==1)
		{
			co2 = ll[0];
			break;
		}
	}
	
	cout << "PART2 oxy = " << oxy << endl;
	cout << "PART2 c02 = " << co2 << endl;
	
	int ox = std::stoi(oxy, 0, 2);
	int co = std::stoi(co2, 0, 2);
	
	cout << "PART2 oxy = " << ox << endl;
	cout << "PART2 c02 = " << co << endl;
	cout << "PART2 answer = " << ox * co << endl;
}

int main()
{
	part1();
	part2();
	return 0;
}

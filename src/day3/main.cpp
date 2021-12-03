#include"ReadFile.h"
#include<iostream>
#include<vector>

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
	
	
	std::cout << "PART1 gamma   = " << gamma << std::endl;
	std::cout << "PART1 epsilon = " << epsilon << std::endl;
	
	int gam = std::stoi(gamma, 0, 2);
	int eps = std::stoi(epsilon, 0, 2);
	
	std::cout << "PART1 gamma   = " << gam << std::endl;
	std::cout << "PART1 epsilon = " << eps << std::endl;
	std::cout << "PART1 answer  = " << gam * eps << std::endl;
}

void part2()
{
}

int main()
{
	part1();
	part2();
	return 0;
}


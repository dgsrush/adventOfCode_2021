#include"ReadFile.h"
#include<iostream>
#include<vector>

void readInput(std::vector<int> *v)
{
	mhr::ReadFile inf("input.txt");
	std::string ll;
	while(inf.readLine(ll))
	{
		if(ll.length() > 0)
		{
			int ii = std::stoi(ll);
			v->push_back(ii);
		}
	}
	inf.close();
}

void part1()
{
	std::vector<int> ll;
	readInput(&ll);
	int cnt = ll.size() - 1;
	
	int incr = 0;
	for(int i = 0; i < cnt; i++)
	{
		int i1 = ll[i];
		int i2 = ll[i+1];
		if(i2 > i1) incr++;
	}
	std::cout << "PART 1 incr = " << incr << std::endl;
}

void part2()
{
	std::vector<int> ll;
	readInput(&ll);
	
	int incr = 0;
	while(ll.size() >= 4)
	{		
		int i1 = ll[0] + ll[1] + ll[2];
		int i2 = ll[1] + ll[2] + ll[3];
		if(i2 > i1) incr++;
		ll.erase(ll.begin());
	}
	std::cout << "PART 2 incr = " << incr << std::endl;
}

int main()
{
	part1();
	part2();	
	return 0;
}

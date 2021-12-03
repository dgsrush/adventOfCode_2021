#include"ReadFile.h"
#include<iostream>
#include<vector>

class Row
{
public:
	std::string cmd;
	int val;
	
	Row(std::string &c, int v)
	{
		cmd = c;
		val = v;
	}
	
	void print()
	{
		std::cout << cmd << " = " << val << std::endl;
	}
};

void readInput(std::vector<Row *> *v)
{
	mhr::ReadFile inf("input.txt");
	std::string ll;
	while(inf.readLine(ll))
	{
		if(ll.length() > 0)
		{
			int indx = ll.find_first_of(" ");
			std::string s1 = ll.substr(0, indx);
			std::string s2 = ll.substr(indx + 1);
			int ii = std::stoi(s2);
			Row *r = new Row(s1, ii);
			v->push_back(r);
		}
	}
	inf.close();
}

void part1()
{
	std::vector<Row *> ll;
	readInput(&ll);
	int cnt = ll.size();
	
	int horiz = 0;
	int depth = 0;
	
	for(int i = 0; i < cnt; i++)
	{
		//ll[i]->print();
		if(ll[i]->cmd == "forward")
			horiz += ll[i]->val;
		else if(ll[i]->cmd == "up")
			depth -= ll[i]->val;
		else if(ll[i]->cmd == "down")
			depth += ll[i]->val;
	}
	
	std::cout << "PART 1 horiz = " << horiz << std::endl;
	std::cout << "PART 1 depth = " << depth << std::endl;
	std::cout << "PART 1 answer = " << horiz * depth << std::endl;
	
	for(int i = 0; i < cnt; i++)
		delete ll[i];
	ll.clear();
}

void part2()
{
	std::vector<Row *> ll;
	readInput(&ll);
	int cnt = ll.size();
	
	int horiz = 0;
	int depth = 0;
	int aim = 0;
	
	for(int i = 0; i < cnt; i++)
	{
		//ll[i]->print();
		if(ll[i]->cmd == "forward")
		{
			horiz += ll[i]->val;
			depth += aim * ll[i]->val;
		}
		else if(ll[i]->cmd == "up")
		{
			aim -= ll[i]->val;
		}
		else if(ll[i]->cmd == "down")
		{
			aim += ll[i]->val;
		}
	}
	
	std::cout << "PART 2 horiz = " << horiz << std::endl;
	std::cout << "PART 2 depth = " << depth << std::endl;
	std::cout << "PART 2 answer = " << horiz * depth << std::endl;
	
	for(int i = 0; i < cnt; i++)
		delete ll[i];
	ll.clear();
}

int main()
{
	part1();
	part2();	
	return 0;
}

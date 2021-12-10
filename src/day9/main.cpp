#include"ReadFile.h"
#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::string;

int grid[100][100];

void readInput()
{
	mhr::ReadFile inf("input.txt");
	string ln;
	int y = 0;
	while(inf.readLine(ln))
	{
		if(ln.size() > 0)
		{
			for(int x = 0; x < ln.size(); x++)
				grid[y][x] = std::stoi(ln.substr(x,1));
			y++;
		}
	}
	inf.close();
}

int getValue(int y, int x)
{
	if(y < 0 || y > 99 || x < 0 || x > 99) return INT_MAX;
	return grid[y][x];
}

bool isLessThanNeighbors(int y, int x)
{
	int vl = getValue(y,x);
	int n1 = getValue(y-1,x);
	int n2 = getValue(y+1,x);
	int n3 = getValue(y,x-1);
	int n4 = getValue(y,x+1);
	if(vl < n1 && vl < n2 && vl < n3 && vl < n4) return true;
	return false;
}

/////

class Point
{
public:
	Point(int yy, int xx) { y = yy; x = xx; }
	string getStr() { return std::to_string(y) + ":" + std::to_string(x); }
	void print() { cout << getStr() << endl; }
	int y,x;
};

/////

class LowPoint
{
public:
	LowPoint(int yy, int xx) { y = yy; x = xx; }

	void print() { cout << y << " " << x << endl; }

	int calcBasinSize()
	{
		int sz = 0;

		vector<Point *> ll;
		ll.push_back(new Point(y,x));
		set<string> done;

		while(ll.size() > 0)
		{
			Point *p = ll[0];
			if(done.count(p->getStr()) > 0)
			{
				ll.erase(ll.begin());
				continue;
			}
			done.insert(p->getStr());
			sz++;

			if(getValue(p->y-1,p->x) < 9)
			{
				Point *pp = new Point(p->y-1,p->x);
				ll.push_back(pp);
			}
			if(getValue(p->y+1,p->x) < 9)
			{
				Point *pp = new Point(p->y+1,p->x);
				ll.push_back(pp);
			}
			if(getValue(p->y,p->x-1) < 9)
			{
				Point *pp = new Point(p->y,p->x-1);
				ll.push_back(pp);
			}
			if(getValue(p->y,p->x+1) < 9)
			{
				Point *pp = new Point(p->y,p->x+1);
				ll.push_back(pp);
			}

			ll.erase(ll.begin());
		}

		return sz;
	}

private:
	int y,x;
};

/////

int main()
{
	readInput();
	vector<LowPoint *> lowPoints;

	int total = 0;
	for(int y = 0; y < 100; y++)
	{
		for(int x = 0; x < 100; x++)
		{
			if(isLessThanNeighbors(y,x))
			{
				total += getValue(y,x) + 1;
				LowPoint *lp = new LowPoint(y,x);
				lowPoints.push_back(lp);
			}
		}
	}
	cout << "PART1 answer = " << total << endl;

	//

	vector<int> szs;
	for(LowPoint *p : lowPoints)
	{
		int sz = p->calcBasinSize();
		szs.push_back(sz);
	}
	std::sort(szs.begin(), szs.end());
	int sz1 = szs[szs.size()-1];
	int sz2 = szs[szs.size()-2];
	int sz3 = szs[szs.size()-3];
	cout << "PART2 answer = " << sz1 * sz2 * sz3 << endl;

	for(LowPoint *p : lowPoints)
		delete p;
	lowPoints.clear();
}

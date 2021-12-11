#include"ReadFile.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int fcnt = 0;
int frow = -1;

class Cell
{
public:
	Cell()
	{
		flashed = false;
		justFlashed = false;
	}

	void set(int xx, int yy, int ll) { x = xx; y = yy; lvl = ll; }

	void inc()
	{
		if(flashed) return;
		lvl++;
		if(lvl > 9)
		{
			fcnt++;
			flashed = true;
			justFlashed = true;
		}
	}

	bool hasFlashed() { return flashed; }
	bool hasJustFlashed() { return justFlashed; }
	void clearJust() { justFlashed = false; }

	void clear()
	{
		if(flashed)
		{
			flashed = false;
			justFlashed = false;
			lvl = 0;
		}
	}

private:
	int x, y, lvl;
	bool flashed;
	bool justFlashed;
};

/////

Cell grid[10][10];

void incNeighbors(int xx, int yy)
{
	for(int y = yy-1; y <= yy+1; y++)
	{
		for(int x = xx-1; x <= xx+1; x++)
		{
			if(x >=0 && x < 10 && y >=0 && y < 10)
				grid[x][y].inc();
		}
	}
}

void step(int row)
{
	for(int y = 0; y < 10; y++)
	{
		for(int x = 0; x < 10; x++)
			grid[x][y].inc();
	}

	bool done = false;
	while(!done)
	{
		done = true;
		for(int y = 0; y < 10; y++)
		{
			for(int x = 0; x < 10; x++)
			{
				if(grid[x][y].hasJustFlashed())
				{
					done = false;
					incNeighbors(x, y);
					grid[x][y].clearJust();
				}
			}
		}
	}

	if(frow < 0)
	{
		int sfcnt = 0;
		for(int y = 0; y < 10; y++)
		{
			for(int x = 0; x < 10; x++)
			{
				if(grid[x][y].hasFlashed()) sfcnt++;
			}
		}
		if(sfcnt == 100)
			frow = row;
	}

	for(int y = 0; y < 10; y++)
	{
		for(int x = 0; x < 10; x++)
			grid[x][y].clear();
	}
}

void readInput()
{
	mhr::ReadFile inf("input.txt");
	string ln;
	int y = 0;
	while(inf.readLine(ln))
	{
		if(ln.size() > 0)
		{
			int x = 0;
			for(char c : ln)
			{
				grid[x][y].set(x, y, c-48);
				x++;
			}
			y++;
		}
	}
	inf.close();
}

/////

int main()
{
	readInput();

	for(int i = 0; i < 100; i++)
		step(i + 1);
	cout << "PART1 answer = " << fcnt << endl; //1634

	/////

	for(int i = 100; i < 300; i++)
	{
		step(i + 1);
		if(frow >= 0) break;
	}
	cout << "PART2 answer = " << frow << endl; //210
}

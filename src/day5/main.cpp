#include"ReadFile.h"
#include<iostream>
#include<vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

string to_string(char c)
{
	char buf[2];
	buf[0] = c;
	buf[1] = 0;
	std::string ss(buf);
	return ss;
}

void tokenize(string &str, string &delims, vector<int> &ll)
{
	std::string tok("");
	for(int i = 0; i < str.length(); i++)
	{
		std::string chr = to_string(str[i]);
		if(delims.find(chr) != std::string::npos)
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
		ll.push_back(std::stoi(tok));
}

//////////////////////////////////////////////////

class Point
{
public:
	Point() {}

	void set(int xx, int yy)
	{
		x = xx;
		y = yy;
	}

	void print()
	{
		cout << x << "," << y;
	}

	int x,y;
};

//////////////////////////////////////////////////

class Line
{
public:
	Line(string &ss)
	{
		string delims = ", ->";
		vector<int> ll;
		tokenize(ss, delims, ll);
		if(ll.size()==4)
		{
			p1.set(ll[0], ll[1]);
			p2.set(ll[2], ll[3]);
		}
	}

	void print()
	{
		 p1.print();
		 cout << " ";
		 p2.print();
		 cout << endl;
	}

	bool isHoriz()
	{
		if(p1.y == p2.y) return true;
		return false;
	}

	bool isVert()
	{
		if(p1.x == p2.x) return true;
		return false;
	}

	Point p1,p2;
};

//////////////////////////////////////////////////

vector<Line *> lines;

void readInput()
{
	mhr::ReadFile inf("input.txt");
	string ll;
	while(inf.readLine(ll))
	{
		if(ll.length() > 0)
		{
			Line *ln = new Line(ll);
			lines.push_back(ln);
		}
	}
	inf.close();
}

int getMaxX()
{
	int maxx = 0;
	for(int i = 0; i < lines.size(); i++)
	{
		if(lines[i]->p1.x > maxx) maxx = lines[i]->p1.x;
		if(lines[i]->p2.x > maxx) maxx = lines[i]->p2.x;
	}
	return maxx;
}

int getMaxY()
{
	int maxy = 0;
	for(int i = 0; i < lines.size(); i++)
	{
		if(lines[i]->p1.y > maxy) maxy = lines[i]->p1.y;
		if(lines[i]->p2.y > maxy) maxy = lines[i]->p2.y;
	}
	return maxy;
}

void calc(bool doDiags)
{
	int maxx = getMaxX();
	int maxy = getMaxY();

	vector<int> grid[1000];
	for(int x = 0; x <= maxx; x++)
	{
		for(int y = 0; y <= maxy; y++)
		{
			grid[x].push_back(0);
		}
	}

	for(int i = 0; i < lines.size(); i++)
	{
		if(lines[i]->isHoriz())
		{
			int x1 = lines[i]->p1.x;
			int x2 = lines[i]->p2.x;
			int y = lines[i]->p1.y;
			if(x1 > x2)
			{
				int tmp = x1;
				x1 = x2;
				x2 = tmp;
			}
			for(int x = x1; x <= x2; x++)
				grid[x][y] = grid[x][y] + 1;
		}
		else if(lines[i]->isVert())
		{
			int y1 = lines[i]->p1.y;
			int y2 = lines[i]->p2.y;
			int x = lines[i]->p1.x;
			if(y1 > y2)
			{
				int tmp = y1;
				y1 = y2;
				y2 = tmp;
			}
			for(int y = y1; y <= y2; y++)
				grid[x][y] = grid[x][y] + 1;
		}
		else if(doDiags)
		{
			int x1 = lines[i]->p1.x;
			int y1 = lines[i]->p1.y;
			int x2 = lines[i]->p2.x;
			int y2 = lines[i]->p2.y;
			int xinc = 1;
			int yinc = 1;
			if(x1 > x2)	xinc = -1;
			if(y1 > y2) yinc = -1;
			int x = x1;
			int y = y1;
			while(x != x2 && y != y2)
			{
				grid[x][y] = grid[x][y] + 1;
				x += xinc;
				y += yinc;
			}
			grid[x][y] = grid[x][y] + 1;
		}
	}

	int ans = 0;
	for(int x = 0; x <= maxx; x++)
	{
		for(int y = 0; y <= maxy; y++)
		{
			if(grid[x][y] > 1)
			{
				ans++;
			}
		}
	}

	if(!doDiags)
		cout << "PART1 answer = " << ans << endl;
	else
		cout << "PART2 answer = " << ans << endl;
}

int main()
{
	readInput();
	calc(false);
	calc(true);
	return 0;
}

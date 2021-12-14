#include"ReadFile.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::string;

void tokenize(string &str, string &delims, vector<string> &ll)
{
	string tok("");
	for(int i = 0; i < str.length(); i++)
	{
		string chr(1,str[i]);
		if(delims.find(chr) != string::npos)
		{
			if(tok.length() > 0)
			{
				if(tok != "fold" && tok != "along")
					ll.push_back(tok);
				tok = "";
			}
		}
		else
			tok += chr;
	}
	if(tok.length() > 0)
		ll.push_back(tok);
}

void readInput(vector<string> &lns)
{
	mhr::ReadFile inf("input.txt");
	string ln;
	while(inf.readLine(ln))
	{
		if(ln.size() > 0)
			lns.push_back(ln);
	}
	inf.close();
}

/////

class Fold
{
public:
	Fold(string xory, int value)
	{
		xy = xory;
		val = value;
	}
	void print() { cout << "fold " << xy << " = " << val << endl; }
	string xy;
	int val;
};

/////

class Dot
{
public:
	Dot(int xx, int yy)
	{
		x = xx;
		y = yy;
	}
	void print() { cout << "x = " << x << " y =" << y << endl; }
	int x, y;
};

/////

int grid[900][1350];
int maxx = 0;
int maxy = 0;

void initGrid()
{
	for(int y = 0; y < 900; y++)
		for(int x = 0; x < 1350; x++)
			grid[y][x] = 0;
}

int countGrid()
{
	int cnt = 0;
	for(int y = 0; y < maxy; y++)
		for(int x = 0; x < maxx; x++)
			if(grid[y][x] == 1) cnt++;
	return cnt;
}

void printGrid(int ycnt, int xcnt)
{
	cout << "-------------------------" << endl;
	for(int y = 0; y < ycnt; y++)
	{
		if(y < 10) cout << " ";
		cout << y << " ";
		for(int x = 0; x < xcnt; x++)
		{
			if(grid[y][x] == 1)
				cout << "#";
			else
				cout << ".";
		}
		cout << endl;
	}
}

void foldY(int &maxy, int maxx, int yy)
{
	int r1 = 0;
	int r2 = maxy - 1;
	while(true)
	{
		for(int i = 0; i < maxx; i++)
			if(grid[r1][i] == 1 || grid[r2][i] == 1)
				grid[r1][i] = 1;
		r1++;
		r2--;
		if(r1 == yy) break;
	}
	maxy = yy;
}

void foldX(int maxy, int &maxx, int xx)
{
	int c1 = 0;
	int c2 = maxx -1;
	while(true)
	{
		for(int i = 0; i < maxy; i++)
			if(grid[i][c1] == 1 || grid[i][c2] == 1)
				grid[i][c1] = 1;
		c1++;
		c2--;
		if(c1 == xx) break;
	}
	maxx = xx;
}

/////

int main()
{
	vector<string> lns;
	readInput(lns);

	vector<Dot *> dots;
	vector<Fold *> folds;

	initGrid();

	string delims = ", =";
	for(string ln : lns)
	{
		vector<string> ll;
		tokenize(ln, delims, ll);

		if(ll[0] == "x" || ll[0] == "y")
		{
			int v = std::stoi(ll[1]);
			Fold *f = new Fold(ll[0], v);
			folds.push_back(f);
		}
		else
		{
			int x = std::stoi(ll[0]);
			int y = std::stoi(ll[1]);
			if(x > maxx) maxx = x;
			if(y > maxy) maxy = y;
			Dot *d = new Dot(x, y);
			dots.push_back(d);
		}
	}

	maxx++;
	maxy++;

	for(Dot *d : dots)
		grid[d->y][d->x] = 1;

	Fold *f = folds[0];
	if(f->xy == "x")
		foldX(maxy, maxx, f->val);
	else
		foldY(maxy, maxx, f->val);

	int cnt = countGrid();
	cout << "PART1 answer = " << cnt << endl;

	///

	for(int i = 1; i < folds.size(); i++)
	{
		Fold *f = folds[i];
		if(f->xy == "x")
			foldX(maxy, maxx, f->val);
		else
			foldY(maxy, maxx, f->val);
	}

	cout << "PART2 answer:" << endl;
	printGrid(maxy, maxx);
}

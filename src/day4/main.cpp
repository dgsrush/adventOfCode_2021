#include"ReadFile.h"
#include<iostream>
#include<vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

class Board
{
public:
	Board() {}

	void add(vector<int> &ll)
	{
		int ii = 0;
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				brd[i][j] = ll[ii];
				marked[i][j] = false;
				ii++;
			}
		}
	}

	void print()
	{
		cout << "*******" << endl;
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				cout << brd[i][j];
				if(marked[i][j])
					cout << "*";
				else
					cout << " ";
				cout << " ";
			}
			cout << endl;
		}
		if(isBingo()) cout << "BINGO" << endl;
	}

	int calc()
	{
		int total = 0;
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				if(!marked[i][j])
					total += brd[i][j];
			}
		}
		return total;
	}

	void call(int num)
	{
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				if(brd[i][j] == num)
				{
					marked[i][j] = true;
					break;
				}
			}
		}
	}

	void reset()
	{
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				marked[i][j] = false;
			}
		}
	}

	bool isBingo()
	{
		for(int i = 0; i < 5; i++)
		{
			if(marked[i][0] && marked[i][1] && marked[i][2] && marked[i][3] && marked[i][4]) return true;
			if(marked[0][i] && marked[1][i] && marked[2][i] && marked[3][i] && marked[4][i]) return true;
		}
		return false;
	}

private:
	int brd[5][5];
	bool marked[5][5];
};

vector<int> randm;
vector<Board *> boards;

string to_string(char c)
{
	char buf[2];
	buf[0] = c;
	buf[1] = 0;
	std::string ss(buf);
	return ss;
}

void tokenize(string &str, string &delims, std::vector<int> &ll)
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

void readInput()
{
	mhr::ReadFile inf("input.txt");
	string ll;

	//parse bingo calls
	inf.readLine(ll);
	string delim = ",";
	tokenize(ll, delim, randm);

	//parse bingo boards
	delim = " ";
	while(inf.readLine(ll))
	{
		if(ll.length() > 0)
		{
			vector<int> brd;
			tokenize(ll, delim, brd);
			for(int i = 0; i < 4; i++)
			{
				inf.readLine(ll);
				tokenize(ll, delim, brd);
			}
			Board *b = new Board();
			b->add(brd);
			boards.push_back(b);
		}
	}
	inf.close();
}

void call(int num)
{
	for(Board *b : boards)
		b->call(num);
}

void part1()
{
	readInput();

	for(int r : randm)
	{
		call(r);
		for(Board *b : boards)
		{
			if(b->isBingo())
			{
				b->print();
				int total = b->calc();
				cout << "PART1 total      = " << total << endl;
				cout << "PART1 final call = " << r << endl;
				cout << "PART1 answer     = " << total * r << endl;
				return;
			}
		}
	}
}

void part2()
{
	for(Board *b : boards)
		b->reset();

	Board *final = NULL;
	int finalr = 0;
	for(int r : randm)
	{
		call(r);

		int cnt = 0;
		for(Board *b : boards)
			if(b->isBingo()) cnt++;

		if(final == NULL && cnt == (boards.size()-1))
		{
			for(Board *b : boards)
				if(!b->isBingo())
					final = b;
		}
		if(cnt == boards.size())
		{
			finalr = r;
			break;
		}
	}

	final->print();
	int total = final->calc();
	cout << "PART2 total      = " << total << endl;
	cout << "PART2 final call = " << finalr << endl;
	cout << "PART2 answer     = " << total * finalr << endl;
}

int main()
{
	part1();
	part2();
	for(Board *p : boards)
		delete p;
	return 0;
}

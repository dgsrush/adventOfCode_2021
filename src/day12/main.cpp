#include"ReadFile.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<set>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;
using std::set;

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

string toLower(string &ss)
{
	string ret;
	std::locale loc;
	for(auto elem : ss)
		ret += std::tolower(elem, loc);
	return ret;
}

/////

class Node
{
public:
	Node(string n)
	{
		name = n;
		if(name == toLower(name))
			small = true;
		else
			small = false;
	}

	void addChild(Node *child) { c.push_back(child); }

	string getName() { return name; }
	bool isSmall() { return small; }
	bool isBig() { return !small; }
	bool isStart() { return name == "start"; }
	bool isEnd() { return name == "end"; }
	void print() { cout << "NODE " << name << " small=" << small << " csize=" << c.size() << endl; }

    vector<Node *> c;

private:
    string name;
    bool small;
};

/////

unordered_map<string,Node *> nodes;

Node * getNode(string name)
{
	unordered_map<string,Node *>::iterator it = nodes.find(name);
	if(it == nodes.end()) return NULL;
	return it->second;
}

Node * getStart()
{
	string name = "start";
	return getNode(name);
}

/////

int ans = 0;

void part1(Node *n, set<string> vst)
{
	string name = n->getName();
	vst.insert(name);
	if(n->isEnd()) { ans++; return; }
	int cnt = n->c.size();
	for(int i = 0; i < cnt; i++)
	{
		Node *nn = n->c[i];
		string nam = nn->getName();
		if(nn->isBig())
			part1(nn, vst);
		else if(nn->isSmall() && vst.count(nam) == 0)
			part1(nn, vst);
	}
}

/////

void part2(Node *n, set<string> vst, bool rv)
{
	string name = n->getName();
	vst.insert(name);
	if(n->isEnd()) { ans++; return; }
	int cnt = n->c.size();
	for(int i = 0; i < cnt; i++)
	{
		Node *nn = n->c[i];
		string nam = nn->getName();
		if(nn->isBig())
			part2(nn, vst, rv);
		else if(nn->isSmall() && vst.count(nam) == 0)
			part2(nn, vst, rv);
		else if(!rv && !nn->isStart())
			part2(nn, vst, true);
	}
}

/////

int main()
{
	vector<string> lns;
	readInput(lns);

	string delims = "-";
	for(string ln : lns)
	{
		vector<string> tkns;
		tokenize(ln, delims, tkns);
		string p = tkns[0];
		string c = tkns[1];

		Node *np = getNode(p);
		if(np == NULL)
		{
			np = new Node(p);
			nodes[p] = np;
		}
		Node *nc = getNode(c);
		if(nc == NULL)
		{
			nc = new Node(c);
			nodes[c] = nc;
		}
		np->addChild(nc);
		nc->addChild(np);
	}

	set<string> vst;
	part1(getStart(), vst);
	cout << "PART1 answer = " << ans << endl;

	///

	ans = 0;
	part2(getStart(), vst, false);
	cout << "PART2 answer = " << ans << endl;

	for(auto it = nodes.begin(); it != nodes.end(); ++it)
		delete it->second;
	nodes.clear();
}

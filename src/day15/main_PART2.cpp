#include"ReadFile.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<bits/stdc++.h>

#define INF 0x3f3f3f3f

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::make_pair;
using std::pair;
using std::priority_queue;
using std::greater;

void tokenize(string &str, string &delims, vector<string> &ll)
{
	string tok("");
	for(int i = 0; i < str.length(); i++)
	{
		string chr(1, str[i]);
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

void readInput(vector<string> &lns)
{
	//mhr::ReadFile inf("sample_input.txt");
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

typedef pair<int,int> Pair;
int V = 250000;
vector<vector<Pair>> adj(V);

void getPath()
{
	//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
	int src = 0;
	priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
	vector<int> dist(V, INF);
	pq.push(make_pair(0, src));
	dist[src] = 0;

	while(!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		for(auto x : adj[u])
		{
			int v = x.first;
			int weight = x.second;
			if(dist[v] > dist[u] + weight)
			{
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}
	printf("answer = %d\n", dist[V-1]);
}

/////

int weights[500][500];

void printWeights()
{
	for(int y = 0; y < 500; y++)
	{
		for(int x = 0; x < 500; x++)
		{
			if(x==100||x==200||x==300||x==400) cout << ",";
			cout << weights[y][x];
		}
		if(y==99||y==199||y==299||y==399) cout << endl;
		cout << endl;
	}
}

/////

int main()
{
	vector<string> lns;
	readInput(lns);

	int y = 0;
	for(string ln : lns)
	{
		int x = 0;
		for(char c : ln)
		{
			int v0 = (int)c - 48;
			int v1 = v0 + 1; if(v1 > 9) v1 = 1;
			int v2 = v1 + 1; if(v2 > 9) v2 = 1;
			int v3 = v2 + 1; if(v3 > 9) v3 = 1;
			int v4 = v3 + 1; if(v4 > 9) v4 = 1;
			int v5 = v4 + 1; if(v5 > 9) v5 = 1;
			int v6 = v5 + 1; if(v6 > 9) v6 = 1;
			int v7 = v6 + 1; if(v7 > 9) v7 = 1;
			int v8 = v7 + 1; if(v8 > 9) v8 = 1;

			weights[y][x] = v0;

			weights[y][x + 100] = v1;
			weights[y][x + 200] = v2;
			weights[y][x + 300] = v3;
			weights[y][x + 400] = v4;

			weights[y + 100][x] = v1;
			weights[y + 200][x] = v2;
			weights[y + 300][x] = v3;
			weights[y + 400][x] = v4;

			weights[y + 100][x + 100] = v2;
			weights[y + 200][x + 100] = v3;
			weights[y + 300][x + 100] = v4;
			weights[y + 400][x + 100] = v5;

			weights[y + 100][x + 200] = v3;
			weights[y + 200][x + 200] = v4;
			weights[y + 300][x + 200] = v5;
			weights[y + 400][x + 200] = v6;

			weights[y + 100][x + 300] = v4;
			weights[y + 200][x + 300] = v5;
			weights[y + 300][x + 300] = v6;
			weights[y + 400][x + 300] = v7;

			weights[y + 100][x + 400] = v5;
			weights[y + 200][x + 400] = v6;
			weights[y + 300][x + 400] = v7;
			weights[y + 400][x + 400] = v8;

			x++;
		}
		y++;
	}
	//printWeights();

	int u = 0;
	for(int y = 0; y < 500; y++)
	{
		for(int x = 0; x < 500; x++)
		{
			if((y-1) >=   0) adj[u].push_back(make_pair(u - 500, weights[y - 1][x]));
			if((y+1) <= 499) adj[u].push_back(make_pair(u + 500, weights[y + 1][x]));
			if((x-1) >=   0) adj[u].push_back(make_pair(u - 1, weights[y][x - 1]));
			if((x+1) <= 499) adj[u].push_back(make_pair(u + 1, weights[y][x + 1]));
			u++;
		}
	}

	getPath();
}

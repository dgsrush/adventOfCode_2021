#include"ReadFile.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

using std::cout;
using std::endl;
using std::vector;
using std::string;

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

void getPath(vector<Pair> adj[], int V, int src)
{
	//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/

	priority_queue< Pair, vector <Pair> ,greater<Pair> > pq;
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
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < V; ++i)
		printf("%d \t\t %d\n", i, dist[i]);
}

/////

void addEdge(vector<Pair> adj[], int u, int v, int wt)
{
	adj[u].push_back(make_pair(v, wt));
}

/////

int weights[100][100];

void printWeights()
{
	for(int y = 0; y < 100; y++)
	{
		for(int x = 0; x < 100; x++)
			cout << weights[y][x];
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
			weights[y][x] = (int)c-48;
			x++;
		}
		y++;
	}

	int V = 10000;
	vector<Pair> adj[V];
	int u = 0;
	for(int y = 0; y < 100; y++)
	{
		for(int x = 0; x < 100; x++)
		{
			if((y-1) >=  0) addEdge(adj, u, u-100, weights[y-1][x]);
			if((y+1) <= 99) addEdge(adj, u, u+100, weights[y+1][x]);
			if((x-1) >=  0) addEdge(adj, u, u-1, weights[y][x-1]);
			if((x+1) <= 99) addEdge(adj, u, u+1, weights[y][x+1]);
			u++;
		}
	}
	getPath(adj, V, 0);
}

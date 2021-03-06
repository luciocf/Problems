// CEOI 2015 - Potemkin Cycle
// Lúcio Cardoso

// Solution:

// 1. For each edge (u, v) in the graph, create two nodes in a new graph: One node representes
// the edge u->v and the other one, v->u. Now, for each triple (u, v, w) of vertices in the original graph such that
// u is connected to v, and v is connected to w, connect vertices (u->v) with (v->w) iff u is not connected with w.
// This way, a cycle in the new graph is a cycle in the original graph and there are no 3-size cycles.

// 2. Thus, if there is a cycle in the new graph, there is an answer. To find such an answer, run a dfs in the new graph
// and print the cycle formed by the first back edge found. This way, we can assure that the conditions of the statement
// are satisfied.

// Complexity: O(nm)

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e3+10;
const int maxm = 2e5+10;

typedef pair<int, int> pii;

int n, m;
int mat[maxn][maxn];

int pai[maxn], iniCycle, fimCycle;
int mark[maxm];

pii edge[maxm];

vector<pii> grafo[maxn];
vector<int> grafo2[maxm], grafo3[maxn];

void dfs(int u, int p)
{
	mark[u] = 1;

	for (auto v: grafo2[u])
	{
		if (!iniCycle && mark[v] == 1)
		{
			iniCycle = v, fimCycle = u;
			break;
		}

		if (!mark[v]) 
		{
			pai[v] = u;
			dfs(v, u);
		}
	}

	mark[u] = 2;
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		mat[u][v] = mat[v][u] = 1;
		edge[i] = {u, v};

		grafo[u].push_back({v, i});
		grafo[v].push_back({u, i+m});
	}

	for (int i = 1; i <= m; i++)
	{
		int u = edge[i].first, v = edge[i].second;

		for (auto pp: grafo[v])
		{
			int w = pp.first, e = pp.second;

			if (w != u && w != v && !mat[w][u])
				grafo2[i].push_back(e);
		}

		for (auto pp: grafo[u])
		{
			int w = pp.first, e = pp.second;

			if (w != u && w != v && !mat[w][v])
				grafo2[i+m].push_back(e);
		}
	}

	for (int i = 1; i <= 2*m; i++)
	{
		if (!mark[i])
			dfs(i, 0);

		if (iniCycle) break;
	}

	if (!iniCycle)
	{
		printf("no\n");
		return 0;
	}

	int at = fimCycle;

	int aux = 0;

	vector<int> ciclo;

	while (true)
	{
		if (at > m)
			ciclo.push_back(edge[at-m].second);
		else
			ciclo.push_back(edge[at].first);

		if (at == iniCycle) break;

		at = pai[at];
	}

	for (auto c: ciclo)
		printf("%d ", c);
	printf("\n");
}

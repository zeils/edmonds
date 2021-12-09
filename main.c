/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>


const int MAXN = 10; // максимально возможное число вершин во входном графе
 
int n;
vector<int> g[MAXN];
int match[MAXN], p[MAXN], base[MAXN], q[MAXN];
bool used[MAXN], blossom[MAXN];
int graph[MAXN][MAXN];



int lca (int a, int b) {
	bool used[MAXN] = { 0 };
	// поднимаемся от вершины a до корня, помечая все чётные вершины
	for (;;) {
		a = base[a];
		used[a] = true;
		if (match[a] == -1)  break; // дошли до корня
		a = p[match[a]];
	}
	// поднимаемся от вершины b, пока не найдём помеченную вершину
	for (;;) {
		b = base[b];
		if (used[b])  return b;
		b = p[match[b]];
	}
}

void mark_path (int v, int b, int children) {
	while (base[v] != b) {
		blossom[base[v]] = blossom[base[match[v]]] = true;
		p[v] = children;
		children = match[v];
		v = p[match[v]];
	}
}

int find_path (int root) {
	memset (used, 0, sizeof used);
	memset (p, -1, sizeof p);
	for (int i=0; i<n; ++i)
		base[i] = i;
 
	used[root] = true;
	int qh=0, qt=0;
	q[qt++] = root;
	while (qh < qt) {
		int v = q[qh++];
		for (size_t i=0; i<g[v].size(); ++i) {
			int to = g[v][i];
			if (base[v] == base[to] || match[v] == to)  continue;
			if (to == root || match[to] != -1 && p[match[to]] != -1) {
				int curbase = lca (v, to);
				memset (blossom, 0, sizeof blossom);
				mark_path (v, curbase, to);
				mark_path (to, curbase, v);
				for (int i=0; i<n; ++i)
					if (blossom[base[i]]) {
						base[i] = curbase;
						if (!used[i]) {
							used[i] = true;
							q[qt++] = i;
						}
					}
			}
			else if (p[to] == -1) {
				p[to] = v;
				if (match[to] == -1)
					return to;
				to = match[to];
				used[to] = true;
				q[qt++] = to;
			}
		}
	}
	return -1;
}


int main()
{
    
   for (int i = 0; i < MAXN; i++ )
   {
       while not (row != column and graph[row][column] == MAXN)
       {
           row = rand(0,MAXN);
           column = rand(0,MAXN-1);
       }
       graph[row][column] = rand(0,1);
   }
    

   memset (match, -1, sizeof match);
	for (int i=0; i<n; ++i)
		if (match[i] == -1) {
			int v = find_path (i);
			while (v != -1) {
				int pv = p[v],  ppv = match[pv];
				match[v] = pv,  match[pv] = v;
				v = ppv;
			}
		}
    return 0;
}

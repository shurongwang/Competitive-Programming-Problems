#include "supertrees.h"
#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e3;
bool vis[nsz + 5];
int n, dis[nsz + 5][nsz + 5];
vector<vector<int>> b;

void inline link(int u, int v) {
	if (u == v) return;
	--u, --v;
	b[u][v] = b[v][u] = 1;
}

void inline bfs(int s, vector<int> &nd) {
	static int q[nsz + 5];
	int ql = 0, qr = 0;
	for (q[qr++] = s, vis[s] = 1; ql != qr;) {
		int u = q[ql++];
		nd.push_back(u);
		cont (v, n) if (dis[u][v] && !vis[v]) {
			q[qr++] = v, vis[v] = 1;
		}
	}
}

bool inline solve(const vector<int> &nd) {
	static bool vis[nsz + 5];
	for (int u : nd) for (int v : nd) if (dis[u][v] == 0 || dis[u][v] == 3) return 0;
	vector<vector<int>> c;
	for (int u : nd) {
		if (vis[u]) continue;
		c.push_back({});
		for (int v : nd) if (dis[u][v] == 1) c.back().push_back(v), vis[v] = 1;
	}
	for (vector<int> &d : c) {
		for (int u : d) for (int v : d) if (dis[u][v] != 1) return 0;
		for (int u : d) {
			int cnt = 0;
			cont (v, n) cnt += dis[u][v] == 2;
			if (cnt != nd.size() - d.size()) return 0;
		}
	}
	if (c.size() == 2) return 0;
	
	for (vector<int> &d : c) {
		int p = d[0];
		for (int u : d) link(p, u);
	}
	loop (i, int(c.size()) - 1) {
		link(c[i][0], c[i + 1][0]);
	}
	if (c.size() > 1) link(c[0][0], c.back()[0]);
	return 1;
}

int construct(vector<vector<int>> p) {
	n = int(p.size());
	b.resize(n, vector<int>(n, 0));
	loop (i, n) loop (j, n) dis[i + 1][j + 1] = p[i][j];
	cont (u, n) if (!vis[u]) {
		vector<int> nd;
		bfs(u, nd);
		if (!solve(nd)) return 0;
	}
	build(b);
	return 1;
}
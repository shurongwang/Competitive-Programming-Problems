#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e2, ndsz = nsz * nsz * 2 + 2, egsz = nsz * nsz * 7;
const int del = 5e4, inf = 1e9, dx[4] = {-1, 0, 0, +1}, dy[4] = {0, -1, +1, 0};
char s[nsz + 5][nsz + 5];
int n, ans, in[nsz + 5][nsz + 5], out[nsz + 5][nsz + 5];
int sz, src, snk, d[ndsz + 5], cur[ndsz + 5];

struct graph {
	int sz, hd[ndsz + 5];
	
	struct edge {
		int nxt, to, f;
		
		edge() {}
		edge(int nxt, int to, int f): nxt(nxt), to(to), f(f) {}
	} e[2 * egsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v, int f) {
		e[++sz] = edge(hd[u], v, f), hd[u] = sz;
		e[++sz] = edge(hd[v], u, 0), hd[v] = sz;
	}
};
graph g;

int inline rev(int id) { return id & 1 ? ++id : --id; }

bool inline bfs() {
	static int q[ndsz + 5];
	int ql = 0, qr = 0;
	cont (u, sz) d[u] = -1, cur[u] = g.hd[u];
	for (d[q[qr++] = src] = 0; ql != qr;) {
		int u = q[ql++];
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to, f = g[i].f;
			if (d[v] != -1 || !f) continue;
			d[q[qr++] = v] = d[u] + 1;
		}
	}
	return d[snk] > 0;
}

int dfs(int u = src, int mf = inf) {
	if (u == snk) return mf;
	int res = 0;
	for (int &i = cur[u]; i; i = g[i].nxt) {
		int v = g[i].to, f = g[i].f;
		if (d[v] != d[u] + 1 || !f) continue;
		int cur = dfs(v, min(mf - res, f));
		if (cur) {
			g[i].f -= cur, g[rev(i)].f += cur, res += cur;
			if (res == mf) break;
		}
	}
	return res;
}

int inline max_flow() {
	int res = 0;
	for (; bfs(); res += dfs());
	return res;
}

void inline graph_init() {
	src = ++sz, snk = ++sz;
	cont (i, n) cont (j, n) in[i][j] = ++sz, out[i][j] = ++sz;
	cont (i, n) cont (j, n) loop (d, 4) {
		int x = i + dx[d], y = j + dy[d];
		if (x < 1 || x > n || y < 1 || y > n) continue;
		g.link(in[i][j], out[x][y], 1);
	}
	cont (i, n) cont (j, n) {
		char c = s[i][j];
		if ((i + j) & 1) {
			if (c != 'W') g.link(src, in[i][j], c == 'B' ? inf : del);
			if (c != 'B') g.link(out[i][j], snk, c == 'W' ? inf : del);
		} else {
			if (c != 'W') g.link(out[i][j], snk, c == 'B' ? inf : del);
			if (c != 'B') g.link(src, in[i][j], c == 'W' ? inf : del);
		}
		if (c == '?') g.link(in[i][j], out[i][j], del);
	}
}

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%s", s[i] + 1);
	graph_init();
	ans = 2 * n * (n - 1) - max_flow() % del;
	printf("%d\n", ans);
}
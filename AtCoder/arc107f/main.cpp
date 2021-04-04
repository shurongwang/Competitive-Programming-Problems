#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 3e2, msz = 3e2;
const int ndsz = 2 * nsz + 2, egsz = 3 * nsz + 2 * msz;
const int inf = 0x3f3f3f3f;
int n, m, a[nsz + 5], b[nsz + 5], ans;
int sz, src, snk, in[nsz + 5], out[nsz + 5], cur[ndsz + 5], d[ndsz + 5];
vector<int> nei[nsz + 5];

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
	int ql, qr = 0;
	cont (u, sz) cur[u] = g.hd[u], d[u] = -1;
	for (q[qr++] = src, d[src] = 0; ql != qr;) {
		int u = q[ql++];
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to, f = g[i].f;
			if (d[v] != -1 || !f) continue;
			q[qr++] = v, d[v] = d[u] + 1;
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
	cont (i, n) in[i] = ++sz, out[i] = ++sz;
	cont (i, n) {
		int w = abs(b[i]), w2 = w << 1;
		g.link(in[i], out[i], w + a[i]);
		if (b[i] < 0) g.link(src, in[i], w2);
		if (b[i] > 0) g.link(out[i], snk, w2);
	}
	cont (u, n) {
		loop (i, nei[u].size()) {
			int v = nei[u][i];
			g.link(out[u], in[v], inf);
		}
	}
}

void inline solve() {
	cont (i, n) ans += abs(b[i]);
	graph_init();
	ans -= max_flow();
	printf("%d\n", ans);
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n) scanf("%d", &a[i]);
	cont (i, n) scanf("%d", &b[i]);
	cont (i, m) {
		int u, v;
		scanf("%d%d", &u, &v);
		nei[u].push_back(v), nei[v].push_back(u);
	}
	solve();
}
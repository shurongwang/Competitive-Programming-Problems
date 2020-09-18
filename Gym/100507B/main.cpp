#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5;
const int inf = 0x3f3f3f3f;
bool est[nsz + 5];
int ts, n, m, sz, sc, src, a[nsz + 5], w[nsz + 5], val[nsz + 5];
int d[nsz + 5], in[nsz + 5], out[nsz + 5], sid[nsz + 5];
int dfn[nsz + 5], low[nsz + 5], vis[nsz + 5];
vector<int> nd;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge() {}
		edge(int nxt, int to) {
			this->nxt = nxt, this->to = to;
		}
	} e[nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	inline edge operator [] (int id) const { return e[id]; }
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
	}
};
graph ig, g, ng;

void inline find_reachable(const graph &g = ig) {
	static int q[nsz + 5];
	int ql = 0, qr = 0;
	q[qr++] = 1, est[1] = 1;
	for (; ql != qr;) {
		int u = q[ql++];
		nd.push_back(u);
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to;
			if (!est[v]) q[qr++] = v, est[v] = 1;
		}
	}
}

void inline graph_init() {
	loop (i, nd.size()) {
		int u = nd[i];
		in[u] = ++sz, out[u] = ++sz;
		w[in[u]] = -1, w[out[u]] = a[u] ? a[u] : -1;
	}
	loop (i, nd.size()) {
		int u = nd[i];
		if (a[u] == 0) g.link(in[u], out[u]);
		for (int i = ig.hd[u]; i; i = ig[i].nxt) {
			int v = ig[i].to;
			g.link(out[u], in[v]);
		}
	}
	src = ++sz, w[src] = 0;
	g.link(src, in[1]);
}

void tarjan(int u) {
	static int t, ss, stk[nsz + 5];
	dfn[u] = low[u] = ++t;
	stk[ss++] = u, vis[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (vis[v] == 2) continue;
		if (!vis[v]) tarjan(v);
		low[u] = min(low[u], low[v]);
	}
	if (dfn[u] != low[u]) return;
	++sc, val[sc] = -1;
	for (int v = -1; v != u;) {
		v = stk[--ss];
		vis[v] = 2, sid[v] = sc, val[sc] = max(val[sc], w[v]);
	}
}

void inline upd(int &a, int b) {
	if (a == -1) a = b;
	else if (a != b) a = inf;
}

void inline topological_solve(const graph &g = ng) {
	static int q[nsz + 5], d[nsz + 5];
	int ql = 0, qr = 0;
	cont (u, sc) if (val[u] != -1) q[qr++] = u;
	cont (u, sc) {
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to;
			++d[v];
		}
	}
	
	for (; ql != qr;) {
		int u = q[ql++];
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to;
			upd(val[v], val[u]);
			if (--d[v] == 0) q[qr++] = v;
		}
	}
}

void inline print(int a, char c) {
	if (a == 0) printf("sober%c", c);
	else if (a == inf) printf("unknown%c", c);
	else printf("%d%c", a, c);
}

int main() {
	scanf("%d", &n);
	cont (u, n) {
		int sz;
		scanf("%d%d", &a[u], &sz);
		cont (i, sz) {
			int v;
			scanf("%d", &v);
			ig.link(u, v);
		}
	}
	find_reachable();
	graph_init();
	cont (u, sz) if (!sid[u]) tarjan(u);
	cont (u, sz) {
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to, su = sid[u], sv = sid[v];
			if (su == sv) continue;
			ng.link(su, sv);
		}
	}
	topological_solve();
	cont (u, n) {
		if (!est[u]) printf("whatever whatever\n");
		else print(val[sid[in[u]]], ' '), print(val[sid[out[u]]], ln);
	}
}
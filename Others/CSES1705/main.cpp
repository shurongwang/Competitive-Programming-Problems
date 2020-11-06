#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5, msz = 2e5;
bool tp[nsz + 5];
int n, m, q, sz;
int dfn[nsz + 5], low[nsz + 5];
int rt = 1, siz[nsz + 5], pr[nsz + 5], dep[nsz + 5], hs[nsz + 5], top[nsz + 5];

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge() {}
		edge(int nxt, int to) {
			this->nxt = nxt, this->to = to;
		}
	} e[2 * msz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
		e[++sz] = edge(hd[v], u), hd[v] = sz;
	}
};
graph g, tr;

void tarjan(int u = rt, int p = -1) {
	static int t, ss, stk[nsz + 5];
	stk[ss++] = u, dfn[u] = low[u] = ++t;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (!dfn[v]) tarjan(v, u), low[u] = min(low[u], low[v]);
		else low[u] = min(low[u], dfn[v]);
	}
	if (p == -1 || low[u] != dfn[p]) return;
	++sz;
	for (int v = -1; v != u; --ss) {
		v = stk[ss - 1];
		tr.link(v, sz);
	}
	tr.link(p, sz);
}

void dfs1(int u = rt) {
	siz[u] = 1;
	for (int i = tr.hd[u]; i; i = tr[i].nxt) {
		int v = tr[i].to;
		if (v == pr[u]) continue;
		pr[v] = u, dep[v] = dep[u] + 1;
		dfs1(v);
		siz[u] += siz[v];
		if (siz[hs[u]] < siz[v]) hs[u] = v;
	}
}

void dfs2(int u = rt, int tp = rt) {
	static int t = 0;
	dfn[u] = ++t, top[u] = tp;
	if (!hs[u]) return;
	dfs2(hs[u], tp);
	for (int i = tr.hd[u]; i; i = tr[i].nxt) {
		int v = tr[i].to;
		if (v == pr[u] || v == hs[u]) continue;
		dfs2(v, v);
	}
}

bool inline in(int l, int r, int k) { return l <= k && k <= r; }

bool inline in_route(int u, int v, int p) {
	for (; top[u] != top[v]; v = pr[top[v]]) {
		if (dep[top[u]] > dep[top[v]]) swap(u, v);
		if (in(dfn[top[v]], dfn[v], dfn[p])) return 1;
	}
	if (dep[u] > dep[v]) swap(u, v);
	return in(dfn[u], dfn[v], dfn[p]);
}

void inline tree_init() {
	sz = n;
	tarjan();
	dfs1(), dfs2();
}

int main() {
	scanf("%d%d%d", &n, &m, &q);
	cont (i, m) {
		int u, v;
		scanf("%d%d", &u, &v);
		g.link(u, v);
	}
	tree_init();
	cont (i, q) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		printf(!in_route(a, b, c) ? "YES\n" : "NO\n");
	}
}
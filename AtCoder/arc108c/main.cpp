#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5, msz = 2e5;
bool vis[nsz + 5];
int n, m, rt = 1, pr[nsz + 5], dep[nsz + 5], dfn[nsz + 5], fm[nsz + 5], c[nsz + 5], ans[nsz + 5];
set<int> est;

struct union_find {
	int pr[nsz + 5];
	
	void inline init() {
		cont (u, n) pr[u] = u;
	}
	
	int qry(int u) {
		return u == pr[u] ? u : pr[u] = qry(pr[u]);
	}
	
	bool inline link(int u, int v) {
		u = qry(u), v = qry(v);
		if (u == v) return 0;
		pr[v] = u;
		return 1;
	}
};
union_find uf;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to, w;
		
		edge() {}
		edge(int nxt, int to, int w): nxt(nxt), to(to), w(w) {}
	} e[2 * nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v, int w) {
		e[++sz] = edge(hd[u], v, w), hd[u] = sz;
		e[++sz] = edge(hd[v], u, w), hd[v] = sz;
	}
};
graph g;

struct edge {
	int u, v, w;
	
	edge() {}
	edge(int u, int v, int w): u(u), v(v), w(w) {}
};
edge e[msz + 5];

void inline tree_init() {
	uf.init();
	cont (i, m) {
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (uf.link(u, v)) g.link(u, v, w);
	}
}

void dfs(int u = rt) {
	static int t;
	dfn[u] = ++t, fm[t] = u;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to, w = g[i].w;
		if (v == pr[u]) continue;
		pr[v] = u, c[v] = w;
		dfs(v);
	}
}

void set_component(int u, int w, bool d = 1) {
	vis[u] = 1;
	if (d) ans[u] = w;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u] || c[v] != w) continue;
		set_component(v, w, d ^ 1);
	}
}

void inline set_unkown(int u) {
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int w = g[i].w;
		est.erase(w);
	}
	ans[u] = *est.begin();
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int w = g[i].w;
		est.insert(w);
	}
}

void solve() {
	dfs();
	circ (t, 2, n) if (!vis[fm[t]]) {
		int u = fm[t];
		set_component(u, c[u]);
	}
	cont (i, n) est.insert(i);
	cont (u, n) if (!ans[u]) {
		set_unkown(u);
	}
	cont (u, n) printf("%d\n", ans[u]);
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, m) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[i] = edge(u, v, w);
	}
	tree_init();
	solve();
}
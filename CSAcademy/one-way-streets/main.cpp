#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5;
int n, m, k, sc, to[nsz + 5], w[nsz + 5];
int vis[nsz + 5], dfn[nsz + 5], low[nsz + 5], sid[nsz + 5];
int rt = 1, pr[nsz + 5], siz[nsz + 5], dep[nsz + 5], hs[nsz + 5], top[nsz + 5], id[nsz + 5];
pair<int, int> e[nsz + 5];
set< pair<int, int> > est;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to, id;
		
		edge() {}
		edge(int nxt, int to, int id = 0): nxt(nxt), to(to), id(id) {}
	} e[2 * nsz * 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v, int id = 0) {
		e[++sz] = edge(hd[u], v, id), hd[u] = sz;
		e[++sz] = edge(hd[v], u, id), hd[v] = sz;
	}
	
	void inline clear(int n) {
		cont (u, n) hd[u] = 0;
		sz = 0; 
	}
};
graph g;

int inline rev(int id) { return id & 1 ? ++id : --id; }

void tarjan(int u, int p = -1) {
	static int stk[nsz + 5], ss, t;
	stk[ss++] = u, dfn[u] = low[u] = ++t, vis[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (vis[v] == 2 || rev(i) == p) continue;
		if (!vis[v]) tarjan(v, i);
		low[u] = min(low[u], low[v]);
	}
	if (dfn[u] != low[u]) return;
	++sc;
	for (int v = -1; v != u; --ss) {
		v = stk[ss - 1];
		vis[v] = 2, sid[v] = sc;
	}
}

void dfs(int u) {
	vis[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u]) continue;
		pr[v] = u;
		dfs(v);
		w[u] += w[v];
	}
}

void inline forest_init() {
	cont (u, n) if (!vis[u]) tarjan(u);
	g.clear(n);
	cont (i, m) {
		int su = sid[e[i].first], sv = sid[e[i].second];
		if (su == sv || est.find(make_pair(su, sv)) != est.end()) continue;
		g.link(su, sv);
		est.insert(make_pair(su, sv)), est.insert(make_pair(sv, su));
	}
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, m) {
		int u, v;
		scanf("%d%d", &u, &v);
		g.link(u, v);
		e[i] = make_pair(u, v);
	}
	forest_init();
	scanf("%d", &k);
	cont (i, k) {
		int u, v, p;
		scanf("%d%d", &u, &v);
		++w[sid[u]], --w[sid[v]];
	}
	memset(vis, 0, sizeof(vis));
	cont (u, n) if (!vis[u]) dfs(u);
	cont (i, m) {
		bool f = 0;
		int u = e[i].first, v = e[i].second, su = sid[u], sv = sid[v];
		if (pr[sv] == su) swap(su, sv), f ^= 1;
		if (su == sv || !w[su]) printf("B");
		else f ^= w[su] < 0, printf(f ? "L" : "R");
	}
	printf("\n");
}
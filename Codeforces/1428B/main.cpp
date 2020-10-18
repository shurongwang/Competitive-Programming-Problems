#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 3e5;
int ts, n, ans;
int t, ss, sc, stk[nsz + 5], dfn[nsz + 5], low[nsz + 5], vis[nsz + 5], sid[nsz + 5], siz[nsz + 5];

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge() {}
		edge(int nxt, int to) {
			this->nxt = nxt, this->to = to;
		}
	} e[2 * nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline clear(int n) {
		cont (u, n) hd[u] = 0;
		sz = 0;
	}
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
	}
};
graph g;

void tarjan(int u) {
	dfn[u] = low[u] = ++t, stk[ss++] = u, vis[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (vis[v] == 2) continue;
		if (!vis[v]) tarjan(v);
		low[u] = min(low[u], low[v]);
	}
	if (dfn[u] != low[u]) return;
	++sc;
	for (int v = -1; v != u; --ss) {
		v = stk[ss - 1];
		vis[v] = 2, sid[v] = sc;
		++siz[sc];
	}
}

int inline nxt(int u) { return u == n ? 1 : u + 1; }

void inline solve() {
	scanf("%d\n", &n);
	cont (u, n) {
		char c;
		scanf("%c", &c);
		if (c == '<') g.link(nxt(u), u);
		else if (c == '>') g.link(u, nxt(u));
		else g.link(u, nxt(u)), g.link(nxt(u), u);
	}
	cont (u, n) if (!sid[u]) tarjan(u);
	cont (u, n) ans += siz[sid[u]] > 1;
	printf("%d\n", ans);
}

void inline clear() {
	cont (u, n) vis[u] = dfn[u] = low[u] = dfn[u] = sid[u] = 0;
	cont (u, sc) siz[u] = 0;
	ans = sc = ss = t = 0;
	g.clear(n);
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
		clear();
	}
}
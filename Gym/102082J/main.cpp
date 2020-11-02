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
int n, m, c[nsz + 5];
int rt = 1, pr[nsz + 5], dep[nsz + 5], siz[nsz + 5], hs[nsz + 5], top[nsz + 5], dfn[nsz + 5], fm[nsz + 5];

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
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
		e[++sz] = edge(hd[v], u), hd[v] = sz;
	}
};
graph g;

struct data_structure {
	set<int> s;
	int sum;
	
	int inline qry() { return s.size() ? sum / 2 : -1; }
};
data_structure d[nsz + 5];

void dfs1(int u = rt) {
	siz[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u]) continue;
		pr[v] = u, dep[v] = dep[u] + 1;
		dfs1(v);
		siz[u] += siz[v];
		if (siz[hs[u]] < siz[v]) hs[u] = v;
	}
}

void dfs2(int u = rt, int tp = rt) {
	static int t;
	dfn[u] = ++t, fm[t] = u, top[u] = tp;
	if (!hs[u]) return;
	dfs2(hs[u], tp);
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u] || v == hs[u]) continue;
		dfs2(v, v);
	}
}

int inline lca(int u, int v) {
	for (; top[u] != top[v]; v = pr[top[v]]) {
		if (dep[top[u]] > dep[top[v]]) swap(u, v);
	}
	if (dep[u] > dep[v]) swap(u, v);
	return u;
}

int inline dis(int u, int v) {
	return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

void inline ins(data_structure &d, int u) {
	set<int> &s = d.s;
	if (!s.size()) { s.insert(dfn[u]); return; }
	set<int>::iterator it = s.lower_bound(dfn[u]), pre = it, nxt = it;
	pre = pre == s.begin() ? --s.end() : --pre;
	nxt = nxt == s.end() ? s.begin() : nxt;
	int v1 = fm[*pre], v2 = fm[*nxt];
	d.sum += dis(v1, u) + dis(u, v2) - dis(v1, v2);
	s.insert(dfn[u]);
}

void inline del(data_structure &d, int u) {
	set<int> &s = d.s;
	if (s.size() == 1) { s.erase(dfn[u]); return; }
	set<int>::iterator it = s.lower_bound(dfn[u]), pre = it, nxt = it;
	pre = pre == s.begin() ? --s.end() : --pre;
	nxt = ++nxt == s.end() ? s.begin() : nxt;
	int v1 = fm[*pre], v2 = fm[*nxt];
	d.sum -= dis(v1, u) + dis(u, v2) - dis(v1, v2);
	s.erase(dfn[u]);
}

int main() {
	scanf("%d", &n);
	cont (i, n - 1) {
		int u, v;
		scanf("%d%d", &u, &v);
		g.link(u, v);
	}
	dfs1(), dfs2();
	cont (u, n) {
		scanf("%d", &c[u]);
		ins(d[c[u]], u);
	}
	scanf("%d\n", &m);
	cont (i, m) {
		char cmd;
		int u, c;
		scanf("%c", &cmd);
		if (cmd == 'U') {
			scanf("%d%d\n", &u, &c);
			if (::c[u] == c) continue;
			del(d[::c[u]], u);
			::c[u] = c;
			ins(d[::c[u]], u);
		} else {
			scanf("%d\n", &c);
			printf("%d\n", d[c].qry());
		}
	}
}
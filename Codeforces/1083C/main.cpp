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
int n, m, p[nsz + 5], fm[nsz + 5];
int rt = 1, pr[nsz + 5], dfn[nsz + 5], dep[nsz + 5], siz[nsz + 5], hs[nsz + 5], top[nsz + 5];

bool inline in(int u, int v, int p) {
	int t = dfn[p];
	for (; top[u] != top[v]; v = pr[top[v]]) {
		if (dep[top[u]] > dep[top[v]]) swap(u, v);
		if (dfn[top[v]] <= t && t <= dfn[v]) return 1;
	}
	if (dep[u] > dep[v]) swap(u, v);
	if (dfn[u] <= t && t <= dfn[v]) return 1;
	return 0;
}

bool inline in(int u, int v) {
	return dfn[u] <= dfn[v] && dfn[v] <= dfn[u] + siz[u] - 1;
}

struct segment_tree {
	#define md ((l + r) >> 1)
	#define lp ls[u], l, md
	#define rp rs[u], md + 1, r
	
	static int rt;
	int sz, ls[2 * nsz], rs[2 * nsz];
	
	struct node {
		bool f;
		int u, v;
		
		node() { u = 0; }
		node(int f, int u = -1, int v = -1) { this->f = f, this->u = u, this->v = v; }
		
		friend inline node operator & (const node &a, const node &b) {
			if (!a.u) return b;
			if (!b.u) return a;
			if (!a.f || !b.f) return node(0);
			int u1 = a.u, u2 = b.u, v1 = a.v, v2 = b.v;
			if (dep[u1] > dep[u2]) swap(u1, u2);
			if (dep[v1] > dep[v2]) swap(v1, v2);
			if (dep[u2] > dep[v1]) swap(u2, v1);
			if (in(u2, v1) && in(v1, v2)) return node(1, u1, v2);
			if (!in(v1, v2) && in(v1, v2, u1) && in(v1, v2, u2)) return node(1, v1, v2);
			if (!in(u2, v1) && !in(u2, v2) && in(u2, v2, u1) && in(u2, v2, v1)) return node(1, u2, v2);
			return node(0);
		}
	};
	node t[2 * nsz];
	
	void inline init(int *w, int &u = rt, int l = 1, int r = n) {
		u = ++sz;
		if (l == r) return (void) (t[u] = node(1, w[l], w[l]));
		init(w, lp), init(w, rp);
		t[u] = t[ls[u]] & t[rs[u]];
	}
	
	void set(int id, int w, int u = rt, int l = 1, int r = n) {
		if (l == r) return (void) (t[u] = node(1, w, w));
		id <= md ? set(id, w, lp) : set(id, w, rp);
		t[u] = t[ls[u]] & t[rs[u]];
	}
	
	int qry(node w = node(), int u = rt, int l = 1, int r = n) {
		node cur = w & t[ls[u]];
		if (l == r) return (w & t[u]).f ? l : l - 1;
		if (cur.f) return qry(cur, rp);
		return qry(w, lp);
	}
};
int segment_tree::rt;
segment_tree tr;

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
	}
};
graph g;

void dfs1(int u = rt) {
	siz[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		dep[v] = dep[u] + 1;
		dfs1(v);
		siz[u] += siz[v];
		if (siz[hs[u]] < siz[v]) hs[u] = v;
	}
}

void dfs2(int u = rt, int tp = rt) {
	static int t;
	dfn[u] = ++t, top[u] = tp;
	if (!hs[u]) return;
	dfs2(hs[u], tp);
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == hs[u]) continue;
		dfs2(v, v);
	}
}

void inline commute(int u, int v) {
	swap(p[u], p[v]);
	tr.set(p[u], u);
	tr.set(p[v], v);
}

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &p[i]), fm[++p[i]] = i;
	circ (u, 2, n) scanf("%d", &pr[u]), g.link(pr[u], u);
	dfs1(), dfs2();
	tr.init(fm);
	scanf("%d", &m);
	cont (i, m) {
		int cmd, u, v;
		scanf("%d", &cmd);
		if (cmd == 1) {
			scanf("%d%d", &u, &v);
			commute(u, v);
		} else printf("%d\n", tr.qry());
	}
}
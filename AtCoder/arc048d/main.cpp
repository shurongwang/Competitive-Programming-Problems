#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5, lgsz = 17, inf = 0x3f3f3f3f;
char on[nsz + 5];
int n, q, a[nsz + 5], dis[nsz + 5], ans;
int rt = 1, pr[nsz + 5], dep[nsz + 5], siz[nsz + 5], hs[nsz + 5], top[nsz + 5], id[nsz + 5];

struct sparse_table {
	int lg[nsz + 5], st[nsz + 5][lgsz + 5];
	
	void inline init(int n, int *a) {
		cont (i, n) lg[i] = lg[i >> 1] + 1, st[i][0] = a[i];
		cont (k, lg[n]) {
			int len = 1 << k;
			for (int i = 1, j = 1 + (len >> 1); i + len - 1 <= n; ++i, ++j) {
				st[i][k] = min(st[i][k - 1], st[j][k - 1]);
			}
		}
	}
	
	int inline qry(int l, int r) {
		int k = lg[r - l + 1] - 1, len = 1 << k;
		return min(st[l][k], st[r - len + 1][k]);
	}
};
sparse_table st0, st1;

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge() {}
		edge(int nxt, int to): nxt(nxt), to(to) {}
	} e[2 * nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
		e[++sz] = edge(hd[v], u), hd[v] = sz;
	}
};
graph g;

bool inline upd(int &a, int b) {
	if (a > b) { a = b; return 1; }
	return 0;
}

void inline dis_init() {
	static int q[nsz + 5];
	int ql = 0, qr = 0;
	cont (u, n) dis[u] = n;
	cont (u, n) if (on[u] == '1') dis[u] = 0, q[qr++] = u;
	for (; ql != qr;) {
		int u = q[ql++];
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to;
			if (upd(dis[v], dis[u] + 1)) q[qr++] = v;
		}
	}
}

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
	static int t = 0;
	id[u] = ++t, top[u] = tp;
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

int inline qry_route(int u, int v, sparse_table &st) {
	int res = inf;
	for (; top[u] != top[v]; v = pr[top[v]]) {
		if (dep[top[u]] > dep[top[v]]) swap(u, v);
		res = min(res, st.qry(id[top[v]], id[v]));
	}
	if (dep[u] > dep[v]) swap(u, v);
	res = min(res, st.qry(id[u], id[v]));
	return res;
}

int main() {
	scanf("%d%d", &n, &q);
	cont (i, n - 1) {
		int u, v;
		scanf("%d%d", &u, &v);
		g.link(u, v);
	}
	scanf("%s", on + 1);
	dis_init();
	dfs1(), dfs2();
	cont (u, n) a[id[u]] = 3 * dis[u] - dep[u];
	st0.init(n, a);
	cont (u, n) a[id[u]] = 3 * dis[u] + dep[u];
	st1.init(n, a);
	cont (i, q) {
		int u, v, p;
		scanf("%d%d", &u, &v);
		p = lca(u, v);
		ans = (dep[u] + dep[v] - 2 * dep[p]) * 2;
		upd(ans, 2 * dep[u] + dep[v] - 2 * dep[p] + qry_route(u, p, st0));
		upd(ans, 2 * dep[u] + dep[v] - 4 * dep[p] + qry_route(v, p, st1));
		printf("%d\n", ans);
	}
}
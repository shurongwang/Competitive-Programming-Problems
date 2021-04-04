#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5, inf = 0x3f3f3f3f;
int n, rt = 1, pr[nsz + 5], ans[nsz + 5];

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

struct value {
	int mx, w, id;
	
	value() {}
	value(int mx, int w, int id): mx(mx), w(w), id(id) {}
};

struct functor {
	value t[3];
	
	functor() { t[0] = t[1] = t[2] = value(-inf, 0, -1); }
	
	value inline operator [] (int id) { return t[id]; }
	
	void inline ins(int mx, int w, int id) {
		if (mx > t[0].mx) t[2] = t[1], t[1] = t[0], t[0] = value(mx, w, id);
		else if (mx > t[1].mx) t[2] = t[1], t[1] = value(mx, w, id);
		else if (mx > t[2].mx) t[2] = value(mx, w, id);
	}
	
	int inline qry_d() { return t[0].mx; }
	
	int inline qry_w() { return t[0].mx == t[1].mx ? 0 : t[0].w; }
	
	int inline qry_d(int b) { return t[0].id == b ? t[1].mx : t[0].mx; }
	
	int inline qry_w(int b) {
		int k0 = 0, k1 = 1;
		if (b == t[0].id) ++k0, ++k1;
		else if (b == t[1].id) ++k1;
		return t[k0].mx == t[k1].mx ? 0 : t[k0].w;
	}
};
functor f[nsz + 5];

void dfs(int u = rt) {
	f[u].ins(0, 0, u);
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u]) continue;
		pr[v] = u;
		dfs(v);
		f[u].ins(f[v].qry_d() + 1, f[v].qry_w() + 1, v);
	}
}

void solve(int u = rt) {
	ans[u] = n - 1 - f[u].qry_w();
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u]) continue;
		f[v].ins(f[u].qry_d(v) + 1, f[u].qry_w(v) + 1, u);
		solve(v);
	}
}

int main() {
	scanf("%d", &n);
	cont (i, n - 1) {
		int u, v;
		scanf("%d%d", &u, &v);
		g.link(u, v);
	}
	dfs(), solve();
	cont (u, n) {
		printf("%d\n", ans[u]);
	}
}
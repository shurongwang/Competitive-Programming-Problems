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
const num inf = 0x3f3f3f3f3f3f3f3f;
int n, m, id[nsz + 5];
num d1[nsz + 5], d2[nsz + 5], dd1[nsz + 5], dd2[nsz + 5], ans;

struct segment_tree {
	#define md ((l + r) >> 1)
	#define lp ls[u], l, md
	#define rp rs[u], md + 1, r
	
	int sz, ls[2 * nsz + 5], rs[2 * nsz + 5];
	num mx1[2 * nsz + 5], mx2[2 * nsz + 5];
	
	void inline init(num *a, num *b) { int rt; init(a, b, rt, 1, n); }
	void init(num *a, num *b, int &u, int l, int r) {
		u = ++sz;
		if (l == r) return (void) (mx1[u] = a[l], mx2[u] = b[l]);
		init(a, b, lp), init(a, b, rp);
		mx1[u] = max(mx1[ls[u]], mx1[rs[u]]);
		mx2[u] = max(mx2[ls[u]], mx2[rs[u]]);
	}
	
	void set(int id, num w1, num w2, int u = 1, int l = 1, int r = n) {
		if (l == r) return (void) (mx1[u] = w1, mx2[u] = w2);
		id <= md ? set(id, w1, w2, lp) : set(id, w1, w2, rp);
		mx1[u] = max(mx1[ls[u]], mx1[rs[u]]);
		mx2[u] = max(mx2[ls[u]], mx2[rs[u]]);
	}
	
	num qry1(int el, int er, int u = 1, int l = 1, int r = n) {
		if (l >= el && r <= er) return mx1[u];
		num res = -inf;
		if (el <= md) res = qry1(el, er, lp);
		if (er > md)  res = max(res, qry1(el, er, rp));
		return res;
	}
	
	num qry2(int el, int er, int u = 1, int l = 1, int r = n) {
		if (l >= el && r <= er) return mx2[u];
		num res = -inf;
		if (el <= md) res = qry2(el, er, lp);
		if (er > md)  res = max(res, qry2(el, er, rp));
		return res;
	}
};
segment_tree tr;

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

void dfs(int u, int p, num *d) {
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to, w = g[i].w;
		if (v == p) continue;
		d[v] = d[u] + w;
		dfs(v, u, d);
	}
}

void inline rearrange_by(int sz, num *a, int *p) {
	static int b[nsz + 5];
	cont (i, sz) b[p[i]] = a[i];
	cont (i, sz) a[i] = b[i];
}

void inline init() {
	vector< pair<num, int> > d;
	dfs(1, -1, d1);
	dfs(n, -1, d2);
	cont (u, n) d.push_back(make_pair(d1[u] - d2[u], u));
	sort(all(d));
	loop (i, d.size()) id[d[i].second] = i + 1;
	cont (i, n) dd1[i] = d1[i], dd2[i] = d2[i];
	rearrange_by(n, dd1, id);
	rearrange_by(n, dd2, id);
	tr.init(dd1, dd2);
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n - 1) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g.link(u, v, w);
	}
	init();
	cont (u, n) {
		for (int i = g.hd[u]; i; i = g[i].nxt) tr.set(id[g[i].to], -inf, -inf);
		if (id[u] != n) ans = max(ans, d1[u] + tr.qry2(id[u] + 1, n));
		if (id[u] != 1) ans = max(ans, d2[u] + tr.qry1(1, id[u] - 1));
		for (int i = g.hd[u]; i; i = g[i].nxt) tr.set(id[g[i].to], d1[g[i].to], d2[g[i].to]);
	}
	cont (i, m) {
		int del;
		scanf("%d", &del);
		printf("%lld\n", min(d1[n], ans + del));
	}
}
#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 5e5;
const num inf = 0x3f3f3f3f3f3f3f3f;
int n, q;
int rt = 1, dfn[nsz + 5], siz[nsz + 5];
num dis[nsz + 5], ans[nsz + 5];
vector< pair<int, int> > g[nsz + 5];
vector< pair<pair<int, int>, int> > qy[nsz + 5];

struct segment_tree {
	#define md ((l + r) >> 1)
	#define lp ls[u], l, md
	#define rp rs[u], md + 1, r
	
	static int rt;
	int sz, ls[2 * nsz], rs[2 * nsz];
	num mn[2 * nsz], del[2 * nsz];
	
	void init(num *a, int &u = rt, int l = 1, int r = n) {
		u = ++sz;
		if (l == r) return (void) (mn[u] = a[l]);
		init(a, lp), init(a, rp);
		mn[u] = min(mn[ls[u]], mn[rs[u]]);
	}
	
	void upd(int el, int er, int w, int u = rt, int l = 1, int r = n) {
		if (l >= el && r <= er) return (void) (mn[u] += w, del[u] += w);
		if (el <= md) upd(el, er, w, lp);
		if (er > md)  upd(el, er, w, rp);
		mn[u] = min(mn[ls[u]], mn[rs[u]]) + del[u];
	}
	
	num qry(int el, int er, int u = rt, int l = 1, int r = n) {
		if (l >= el && r <= er) return mn[u];
		num res = inf;
		if (el <= md) res = qry(el, er, lp);
		if (er > md)  res = min(res, qry(el, er, rp));
		return res + del[u];
	}
};
int segment_tree::rt;
segment_tree tr;

void dfs(int u = rt) {
	static int t;
	bool lf = 1;
	dfn[u] = ++t, siz[u] = 1;
	loop (i, g[u].size()) {
		int v = g[u][i].first, w = g[u][i].second;
		dis[v] = dis[u] + w;
		dfs(v), lf = 0;
		siz[u] += siz[v];
	}
	if (!lf) dis[u] = inf;
}

void solve(int u = rt) {
	loop (i, qy[u].size()) {
		int id = qy[u][i].second;
		pair<int, int> &cur = qy[u][i].first;
		int l = cur.first, r = cur.second;
		ans[id] = tr.qry(cur.first, cur.second);
	}
	loop (i, g[u].size()) {
		int v = g[u][i].first, w = g[u][i].second;
		tr.upd(1, n, w);
		tr.upd(dfn[v], dfn[v] + siz[v] - 1, -2 * w);
		solve(v);
		tr.upd(1, n, -w);
		tr.upd(dfn[v], dfn[v] + siz[v] - 1, 2 * w);
	}
}

void inline rearrage_by_dfn(num *a) {
	num b[nsz + 5];
	cont (i, n) b[dfn[i]] = a[i];
	cont (i, n) a[i] = b[i];
}

int main() {
	scanf("%d%d", &n, &q);
	circ (u, 2, n) {
		int p, w;
		scanf("%d%d", &p, &w);
		g[p].push_back(make_pair(u, w));
	}
	cont (i, q) {
		int u, l, r;
		scanf("%d%d%d", &u, &l, &r);
		qy[u].push_back(make_pair(make_pair(l, r), i));
	}
	dfs();
	rearrage_by_dfn(dis);
	tr.init(dis);
	solve();
	cont (i, q) printf("%lld\n", ans[i]);
}
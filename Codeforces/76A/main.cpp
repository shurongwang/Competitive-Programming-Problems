#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 5e2, inf = 0x3f3f3f3f;
const num inff = 0x3f3f3f3f3f3f3f3f;
int n, m, c_1, c_2, mx_1, mx_2;
int rt = 1, val[nsz + 5], pr[nsz + 5], dep[nsz + 5];
num ans;

struct edge {
	int u, v, w, w2;
	
	edge() {}
	edge(int u, int v, int w, int w2 = 0) {
		this->u = u, this->v = v, this->w = w, this->w2 = w2;
	}
	
	bool inline operator < (const edge &b) const { return w < b.w; }
	
	bool inline operator == (const edge &b) const { return u == b.u && v == b.v && w == b.w; }
};
vector<edge> e1, e2, te;

struct union_find {
	int pr[nsz + 5];
	
	void inline init() {
		cont (u, n) pr[u] = u;
	}
	
	int qry(int u) { return pr[u] == u ? u : pr[u] = qry(pr[u]); }
	
	int inline operator [] (int id) { return qry(id); }
	
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
		edge(int nxt, int to, int w) {
			this->nxt = nxt, this->to = to, this->w = w;
		}
	} e[2 * nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline clear() {
		cont (i, n) hd[i] = 0;
		sz = 0;
	}
	
	void inline link(int u, int v, int w) {
		e[++sz] = edge(hd[u], v, w), hd[u] = sz;
		e[++sz] = edge(hd[v], u, w), hd[v] = sz;
	}
};
graph g;

void dfs(int u = rt) {
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to, w = g[i].w;
		if (v == pr[u]) continue;
		pr[v] = u;
		val[v] = w;
		dep[v] = dep[u] + 1;
		dfs(v);
	}
}

void inline init_tree() {
	g.clear();
	loop (i, te.size()) {
		g.link(te[i].u, te[i].v, te[i].w);
	}
	dfs();
}

edge inline find_max_edge(int u, int v) {
	edge e = edge(-1, -1, 0);
	if (dep[u] > dep[v]) swap(u, v);
	for (; dep[v] != dep[u]; v = pr[v]) {
		if (val[v] > e.w) e = edge(v, pr[v], val[v]);
	}
	for (; u != v; u = pr[u], v = pr[v]) {
		if (val[u] > e.w) e = edge(u, pr[u], val[u]);
		if (val[v] > e.w) e = edge(v, pr[v], val[v]);
	}
	return e;
}

vector<edge> inline kruskal() {
	union_find uf;
	uf.init();
	sort(all(te));
	vector<edge> r;
	loop (i, te.size()) {
		int u = te[i].u, v = te[i].v, w = te[i].w;
		if (uf.link(u, v)) {
			r.push_back(te[i]);
			mx_2 = w;
		}
	}
	return r;
}

void inline solve() {
	uf.init();
	sort(all(e1));
	int it = 0, cnt = 0;
	for (; it < e1.size(); ++it) {
		int u = e1[it].u, v = e1[it].v, w = e1[it].w, w2 = e1[it].w2;
		mx_1 = w;
		te.push_back(edge(u, v, w2));
		if (uf.link(u, v)) {
			++cnt;
			if (cnt == n - 1) break;
		}
	}
	if (cnt != n - 1) { printf("-1\n"); return; }
	te = kruskal();
	ans = (num) mx_1 * c_1 + (num) mx_2 * c_2;
	init_tree();
	for (++it; it < e1.size(); ++it) {
		int u = e1[it].u, v = e1[it].v, w = e1[it].w, w2 = e1[it].w2;
		edge e = find_max_edge(u, v);
		if (e.w > w2) {
			if (e.u > e.v) swap(e.u, e.v);
			loop (i, te.size()) if (te[i] == e) { te.erase(te.begin() + i); break; }
			te.push_back(edge(u, v, w2));
			init_tree();
			mx_1 = w, mx_2 = 0;
			loop (i, te.size()) mx_2 = max(mx_2, te[i].w);
			ans = min(ans, (num) mx_1 * c_1 + (num) mx_2 * c_2);
		}
	}
	printf("%lld\n", ans);
}

int main() {
	scanf("%d%d%d%d", &n, &m, &c_1, &c_2);
	cont (i, m) {
		int u, v, w1, w2;
		scanf("%d%d%d%d", &u, &v, &w1, &w2);
		if (u == v) continue;
		if (u > v) swap(u, v);
		e1.push_back(edge(u, v, w1, w2));
	}
	solve();
	return 0;
}
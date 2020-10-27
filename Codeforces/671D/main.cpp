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
bool leaf[nsz + 5];
int n, m, dm, w[nsz + 5], id[nsz + 5];
int rt = 1, pr[nsz + 5], in[nsz + 5], out[nsz + 5];
num dp[nsz + 5], ans;
vector<int> ev[nsz + 5][2];

struct segment_tree {
	#define md ((l + r) >> 1)
	#define lp ls[u], l, md
	#define rp rs[u], md + 1, r
	
	static int rt;
	int sz, ls[2 * nsz], rs[2 * nsz];
	num mn[2 * nsz], del[2 * nsz];
	
	void init(int &u = rt, int l = 1, int r = dm) {
		u = ++sz;
		if (l == r) return;
		init(lp), init(rp);
	}
	
	void upd(int id, num w, int u = rt, int l = 1, int r = dm) {
		if (l == r) return (void) (mn[u] += w);
		id <= md ? upd(id, w, lp) : upd(id, w, rp);
		mn[u] = min(mn[ls[u]], mn[rs[u]]) + del[u];
	}
	
	void upd(int el, int er, num w, int u = rt, int l = 1, int r = dm) {
		if (l >= el && r <= er) return (void) (mn[u] += w, del[u] += w);
		if (el <= md) upd(el, er, w, lp);
		if (er > md)  upd(el, er, w, rp);
		mn[u] = min(mn[ls[u]], mn[rs[u]]) + del[u];
	}
	
	num qry(int el, int er, int u = rt, int l = 1, int r = dm) {
		if (l >= el && r <= er) return mn[u];
		num res = inf;
		if (el <= md) res = qry(el, er, lp);
		if (er > md)  res = min(res, qry(el, er, rp));
		return res + del[u];
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
		e[++sz] = edge(hd[v], u), hd[v] = sz;
	}
};
graph g;

void dfs(int u = rt) {
	in[u] = dm + 1, leaf[u] = 1;
	loop (i, ev[u][0].size()) id[ev[u][0][i]] = ++dm;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u]) continue;
		pr[v] = u, leaf[u] = 0;
		dfs(v);
	}
	out[u] = dm;
}

bool solve(int u = rt) {
	num sum = 0;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u]) continue;
		if (!solve(v)) return 0;
		sum += dp[v];
	}
	loop (i, ev[u][0].size()) {
		int id = ev[u][0][i], t = ::id[id];
		tr.upd(t, sum + w[id]);
	}
	loop (i, ev[u][1].size()) {
		int id = ev[u][1][i], t = ::id[id];
		tr.upd(t, inf);
	}
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == pr[u]) continue;
		if (sum != dp[v]) tr.upd(in[v], out[v], sum - dp[v]);
	}
	if (u != rt) dp[u] = in[u] <= out[u] ? tr.qry(in[u], out[u]) : inf;
	else for (int i = g.hd[u]; i; i = g[i].nxt) dp[u] += dp[g[i].to];
	return dp[u] < inf;
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n - 1) {
		int u, v;
		scanf("%d%d", &u, &v);
		g.link(u, v);
	}
	cont (i, m) {
		int u, v;
		scanf("%d%d%d", &u, &v, &w[i]);
		if (u == v) continue;
		ev[u][0].push_back(i), ev[v][1].push_back(i);
	}
	dfs();
	if (dm) tr.init();
	ans = solve() ? dp[rt] : -1;
	printf("%lld\n", ans);
}
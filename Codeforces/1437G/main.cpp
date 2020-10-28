#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 3e5, asz = 26;
int n, m, sz, w[nsz + 5], id[nsz + 5];
int rt, pr[nsz + 5], siz[nsz + 5], dep[nsz + 5], hs[nsz + 5], top[nsz + 5], in[nsz + 5], out[nsz + 5];

struct ac_automaton {
	int rt, sz, pr[nsz + 5], g[nsz + 5][asz + 5];
	vector<int> fm[nsz + 5];
	
	ac_automaton() { rt = ++sz; }
	
	void inline ins(const string &s, int id) {
		int u = rt;
		loop (i, s.size()) {
			int c = s[i] - 'a';
			if (!g[u][c]) g[u][c] = ++sz;
			u = g[u][c];
		}
		fm[u].push_back(id);
	}
	
	void inline init() {
		static int q[nsz + 5];
		int ql = 0, qr = 0;
		loop (c, asz) {
			int &v = g[rt][c];
			if (v) pr[v] = rt, q[qr++] = v;
			else v = rt;
		}
		for (; ql != qr;) {
			int u = q[ql++];
			loop (c, asz) {
				int &v = g[u][c];
				if (v) pr[v] = g[pr[u]][c], q[qr++] = v;
				else v = g[pr[u]][c];
			}
		}
	}
};
ac_automaton ma;

struct segment_tree {
	#define md ((l + r) >> 1)
	#define lp ls[u], l, md
	#define rp rs[u], md + 1, r
	
	static int rt;
	int sz, ls[2 * nsz], rs[2 * nsz], mx[2 * nsz];
	
	void init(int &u = rt, int l = 1, int r = n) {
		u = ++sz;
		if (l == r) return;
		init(lp), init(rp);
	}
	
	void upd(int id, int w, int u = rt, int l = 1, int r = n) {
		if (l == r) return (void) (mx[u] = w);
		id <= md ? upd(id, w, lp) : upd(id, w, rp);
		mx[u] = max(mx[ls[u]], mx[rs[u]]);
	}
	
	int qry(int el, int er, int u = rt, int l = 1, int r = n) {
		if (l >= el && r <= er) return mx[u];
		int res = 0;
		if (el <= md) res = qry(el, er, lp);
		if (er > md)  res = max(res, qry(el, er, rp));
		return res;
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
	} e[nsz + 5];
	
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
	in[u] = t + 1, top[u] = tp;
	foreach (it, ma.fm[u]) id[*it] = ++t;
	out[u] = t;
	if (!hs[u]) return;
	dfs2(hs[u], tp);
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == hs[u]) continue;
		dfs2(v, v);
	}
}

void inline init() {
	ma.init();
	rt = ma.rt, sz = ma.sz;
	cont (u, sz) if (u != ma.rt) pr[u] = ma.pr[u], g.link(pr[u], u);
	dfs1(), dfs2();
	tr.init();
}

int inline qry_route(int u, int v) {
	int res = -1;
	for (; top[u] != top[v]; v = pr[top[v]]) {
		if (dep[top[u]] > dep[top[v]]) swap(u, v);
		if (in[top[v]] <= out[v]) res = max(res, tr.qry(in[top[v]], out[v]));
	}
	if (dep[u] > dep[v]) swap(u, v);
	if (in[u] <= out[v]) res = max(res, tr.qry(in[u], out[v]));
	return res;
}

int inline qry(const string &s) {
	int u = rt, res = -1;
	loop (i, s.size()) {
		int c = s[i] - 'a';
		u = ma.g[u][c];
		res = max(res, qry_route(rt, u));
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	cont (i, n) {
		string s;
		cin >> s;
		ma.ins(s, i);
	}
	init();
	cont (i, m) {
		int cmd, id, val;
		string s;
		cin >> cmd;
		if (cmd == 1) {
			cin >> id >> val;
			tr.upd(::id[id], val);
		} else {
			cin >> s;
			cout << qry(s) << ln;
		}
	}
}
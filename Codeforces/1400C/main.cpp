
#include <bits/stdc++.h>

#define ln                '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fr, to)    for (int i = fr; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 3e5;
bool res[nsz + 5];
int ts, n, m, k, sz, s[nsz + 5][2];
int sc, dfn[nsz + 5], low[nsz + 5], vis[nsz + 5], sid[nsz + 5];
string t;

struct subsentence {
	bool tu, tv;
	int u, v, w;
	
	subsentence(int u = 0, int v = 0, bool tu = 0, bool tv = 0, char c = 0) {
		this->u = u, this->v = v, this->tu = tu, this->tv = tv, w = c == '&' ? 0 : (c == '|' ? 1 : 2);
	}
};
subsentence dat[nsz + 5];

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge(int nxt = 0, int to = 0) {
			this->nxt = nxt, this->to = to;
		}
	} e[4 * nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
	}
};
graph g;

void inline tarjan(int u) {
	static int t = 0, ss = 0, stk[nsz + 5];
	dfn[u] = low[u] = ++t;
	stk[ss++] = u;
	vis[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (vis[v] == 2)  continue;
		if (!vis[v]) {
			tarjan(v);
		}
		low[u] = min(low[u], low[v]);
	}
	if (dfn[u] != low[u])  return;
	++sc;
	for (; ss;) {
		int v = stk[--ss];
		sid[v] = sc;
		vis[v] = 2;
		if (v == u)  break;
	}
}

bool inline in(int k, int l = 1, int r = n) { return l <= k && k <= r; }

void inline init_graph() {
	cont (i, n) {
		int l = i - k, r = i + k;
		if (t[i - 1] == '1') {
			if (in(l) && in(r)) dat[++m] = subsentence(l, r, 1, 1, '|');
			if (in(l) && !in(r)) dat[++m] = subsentence(l, l, 1, 1, '|');
			if (!in(l) && in(r)) dat[++m] = subsentence(r, r, 1, 1, '|');
		} else {
			if (in(l) && in(r)) dat[++m] = subsentence(l, r, 0, 0, '&');
			if (in(l) && !in(r)) dat[++m] = subsentence(l, l, 0, 0, '&');
			if (!in(l) && in(r)) dat[++m] = subsentence(r, r, 0, 0, '&');
		}
	}
	
	cont (i, n) s[i][0] = ++sz, s[i][1] = ++sz;
	cont (i, m) {
		int a = dat[i].u, b = dat[i].v, ta = dat[i].tu, tb = dat[i].tv, c = dat[i].w;
		if (c == 0) {         // and
			g.link(s[a][ta], s[b][tb]);
			g.link(s[b][tb], s[a][ta]);
			g.link(s[a][!ta], s[a][ta]);
			g.link(s[b][!tb], s[b][tb]);
		} else if (c == 1) {  // or
			g.link(s[a][!ta], s[b][tb]);
			g.link(s[b][!tb], s[a][ta]);
		} else if (c == 2) {  // xor
			g.link(s[a][ta], s[b][!tb]);
			g.link(s[b][tb], s[a][!ta]);
			g.link(s[a][!ta], s[b][tb]);
			g.link(s[b][!tb], s[a][ta]);
		}
	}
}

bool inline two_sat(subsentence dat[] = ::dat) {
	cont (u, sz) {
		if (vis[u])  continue;
		tarjan(u);
	}
	cont (u, n) {
		int su = sid[s[u][1]], snu = sid[s[u][0]];
		if (su == snu)  return 0;
		res[u] = su < snu;
	}
	return 1;
}

void inline solve() {
	cin >> t >> k;
	n = int(t.size());
	cont (i, n) {
		int l = i - k, r = i + k;
		if (!in(l) && !in(r) && t[i - 1] == '1') {
			cout << -1 << ln;
			return;
		}
	}
	init_graph();
	if (!two_sat()) {
		cout << -1 << ln;
	} else {
		cont (i, n) {
			cout << res[i];
		}
		cout << ln;
	}
}

void inline clear() {
	cont (u, sz) {
		g.hd[u] = dfn[u] = low[u] = vis[u] = sid[u] = 0;
	}
	sc = sz = m = 0;
	g.sz = 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin >> ts;
	cont (cs, ts) {
		solve();
		clear();
	}
}
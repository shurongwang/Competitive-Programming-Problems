#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;
typedef std::bitset<2500>  bits;

using namespace std;

const int nsz = 50, ndsz = nsz * nsz * 2, scsz = nsz * nsz / 2, egsz = 3 * ndsz;
char grd[nsz + 5][nsz + 5];
int n, m, sz, ss, sc, s1, s2, d[nsz + 5][nsz + 5][2], id[ndsz + 5], sid[ndsz + 5];
bits w[scsz + 5];
map< pair<int, int>, bool> est;

struct graph {
	int sz, hd[ndsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge() {}
		edge(int nxt, int to) {
			this->nxt = nxt, this->to = to;
		}
	} e[2 * egsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	inline edge operator [] (int id) const { return e[id]; }
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
	}
	
	void inline link_both(int u, int v) {
		link(u, v), link(v, u);
	}
};
graph g, ng;

bool inline empty(char c) { return c == '.' || c == 'O' || c == '*'; }
bool inline block(char c) { return c == '#' || c == '\0'; }

void tarjan(int u) {
	static int t, ss, dfn[ndsz + 5], low[ndsz + 5], vis[ndsz + 5], stk[ndsz + 5];
	dfn[u] = low[u] = ++t;
	stk[ss++] = u, vis[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (vis[v] == 2) continue;
		if (!vis[v]) tarjan(v);
		low[u] = min(low[u], low[v]);
	}
	if (dfn[u] != low[u]) return;
	++sc;
	for (int v = -1; ss && u != v; --ss) {
		v = stk[ss - 1];
		vis[v] = 2, sid[v] = sc;
		if (id[v]) w[sc][id[v] - 1] = 1;
	}
}

bool inline solve(int src, const graph &g = ng) {
	static bool vis[scsz + 5];
	static int q[scsz + 5], d[scsz + 5];
	int ql = 0, qr = 0;
	bits S[scsz + 5];
	
	memset(vis, 0, sizeof(vis));
	q[qr++] = src, vis[src] = 1;
	for (; ql != qr;) {
		int u = q[ql++];
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to;
			++d[v];
			if (!vis[v]) q[qr++] = v, vis[v] = 1;
		}
	}
	
	ql = qr = 0;
	S[src] = w[src], q[qr++] = src;
	for (; ql != qr;) {
		int u = q[ql++];
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to;
			if (!d[v]) continue;
			if (S[v].count() < (S[u] | w[v]).count()) S[v] = S[u] | w[v];
			if (--d[v] == 0) q[qr++] = v;
		}
	}
	cont (u, sc) if (S[u].count() == ss) return 1;
	return 0;
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n) scanf("%s", &grd[i][1]);
	cont (i, n) cont (j, m) {
		if (block(grd[i][j])) continue;
		int &d0 = d[i][j][0] = ++sz, &d1 = d[i][j][1] = ++sz;
		if (empty(grd[i - 1][j])) g.link_both(d[i - 1][j][0], d0);
		if (empty(grd[i][j - 1])) g.link_both(d[i][j - 1][1], d1);
		if (block(grd[i - 1][j]) || block(grd[i + 1][j])) g.link(d0, d1);
		if (block(grd[i][j - 1]) || block(grd[i][j + 1])) g.link(d1, d0);
		if (grd[i][j] == 'O') s1 = d0, s2 = d1;
		if (grd[i][j] == '*') id[d0] = id[d1] = ++ss;
	}
	cont (u, sz) if (!sid[u]) tarjan(u);
	cont (u, sz) {
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to, su = sid[u], sv = sid[v];
			if (su == sv || est[{su, sv}]) continue;
			ng.link(su, sv), est[{su, sv}] = 1;
		}
	}
	printf("%s\n", solve(sid[s1]) || solve(sid[s2]) ? "YES" : "NO");
}
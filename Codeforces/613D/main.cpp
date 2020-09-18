#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

namespace io {
	#define isdigit(c)  (c >= '0' && c <= '9')
	#define getchar()   (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufsz, stdin), p1 == p2) ? EOF : *p1++)
	#define flush()     (fwrite(puf, 1, pp - puf, stdout), pp = puf)
	#define putchar(c)  (*pp++ = c, pp - puf == bufsz && flush())
	
	const int bufsz = 1 << 24;
	static char buf[bufsz], puf[bufsz], *p1, *p2, *pp = puf;
	struct flusher { ~flusher() { flush(); } } flusher;
	
	template<class type> void inline read(type &a) {
		int f = 1, c = getchar();
		for (; !isdigit(c); c = getchar());
		for (a = 0; isdigit(c); a *= 10, a += c & 15, c = getchar());
		a *= f;
	}
	
	template<class type> void inline write(type a, char c = ln) {
		static int d[20];
		int s = d[0] = 0;
		for (a < 0 && (putchar(45), a = -a); a; d[s++] = a % 10, a /= 10);
		for (s || (s = 1); s; putchar(d[--s] + 48));
		putchar(c);
	}
}
using namespace io;

const int nsz = 1e5;
const int inf = 0x3f3f3f3f;
bool mrk[nsz + 5];
int n, q, rt = 1, dp[nsz + 5][2], ans;
int pr[nsz + 5], dep[nsz + 5], siz[nsz + 5], hs[nsz + 5], top[nsz + 5], dfn[nsz + 5];
vector<int> nd;

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
graph g, tr;

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
	static int t;
	dfn[u] = ++t;
	top[u] = tp;
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

bool inline by_dfn(int u, int v) { return dfn[u] < dfn[v]; }

void inline build_virtual_tree(vector<int> &nd, graph &g, int &rt) {
	static int stk[nsz + 5];
	sort(all(nd), by_dfn), nd.erase(unique(all(nd)), nd.end());
	int ss = 0, sz = int(nd.size());
	loop (i, sz) {
		int u = nd[i];
		if (!ss) { stk[ss++] = u; continue; }
		int p = stk[ss - 1], pp = lca(p, u);
		for (; ss > 1 && dep[stk[ss - 2]] >= dep[pp]; --ss) g.link(stk[ss - 2], stk[ss - 1]);
		p = stk[ss - 1];
		if (p != pp) {
			nd.push_back(pp);
			g.link(pp, p);
			stk[ss - 1] = pp;
		}
		stk[ss++] = u;
	}
	for (rt = stk[0]; ss > 1; g.link(stk[ss - 2], stk[ss - 1]), --ss);
}

void inline upd(int &a, int b) {
	if (a > b) a = b;
}

int solve(int u, int p = -1) {
	int sum = 0;
	dp[u][0] = mrk[u] * inf, dp[u][1] = 0;
	for (int i = tr.hd[u]; i; i = tr[i].nxt) {
		int v = tr[i].to;
		if (v == p) continue;
		solve(v, u);
		if (mrk[u]) {
			dp[u][1] += dp[v][0];
			upd(dp[u][1], inf);
		} else {
			sum += min(dp[v][0], dp[v][1]);
			dp[u][1] = min(dp[u][0] + dp[v][1], dp[u][1] + dp[v][0]);
			dp[u][0] += dp[v][0];
			upd(dp[u][0], inf), upd(dp[u][1], inf);
		}
	}
	if (!mrk[u]) upd(dp[u][0], sum + 1);
	return min(dp[u][0], dp[u][1]);
}

int main() {
	read(n);
	cont (i, n - 1) {
		int u, v;
		read(u), read(v);
		g.link(u, v);
	}
	dfs1(), dfs2();
	read(q);
	cont (i, q) {
		bool f = 0;
		int k, rt;
		read(k);
		cont (i, k) {
			int u;
			read(u);
			nd.push_back(u);
			mrk[u] = 1;
		}
		for (int u : nd) f |= mrk[pr[u]];
		if (f) write(-1);
		else {
			loop (i, k) {
				int u = nd[i];
				if (u != ::rt) nd.push_back(pr[u]);
			}
			build_virtual_tree(nd, tr, rt);
			write(solve(rt));
		}
		for (int u : nd) {
			tr.hd[u] = mrk[u] = 0;
		}
		tr.sz = 0;
		nd.clear();
	}
}

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
		for (; !isdigit(c); c == 45 && (f = -1), c = getchar());
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

const int nsz = 1e6, msz = 5e5;
const int inf = 2e9;
bool cs[nsz + 5];
int n, m, sz, w[nsz + 5], val[nsz + 5];
int sc, vis[nsz + 5], dfn[nsz + 5], low[nsz + 5], sid[nsz + 5];

struct graph {
	int sz, hd[nsz + 5];
	
	struct edge {
		int nxt, to, tp;
		
		edge() {}
		edge(int nxt, int to, int tp) {
			this->nxt = nxt, this->to = to, this->tp = tp;
		}
	} e[msz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v, int tp) {
		e[++sz] = edge(hd[u], v, tp), hd[u] = sz;
	}
};
graph g, ng;

void inline report_no_solution() {
	putchar('N'), putchar('O'), putchar(ln);
	exit(0);
}

void inline report_solution() {
	putchar('Y'), putchar('E'), putchar('S'), putchar(ln);
	cont (u, n) write(val[sid[u]]);
}

void tarjan(int u) {
	static int t, ss, stk[nsz + 5];
	stk[ss++] = u, dfn[u] = low[u] = ++t, vis[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (vis[v] == 2) continue;
		if (!vis[v]) tarjan(v);
		low[u] = min(low[u], low[v]);
	}
	if (dfn[u] != low[u]) return;
	++sc;
	for (int v = -1; u != v; --ss) {
		v = stk[ss - 1];
		vis[v] = 2, sid[v] = sc;
		if (w[v] != -inf) val[sc] = w[v], cs[sc] = 1;
	}
}

void inline topological_solve(graph &g = ng) {
	static int d[nsz + 5], q[nsz + 5];
	int ql = 0, qr = 0;
	cont (u, sc) for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		++d[v];
	}
	cont (u, sc) if (!d[u]) q[qr++] = u;
	for (; ql != qr;) {
		int u = q[ql++];
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to, tp = g[i].tp, w = val[u] + tp;
			if (cs[v]) {
				if (w > val[v]) report_no_solution();
			} else val[v] = max(val[v], w);
			if (--d[v] == 0) q[qr++] = v;
		}
	}
}

int main() {
	freopen("dat.in", "r", stdin);
	freopen("dat.out", "w", stdout);
	read(n), read(m);
	sz = n;
	cont (i, nsz) w[i] = val[i] = -inf;
	cont (i, m) {
		int tp, tp1, x1, tp2, x2;
		read(tp), read(tp1), read(x1), read(tp2), read(x2);
		if (tp1 == 1 && tp2 == 1) {
			if (!(x1 + tp <= x2)) report_no_solution();
		} else if (tp1 == 1) {
			++sz;
			w[sz] = x1;
			g.link(sz, x2, tp);
		} else if (tp2 == 1) {
			++sz;
			w[sz] = x2;
			g.link(x1, sz, tp);
		} else {
			g.link(x1, x2, tp);
		}
	}
	cont (u, sz) if (!vis[u]) tarjan(u);
	cont (u, sz) for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to, tp = g[i].tp, su = sid[u], sv = sid[v];
		if (su == sv) {
			if (tp == 1) report_no_solution();
		} else {
			ng.link(su, sv, g[i].tp);
		}
	}
	topological_solve();
	report_solution();
	return 0;
}
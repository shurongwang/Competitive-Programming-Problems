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
		char c = getchar();
		for (; !isdigit(c); c = getchar());
		for (a = 0; isdigit(c); a *= 10, a += c & 15, c = getchar());
	}
	
	template<class type> void inline write(type a, char c = ln) {
		static int d[20];
		int s = d[0] = 0;
		for (; a; d[s++] = a % 10, a /= 10);
		for (s || (s = 1); s; putchar(d[--s] + 48));
		putchar(c);
	}
}
using namespace io;

const int nsz = 5e5, inf = 0x3f3f3f3f;
int n, m, a[nsz + 5], ans[nsz + 5];
int rt = 1, t, c[nsz + 5], w[nsz + 5], pr[nsz + 5], dep[nsz + 5], siz[nsz + 5], dfn[nsz + 5];
pair<int, int> e[nsz + 5];

struct segment_tree {
	#define md ((l + r) >> 1)
	#define lp ls[u], l, md
	#define rp rs[u], md + 1, r
	
	bool rev[2 * nsz + 5];
	static int rt;
	int sz, ls[2 * nsz + 5], rs[2 * nsz + 5], w[2 * nsz + 5][2];
	
	void inline up(int u) {
		w[u][0] = max(w[ls[u]][0], w[rs[u]][0]);
		w[u][1] = max(w[ls[u]][1], w[rs[u]][1]);
	}
	
	void inline down(int u) {
		if (!rev[u]) return;
		swap(w[ls[u]][0], w[ls[u]][1]), rev[ls[u]] ^= 1;
		swap(w[rs[u]][0], w[rs[u]][1]), rev[rs[u]] ^= 1;
		rev[u] = 0;
	}
	
	void init(int *w, int *a, int &u = rt, int l = 1, int r = n) {
		u = ++sz;
		rev[u] = 0;
		if (l == r) { this->w[u][a[l]] = w[l], this->w[u][a[l] ^ 1] = -inf; return; }
		init(w, a, lp), init(w, a, rp);
		up(u);
	}
	
	void flip(int el, int er, int u = rt, int l = 1, int r = n) {
		if (l >= el && r <= er) { swap(w[u][0], w[u][1]), rev[u] ^= 1; return; }
		down(u);
		if (el <= md) flip(el, er, lp);
		if (er > md)  flip(el, er, rp);
		up(u);
	}
	
	int inline qry_all() { return w[rt][0]; }
};
int segment_tree::rt;
segment_tree tr;

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
	
	void inline link(int u, int v, int w) {
		e[++sz] = edge(hd[u], v, w), hd[u] = sz;
		e[++sz] = edge(hd[v], u, w), hd[v] = sz;
	}
};
graph g;

int inline bfs(int s) {
	static int q[nsz + 5], d[nsz + 5];
	int ql = 0, qr = 0, r = -1;
	cont (i, n) d[i] = -1;
	for (q[qr++] = s, d[s] = 0; ql != qr;) {
		int u = q[ql++];
		for (int i = g.hd[u]; i; i = g[i].nxt) {
			int v = g[i].to;
			if (d[v] == -1) q[qr++] = v, d[v] = d[u] + 1;
		}
	}
	cont (u, n) if (r == -1 || d[u] > d[r]) r = u;
	return r;
}

void dfs(int u = rt) {
	dfn[u] = ++t, siz[u] = 1;
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to, w = g[i].w;
		if (v == pr[u]) continue;
		pr[v] = u, dep[v] = dep[u] + 1, c[v] = c[u] ^ w;
		dfs(v);
		siz[u] += siz[v];
	}
}

void inline rearrange_with_dfn(int *a) {
	static int tmp[nsz + 5];
	cont (i, n) tmp[i] = a[i];
	cont (i, n) a[dfn[i]] = tmp[i];
}

void inline flip_subtree(int u) {
	tr.flip(dfn[u], dfn[u] + siz[u] - 1);
}

void inline solve(int rt) {
	::rt = rt, t = pr[rt] = dep[rt] = tr.sz = 0;
	cont (i, n) c[i] = 0;
	dfs();
	cont (i, n) w[i] = dep[i];
	rearrange_with_dfn(w);
	rearrange_with_dfn(c);
	tr.init(w, c);
	cont (i, m) {
		int id = a[i], u = e[id].first, v = e[id].second;
		if (dep[u] > dep[v]) swap(u, v);
		flip_subtree(v);
		ans[i] = max(ans[i], tr.qry_all());
	}
}

int main() {
	read(n);
	cont (i, n - 1) {
		int u, v, w;
		read(u), read(v), read(w);
		g.link(u, v, w);
		e[i] = make_pair(u, v);
	}
	read(m);
	cont (i, m) read(a[i]);
	int r1 = bfs(rt), r2 = bfs(r1);
	solve(r1), solve(r2);
	cont (i, m) write(ans[i]);
}
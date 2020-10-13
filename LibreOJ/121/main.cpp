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
		for (; a; d[s++] = a % 10, a /= 10);
		for (s || (s = 1); s; putchar(d[--s] + 48));
		putchar(c);
	}
}
using namespace io;

const int nsz = 5e3, msz = 5e5;
int n, m, q, rt, fm[nsz + 5][nsz + 5], ans[msz + 5];

struct two_int {
	int a, b;
	
	two_int() {}
	two_int(int a, int b) { this->a = a, this->b = b; }
};

struct event {
	int l, r;
	two_int k;
	
	event() {}
	event(int l, int r, two_int k) { this->l = l, this->r = r, this->k = k; }
};
vector<event> e;

struct union_find {
	struct node {
		int pr, sz;
		
		node() {}
		node(int pr, int sz) { this->pr = pr, this->sz = sz; }
	};
	node nd[nsz + 5];
	
	struct info {
		int u, v, t;
		
		info() {}
		info(int u, int v, int t) { this->u =u, this->v = v, this->t = t; }
	};
	int ss;
	info stk[nsz + 5];
	
	inline node& operator [] (int id) { return nd[qry(id)]; }
	
	void inline init(int n) {
		cont (u, n) nd[u] = node(u, 1);
	}
	
	int inline qry(int u) { return nd[u].pr == u ? u : qry(nd[u].pr); }
	
	void inline link(int u, int v, int t = 0) {
		u = qry(u), v = qry(v);
		if (u == v) return;
		if (nd[u].sz < nd[v].sz) swap(u, v);
		nd[v].pr = u, nd[u].sz += nd[v].sz;
		stk[ss++] = info(u, v, t);
	}
	
	void inline undo_until(int t) {
		for (; ss && stk[ss - 1].t >= t; --ss) {
			int u = stk[ss - 1].u, v = stk[ss - 1].v;
			nd[v].pr = v, nd[u].sz -= nd[v].sz;
		}
	}
};
union_find uf;

struct time_line_tree {
	#define md ((l + r) >> 1)
	#define lp ls[u], l, md
	#define rp rs[u], md + 1, r
	
	int sz, ls[2 * msz + 5], rs[2 * msz + 5];
	two_int qy[msz + 5];
	vector<two_int> tr[2 * msz + 5];
	
	void inline init(int &u = rt, int l = 1, int r = q) {
		u = ++sz;
		if (l == r) return;
		init(lp), init(rp);
	}
	
	void upd(int el, int er, two_int w, int u = rt, int l = 1, int r = q) {
		if (l >= el && r <= er) {
			tr[u].push_back(w); return; }
		if (el <= md) upd(el, er, w, lp);
		if (er > md)  upd(el, er, w, rp);
	}
	
	void trav(int u = rt, int l = 1, int r = q) {
		static int t;
		int cur = ++t;
		loop (i, tr[u].size()) uf.link(tr[u][i].a, tr[u][i].b, cur);
		if (l == r) ans[l] = uf[qy[l].a].pr == uf[qy[l].b].pr;
		else trav(lp), trav(rp);
		uf.undo_until(cur);
	}
};
time_line_tree tr;

int main() {
	read(n), read(m);
	cont (i, m) {
		int tp, u, v;
		read(tp), read(u), read(v);
		if (u > v) swap(u, v);
		two_int cur = two_int(u, v);
		if (tp == 0) {
			fm[u][v] = q + 1;
		} else if (tp == 1) {
			int l = fm[u][v];
			if (l <= q) e.push_back(event(l, q, cur));
			fm[u][v] = 0;
		} else if (tp == 2) tr.qy[++q] = cur;
	}
	cont (u, n) circ (v, u + 1, n) if (fm[u][v]) {
		int l = fm[u][v];
		if (l <= q) e.push_back(event(l, q, two_int(u, v)));
	}
	if (q) {
		tr.init();
		loop (i, e.size()) tr.upd(e[i].l, e[i].r, e[i].k);
		uf.init(n), tr.trav();
		cont (i, q) putchar(ans[i] ? 'Y' : 'N'), putchar(ln);
	}
}
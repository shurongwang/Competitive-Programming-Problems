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
		for (a < 0 && (putchar(45), a = -a); a; d[s++] = a % 10, a /= 10);
		for (s || (s = 1); s; putchar(d[--s] + 48));
		putchar(c);
	}
}
using namespace io;

const int nsz = 2e5, asz = 1e6;
int n, m, a[nsz + 5];
random_device rd;
mt19937 rdm(rd());

struct treap {
	static int sz, ls[nsz + 5], rs[nsz + 5], siz[nsz + 5], val[nsz + 5];
	int rt;
	
	int inline node(int w) {
		int u = ++sz;
		siz[u] = 1, val[u] = w;
		return u;
	}
	
	void inline up(int u) {
		siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
	}
	
	int mrg(int v1, int v2) {
		if (!v1 || !v2) return v1 | v2;
		if (rand() % (siz[v1] + siz[v2]) < siz[v1]) {
			rs[v1] = mrg(rs[v1], v2), up(v1); return v1;
		} else {
			ls[v2] = mrg(v1, ls[v2]), up(v2); return v2;
		}
	}
	
	void spl(int u, int w, int &v1, int &v2) {
		if (!u) { v1 = v2 = 0; return; }
		if (val[u] <= w) {
			v1 = u, spl(rs[u], w, rs[u], v2);
		} else {
			v2 = u, spl(ls[u], w, v1, ls[u]);
		}
		up(u);
	}
	
	int inline qry(int l, int r) {
		int v1, v2, v3, res;
		spl(rt, l - 1, v1, v2);
		spl(v2, r, v2, v3);
		res = siz[v2];
		rt = mrg(mrg(v1, v2), v3);
		return res;
	}
	
	int inline del(int l, int r) {
		int v1, v2, v;
		spl(rt, l - 1, v1, v2);
		spl(v2, r, v, v2);
		rt = mrg(v1, v2);
		return v;
	}
};
int treap::sz, treap::ls[nsz + 5], treap::rs[nsz + 5], treap::siz[nsz + 5], treap::val[nsz + 5];
treap tr[asz + 5], t;

struct segment {
	int l, r, c;
	
	segment() {}
	segment(int l, int r, int c) {
		this->l = l, this->r = r, this->c = c;
	}
	
	bool inline operator < (const segment &b) const { return l < b.l; }
};
set<segment> s;

int inline random(int l, int r) { return rdm() % (r - l + 1) + l; }

int inline at(int id) { return (--s.lower_bound(segment(id + 1, 0, 0)))->c; }

void inline init() {
	int p = 1;
	cont (i, n) tr[a[i]].rt = t.mrg(tr[a[i]].rt, t.node(i));
	cont (i, n + 1) if (a[i] != a[p]) {
		s.insert(segment(p, i - 1, a[p]));
		p = i;
	}
}

int inline query(int l, int r) {
	static bool vis[asz + 5];
	vector<int> d;
	int len = r - l + 1, sum = 0, res = -1;
	cont (t, 10) {
		int p = random(l, r), c = at(p), cnt;
		for (; vis[c]; p = random(l, r), c = at(p));
		cnt = tr[c].qry(l, r);
		if (cnt > len / 2) { res = c; break; }
		vis[c] = 1, d.push_back(c);
		sum += cnt;
		if (sum >= (len - 1) / 2 + 1) break;
	}
	loop (i, d.size()) vis[d[i]] = 0;
	return res;
}

void inline update(int l, int r, int c) {
	set<segment>::iterator it = --s.lower_bound(segment(l + 1, 0, 0));
	int cl = it->l, cr = -1, c1 = it->c, c2, v1, v2;
	t.spl(tr[c].rt, l - 1, v1, v2);
	t.spl(v2, r, tr[c].rt, v2);
	for (; it != s.end() && it->r <= r;) {
		auto pit = it++;
		v1 = t.mrg(v1, tr[pit->c].del(max(pit->l, l), min(pit->r, r)));
		s.erase(pit);
	}
	if (it != s.end()) {
		auto pit = it++;
		cr = pit->r, c2 = pit->c;
		v1 = t.mrg(v1, tr[pit->c].del(max(l, pit->l), r));
		s.erase(pit);
	}
	if (cl != l) s.insert(segment(cl, l - 1, c1));
	if (cr != r && cr != -1) s.insert(segment(r + 1, cr, c2));
	tr[c].rt = t.mrg(v1, v2);
	s.insert(segment(l, r, c));
}

int main() {
	read(n);
	cont (i, n) read(a[i]);
	init();
	read(m);
	cont (i, m) {
		char c = getchar();
		int l, r, w;
		read(l), read(r);
		if (c == 's') {
			read(w);
			update(l, r, w);
		} else if (c == 'q') {
			write(query(l, r));
		}
	}
}
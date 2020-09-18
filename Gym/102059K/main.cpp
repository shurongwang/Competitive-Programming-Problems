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

const int nsz = 3e5;
int n, p[nsz + 5], w[nsz + 5];

void inline upd_max(num &a, num b) {
	if (a < b) a = b;
}

struct fenwick_tree {
	num tr[nsz + 5];
	
	void inline upd_pre(int u, num w) {
		for (; u > 0; u -= u & -u) upd_max(tr[u], w);
	}
	
	num inline at(int u) {
		num res = 0;
		for (; u <= n; u += u & -u) upd_max(res, tr[u]);
		return res;
	}
};
fenwick_tree tr;

struct event {
	int l, r, w;
	
	bool inline operator < (const event b) const { return l != b.l ? l < b.l : r > b.r; }
};
vector<event> e[2];

#define e0 e[0][ptr]
#define e1 e[1][ptr]

int main() {
	read(n);
	cont (i, n) read(p[i]);
	cont (i, n) read(w[i]);
	cont (i, n) {
		int p = ::p[i], l, r;
		l = i - p + 1, r = i - 1;
		if (l <= r && l >= 1) e[0].push_back({l, i, w[i]});
		l = i + 1, r = i + p - 1;
		if (l <= r && r <= n) e[1].push_back({i, r, w[i]});
	}
	sort(all(e[0])), sort(all(e[1]));
	cont (l, n) {
		for (static int ptr = 0; ptr < e[1].size() && e1.l + 1 == l; ++ptr) {
			tr.upd_pre(e1.r, tr.at(e1.r) + e1.w);
		}
		for (static int ptr = 0; ptr < e[0].size() && e0.l == l; ++ptr) {
			tr.upd_pre(e0.r - 1, tr.at(e0.r) + e0.w);
		}
		write(tr.at(l) + (p[l] == 1) * w[l], ' ');
	}
}
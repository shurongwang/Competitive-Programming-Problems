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
using io::read;
using io::write;

const int nsz = 1e6;
int n, m, p1[nsz + 5], p2[nsz + 5], q1[nsz + 5], a[nsz + 5], ans;

struct segment_tree {
	#define ls (u << 1)
	#define rs (u << 1 | 1)
	#define md ((l + r) >> 1)
	#define lp ls, l, md
	#define rp rs, md + 1, r
	
	vector<int> tr[4 * nsz + 5];
	
	vector<int> inline merge(const vector<int> &a, const vector<int> &b) {
		int s1 = int(a.size()), s2 = int(b.size());
		vector<int> r;
		for (int i = 0, j = 0; i < s1 || j < s2;) r.push_back(j == s2 || (i < s1 && a[i] < b[j]) ? a[i++] : b[j++]);
		return r;
	}
	
	void inline init(int *a, int u = 1, int l = 1, int r = n) {
		if (l == r) { tr[u].push_back(a[l]); return; }
		init(a, lp), init(a, rp);
		tr[u] = merge(tr[ls], tr[rs]);
	}
	
	int qry(int el, int er, int vl, int vr, int u = 1, int l = 1, int r = n) {
		if (l >= el && r <= er) return lower_bound(all(tr[u]), vr + 1) - lower_bound(all(tr[u]), vl);
		int res = 0;
		if (el <= md) res = qry(el, er, vl, vr, lp);
		if (er > md) res += qry(el, er, vl, vr, rp);
		return res;
	}
};
segment_tree tr;

int inline f(int x) { return (x - 1 + ans) % n + 1; }

int main() {
	read(n);
	cont (i, n) read(p1[i]), q1[p1[i]] = i;
	cont (i, n) read(p2[i]), a[i] = q1[p2[i]];
	tr.init(a);
	read(m);
	cont (i, m) {
		int a, b, c, d;
		read(a), read(b), read(c), read(d);
		int l1 = min(f(a), f(b)), r1 = max(f(a), f(b));
		int l2 = min(f(c), f(d)), r2 = max(f(c), f(d));
		ans = tr.qry(l2, r2, l1, r1);
		write(ans);
		ans += 1;
	}
}
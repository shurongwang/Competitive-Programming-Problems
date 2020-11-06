#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5, sqrtsz = 450, full = (1 << 20) - 1;
int n, m, a[nsz + 5];

struct block {
	int del0, del1, mx, fix;
	vector<int> d;
	
	block() { del0 = full, del1 = 0, mx = -1, fix = 0; }
	
	inline int operator [] (int id) { return (d[id] & del0) | del1; }
	
	int inline back() { return int(d.size()) - 1; }
	
	void inline push_back(int w) { d.push_back(w); }
	
	void inline down() {
		if (del0 == full && del1 == 0) return;
		if (del0 != full) {
			loop (i, d.size()) d[i] &= del0;
			del0 = full;
		}
		if (del1 != 0) {
			loop (i, d.size()) d[i] |= del1;
			del1 = 0;
		}
		fix = 0;
	}
	
	void inline upd_all(int w0, int w1) {
		if (w0 != full) del0 &= w0, del1 &= w0;
		if (w1 != 0) del1 |= w1;
		int cur = (del0 ^ full) | del1;
		if (cur != fix) fix = cur, mx = -1;
		else if (mx != -1) mx &= w0, mx |= w1;
	}
	
	int inline qry_all() {
		if (mx == -1) loop (i, d.size()) mx = max(mx, (d[i] & del0) | del1);
		return mx;
	}
	
	void inline upd(int l, int r, int w0, int w1) {
		down();
		circ (i, l, r) {
			if (w0 != full) d[i] &= w0;
			if (w1 != 0) d[i] |= w1;
		}
		mx = -1;
		loop (i, d.size()) mx = max(mx, d[i]);
	}
	
	int inline qry(int l, int r) {
		int mx = -1;
		circ (i, l, r) mx = max(mx, (d[i] & del0) | del1);
		return mx;
	}
};

struct sqrt_decomposition {
	int sz, s;
	block b[sqrtsz + 5];
	
	void inline init(int n, int *a) {
		s = int(sqrt(n) + 1), sz = (n - 1) / s + 1;
		loop (i, n) b[i / s].push_back(a[i]);
	}
	
	void inline upd(int l, int r, int w0, int w1) {
		int bl = l / s, br = r / s;
		if (bl == br) return (void) (b[bl].upd(l % s, r % s, w0, w1));
		b[bl].upd(l % s, b[bl].back(), w0, w1);
		b[br].upd(0, r % s, w0, w1);
		circ (id, bl + 1, br - 1) b[id].upd_all(w0, w1);
	}
	
	int inline qry(int l, int r) {
		int bl = l / s, br = r / s, res = 0;
		if (bl == br) return b[bl].qry(l % s, r % s);
		res = max(b[bl].qry(l % s, b[bl].back()), b[br].qry(0, r % s));
		circ (id, bl + 1, br - 1) res = max(res, b[id].qry_all());
		return res;
	}
};
sqrt_decomposition d;

int main() {
	scanf("%d%d", &n, &m);
	loop (i, n) scanf("%d", &a[i]);
	d.init(n, a);
	cont (i, m) {
		int cmd, l, r, w;
		scanf("%d%d%d", &cmd, &l, &r);
		--l, --r;
		if (cmd == 1) {
			scanf("%d", &w);
			d.upd(l, r, w, 0);
		} else if (cmd == 2) {
			scanf("%d", &w);
			d.upd(l, r, full, w);
		} else if (cmd == 3) {
			printf("%d\n", d.qry(l, r));
		}
	}
}
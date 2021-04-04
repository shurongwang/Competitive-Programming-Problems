#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

template<int mod> struct modulo {
	int w;
	operator int&() { return w; }
	operator int() const { return w; }
	
	modulo() {}
	modulo(int w, bool f = 0) { this->w = w; if (f) fix(); }
	void inline fix() { if (w >= mod || w < -mod) w %= mod; if (w < 0) w += mod; }
	
	inline modulo  operator -  () { w = -w + mod; return *this; }
	inline modulo  operator +  (const modulo &b) { modulo r = *this; return r += b; }
	inline modulo  operator -  (const modulo &b) { modulo r = *this; return r -= b; }
	inline modulo  operator *  (const modulo &b) { modulo r = *this; return r *= b; }
	inline modulo  operator /  (const modulo &b) { modulo r = *this; return r /= b; }
	inline modulo& operator += (const modulo &b) { if ((w += b.w) >= mod) w -= mod; return *this; }
	inline modulo& operator -= (const modulo &b) { if ((w -= b.w) < 0) w += mod; return *this; }
	inline modulo& operator *= (const modulo &b) { w = (num) w * b.w % mod; return *this; }
	inline modulo& operator /= (const modulo &b) { return *this *= inv(b); }
	
	friend inline modulo inv(const modulo &w) {
		int a = w, m = mod, u = 0, v = 1, t;
		for (; a != 0; t = m / a, m -= t * a, swap(a, m), u -= t * v, swap(u, v));
		return modulo(u, 1);
	}
	
	friend inline modulo pow(const modulo &w, int p) {
		if (!w)  return 0;
		modulo a = w, r = 1;
		for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a;
		return r;
	}
};
const int mod = 998244353;
typedef modulo<mod> rem;

const int nsz = 2e5;
int n, m;
rem pw[nsz + 5], pre[nsz + 5];

struct segment_tree {
	#define ls (u << 1)
	#define rs (u << 1 | 1)
	#define md ((l + r) >> 1)
	#define lp ls, l, md
	#define rp rs, md + 1, r
	
	bool d[4 * nsz + 5];
	int tag[4 * nsz + 5];
	rem res[4 * nsz + 5];
	
	void inline chg(int u, rem w, int l, int r) {
		res[u] = pre[r - l] * w;
		tag[u] = w, d[u] = 1;
	}
	
	void inline down(int u, int l, int r) {
		if (!d[u]) return;
		chg(ls, tag[u], l, md), chg(rs, tag[u], md + 1, r);
		d[u] = 0;
	}
	
	void set(int el, int er, rem w, int u = 1, int l = 1, int r = n) {
		if (l >= el && r <= er) { chg(u, w, l, r); return; }
		down(u, l, r);
		if (el <= md) set(el, er, w, lp);
		if (er > md)  set(el, er, w, rp);
		res[u] = res[ls] * pw[r - md] + res[rs];
	}
	
	rem qry(int el, int er, int u = 1, int l = 1, int r = n) {
		if (l >= el && r <= er) return this->res[u];
		rem res = 0;
		if (el <= md) res = qry(el, er, lp);
		if (er > md)  res = res * pw[r - md] + qry(el, er, rp);
		return res;
	}
};
segment_tree tr;

void inline pow_init() {
	pw[0] = pre[0] = 1;
	cont (i, nsz) pw[i] = pw[i - 1] * rem(10), pre[i] = pre[i - 1] + pw[i];
}

int main() {
	pow_init();
	scanf("%d%d", &n, &m);
	tr.set(1, n, 1);
	cont (i, m) {
		int l, r, w;
		scanf("%d%d%d", &l, &r, &w);
		tr.set(l, r, w);
		printf("%d\n", tr.qry(1, n).w);
	}
}
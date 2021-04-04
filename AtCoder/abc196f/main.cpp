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
	typedef modulo T;
	int w;
	operator int() const { return w; }
	
	modulo() {}
	modulo(int w) { this->w = w; fix(); }
	template<class type> modulo(type w) { this->w = w % mod; fix(); }
	void inline fix() { if (w >= mod || w < -mod) w %= mod; if (w < 0) w += mod; }
	
	inline T  operator -  () const { return mod - w; }
	inline T& operator += (const T &b) { if ((w += b.w) >= mod) w -= mod; return *this; }
	inline T& operator -= (const T &b) { if ((w -= b.w) < 0) w += mod; return *this; }
	inline T& operator *= (const T &b) { w = (unsigned long long) w * b.w % mod; return *this; }
	inline T& operator /= (const T &b) { return *this *= b.inv(); }
	#define make_operation(P)\
	friend inline T operator P (const T &a, const T &b) { return T(a) P##= b; }\
	template<class U> friend inline T operator P (const T &a, const U &b) { return T(a) P##= b; }\
	template<class U> friend inline T operator P (const U &a, const T &b) { return T(a) P##= b; }
	make_operation(+) make_operation(-) make_operation(*) make_operation(/)
	#undef make_operation
	
	T inline inv() const {
		int a = w, m = mod, u = 0, v = 1, t;
		for (; a != 0; t = m / a, m -= t * a, swap(a, m), u -= t * v, swap(u, v));
		return u;
	}
	
	friend inline T pow(const T &w, int p) {
		T a = w, r = 1; for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a; return r;
	}
};
const int mod = 998244353, g_n = 3;
const int degsz = 2097152;
typedef modulo<mod> rem;
typedef unsigned long long u64;

struct fourier_transform {
	int sz, k, rev[degsz + 5];
	u64 sz_inv, pw[degsz + 5];
	
	void inline init(int n) {
		for (sz = 2, k = 1; n >= sz; sz <<= 1, ++k);
		loop (i, sz) rev[i] = rev[i >> 1] >> 1 | (i & 1) << (k - 1);
		pw[0] = 1, sz_inv = rem(1) / sz;
	}
	
	void inline dft(u64 *a, int tp = 1) {
		loop (i, sz) if (i > rev[i]) swap(a[i], a[rev[i]]);
		for (int len = 1; len < sz; len <<= 1) {
			rem w = pow(rem(g_n), (mod - 1) / (len << 1));
			if (tp == -1) w = 1 / w;
			cont (i, len - 1) pw[i] = pw[i - 1] * w;
			for (int l = 0; l < sz; l += len << 1) {
				u64 *w0 = a + l, *w1 = a + l + len, *w = pw, t;
				for (int i = 0; i < len; ++i, ++w0, ++w1, ++w) {
					t = *w1 * *w % mod, *w1 = *w0 + mod - t, *w0 += t;
				}
			}
		}
		loop (i, sz) a[i] %= mod;
		if (tp == -1) loop (i, sz) a[i] = a[i] * sz_inv % mod;
	}
};
fourier_transform ft;

void inline convolution(int n, rem *f, int m, rem *g, int &sz, rem *h) {
	static u64 a[degsz + 5], b[degsz + 5];
	ft.init(sz = n + m);
	loop (i, ft.sz) a[i] = b[i] = 0;
	circ (i, 0, n) a[i] = f[i];
	circ (i, 0, m) b[i] = g[i];
	ft.dft(a), ft.dft(b);
	loop (i, ft.sz) a[i] = a[i] * b[i] % mod;
	ft.dft(a, -1);
	circ (i, 0, sz) h[i] = a[i];
}

const int nsz = 1e6, inf = 0x3f3f3f3f;
int n, m, sz, ans = inf;
rem w0[nsz + 5], w1[nsz + 5], r0[nsz + 5], r1[nsz + 5], r[nsz + 5];
char s[nsz + 5], t[nsz + 5];

void inline solve() {
	reverse(t, t + m);
	n -= 1, m -= 1;
	circ (i, 0, n) w0[i] = s[i] ^ 48;
	circ (i, 0, m) w1[i] = t[i] ^ 48 ^ 1;
	convolution(n, w0, m, w1, sz, r0);
	circ (i, 0, n) w0[i] = s[i] ^ 48 ^ 1;
	circ (i, 0, m) w1[i] = t[i] ^ 48;
	convolution(n, w0, m, w1, sz, r1);
	circ (i, 0, n - m) ans = min(ans, (r0[i + m] + r1[i + m]).w);
	ans = ans == inf ? -1 : ans;
}

int main() {
	scanf("%s", s);
	scanf("%s", t);
	n = strlen(s), m = strlen(t);
	solve();
	printf("%d\n", ans);
}
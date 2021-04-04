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
	operator int() const { return w; }
	
	modulo() {}
	modulo(int w) { this->w = w; fix(); }
	template<class type> modulo(type w) { this->w = w % mod; fix(); }
	void inline fix() { if (w >= mod || w < -mod) w %= mod; if (w < 0) w += mod; }
	
	inline modulo  operator -  () const { return mod - w; }
	inline modulo& operator += (const modulo &b) { if ((w += b.w) >= mod) w -= mod; return *this; }
	inline modulo& operator -= (const modulo &b) { if ((w -= b.w) < 0) w += mod; return *this; }
	inline modulo& operator *= (const modulo &b) { w = (unsigned long long) w * b.w % mod; return *this; }
	inline modulo& operator /= (const modulo &b) { return *this *= inv(b); }
	friend modulo operator + (const modulo& a, const modulo& b) { return modulo(a) += b; }
	template<class type> friend modulo operator + (const modulo &a, const type &b) { return modulo(a) += b; }
	template<class type> friend modulo operator + (const type &a, const modulo &b) { return modulo(a) += b; }
	friend modulo operator - (const modulo& a, const modulo& b) { return modulo(a) -= b; }
	template<class type> friend modulo operator - (const modulo &a, const type &b) { return modulo(a) -= b; }
	template<class type> friend modulo operator - (const type &a, const modulo &b) { return modulo(a) -= b; }
	friend modulo operator * (const modulo& a, const modulo& b) { return modulo(a) *= b; }
	template<class type> friend modulo operator * (const modulo &a, const type &b) { return modulo(a) *= b; }
	template<class type> friend modulo operator * (const type &a, const modulo &b) { return modulo(a) *= b; }
	friend modulo operator / (const modulo& a, const modulo& b) { return modulo(a) /= b; }
	template<class type> friend modulo operator / (const modulo &a, const type &b) { return modulo(a) /= b; }
	template<class type> friend modulo operator / (const type &a, const modulo &b) { return modulo(a) /= b; }
	
	friend inline modulo inv(const modulo &w) {
		int a = w, m = mod, u = 0, v = 1, t;
		for (; a != 0; t = m / a, m -= t * a, swap(a, m), u -= t * v, swap(u, v));
		return u;
	}
	
	friend inline modulo pow(const modulo &w, int p) {
		if (!w)  return 0;
		modulo a = w, r = 1;
		for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a;
		return r;
	}
};
const int mod = 998244353, g_rt = 3;
typedef modulo<mod> rem;
typedef unsigned long long u64;

struct fourier_transform;
struct poly;

const int degsz = 4e4;
struct fourier_transform {
	int k, sz, rev[degsz + 5];
	u64 b[degsz + 5], pw[degsz + 5];
	rem inv;
	
	void inline init(int n) {
		for (sz = 2, k = 1; sz <= n; sz <<= 1, k += 1);
		loop (i, sz) rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (k - 1));
		inv = rem(1) / sz, pw[0] = 1;
	}
	
	void inline dft(u64 *a, int tp = 1) {
		loop (i, sz) if (rev[i] < i) swap(a[i], a[rev[i]]);
		for (int len = 1; len < sz; len <<= 1) {
			rem w = pow(rem(g_rt), (mod - 1) / (len << 1));
			if (tp == -1) w = 1 / w;
			cont (i, len) pw[i] = pw[i - 1] * w;
			for (int l = 0; l < sz; l += len << 1) {
				u64 *w0 = a + l, *w1 = a + l + len, *w = pw, tmp;
				for (int i = 0; i < len; ++i, ++w0, ++w1, ++w) {
					tmp = *w1 * *w % mod, *w1 = *w0 + mod - tmp, *w0 += tmp;
				}
			}
		}
		loop (i, sz) a[i] %= mod;
		if (tp == -1) loop (i, sz) (a[i] *= inv) %= mod;
	}
};
fourier_transform ft;

struct poly {
	int deg;
	vector<rem> d;
	
	poly() {}
	poly(int deg) { set_deg(deg); }
	poly(vector<rem> d): deg(int(d.size() - 1)), d(d) {}
	
	inline rem operator [] (int id) const { return d[id]; }
	inline rem& operator [] (int id) { return d[id]; }
	
	void inline set_deg(int n) { deg = n, d.resize(n + 1, 0); }
	
	friend inline poly fix_deg(poly a, int n) { a.set_deg(n); return a; }
	
	friend inline poly operator * (const poly &f, const poly &g) {
		static u64 a[degsz + 5], b[degsz + 5];
		poly r(f.deg + g.deg);
		ft.init(r.deg);
		loop (i, ft.sz) a[i] = i <= f.deg ? int(f[i]) : 0;
		loop (i, ft.sz) b[i] = i <= g.deg ? int(g[i]) : 0;
		ft.dft(a), ft.dft(b);
		loop (i, ft.sz) a[i] = (a[i] * b[i]) % mod;
		ft.dft(a, -1);
		circ (i, 0, r.deg) r[i] = a[i];
		return r;
	}
	
	friend inline poly pow(poly a, int p, int lim) {
		if (p == 0) return poly(vector<rem>{1});
		poly r = poly(vector<rem>{1});
		for (; p > 0; a = fix_deg(a * a, lim), p >>= 1) if (p & 1) r = fix_deg(r * a, lim);
		return r;
	}
	
	friend inline ostream& operator << (ostream& out, const poly &f) {
		out << '{';
		if (f.deg >= 0) out << f[0];
		cont (i, f.deg) out << ' ' << f[i]; 
		return out << '}';
	}
};

const int nsz = 2e4;
char s[nsz + 5], t[nsz + 5];
int n, chn, cir;
rem ans, fac[2][nsz + 5], dp[nsz + 5][nsz + 5];
poly F, G, R;

void inline factorial_init(int n = nsz + 1) {
	fac[0][0] = 1;
	cont (i, n) fac[0][i] = fac[0][i - 1] * i;
	fac[1][n] = 1 / fac[0][n];
	for (int i = n; i >= 1; --i) fac[1][i - 1] = fac[1][i] * i;
}

void inline solve() {
	G.set_deg(cir);
	circ (k, 0, cir) G[k] = fac[1][k + 1];
	R = fix_deg(poly(vector<rem>{fac[0][n]}) * pow(G, chn, cir), cir);
	circ (k, 0, cir) ans += R[k];
	ans *= fac[0][chn] * fac[0][cir];
}

int main() {
	factorial_init();
	scanf("%s", s), scanf("%s", t);
	n = strlen(s);
	loop (i, n) chn += s[i] == '0' && t[i] == '1';
	loop (i, n) cir += s[i] == '1' && t[i] == '1';
	n = chn + cir;
	solve();
	printf("%d\n", ans.w);
}
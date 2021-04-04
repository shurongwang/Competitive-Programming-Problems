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
const int mod = 998244353;
typedef modulo<mod> rem;

const int nsz = 400;
int n, A, B, a[nsz + 5], b[nsz + 5];
rem ans, fac[2][nsz + 5], c[2][nsz + 5][nsz + 5];

void inline factorial_init(int n = nsz) {
	fac[0][0] = 1;
	cont (i, n) fac[0][i] = fac[0][i - 1] * i;
	fac[1][n] = 1 / fac[0][n];
	for (int i = n; i >= 1; --i) fac[1][i - 1] = fac[1][i] * i;
}

void inline solve() {
	int o = 0, x = 1;
	c[o][0][0] = 1;
	cont (i, n) A += a[i], B += b[i];
	cont (k, n) {
		circ (i, a[k], A) circ (j, 0, B) c[x][i][j] += c[o][i - a[k]][j];
		rem coef = -1, w = rem(a[k]) / A;
		loop (d, b[k]) {
			circ (i, 0, A) circ (j, d, B) c[x][i][j] += coef * c[o][i][j - d];
			coef *= w, coef /= (d + 1);
		}
		swap(o, x), memset(c[x], 0, sizeof(c[x]));
	}
	circ (i, 0, A) circ (j, 0, B) c[o][i][j] = -c[o][i][j];
	c[o][A][0] += 1;
	loop (i, A) circ (j, 0, B) ans += c[o][i][j] * (fac[0][j]) / pow(1 - rem(i) / A, j + 1);
}

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d%d", &a[i], &b[i]);
	factorial_init();
	solve();
	printf("%d\n", ans.w);
}
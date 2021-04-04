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

const int nsz = 5e3;
int n, p;
rem ans, f[nsz + 5][2], fac[2][nsz + 5], dp[nsz + 5][nsz + 5];

rem inline C(int n, int m) {
	return fac[0][n] * fac[1][m] * fac[1][n - m];
}

void inline factorial_init(int n) {
	fac[0][0] = 1;
	cont (i, n) fac[0][i] = fac[0][i - 1] * i;
	fac[1][n] = 1 / fac[0][n];
	for (int i = n; i >= 1; --i) fac[1][i - 1] = fac[1][i] * i;
}

void inline solve() {
	dp[0][0] = 1, dp[0][1] = -1;
	loop (k, n) {
		rem val = 0;
		circ (s, 0, n) {
			val += dp[k][s];
			int l = s + 1, r = min(n, s + p - 2);
			if (val && l <= n && l <= r) dp[k + 1][l] += val, dp[k + 1][r + 1] -= val;
		}
	}
	
	rem res = 0;
	circ (k, 0, n) {
		rem val = 0;
		circ (s, 0, n) {
			val += dp[k][s];
			int sum = n - k + p - s % p;
			if (sum % p && n - k > p - 1 + s) {
				res += C(n, k) * val;
			}
		}
	}
	res *= p - 1;
	ans -= res;
}

int main() {
	scanf("%d%d", &n, &p);
	factorial_init(n);
	f[0][0] = 1;
	loop (i, n) {
		rem w0 = f[i][0], w1 = f[i][1];
		f[i + 1][0] += w1;
		f[i + 1][1] += w1 * (p - 2) + w0 * (p - 1);
	}
	ans = pow(rem(p - 1), n) - f[n][0];
	if (n > p - 1) solve();
	printf("%d\n", ans.w);
}
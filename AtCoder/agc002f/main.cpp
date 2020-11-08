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
	template<typename type> operator type() const { return static_cast<type>(w); }
	
	modulo() {}
	modulo(int w, bool f = 0) { this->w = w; if (f) fix(); }
	void inline fix() { if (w >= mod || w < -mod) w %= mod; if (w < 0) w += mod; }
	
	inline modulo  operator -  () { w = -w + mod; return *this; }
	inline modulo& operator += (const modulo &b) { if ((w += b.w) >= mod) w -= mod; return *this; }
	inline modulo& operator -= (const modulo &b) { if ((w -= b.w) < 0) w += mod; return *this; }
	inline modulo& operator *= (const modulo &b) { w = (unsigned long long) w * b.w % mod; return *this; }
	inline modulo& operator /= (const modulo &b) { return *this *= inv(b); }
	friend modulo operator + (const modulo& a, const modulo& b) { return modulo(a) += b; }
	template<typename type> friend modulo operator + (const modulo &a, const type &b) { return modulo(a) += b; }
	template<typename type> friend modulo operator + (const type &a, const modulo &b) { return modulo(a) += b; }
	friend modulo operator - (const modulo& a, const modulo& b) { return modulo(a) -= b; }
	template<typename type> friend modulo operator - (const modulo &a, const type &b) { return modulo(a) -= b; }
	template<typename type> friend modulo operator - (const type &a, const modulo &b) { return modulo(a) -= b; }
	friend modulo operator * (const modulo& a, const modulo& b) { return modulo(a) *= b; }
	template<typename type> friend modulo operator * (const modulo &a, const type &b) { return modulo(a) *= b; }
	template<typename type> friend modulo operator * (const type &a, const modulo &b) { return modulo(a) *= b; }
	friend modulo operator / (const modulo& a, const modulo& b) { return modulo(a) /= b; }
	template<typename type> friend modulo operator / (const modulo &a, const type &b) { return modulo(a) /= b; }
	template<typename type> friend modulo operator / (const type &a, const modulo &b) { return modulo(a) /= b; }
	friend istream& operator >> (istream& in, modulo& a) { return in >> a.w; }
	friend ostream& operator << (ostream& out, const modulo& a) { return out << a.w; }
	
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
const int mod = int(1e9) + 7;
typedef modulo<mod> rem;

const int nsz = 2e3, msz = nsz * nsz;
int n, k, m;
rem f[2][msz + 5], dp[2][nsz + 5], ans;

void inline factorial_init(int n) {
	f[0][0] = 1;
	cont (i, n) f[0][i] = f[0][i - 1] * i;
	f[1][n] = 1 / f[0][n];
	for (int i = n; i >= 1; --i) f[1][i - 1] = f[1][i] * i;
}

rem inline C(int n, int m) { return f[0][n] * f[1][m] * f[1][n - m]; }

void inline solve() {
	if (k == 1) return (void) (ans = 1);
	int o = 0, x = 1;
	dp[o][0] = 1;
	circ (i, 0, n) {
		circ (j, 0, i) {
			rem val = dp[o][j];
			int lft = m - i - (k - 1) * j;
			dp[x][j] += val;
			if (j + 1 <= i) dp[o][j + 1] += val * C(lft - 1, k - 2);
		}
		if (i == n) ans = dp[o][n];
		swap(o, x);
		memset(dp[x], 0, sizeof(dp[x]));
	}
	ans *= f[0][n];
}

int main() {
	scanf("%d%d", &n, &k);
	m = n * k;
	factorial_init(m);
	solve();
	printf("%d", ans.w);
}
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
const int mod = int(1e9) + 7;
typedef modulo<mod> rem;

const int nsz = 2e3;
int n0, n1, m0, m1, k;
rem dp[2][nsz + 5][2], ans;

bool inline chk(int k0, int k1) {
	return k0 <= n0 && k0 % (k - 1) == m0 && k1 <= n1 && k1 % (k - 1) == m1;
}

void inline solve() {
	m0 = n0 % (k - 1), m1 = n1 % (k - 1);
	int o = 0, x = 1;
	dp[o][0][0] = 1;
	loop (i, n0 + n1) {
		rem val0 = 0, val1 = 0, val;
		circ (d, 0, min(i * k, n1)) {
			val0 = dp[o][d][0], val1 += dp[o][d][1], val = val0 + val1;
			if (chk(i * (k - 1) + 1 - d, d)) ans += val1;
			dp[x][d][0] += val;
			dp[x][d + 1][1] += val, dp[x][d + min(n1 - d, k - 1) + 1][1] -= val;
		}
		swap(o, x);
		memset(dp[x], 0, sizeof(dp[x]));
	}
}

int main() {
	scanf("%d%d%d", &n0, &n1, &k);
	solve();
	printf("%d\n", ans.w);
}
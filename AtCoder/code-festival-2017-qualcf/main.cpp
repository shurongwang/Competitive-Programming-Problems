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
const int mod = int(1e9) + 7;
typedef modulo<mod> rem;

const int msz = 399, nsz = msz / 3;
rem ans, f[msz + 5][nsz + 5], dp[2][msz + 5][nsz + 5][2];
int n, m, a[msz + 5], b[msz + 5], fm_a[msz + 5], fm_b[msz + 5];

void inline solve() {
	f[0][0] = 1;
	loop (i, m) circ (j, 0, min(i, n)) {
		rem val = f[i][j];
		f[i + 1][j + 1] += val;
		f[i + 1][j] += val * (3 * j - i);
	}
	int o = 0, x = 1;
	dp[o][0][0][0] = 1;
	circ (i, 0, m + 1) {
		circ (j, 0, m) circ (k, 0, n) {
			int ni = i + 1, nj = j + 1;
			rem w0 = dp[o][j][k][0], w1 = dp[o][j][k][1];
			if (w0 && ni <= m) {
				if (fm_b[a[ni]] > j) {
					if (k > 0) dp[x][j][k - 1][0] += w0 * k;
					dp[x][j][k][1] += w0;
				} else dp[x][j][k][0] += w0;
			} else dp[x][j][k][1] += w0;
			if (w1 && nj <= m && b[nj] != a[i]) {
				if (fm_a[b[nj]] > i) {
					if (k > 0) dp[o][nj][k - 1][1] += w1 * k;
					dp[o][nj][k + 1][0] += w1;
				} else dp[o][nj][k][1] += w1;
			} else if (i == m + 1 && k == 0) ans += w1;
		}
		swap(o, x), memset(dp[x], 0, sizeof(dp[x]));
	}
	ans *= f[m][n];
}

int main() {
	scanf("%d", &m), n = m / 3;
	cont (i, m) scanf("%d", &a[i]), fm_a[a[i]] = i;
	cont (i, m) scanf("%d", &b[i]), fm_b[b[i]] = i;
	solve();
	printf("%d\n", ans.w);
}
#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int mod; struct modulo {
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
typedef modulo rem;

const int nsz = 1500;
int n;
rem dp[nsz + 5][nsz + 5], pre[nsz + 5][nsz + 5];

int main() {
	scanf("%d%d", &n, &mod);
	circ (k, 0, n) dp[0][k] = 1, pre[0][k] = k + 1;
	cont (i, n) cont (j, n) {
		dp[i][j] = dp[i][j - 1] + dp[i - 1][j - 1] + pre[i - 2][j - 1];
		pre[i][j] = pre[i][j - 1] + dp[i][j];
	}
	printf("%d\n", dp[n][n].w);
}

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
const int mod = int(1e9 + 7);
typedef modulo<mod> rem;

const int nsz = int(3e3);
int n, m;
rem dp[2][nsz + 5][2], ans;

int main() {
	scanf("%d%d", &n, &m);
	n -= 1, m -= 1;
	int o = 0, x = 1;
	circ (k, 0, n) dp[o][k][k == 0] = 1;
	loop (i, m) {
		circ (k, 0, n) {
			rem val = dp[o][k][0];
			if (val) {
				dp[x][k][0] += val * rem(2);
				if (k > 0) dp[x][k - 1][k == 1] += val;
				dp[x][k + 1][0] += val;
			}
			val = dp[o][k][1];
			if (val) {
				dp[x][k][1] += val * rem(2);
				if (k > 0) dp[x][k - 1][1] += val;
				dp[x][k + 1][1] += val;
			}
		}
		swap(o, x);
		memset(dp[x], 0, sizeof(dp[x]));
	}
	circ (k, 0, n) ans += dp[o][k][1];
	ans *= rem(4);
	printf("%d\n", ans.w);
}
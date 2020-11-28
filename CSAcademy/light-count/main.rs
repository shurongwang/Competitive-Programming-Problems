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
const int mod = int(1e9) + 7;
typedef modulo<mod> rem;
typedef modulo<101> Z_101;

const int nsz = 200;
char s[nsz + 5];
int n, r[5];
rem dp[nsz + 5][nsz + 5][5][101], ans;

int main() {
	scanf("%d", &n);
	scanf("%s", s + 1);
	loop (i, 4) {
		static int p10 = 1;
		p10 *= 10, p10 %= 101;
		r[i] = (p10 + 1) % 101;
	}
	cont (i, n) {
		int c = s[i] - '0';
		dp[i][i][3][c] = 1;
		circ (j, i + 1, n) if (s[i] == s[j]) dp[i][j][0][c * 11] = 1;
	}
	circ (len, 0, n) for (int l = 1, r = len; r <= n; ++l, ++r) {
		loop (k, 4) loop (m, 101) {
			rem &val = dp[l][r][k][m];
			val -= dp[l + 1][r - 1][k][m];
			dp[l - 1][r][k][m] += val;
			dp[l][r + 1][k][m] += val;
			if (l <= 1 || r >= n || s[l - 1] != s[r + 1] || !val) continue;
			dp[l - 1][r + 1][(k + 2) % 4][(10 * m + (s[l - 1] - '0') * ::r[(k + 2) % 4]) % 101] += val;
		}
	}
	loop (k, 4) ans += dp[1][n][k][0];
	printf("%d\n", ans.w);
}
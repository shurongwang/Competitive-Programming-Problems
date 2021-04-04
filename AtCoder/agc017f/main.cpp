#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

template<int mod>
struct modulo {
	int w;
	operator int&() { return w; }
	operator int() const { return w; }
	
	modulo() {}
	modulo(int w, bool f = 0) { this->w = w; if (f) fix(); }
	void inline fix() { w %= mod; if (w < 0) w += mod; }
	modulo inline fix(int w) const { w %= mod; if (w < 0) w += mod; return w; }
	
	inline modulo  operator - () { w = -w + mod; return *this; }
	inline modulo& operator += (const modulo &b) { if ((w += b.w) >= mod) w -= mod; return *this; }
	inline modulo& operator -= (const modulo &b) { if ((w -= b.w) < 0) w += mod; return *this; }
	inline modulo& operator *= (const modulo &b) { w = (num) w * b.w % mod; return *this; }
	inline modulo& operator /= (const modulo &b) { w = (num) w * b.inv() % mod; return *this; }
	inline modulo  operator +  (const modulo &b) { modulo r = *this; r += b; return r; }
	inline modulo  operator -  (const modulo &b) { modulo r = *this; r -= b; return r; }
	inline modulo  operator *  (const modulo &b) { modulo r = *this; r *= b; return r; }
	inline modulo  operator /  (const modulo &b) { modulo r = *this; r /= b; return r; }
	
	modulo inline inv() const {
		int a = w, m = mod, u = 0, v = 1, t;
		for (; a != 0; t = m / a, m -= t * a, swap(a, m), u -= t * v, swap(u, v));
		return fix(u);
	}
	
	modulo inline pow(int p) const {
		if (!w)  return 0;
		modulo a = *this, r = 1;
		for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a;
		return r;
	}
};
const int mod = int(1000000007);
typedef modulo<mod> rem;

const int nsz = 20, msksz = (1 << nsz) - 1;
int n, m, k, full, g[nsz + 5][nsz + 5], lg[msksz + 5];
rem dp[2][2][msksz + 5], ans;

int inline lowbit(int S) { return S & -S; }

int inline at(int S, int id) { return S >> id & 1; }

int inline chg(int S, int id, int w) { return S + ((w - at(S, id)) << id); } 

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> k >> m;
	full = (1 << n) - 1;
	memset(g, -1, sizeof(g));
	cont (i, m) {
		int id, lvl, d;
		cin >> id >> lvl >> d;
		--id, --lvl;
		g[id][lvl] = d;
	}
	loop (i, n) lg[1 << i] = i;
	
	int o = 0, x = 1;
	dp[o][0][0] = 1;
	loop (i, k) {
		int oo = 0, xx = 1;
		loop (j, n) {
			circ (S, 0, full) {
				rem val = dp[o][oo][S];
				if (!val) continue;
				if (j == n - 1) { dp[x][0][S] += val; continue; }
				if (at(S, j) == 0) {
					if (g[i][j] == 0 || g[i][j] == -1) dp[o][xx][S] += val;
					if (g[i][j] == 1 || g[i][j] == -1) {
						int to = lg[lowbit(S & (full ^ ((1 << j) - 1)))], nS = chg(to > j ? chg(S, to, 0) : S, j, 1);
						dp[o][xx][nS] += val;
					}
				} else if (g[i][j] == 1 || g[i][j] == -1) dp[o][xx][S] += val;
			}
			swap(oo, xx);
			memset(dp[o][xx], 0, sizeof(dp[o][xx]));
		}
		swap(o, x);
		memset(dp[x], 0, sizeof(dp[x]));
	}
	circ (S, 0, full) ans += dp[o][0][S];
	cout << ans << ln;
}
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
const int mod = 998244353;
typedef modulo<mod> rem;

const int nsz = 2e5;
bool vis[nsz + 5];
int n, m, dm, a[nsz + 5], b[nsz + 5], lft[nsz + 5], rgt[nsz + 5];
rem ans;
vector<int> p[nsz + 5];

struct fenwick_tree {
	int t, vr[nsz + 5][2];
	rem tr[nsz + 5][2];
	
	void inline clear() {
		t += 1;
	}
	
	rem& f(int u, int me) { return vr[u][me] == t ? tr[u][me] : (vr[u][me] = t, tr[u][me] = 0); }
	
	void inline upd(int l, int r, rem w) { upd(l, w), upd(r + 1, -w); }
	void inline upd(int id, rem w0) {
		rem w1 = w0 * rem(id);
		for (int u = id + 1; u <= n + 1; u += u & -u) f(u, 0) += w0, f(u, 1) += w1;
	}
	
	rem inline qry(int l, int r) { return qry(r) - qry(l - 1); }
	rem inline qry(int id) {
		rem r0 = 0, r1 = 0;
		for (int u = id + 1; u > 0; u -= u & -u) r0 += f(u, 0), r1 += f(u, 1);
		return r0 * rem(id + 1) - r1;
	}
};
fenwick_tree dp[2];

void inline discretize() {
	vector<int> d;
	cont (i, n) d.push_back(a[i]);
	cont (i, m) d.push_back(b[i]);
	sort(all(d)), d.erase(unique(all(d)), d.end());
	cont (i, n) a[i] = lower_bound(all(d), a[i]) - d.begin() + 1;
	cont (i, m) b[i] = lower_bound(all(d), b[i]) - d.begin() + 1, vis[b[i]] = 1;
	cont (i, n) {
		if (!vis[a[i]]) continue;
		p[a[i]].push_back(i);
	}
}

void inline solve() {
	static int ss, stk[nsz + 5];
	ss = 0;
	cont (i, n) {
		for (; ss && a[stk[ss - 1]] >= a[i]; --ss);
		lft[i] = ss ? stk[ss - 1] + 1 : 0;
		stk[ss++] = i;
	}
	ss = 0;
	for (int i = n; i >= 1; --i) {
		for (; ss && a[stk[ss - 1]] > a[i]; --ss);
		rgt[i] = ss ? stk[ss - 1] - 1 : n;
		stk[ss++] = i;
	}
	int o = 0, x = 1;
	dp[o].upd(0, 0, 1);
	cont (k, m) {
		int d = b[k];
		loop (i, p[d].size()) {
			int cur = p[d][i], pre = lft[cur], nxt = rgt[cur];
			dp[x].upd(cur, nxt, dp[o].qry(pre, cur));
		}
		swap(o, x);
		dp[x].clear();
	}
	ans = dp[o].qry(n, n);
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n) scanf("%d", &a[i]);
	cont (i, m) scanf("%d", &b[i]);
	discretize();
	solve();
	printf("%d\n", ans);
}
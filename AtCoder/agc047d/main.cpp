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
	void inline fix() { if (w >= mod && w < 0) w %= mod; if (w < 0) w += mod; }
	
	inline modulo operator - () const {}
	inline modulo operator + (const modulo &b) const { modulo r = *this; return r += b; }
	inline modulo operator - (const modulo &b) const { modulo r = *this; return r -= b; }
	inline modulo operator * (const modulo &b) const { return (num) w * b.w % mod; }
	inline modulo operator / (const modulo &b) const { return *this * inv(b); }
	inline modulo& operator += (const modulo &b) { w += b.w; if (w >= mod) w -= mod; return *this; }
	inline modulo& operator -= (const modulo &b) { w -= b.w; if (w < 0) w += mod; return *this; }
	inline modulo& operator *= (const modulo &b) { return *this = *this * b; }
	inline modulo& operator /= (const modulo &b) { return *this = *this / b; }
	
	friend inline modulo inv(const modulo &w) {
		int a = w, m = mod, u = 0, v = 1, t;
		for (; a != 0; t = m / a, m -= t * a, swap(a, m), u -= t * v, swap(u, v));
		return modulo(u, 1);
	}
	
	friend inline modulo pow(const modulo &w, int p) {
		modulo a = w, r = 1;
		for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a;
		return r;
	}
};
const int mod = int(1e9) + 7;
typedef modulo<mod> rem;

const int ksz = 18, nsz = 1 << ksz;
int k, n, m, p[nsz + 5], q[nsz + 5], dep[nsz + 5];
rem pre[nsz + 5], pre_inv[nsz + 5], dp[nsz + 5][2], ans;

struct graph {
	int sz, hd[nsz + 5];

	struct edge {
		int nxt, to;

		edge() {}
		edge(int nxt, int to) {
			this->nxt = nxt, this->to = to;
		}
	} e[nsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
	}
};
graph g;

int inline lca(int a, int b) {
	if (dep[a] > dep[b]) swap(a, b);
	b >>= dep[b] - dep[a];
	if (a == b) return a;
	return a >> (32 - __builtin_clz(a ^ b));
}

vector<int> inline merge(const vector<int> &a, const vector<int> &b) {
	int i = 0, j = 0;
	vector<int> res;
	for (; i < a.size() || j < b.size();) {
		res.push_back(j == b.size() || (i < a.size() && a[i] < b[j]) ? a[i++] : b[j++]);
	}
	return res;
}

vector<int> inline build_virtual_tree(const vector<int> &nd, graph &g, int &rt) {
	static int stk[nsz + 5];
	int ss = 0;
	vector<int> nds;
	loop (i, nd.size()) {
		int u = nd[i];
		if (!ss) { stk[ss++] = u; continue; }
		int p = stk[ss - 1], pp = lca(u, p);
		for (; ss > 1 && dep[stk[ss - 2]] >= dep[pp]; --ss) g.link(stk[ss - 2], stk[ss - 1]);
		if (stk[ss - 1] != pp) g.link(pp, stk[ss - 1]), stk[ss - 1] = pp, nds.push_back(pp);
		stk[ss++] = u;
	}
	for (; ss > 1; --ss) g.link(stk[ss - 2], stk[ss - 1]);
	rt = stk[ss - 1];
	return nds;
}

void dfs(int u) {
	if (dep[u] == k) return;
	int i = g.hd[u], ls, rs;
	ls = g[i].to;
	i = g[i].nxt;
	rs = g[i].to;
	dfs(ls), dfs(rs);
	rem w_ls = pre[ls] * pre_inv[u], w_rs = pre[rs] * pre_inv[u];
	dp[ls][0] *= w_ls, dp[ls][1] *= w_ls;
	dp[rs][0] *= w_rs, dp[rs][1] *= w_rs;
	dp[u][0] = dp[ls][0] + dp[rs][0];
	dp[u][1] = dp[ls][1] + dp[rs][1];
	ans += dp[ls][0] * dp[rs][1] * rem(u);
	ans += dp[ls][1] * dp[rs][0] * rem(u);
}

vector<int> solve(int p = 1) {
	if (dep[p] == k) return vector<int>(1, ::p[p]);
	int ql = 0, qr = 0, rt = 0;
	vector<int> ls = solve(p << 1), rs = solve(p << 1 | 1), nd = merge(ls, rs), nds = build_virtual_tree(nd, g, rt);
	loop (i, ls.size()) dp[ls[i]][0] = pre[q[ls[i]]] * pre_inv[p] * rem(p);
	loop (i, rs.size()) dp[rs[i]][1] = pre[q[rs[i]]] * pre_inv[p];
	dfs(rt);
	loop (i, nd.size()) dp[nd[i]][0] = dp[nd[i]][1] = g.hd[nd[i]] = 0;
	loop (i, nds.size()) g.hd[nds[i]] = 0;
	g.sz = 0;
	return nd;
}

int main() {
	scanf("%d", &k);
	n = (1 << k) - 1, m = (1 << (k - 1)) - 1;	
	cont (i, n - m) {
		int j;
		scanf("%d", &j);
		p[i + m] = j + m;
		q[j + m] = i + m;
	}
	cont (i, n) {
		dep[i] = dep[i >> 1] + 1;
		pre[i] = i == 1 ? rem(1) : pre[i >> 1] * rem(i);
		pre_inv[i] = inv(pre[i]);
	}
	solve();
	printf("%d\n", ans.w);
}

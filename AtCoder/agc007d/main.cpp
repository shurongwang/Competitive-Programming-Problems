#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5;
const num inf = 0x3f3f3f3f3f3f3f3f;
int n, m, a[nsz + 5];
num t, dp[nsz + 5], ans;

struct segment_tree {
	#define ls  (u << 1)
	#define rs  (u << 1 | 1)
	int fm[4 * nsz + 5];
	num mn[4 * nsz + 5], del[4 * nsz + 5];
	
	void inline down(int u) {
		if (!del[u])  return;
		mn[ls] += del[u];
		mn[rs] += del[u];
		del[ls] += del[u];
		del[rs] += del[u];
		del[u] = 0;
	}
	
	void init(int u = 1, int l = 0, int r = n) {
		if (l == r) {
			fm[u] = l;
			return;
		}
		int md = (l + r) >> 1;
		init(ls, l, md);
		init(rs, md + 1, r);
		fm[u] = fm[ls];
	}
	
	void upd(int el, int er, int val, int u = 1, int l = 0, int r = n) {
		if (l >= el && r <= er) {
			mn[u] += val;
			del[u] += val;
			return;
		}
		down(u);
		int md = (l + r) >> 1;
		if (el <= md) {
			upd(el, er, val, ls, l, md);
		}
		if (er > md) {
			upd(el, er, val, rs, md + 1, r);
		}
		fm[u] = mn[ls] < mn[rs] ? fm[ls] : fm[rs];
		mn[u] = min(mn[ls], mn[rs]);
	}
	
	pair<num, int> qry(int el, int er, int u = 1, int l = 0, int r = n) {
		if (l >= el && r <= er)  return make_pair(mn[u], fm[u]);
		down(u);
		int md = (l + r) >> 1, fm = -1;
		num mn = inf;
		pair<num, int> res;
		if (el <= md) {
			res = qry(el, er, ls, l, md);
			mn = res.first, fm = res.second;
		}
		if (er > md) {
			res = qry(el, er, rs, md + 1, r);
			fm = mn < res.first ? fm : res.second, mn = min(mn, res.first);
		}
		return make_pair(mn, fm);
	}
};
segment_tree tr;

num f(int i, int j) {
	return t - 2LL * (a[i] - a[j + 1]);
}

num calc(int i, int j) {
	return dp[j] + 3LL * a[i] - a[j] - 2LL * a[j + 1] + max(0LL, t - 2 * (a[i] - a[j + 1]));
}

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> m >> t;
	cont (i, n) {
		cin >> a[i];
	}
	tr.init();
	int j = 0;
	tr.upd(0, 0, dp[0] - a[0] - 2 * a[1] + max(0LL, t - 2 * (a[0] - a[1])));
	cont (i, n) {
		for (; j < i && f(i, j) <= 0; tr.upd(j, j, -f(i - 1, j)), ++j);
		tr.upd(j, i - 1, -2 * (a[i] - a[i - 1]));
		pair<num, int> tmp = tr.qry(0, i - 1);
		int p = tmp.second;
		dp[i] = calc(i, p);
		tr.upd(i, i, dp[i] - a[i] - 2 * a[i + 1] + max(0LL, t - 2 * (a[i] - a[i + 1])));
	}
	ans = dp[n] + m - a[n];
	cout << ans << ln;
}
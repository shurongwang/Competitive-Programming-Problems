#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 5e3, msz = 2e2;
const num inf = 0x3f3f3f3f3f3f3f3f;
int n, m, a[msz + 5][nsz + 5], b[nsz + 5], ss[msz + 5], stk[msz + 5][nsz + 5];
num ans;

struct segment_tree {
	#define ls (u << 1)
	#define rs (u << 1 | 1)
	#define md ((l + r) >> 1)
	#define lp ls, l, md
	#define rp rs, md + 1, r
	
	num mx[4 * nsz + 5], del[4 * nsz + 5];
	
	void upd(int el, int er, int w, int u = 1, int l = 1, int r = n) {
		if (l >= el && r <= er) return (void) (mx[u] += w, del[u] += w);
		if (el <= md) upd(el, er, w, lp);
		if (er > md)  upd(el, er, w, rp);
		mx[u] = max(mx[ls], mx[rs]) + del[u];
	}
	
	num qry(int el, int er, int u = 1, int l = 1, int r = n) {
		if (l >= el && r <= er) return mx[u];
		num res = -inf;
		if (el <= md) res = qry(el, er, lp);
		if (er > md)  res = max(res, qry(el, er, rp));
		return res + del[u];
	}
};
segment_tree tr;

void inline solve() {
	cont (k, m) stk[k][0] = n + 1;
	for (int r = n; r >= 1; --r) {
		cont (k, m) {
			int *a = ::a[k], *stk = ::stk[k], &ss = ::ss[k], pre = r + 1;
			for (; ss && a[stk[ss]] <= a[r]; pre = stk[ss - 1], --ss) tr.upd(stk[ss], stk[ss - 1] - 1, -a[stk[ss]]);
			stk[++ss] = r, tr.upd(r, pre - 1, a[r]);
		}
		if (r != n) tr.upd(r + 1, n, -b[r]);
		ans = max(ans, tr.qry(r, n));
	}
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n - 1) scanf("%d", &b[i]);
	cont (i, n) cont (j, m) scanf("%d", &a[j][i]);
	solve();
	printf("%lld\n", ans);
}
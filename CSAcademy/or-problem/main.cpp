#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5, lgsz = 20, asz = (1 << 20) - 1;
const num inf = 0x3f3f3f3f3f3f3f3f;
int n, k, a[nsz + 5];
num ans;

struct value {
	int cnt;
	num w;
	
	value() { w = cnt = 0; }
	value(num w, int cnt): w(w), cnt(cnt) {}
	
	bool inline operator < (const value &b) const { return w != b.w ? w < b.w : cnt > b.cnt; }
	
	value inline operator + (const value &b) const { return value(w + b.w, cnt + b.cnt); }
};
value dp[nsz + 5];

struct element {
	int r, w;
	value val;
	
	element() {}
	element(int r, int w, value val): r(r), w(w), val(val) {}
};

void inline upd(value &a, value b) {
	if (a < b) a = b;
}

value inline calc(int del) {
	static element stk[lgsz + 5], tmp[lgsz + 5];
	int ss = 0;
	cont (i, n) dp[i] = value(-inf, 0);
	stk[ss++] = element(0, 0, dp[0]);
	cont (i, n) {
		loop (s, ss) upd(dp[i], stk[s].val + value((stk[s].w | a[i]) + del, 1));
		loop (s, ss) tmp[s] = stk[s], tmp[s].w |= a[i];
		int sz = 0;
		loop (s, ss) {
			if (sz && stk[sz - 1].w == tmp[s].w) {
				stk[sz - 1].r = tmp[s].r;
				upd(stk[sz - 1].val, tmp[s].val);
			} else stk[sz++] = tmp[s];
		}
		ss = sz;
		stk[ss++] = element(i, 0, dp[i]);
	}
	return dp[n];
}

void inline solve() {
	int l = -asz - 10, r = asz + 10, md = (l + r) >> 1;
	for (; r - l > 1; md = (l + r) >> 1) (calc(md).cnt <= k ? l : r) = md;
	ans = calc(l).w - (num) l * k;
}

int main() {
	scanf("%d%d", &n, &k);
	cont (i, n) scanf("%d", &a[i]);
	solve();
	printf("%lld\n", ans);
	return 0;
}
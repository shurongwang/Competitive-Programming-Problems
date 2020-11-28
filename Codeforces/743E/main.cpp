#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e3, asz = 8, csz = nsz / asz;
const int msk2sz = (1 << asz) - 1, msk3sz = 6560;
const int inf = 0x3f3f3f3f;
short lg2[msk2sz + 5];
int pw3[asz + 5];
int n, a[nsz + 5], nxt[nsz + 5][asz + 5], ans;

int inline at(int S, int id) { return S / pw3[id] % 3; }

int inline chg(int S, int id, int w) { return S += (w - at(S, id)) * pw3[id]; }

void inline init() {
	static int lst[asz + 5];
	loop (i, asz) lg2[1 << i] = i;
	pw3[0] = 1;
	cont (i, asz) pw3[i] = pw3[i - 1] * 3;
	loop (i, asz) lst[i] = inf;
	for (int i = n; i >= 0; --i) {
		if (i) --a[i];
		loop (c, asz) nxt[i][c] = lst[c];
		lst[a[i]] = i;
	}
}

void inline upd(int &a, int b) {
	if (a > b) a = b;
}

bool inline chk(int k) {
	static const int full = msk2sz;
	int dp[msk2sz + 5][asz + 5][csz + 5];
	memset(dp, inf, sizeof(dp));
	loop (c, asz) dp[1 << c][c][0] = 0;
	cont (S, full) {
		loop (c, asz) {
			loop (cnt, k) {
				int p = dp[S][c][cnt];
				if (p <= n) upd(dp[S][c][cnt + 1], nxt[p][c]);
			}
			int p = dp[S][c][k];
			if (p <= n) for (int t = S ^ full, d = t & -t; d; t -= d, d = t & -t) {
				int c = lg2[d];
				upd(dp[S | (1 << c)][c][0], p);
			}
		}
	}
	loop (c, asz) if (dp[full][c][k] <= n) return 1;
	return 0;
}

int inline calc(int k) {
	static const int full = msk3sz;
	int dp[msk3sz + 5][asz + 5][csz + 5];
	memset(dp, inf, sizeof(dp));
	int res = 0;
	
	loop (c, asz) dp[chg(0, c, 1)][c][0] = 0;
	cont (S, full) {
		loop (c, asz) {
			int p;
			loop (cnt, k) {
				p = dp[S][c][cnt];
				if (p <= n) upd(dp[S][c][cnt + 1], nxt[p][c]);
			}
			p = dp[S][c][k];
			if (p <= n) {
				upd(dp[chg(S, c, 2)][c][k + 1], nxt[p][c]);
				loop (c, asz) {
					if (at(S, c)) continue;
					upd(dp[chg(S, c, 1)][c][0], p);
				}
			}
			p = dp[S][c][k + 1];
			if (p <= n) loop (c, asz) {
				if (at(S, c)) continue;
				upd(dp[chg(S, c, 1)][c][0], p);
			}
		}
	}
	cont (S, full) {
		bool f = 1;
		int sum = 0;
		loop (c, asz) if (!at(S, c)) { f = 0; break; } else sum += at(S, c) - 1;
		if (!f) continue;
		f = 0;
		loop (c, asz) f |= (dp[S][c][k] <= n) || (dp[S][c][k + 1] <= n);
		if (f) res = max(res, k * asz + sum);
	}
	return res;
}

void inline solve() {
	int l = 0, r = n / asz + 1, md = (l + r) >> 1;
	for (; r - l > 1; md = (l + r) >> 1) {
		(chk(md) ? l : r) = md;
	}
	ans = calc(l);
}

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &a[i]);
	init();
	solve();
	printf("%d\n", ans);
}
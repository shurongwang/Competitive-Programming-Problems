#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e3, inf = 0x3f3f3f3f;
int n, k, a[nsz + 5], ans;

void inline upd(int &a, int b) {
	if (a > b) a = b;
}

bool inline chk(num h) {
	static int dp[nsz + 5][nsz + 5];
	int res = inf;
	memset(dp, inf, sizeof(dp));
	dp[0][0] = 0;
	loop (i, n + 1) circ (j, 0, i) {
		int val = dp[i][j], dis = abs(a[i + 1] - a[j]);
		if (val == inf) continue;
		upd(dp[i + 1][j], dp[i][j] + 1);
		if (j == 0 || h * (i - j + 1) >= dis) upd(dp[i + 1][i + 1], val);
	}
	circ (k, 0, n) upd(res, dp[n][k]);
	return res <= k;
}

void inline solve() {
	num l = -1, r = 2e9, md = (l + r) >> 1;
	for (; r - l > 1; md = (l + r) >> 1) (chk(md) ? r : l) = md;
	ans = r;
}

int main() {
	scanf("%d%d", &n, &k);
	cont (i, n) scanf("%d", &a[i]);
	solve();
	printf("%d\n", ans);
	return 0;
}
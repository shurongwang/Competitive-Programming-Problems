#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 300;
const num inf = 0x3f3f3f3f3f3f3f3f;
int n, m, a[nsz + 5];
num dp[2][nsz + 5][nsz + 5], ans = inf;

void inline upd(num &a, num b) {
	if (a > b) a = b;
}

void inline solve() {
	int o = 0, x = 1;
	memset(dp, inf, sizeof(dp));
	dp[o][0][0] = 0;
	cont (i, n) {
		circ (j, 0, min(m, i - 1)) loop (p, i) {
			num val = dp[o][j][p];
			if (val == inf) continue;
			if (j + 1 <= m) upd(dp[x][j + 1][p], val);
			upd(dp[x][j][i], val + max(a[i] - a[p], 0));
		}
		swap(o, x);
		memset(dp[x], inf, sizeof(dp[x]));
	}
	circ (j, 0, m) circ (p, 0, n) upd(ans, dp[o][j][p]);
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n) scanf("%d", &a[i]);
	solve();
	printf("%lld\n", ans);
}
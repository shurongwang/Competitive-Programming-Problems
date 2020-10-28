#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e2, msz = 2 * nsz, inf = 0x3f3f3f3f;
int ts, n, a[nsz + 5], dp[nsz + 5][msz + 5], ans;

void inline solve() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	memset(dp, inf, sizeof(dp));
	ans = inf;
	dp[0][0] = 0;
	cont (i, n) {
		int mn = inf;
		circ (j, 0, msz) {
			mn = min(mn, dp[i - 1][j]);
			circ (k, j + 1, msz) {
				dp[i][k] = min(dp[i][k], mn + abs(k - a[i]));
			}
		}
	}
	circ (k, 0, msz) ans = min(ans, dp[n][k]);
	printf("%d\n", ans);
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
	}
}
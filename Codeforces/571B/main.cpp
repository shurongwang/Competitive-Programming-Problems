#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 3e5, ksz = int(5e3);
const num inf = 0x3f3f3f3f3f3f3f3f;
int n, k, m1, m2, b1, b2, a[nsz + 5];
num dp[2][ksz + 5], ans;

void inline upd(num &a, num b) {
	if (a > b) a = b;
}

void inline solve() {
	sort(a + 1, a + n + 1);
	int o = 0, x = 1;
	memset(dp, inf, sizeof(dp));
	dp[0][0] = 0;
	loop (i, m1 + m2) {
		circ (k1, 0, i) {
			int k2 = i - k1, p = k1 * b1 + k2 * b2 + 1;
			num val = dp[o][k1];
			upd(dp[x][k1], val + a[p + b2 - 1] - a[p]);
			upd(dp[x][k1 + 1], val + a[p + b1 - 1] - a[p]);
		}
		swap(o, x);
		memset(dp[x], inf, sizeof(dp[x]));
	}
	ans = dp[o][m1];
}

int main() {
	scanf("%d%d", &n, &k);
	b1 = n / k, b2 = n / k + 1;
	m2 = n % k, m1 = k - m2;
	cont (i, n) scanf("%d", &a[i]);
	solve();
	printf("%lld\n", ans);
}
#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 50;
int n;
num s, a[nsz + 5], d[nsz + 5], k[nsz + 5], dp[2][2];

void inline solve() {
	int o = 0, x = 1;
	dp[o][0] = 1;
	loop (i, n) {
		loop (b, 2) {
			num c = d[i] + b, val = dp[o][b];
			if (val == 0) continue;
			dp[x][c / k[i]] += val;
			if (c % k[i]) dp[x][1] += val;
		}
		swap(o, x);
		memset(dp[x], 0, sizeof(dp[x]));
	}
	printf("%lld\n", dp[o][0]);
}

int main() {
	scanf("%d%lld", &n, &s);
	loop (i, n) scanf("%lld", &a[i]);
	loop (i, n - 1) k[i] = a[i + 1] / a[i];
	k[n - 1] = num(1e18);
	for (int i = n - 1; i >= 0; --i) d[i] = s / a[i], s %= a[i];
	solve();
}
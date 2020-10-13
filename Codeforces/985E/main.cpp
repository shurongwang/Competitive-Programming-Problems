#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 5e5;
int n, k, d, a[nsz + 5], dp[nsz + 5], pre[nsz + 5];

int inline qry(int l, int r) { return pre[r] - (l > 0 ? pre[l - 1] : 0); }

int main() {
	scanf("%d%d%d", &n, &k, &d);
	cont (i, n) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	dp[0] = pre[0] = 1;
	for (int l = 0, i = 1; i <= n; ++i) {
		for (; a[i] - a[l] > d; ++l);
		if (l <= i - k + 1 && qry(l - 1, i - k)) dp[i] = 1;
		pre[i] = pre[i - 1] + dp[i];
	}
	printf(dp[n] ? "YES\n" : "NO\n");
}
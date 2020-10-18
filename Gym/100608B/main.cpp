#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 64;
char s[nsz + 5];
int n, pre[nsz + 5];
num k, dp[nsz + 5];

bool inline potential_border(int n, int k) {
	for (int i = 0, j = n - k; i < k; ++i, ++j) {
		if (s[i] != '?' && s[j] != '?' && s[i] != s[j]) return 0;
	}
	return 1;
}

num inline calc(int n) {
	if (dp[n] != -1) return dp[n];
	if (n == 1) return dp[n] = s[0] == '?' ? 2 : 1;
	num res = 1LL << pre[n];
	cont (k, n / 2) if (potential_border(n, k)) res -= calc(k) * (1LL << (pre[n - k] - pre[k]));
	return dp[n] = res;
}

void inline solve() {
	num mn_rk = 0, cur;
	loop (i, n) s[i] = '?', pre[i + 1] = i + 1;
	loop (i, n) {
		circ (j, i, n) dp[j] = -1, pre[j] -= j >= i + 1;
		s[i] = 'a', cur = calc(n);
		if (mn_rk + cur < k) s[i] = 'b', mn_rk += cur;
	}
	s[n] = '\0';
	printf("%s\n", s);
}

int main() {
	freopen("borderless.in", "r", stdin);
	freopen("borderless.out", "w", stdout);
	for (; scanf("%d%lld", &n, &k) == 2 && n + k;) {
		solve();
	}
}
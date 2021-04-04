#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 50, lgsz = 18, msksz = (1 << lgsz) - 1;
int n, k, Tand, Tor, a[nsz + 5];
num ans, C[nsz + 5][nsz + 5], sum[nsz + 5];

void inline init() {
	for (int i = 1, s = 0, sz = n; i <= sz; ++i) {
		if ((a[i] & Tand) != Tand || (a[i] | Tor) != Tor) continue;
		a[n = ++s] = a[i];
	}
	circ (i, 0, n) {
		C[i][0] = 1;
		cont (j, min(i, k)) {
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
			sum[i] += C[i][j];
		}
	}
}

void inline solve() {
	static bool vis[msksz + 5];
	static int cnt[msksz + 5], s[msksz + 5];
	if ((Tand & Tor) != Tand) return (void) (ans = 0);
	for (int T = Tand ^ Tor, S = T, sz = 0;; S = (S - 1) & T, sz = 0) {
		num res = 0;
		cont (i, n) {
			int w = a[i] & S;
			if (!vis[w]) s[sz++] = w, vis[w] = 1;
			cnt[w] += 1;
		}
		loop (i, sz) res += sum[cnt[s[i]]];
		ans += __builtin_popcount(S) & 1 ? -res : +res;
		loop (i, sz) cnt[s[i]] = vis[s[i]] = 0;
		if (S == 0) break;
	}
}

int main() {
	scanf("%d%d%d%d", &n, &k, &Tand, &Tor);
	cont (i, n) scanf("%d", &a[i]);
	init();
	solve();
	printf("%lld\n", ans);
}
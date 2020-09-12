
#include <bits/stdc++.h>

#define ln                '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fr, to)    for (int i = fr; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 3e3;
int ts, n, a[nsz + 5], pre[nsz + 5], suf[nsz + 5];
num res, ans;

void inline ins(int w) {
	pre[w] += 1;
	res += suf[w];
}

void inline del(int w) {
	suf[w] -= 1;
	res -= pre[w];
}

void inline solve() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &a[i]);
	ans = 0;
	cont (l, n) {
		res = 0;
		cont (i, n) pre[i] = suf[i] = 0;
		circ (i, l + 1, n) suf[a[i]] += 1;
		del(a[l + 1]);
		res = 0;
		circ (r, l + 1, n) {
			if (a[r] == a[l]) ans += res;
			ins(a[r]);
			del(a[r + 1]);
		}
	}
	printf("%lld\n", ans);
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
	}
}
#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int k;
num l, r, ans;

void inline solve() {
	num d = 1LL << k, p = -1, q = l | d, full = (1LL << (k + 1)) - 1;
	loop (i, k) {
		if (d + (1LL << i) <= r) p = i;
		else break;
	}
	p = d + (1LL << (p + 1)) - 1;
	q = max(q, p + 1);
	ans += full - q + 1 + (p ^ d) + (d - l + 1);
}

int main() {
	scanf("%lld%lld", &l, &r);
	cin >> l >> r;
	for (num a = r; a; a >>= 1, ++k);
	--k;
	for (; k >= 0 && (l >> k & 1) == (r >> k & 1); --k);
	l &= (1LL << (k + 1)) - 1;
	r &= (1LL << (k + 1)) - 1;
	solve();
	printf("%lld\n", ans);
}
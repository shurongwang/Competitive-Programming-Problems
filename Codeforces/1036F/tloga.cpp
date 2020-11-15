#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int ts;
num n, ans;
vector<num> d;

bool inline is_perfect_square(num a) {
	num q = sqrt(a);
	if (q * q == a || (q - 1) * (q - 1) == a || (q + 1) * (q + 1) == a) return 1;
	return 0;
}

void inline init() {
	num b1 = 1e6, b2 = 1e18;
	for (num k = 2; k <= b1; ++k) for (num a = k * k; a <= b2 / k;) {
		a *= k;
		if (!is_perfect_square(a)) d.push_back(a);
	}
	d.push_back(0);
	sort(all(d)), d.erase(unique(all(d)), d.end());
}

void inline solve() {
	scanf("%lld", &n);
	ans = n - 1;
	ans -= upper_bound(all(d), n) - d.begin() - 1;
	ans -= int(sqrt(n)) - 1;
	printf("%lld\n", ans);
}

int main() {
	scanf("%d", &ts);
	init();
	cont (cs, ts) {
		solve();
	}
}
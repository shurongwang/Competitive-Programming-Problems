#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

num n, h;

bool inline chk(num k) {
	if (k <= h) return (long double) (k + 1) * k / 2 >= n;
	long long d = k - h + 1, r = d / 2;
	long double sum = (long double) (2 * h + r - 1) * r + (d & 1) * (h + r) - h + (h + 1) * h / 2;
	return sum >= n;
}

num inline solve() {
	num l = 0, r = n, md = (l + r) >> 1;
	for (; r - l > 1; md = (l + r) >> 1) (chk(md) ? r : l) = md;
	return r;
}

int main() {
	scanf("%lld%lld", &n, &h);
	printf("%lld\n", solve());
}
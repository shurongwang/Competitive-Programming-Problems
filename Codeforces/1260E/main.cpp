#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1 << 18;
int n, k, a[nsz + 5];
num ans;
multiset<int> s;

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &a[i]);
	for (int a = n - 1; a; a >>= 1, ++k);
	cont (i, n) {
		if (a[i] == -1) { a[i] = 0; break; }
		a[i] = 0;
	}
	reverse(a + 1, a + n + 1);
	ans += a[1];
	for (int i = k - 1, it = 2; i >= 1; --i) {
		for (int to = it + (1 << i); it < to; ++it) s.insert(a[it]);
		ans += *s.begin();
		s.erase(s.begin());
	}
	printf("%lld\n", ans);
}
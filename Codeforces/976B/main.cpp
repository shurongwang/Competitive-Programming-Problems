#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

num n, m, k;

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> m >> k;
	k += 1;
	if (k <= n) cout << k << ' ' << 1 << ln;
	else {
		k -= n;
		num r = (k - 1) / (m - 1) + 1;
		if (r & 1) cout << n - r + 1 << ' ' << (k - 1) % (m - 1) + 2 << ln;
		else cout << n - r + 1 << ' ' << m - (k - 1) % (m - 1) << ln;
	}
}
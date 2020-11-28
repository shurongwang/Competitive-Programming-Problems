#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

num S, P;

int main() {
	scanf("%lld%lld", &S, &P);
	cont (a, 1e6) {
		if (S - a <= 0) break;
		if (a * (S - a) == P) { cout << "Yes" << ln; return 0; }
	}
	cout << "No" << ln;
}
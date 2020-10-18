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

int main() {
	cin >> ts;
	cont (cs, ts) {
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 == x2 || y1 == y2) {
			cout << abs(x1 - x2) + abs(y1 - y2) << ln;
		} else {
			cout << abs(x1 - x2) + abs(y1 - y2) + 2 << ln;
		}
	}
}
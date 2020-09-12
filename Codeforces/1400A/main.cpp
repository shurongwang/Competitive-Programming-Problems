
#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int ts, n;
string s;

void inline solve() {
	cin >> n >> s;
	for (int i = 0; i < s.size(); i += 2) {
		cout << s[i];
	}
	cout << ln;
}

int main() {
	cin >> ts;
	cont (cs, ts) {
		solve();
	}
}
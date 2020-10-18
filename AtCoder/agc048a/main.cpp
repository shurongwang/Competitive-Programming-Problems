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
string s, t = "atcoder";

void inline solve() {
	cin >> s;
	if (t < s) {
		cout << 0 << ln;
		return;
	}
	int p = -1;
	loop (i, s.size()) {
		if (s[i] != 'a') {
			p = i;
			break;
		}
	}
	if (p == -1) {
		cout << -1 << ln;
		return;
	}
	cout << p - (s[p] > 't') << ln;
}

int main() {
	ios::sync_with_stdio(0);
	cin >> ts;
	cont (cs, ts) {
		solve();
	}
}
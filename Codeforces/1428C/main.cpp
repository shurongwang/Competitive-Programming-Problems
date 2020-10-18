#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5;
bool del[nsz + 5];
int ts, ss, stk[nsz + 5], ans;
string s;

void inline solve() {
	cin >> s;
	loop (i, s.size()) {
		if (s[i] == 'A') stk[ss++] = i;
		else if (ss && s[stk[ss - 1]] == 'A') {
			del[i] = del[stk[ss - 1]] = 1;
			--ss;
		}
	}
	string t;
	loop (i, s.size()) if (!del[i]) t += s[i];
	loop (i, t.size()) {
		if (t[i] == 'B' && t[i + 1] == 'B') i += 1;
		else ++ans;
	}
	cout << ans << ln;
}

void inline clear() {
	loop (i, s.size()) del[i] = 0;
	ans = ss = 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin >> ts;
	cont (i, ts) {
		solve();
		clear();
	}
}
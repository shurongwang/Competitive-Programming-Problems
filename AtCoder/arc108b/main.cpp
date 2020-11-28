#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int n, ans;
string s, stk;

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> s;
	ans = n;
	loop (i, n) {
		if (s[i] == 'x' && stk.size() >= 2 && stk.substr(stk.size() - 2, 2) == "fo") {
			stk.pop_back(), stk.pop_back();
			ans -= 3;
		} else stk += s[i];
	}
	cout << ans << ln;
}
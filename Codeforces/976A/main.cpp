#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int n;
string s;

int main() {
	ios::sync_with_stdio(0);
	cin >> n >> s;
	if (s == "0") cout << s << ln;
	else {
		int cnt = 0;
		loop (i, s.size()) cnt += s[i] == '0';
		cout << 1;
		cont (i, cnt) cout << 0;
		cout << ln;
	}
}
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
int n, a[nsz + 5], b[nsz + 5], da[nsz + 5], db[nsz + 5];
vector<int> s, z;

void inline z_init(const vector<int> &s, vector<int> &z) {
	z.resize(s.size(), 0);
	for (int i = 1, l = 0, r = 0; i < s.size(); ++i) {
		i <= r && (z[i] = min(r - i + 1, z[i - l]));
		for (; i + z[i] < s.size() && s[z[i]] == s[i + z[i]]; ++z[i]);
		i + z[i] - 1 > r && (l = i, r = i + z[i] - 1);
	}
}

void inline differentiate(int *a) {
	int w = a[0] ^ a[n - 1];
	loop (i, n - 1) a[i] ^= a[i + 1];
	a[n - 1] = w;
}

int main() {
	scanf("%d", &n);
	loop (i, n) scanf("%d", &a[i]), da[i] = a[i];
	loop (i, n) scanf("%d", &b[i]), db[i] = b[i];
	differentiate(da);
	differentiate(db);
	loop (i, n) s.push_back(db[i]);
	s.push_back(-1);
	loop (i, n) s.push_back(da[i]);
	loop (i, n) s.push_back(da[i]);
	z_init(s, z);
	loop (i, n) z[i] = z[i + n + 1];
	loop (i, n) if (z[i] == n) printf("%d %d\n", i, b[0] ^ a[i]);
}
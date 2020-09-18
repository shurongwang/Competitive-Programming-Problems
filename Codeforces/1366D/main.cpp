#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int asz = 3163;
int n;
vector<int> p;
vector<pair<int, int>> ans;

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

void inline prime_init(int to = asz) {
	static bool inp[asz + 5];
	circ (a, 2, to) {
		if (inp[a]) continue;
		p.push_back(a);
		for (int b = a + a; b <= to; b += a) inp[b] = 1;
	}
}

int inline find_smallest_prime(int a) {
	loop (i, p.size()) {
		int p = ::p[i];
		if (a % p == 0) return p;
	}
	return a;
}

int inline log_of(int a, int b) {
	int res = 0;
	for (; a % b == 0; a /= b, ++res);
	return res;
}

int main() {
	prime_init();
	scanf("%d", &n);
	cont (i, n) {
		int a, p, q, e;
		scanf("%d", &a);
		p = find_smallest_prime(a);
		e = log_of(a, p);
		q = a / pow(p, e);
		if (q > 1) ans.push_back({a / q, q});
		else ans.push_back({-1, -1});
	}
	loop (i, ans.size()) printf("%d%c", ans[i].first, "\n "[i < ans.size() - 1]);
	loop (i, ans.size()) printf("%d%c", ans[i].second, "\n "[i < ans.size() - 1]);
}
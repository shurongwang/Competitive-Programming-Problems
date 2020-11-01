#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e6;
char s[nsz + 5], t[nsz + 5];
int n, m;
vector<int> e, l;

vector<int> inline operator * (const vector<int> &a, const vector<int> &b) {
	vector<int> r(n);
	loop (i, a.size()) r[i] = b[a[i]];
	return r;
}
vector<int> inline operator *= (vector<int> &a, const vector<int> &b) { return a = a * b; }

vector<int> inline pow(const vector<int> &w, int p) {
	vector<int> r = e, a = w;
	for (; p > 0; a *= a, p >>= 1) if (p & 1) r *= a;
	return r;
}

void inline operate(int k, int d) {
	vector<int> p(n);
	int b = 0, it = 0;
	loop (i, k) {
		p[it] = i;
		if ((it += d) >= k) it = ++b;
	}
	circ (i, k, n - 1) p[i] = i;
	p = pow(p * l, n - k + 1);
	loop (i, n) t[p[i]] = s[i];
	loop (i, n) s[i] = t[(i + k - 1) % n];
}

int main() {
	scanf("%s", s);
	n = strlen(s);
	scanf("%d", &m);
	loop (i, n) e.push_back(i);
	l.push_back(n - 1);
	cont (i, n - 1) l.push_back(i - 1);
	cont (i, m) {
		int k, d;
		scanf("%d%d", &k, &d);
		operate(k, d);
		printf("%s\n", s);
	}
}
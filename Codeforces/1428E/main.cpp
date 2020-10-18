#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e5;
int n, m;
num ans;

struct sheep {
	int s, k;
	num del;
	
	sheep() {}
	sheep(num del, int s, int k) {
		this->del = del, this->s = s, this->k = k;
	}
	
	bool inline operator < (const sheep &b) const { return del < b.del; }
};
priority_queue<sheep> q;

num f(int n, int k) {
	int l = n / k, r = l + 1, cr = n - l * k, cl = k - cr;
	return (num) l * l * cl + (num) r * r * cr;
}

int main() {
	scanf("%d%d", &n, &m);
	cont (i, n) {
		int a;
		scanf("%d", &a);
		q.push(sheep(f(a, 1) - f(a, 2), a, 1));
	}
	cont (i, m - n) {
		sheep cur = q.top(); q.pop();
		int s = cur.s, k = cur.k + 1;
		q.push(sheep(f(s, k) - f(s, k + 1), s, k));
	}
	for (; q.size(); q.pop()) {
		sheep cur = q.top();
		ans += f(cur.s, cur.k);
	}
	printf("%lld\n", ans);
}
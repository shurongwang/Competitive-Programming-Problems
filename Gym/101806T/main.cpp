#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2.5e5;
int n, ans;
priority_queue<num> q;

struct sheep {
	num w, c;
	
	sheep() {}
	sheep(num w, num c) {
		this->w = w, this->c = c;
	}
	
	bool inline operator < (const sheep &b) const { return c - b.w < b.c - w; }
};
sheep a[nsz + 5];

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%lld%lld", &a[i].c, &a[i].w);
	sort(a + 1, a + n + 1);
	num sum = 0;
	cont (i, n) {
		num w = a[i].w, cap = a[i].c;
		if (sum <= cap) q.push(w), sum += w;
		else {
			q.push(w), sum += w;
			sum -= q.top(), q.pop();
		}
	}
	ans = int(q.size());
	printf("%d\n", ans);
}
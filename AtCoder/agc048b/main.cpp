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
int n, a[nsz + 5], b[nsz + 5];
num ans;
priority_queue<int> q[2];

int main() {
	scanf("%d", &n);
	cont (i, n) scanf("%d", &a[i]), ans += a[i];
	cont (i, n) scanf("%d", &b[i]);
	cont (i, n) q[i & 1].push(b[i] - a[i]);
	for (; q[0].size() && q[1].size();) {
		int w1 = q[0].top(), w2 = q[1].top();
		if (w1 + w2 < 0) break;
		ans += w1 + w2;
		q[0].pop(), q[1].pop();
	}
	printf("%lld\n", ans);
}
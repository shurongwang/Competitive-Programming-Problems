
#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

int u = 0, v = 1, d[2], meaningless, ans;

bool inline move(int id) {
	bool res;
	printf("F %c\n", char(id + 'A'));
	fflush(stdout);
	scanf("%d", &res);
	return res;
}

void inline replace(int id) {
	printf("R %c\n", char(id + 'A'));
	fflush(stdout);
}

bool inline same() {
	bool res;
	printf("E\n");
	fflush(stdout);
	scanf("%d", &res);
	return res;
}

bool inline move_and_check(int id, int &dis = meaningless) {
	dis += move(id);
	return same();
}

void inline answer() {
	printf("A %d\n", ans);
	fflush(stdout);
}

int main() {
	circ (k, 0, 20) {
		bool f = 1;
		int len = 1 << k;
		if (f) for (int i = f = 0; i < len && !move_and_check(u, d[u]); ++i, f |= i == len);
		else break;
		if (f) for (int i = f = 0; i < len && !move_and_check(v, d[v]); ++i, f |= i == len);
		else break;
		if (!f) break;
		swap(u, v);
	}
	if (d[u] > d[v]) swap(u, v);
	replace(u), replace(v);
	loop (i, d[v] - d[u]) move(v), ++ans;
	if (!same()) for (ans += 2; !move_and_check(u) && !move_and_check(v); ans += 2);
	answer();
}
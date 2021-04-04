#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e6, ksz = 2e3;
int ts, n, m, k, f[ksz + 5][ksz + 5], fm[ksz + 5][ksz + 5], ans;
char s[nsz + 5], t[nsz + 5];

struct cat {
	char c;
	int tp, id;
	
	cat() {}
	cat(int tp, int id, char c): tp(tp), id(id), c(c) {}
};
vector<cat> res;

bool inline upd(int &a, int b) {
	if (a < b) { a = b; return 1; }
	return 0;
}

void inline solve() {
	scanf("%d%d%d", &n, &m, &k);
	scanf("%s", s), scanf("%s", t);
	if (abs(n - m) > k) return (void) (printf("NO\n"));
	memset(f, -1, sizeof(f)), memset(fm, 0, sizeof(fm));
	for (int i = f[0][k] = 0; i < n && s[i] == t[i]; ++i, ++f[0][k]);
	circ (c, 0, k) {
		circ (d, 0, 2 * k + 1) if (f[c][d] != -1) {
			int i = f[c][d], j = i + d - k;
			{ // insert
				int ni = i, nj = j + 1;
				for (; ni < n && nj < m && s[ni] == t[nj]; ++ni, ++nj);
				if (upd(f[c + 1][d + 1], ni)) fm[c + 1][d + 1] = +1;
			} { // delete
				int ni = i + 1, nj = j;
				for (; ni < n && nj < m && s[ni] == t[nj]; ++ni, ++nj);
				if (d > 0 && upd(f[c + 1][d - 1], ni)) fm[c + 1][d - 1] = -1;
			} { // replace
				int ni = i + 1, nj = j + 1;
				for (; ni < n && nj < m && s[ni] == t[nj]; ++ni, ++nj);
				if (upd(f[c + 1][d], ni)) fm[c + 1][d] = 0;
			}
		}
	}
	int del = m - n + k;
	ans = -1;
	circ (c, 0, k) if (f[c][del] == n) { ans = c; break; }
	if (ans == -1) printf("NO\n");
	else {
		res.clear();
		int c = ans, d = m - n + k;
		for (int del, i = n, j = m; c != 0 || d != k;) {
			del = fm[c][d];
			c -= 1, d -= del;
			i = f[c][d], j = i + d - k;
			res.push_back(cat(del, j + 1, t[j]));
		}
		reverse(all(res));
		printf("YES\n%d\n", int(res.size()));
		loop (i, res.size()) {
			int tp = res[i].tp, id = res[i].id, c = res[i].c;
			if (tp == +1) printf("INSERT %d %c\n", id, c);
			else if (tp == -1) printf("DELETE %d\n", id);
			else printf("REPLACE %d %c\n", id, c);
		}
	}
}

int main() {
	scanf("%d", &ts);
	cont (cs, ts) {
		solve();
	}
}
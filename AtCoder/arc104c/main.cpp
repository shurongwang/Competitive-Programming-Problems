#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e2;
bool f[nsz + 5];
char s[nsz + 5];
int n, fm[nsz + 5], l[nsz + 5], r[nsz + 5];

void inline exit_with(bool can) {
	printf(can ? "Yes\n" : "No\n");
	exit(0);
}

bool inline chk(int l, int r) {
	int md = (l + r) >> 1;
	circ (i, l, md) if (s[i] == ')') return 0;
	circ (i, md + 1, r) if (s[i] == '(') return 0;
	circ (i, l, md) if (fm[i] && ::r[fm[i]] != -1 && ::r[fm[i]] != i + md - l + 1) return 0;
	circ (i, md + 1, r) if (fm[i] && ::l[fm[i]] != -1 && ::l[fm[i]] != i - md + l - 1) return 0;
	circ (i, l, md) {
		int j = i + md - l + 1;
		if (fm[i] && fm[j] && fm[i] != fm[j]) return 0; 
	}
	return 1;
}

int main() {
	scanf("%d", &n);
	cont (i, 2 * n) s[i] = '?';
	cont (i, n) {
		int l, r;
		scanf("%d%d", &l, &r);
		if ((l != -1 && s[l] != '?') || (r != -1 && s[r] != '?')) exit_with(0);
		if (l != -1) s[l] = '(';
		if (r != -1) s[r] = ')';
		::l[i] = l, ::r[i] = r;
		fm[l] = fm[r] = i;
	}
	f[0] = 1;
	cont (i, 2 * n) {
		for (int j = i - 1; j >= 0; --j) {
			if ((i - j) % 2 == 1) continue;
			f[i] |= f[j] & chk(j + 1, i);
		}
	}
	exit_with(f[2 * n]);
}
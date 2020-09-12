
#include <bits/stdc++.h>

#define ln                '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fr, to)    for (int i = fr; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 1e3, ndsz = 13740, alphsz = 9;
int n, k, dp[nsz + 5][ndsz + 5];
vector<int> d;

struct ac_automaton {
	bool vis[ndsz + 5];
	int rt, sz, g[ndsz + 5][alphsz + 5], pr[ndsz + 5];
	
	ac_automaton() { rt = ++sz; }
	
	void inline ins(vector<int> &d) {
		int u = rt;
		loop (i, d.size()) {
			int &v = g[u][d[i]];
			if (!v) v = ++sz;
			u = v;
		}
		vis[u] = 1;
	}
	
	void inline init() {
		static int q[ndsz + 5];
		int ql = 0, qr = 0;
		cont (c, 9) {
			int &v = g[rt][c];
			if (v) pr[v] = rt, q[qr++] = v;
			else v = rt;
		}
		for (; qr - ql;) {
			int u = q[ql++];
			cont (c, 9) {
				int &v = g[u][c];
				if (v) pr[v] = g[pr[u]][c], q[qr++] = v;
				else v = g[pr[u]][c];
			}
		}
	}
};
ac_automaton ma;

bool inline chk(const vector<int> &d) {
	loop (i, d.size()) {
		int s = 0;
		circ (j, i, d.size() - 1) {
			s += d[j];
			if (s != k && k % s == 0) return 0;
		}
	}
	return 1;
}

void dfs(int sum = 0) {
	if (sum == k) {
		if (chk(d)) ma.ins(d);
		return;
	}
	cont (c, 9) {
		if (sum + c > k) break;
		d.push_back(c), dfs(sum + c), d.pop_back();
	}
}

int main() {
	scanf("%d", &k);
	dfs();
	ma.init();
	
}
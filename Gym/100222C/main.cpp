#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;
typedef unsigned long long hsh;

using namespace std;

const int nsz = int(200), alphsz = 26, ksz = 10, lsz = int(1e3), hsz = int(1e5);
const double inf = 1e9;
const hsh bas = 173;
int n, l, k, alph, pre[lsz + 5][nsz + 5];
hsh pp[nsz + 5], full[nsz + 5];
long double p[lsz + 5][alphsz + 5], dp[lsz + 5][nsz + 5];
string s[nsz + 5], ans;
vector<int> to[nsz + 5];

struct hash_table {
	int sz, hd[hsz + 5];
	
	struct node {
		int nxt, fm;
		hsh h;
		
		node() {}
		node(int nxt, int fm, hsh h) {
			this->nxt = nxt, this->fm = fm, this->h = h;
		}
	} nd[nsz + 5];
	
	void inline ins(hsh cur, int id) {
		int u = cur % hsz;
		nd[++sz] = node(hd[u], id, cur), hd[u] = sz;
	}
	
	void inline qry(hsh cur, vector<int> &to) {
		int u = cur % hsz;
		for (int i = hd[u]; i; i = nd[i].nxt) {
			if (nd[i].h == cur) to.push_back(nd[i].fm);
		}
	}
};
hash_table dat;

int main() {
	freopen("decoding.in", "r", stdin);
	freopen("decoding.out", "w", stdout);
	scanf("%d%d%d", &n, &k, &alph);
	cont (id, n) {
		static char str[ksz + 5];
		scanf("%s", str);
		
		string s;
		loop (i, k) s += str[i];
		hsh h = 0;
		::s[id] = s;
		loop (i, s.size()) h = h * bas + s[i];
		full[id] = h;
		h = 0;
		cont (i, s.size() - 1) h = h * bas + s[i];
		pp[id] = h;
		dat.ins(full[id], id);
	}
	cont (i, n) {
		loop (c, alph) {
			hsh cur = pp[i] * bas + (c + 'a');
			dat.qry(cur, to[i]);
		}
	}
	scanf("%d", &l);
	cont (i, l) loop (j, alph) scanf("%Lf", &p[i][j]);
	cont (i, l) cont (j, n) dp[i][j] = -inf;
	cont (i, n) {
		long double cur = 1;
		loop (j, k) {
			double pp = p[j + 1][s[i][j] - 'a'];
			if (pp == 0) {
				cur = -inf;
				break;
			}
			cur *= p[j + 1][s[i][j] - 'a'];
		}
		dp[k][i] = cur * 1000;
	}
	circ (i, k, l) {
		cont (fm, n) {
			if (dp[i][fm] < 0) continue;
			loop (it, to[fm].size()) {
				int to = ::to[fm][it], c = s[to].back() - 'a';
				if (p[i + 1][c] == 0) continue;
				long double cur = dp[i][fm] * p[i + 1][c];
				if (cur > dp[i + 1][to]) {
					dp[i + 1][to] = cur;
					pre[i + 1][to] = fm;
				}
			}
		}
		long double t = inf;
		cont (fm, n) {
			if (dp[i + 1][fm] < 0) continue;
			t = min(t, (long double) 1 / dp[i + 1][fm]);
		}
		cont (fm, n) dp[i + 1][fm] *= t;
	}
	int fm = -1;
	long double res = -inf;
	cont (i, n) {
		if (dp[l][i] > res) res = dp[l][i], fm = i;
	}
	if (fm == -1) {
		printf("---\n");
		return 0;
	}
	for (int i = l; i > k; --i) {
		ans += s[fm].back();
		fm = pre[i][fm];
	}
	string t = s[fm];
	reverse(all(t));
	ans += t;
	reverse(all(ans));
	printf("%s\n", ans.c_str());
	return 0;
}
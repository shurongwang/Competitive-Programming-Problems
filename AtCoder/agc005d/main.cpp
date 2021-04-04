#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e3, mod = 924844033;
int n, m, k, o, x = 1, fac[nsz + 5], dp[2][nsz + 5][2], f[nsz + 5], ans;

void inline upd(int &a, int b) {
    (a += b) && (a >= mod) && (a -= mod);
    (a < 0) && (a += mod);
}

int main() {
    scanf("%d%d", &n, &k);
    fac[0] = f[0] = 1;
    cont (i, n) {
        fac[i] = (num) fac[i - 1] * i % mod;
    }
    cont (s, k) {
        int len = (n - s) / k + 1;
        memset(dp[o], 0, sizeof(dp[o]));
        dp[o][0][0] = 1;
        cont (i, len - 1) {
            loop (j, i) {
                upd(dp[x][j][0], dp[o][j][0]);
                upd(dp[x][j + 1][1], dp[o][j][0]);
                upd(dp[x][j][0], dp[o][j][1]);
            }
            swap(o, x);
            memset(dp[x], 0, sizeof(dp[x]));
        }
        m += len;
        cont (_, 2)  for (int i = m; i >= 0; --i) {
            cont (j, min(len, i)) {
                upd(f[i], (num) f[i - j] * (dp[o][j][0] + dp[o][j][1]) % mod);
            }
        }
    }
    circ (i, 0, n) {
        upd(ans, (num) (i & 1 ? -1 : 1) * fac[n - i] * f[i] % mod);
    }
    printf("%d\n", ans);
}
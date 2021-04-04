#include <bits/stdc++.h>

#define ln                 '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 3e2;
int n, m, mod, dp[nsz + 5][nsz + 5], suf[nsz + 5][nsz + 5], C[nsz + 5][nsz + 5];

void inline upd(int &a, const int b) {
    a += b;
    if (a >= mod) {
        a -= mod;
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &mod);
    circ (i, 0, n) {
        C[i][0] = 1;
        cont (j, i) {
            upd(C[i][j], C[i - 1][j] + C[i - 1][j - 1]);
        }
    }
    for (int i = m; i >= 0; --i) {
        dp[1][i] = 1;
        upd(suf[1][i], suf[1][i + 1] + dp[1][i]);
    }
    circ (i, 2, n + 1) {
        for (int k = m; k >= 0; --k) {
            cont (j, i - 1) {
                upd(dp[i][k], (num) dp[i - j][k] * suf[j][k + 1] % mod * C[i - 2][j - 1] % mod);
            }
            upd(suf[i][k], suf[i][k + 1] + dp[i][k]);
        }
    }
    printf("%d\n", dp[n + 1][0]);
}
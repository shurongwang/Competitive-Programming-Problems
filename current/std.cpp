#include <bits/stdc++.h>
 
#define ed end()
#define bg begin()
#define mp make_pair
#define pb push_back
#define vv(T) v(v(T))
#define v(T) vector<T>
#define all(x) x.bg,x.ed
#define newline puts("")
#define si(x) ((int)x.size())
#define cls(x,v) memset(x,v,sizeof(x))
#define rep(i,n) for(int i=1;i<=n;++i)
#define rrep(i,n) for(int i=0;i<n;++i)
#define srep(i,s,t) for(int i=s;i<=t;++i)
#define drep(i,s,t) for(int i=t;i>=s;--i)
 
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int,int> pii;
const int Maxn = 1e5+10;
const int Inf = 0x7f7f7f7f;
const ll Inf_ll = 1ll*Inf*Inf;
const int Mod = 1e9+7;
const double eps = 1e-7;
 
char s[Maxn];
bool vis[Maxn];
 
int main(){
    int T;
    scanf("%d",&T);
    for(int _=1;_<=T;_++)
    {
        int x, n;
        scanf("%s %d",s+1,&x);
        n = strlen(s+1);
        for(int i=1;i<=n;i++)  vis[i] = false;
        for(int i=1;i<=n;i++)
            if( s[i] == '0' )
            {
                if( i-x >= 1 )  vis[i-x] = true;
                if( i+x <= n )  vis[i+x] = true;
            }
        bool flag = true;
        for(int i=1;i<=n;i++)
            if( s[i] == '1' )
            {
                bool f = false;
                if( i-x >= 1 && !vis[i-x] )  f = true;
                if( i+x <= n && !vis[i+x] )  f = true;
                if( !f )
                {
                    flag = false;
                    break;
                }
            }
        if( !flag )  {puts("-1");continue;}
        for(int i=1;i<=n;i++)  printf("%d",!vis[i]);
        newline;
    }
    return 0;
}
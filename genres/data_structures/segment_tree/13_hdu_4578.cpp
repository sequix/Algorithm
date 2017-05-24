// HDU No.4578 (区间更新的新方法) (2355MS 12884K)
// 1.确定整个lazy更新流程由pushdown和pushup实现
// 2.pushdown将标号下传，并计算考虑标号后下层信息为何
// 3.pushup由下层附加信息更新该层信息
// 4.标号之间存在优先级，在这里set > mul > add
// 5.lazy的具体思想：
//   将所需区间分割到能完整表示其一个子区间的结点上
//   更新其标号，但不再往下继续分割（因为该节点代表了其所有
//   的子区间），这就避免了要更新到叶的麻烦，right, it's lazy.
//   但这时树的信息是不一致的。
//   准确的说是该结点以上的部分(包括该结点)与以下的部分是不一致的
//   那么询问以上部分时是没有问题的，而询问以下部分则需要处理
//   这不一致，所以要将标号pushdown。注意其子节点也是有可能有
//   标号的，所以要注意是合并标号，还是覆盖标号，并且也是
//   因为这个原因，由该结点标号所算出的信息，可能与其子节点
//   算出的信息不一致，所以需要pushup。
#include <cstdio>
using namespace std;
const int MOD = 10007;
const int maxn = 1e5 + 10;
const int maxnode = maxn << 2;
#define lc(o) ((o)<<1)
#define rc(o) ((o)<<1|1)

struct {
    int qT, qL, qR, qV;
    int sum[maxnode][4];
    int L[maxnode], R[maxnode], M[maxnode], sz[maxnode];
    int add[maxnode], mul[maxnode], set[maxnode];

    void build(int o, int l, int r) {
        M[o] = (l + r) >> 1;
        L[o] = l, R[o] = r, sz[o] = r - l + 1;
        add[o] = mul[o] = set[o] = 0;
        sum[o][1] = sum[o][2] = sum[o][3] = 0;
        if(l != r) {
            build(lc(o), l, M[o]);
            build(rc(o), M[o]+1, r);
        }
    }
    void passSet(int o, int s) {
        set[o] = s;
        add[o] = mul[o] = 0;

        int tmp = s % MOD;
        sum[o][1] = (s * sz[o]) % MOD;

        tmp = (tmp * s) % MOD;
        sum[o][2] = (tmp * sz[o]) % MOD;

        tmp = (tmp * s) % MOD;
        sum[o][3] = (tmp * sz[o]) % MOD;
    }
    void passMul(int o, int m) {
        if(mul[o])
            mul[o] = (mul[o] * m) % MOD;
        else
            mul[o] = m % MOD;

        add[o] = (add[o] * m) % MOD;

        int tmp = m % MOD;
        sum[o][1] = (tmp * sum[o][1]) % MOD;

        tmp = (tmp * m) % MOD;
        sum[o][2] = (tmp * sum[o][2]) % MOD;

        tmp = (tmp * m) % MOD;
        sum[o][3] = (tmp * sum[o][3]) % MOD;
    }
    void passAdd(int o, int a) {
        add[o] = (add[o] + a) % MOD;

        int s = sz[o];
        int s1 = sum[o][1], s2 = sum[o][2], s3 = sum[o][3];

        sum[o][1] += (a * s) % MOD;
        sum[o][1] %= MOD;

        int a2 = (a * a) % MOD;
        sum[o][2] += 2*s1*a%MOD + a2*s%MOD;
        sum[o][2] %= MOD;

        int a3 = (a2 * a) % MOD;
        sum[o][3] += 3*a2*s1%MOD + 3*a*s2%MOD + a3*s%MOD;
        sum[o][3] %= MOD;
    }
    void pushdown(int o) {
        if(L[o] == R[o]) return;
        if(set[o]) {
            passSet(lc(o), set[o]);
            passSet(rc(o), set[o]);
            set[o] = 0;
        }
        if(mul[o]) {
            passMul(lc(o), mul[o]);
            passMul(rc(o), mul[o]);
            mul[o] = 0;
        }
        if(add[o]) {
            passAdd(lc(o), add[o]);
            passAdd(rc(o), add[o]);
            add[o] = 0;
        }
    }
    void pushup(int o) {
        if(sz[o] > 1) {
            sum[o][1] = (sum[lc(o)][1] + sum[rc(o)][1]) % MOD;
            sum[o][2] = (sum[lc(o)][2] + sum[rc(o)][2]) % MOD;
            sum[o][3] = (sum[lc(o)][3] + sum[rc(o)][3]) % MOD;
        }
    }
    void update(int o) {
        if(qL <= L[o] && R[o] <= qR) {
            switch(qT) {
                case 1: passAdd(o, qV); break;
                case 2: passMul(o, qV); break;
                case 3: passSet(o, qV); break;
            }
        } else {
            pushdown(o);
            if(qL <= M[o]) update(lc(o));
            if(qR > M[o]) update(rc(o));
            pushup(o);
        }
    }
    int query(int o) {
        if(qL <= L[o] && R[o] <= qR) {
            return sum[o][qV];
        } else {
            pushdown(o);
            int sum = 0;
            if(qL <= M[o]) sum = (sum + query(lc(o))) % MOD;
            if(qR > M[o]) sum = (sum + query(rc(o))) % MOD;
            pushup(o);
            return sum;
        }
    }
} seg;

int main()
{
    int n, m;

    while(~scanf("%d%d", &n, &m) && n+m) {
        seg.build(1, 1, n);
        for(int i = 0; i < m; ++i) {
            scanf("%d%d%d%d", &seg.qT, &seg.qL, &seg.qR, &seg.qV);
            if(seg.qT != 4) seg.update(1);
            else printf("%d\n", seg.query(1));
        }
    }
}

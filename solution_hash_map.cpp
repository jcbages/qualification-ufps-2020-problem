#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX = 5002;
const ll MOD[] = {(ll) (1e9+7), (ll) (1e9+9)}, X[] = {137LL, 139LL};

struct BIT {
    vector<int> arr;
    BIT() {}
    BIT(int sz) { arr.assign(sz+3, 0); }
    void update(int p, int v) {
        while (p < arr.size()) {
            arr[p] += v;
            p += (p&-p);
        }
    }
    int query(int p) {
        int ans = 0;
        while (p > 0) {
            ans += arr[p];
            p -= (p&-p);
        }
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l-1);
    }
};

int add(int a, int b, int m) {
    ll ans = 1LL*a+b;
    return ans >= m ? ans-m : ans;
}

int mul(int a, int b, int m) {
    ll ans = 1LL*a*b;
    return ans >= m ? ans%m : ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, h[] = {0, 0};
    string s;
    cin >> n >> q;
    map<ll, int> h_lst;
    vector<BIT> mat(n+1);
    for (int k = 1; k <= n; ++k) {
        cin >> s;
        mat[k] = BIT(MAX);
        if (k-1 > 0) {
            for (int i = 1; i <= MAX; ++i) {
                mat[k].update(i, mat[k-1].query(i, i));
            }
        }
        for (int i = 0; i < s.size(); ++i) {
            h[0] = h[1] = 0;
            for (int j = i; j < s.size(); ++j) {
                for (int k = 0; k < 2; ++k) {
                    h[k] = add(mul(h[k], X[k], MOD[k]), s[j], MOD[k]);
                }
                ll val = (1LL*h[0]<<32LL) + h[1];
                if (h_lst.find(val) != h_lst.end()) {
                    mat[k].update(h_lst[val], -1);
                }
                h_lst[val] = k;
                mat[k].update(k, 1);
            }
        }
    }
    int lst = 0;
    while (q--) {
        int l, r;
        cin >> l >> r;

        // TODO: enable for online only
        // l = (l+lst-1)%n+1;
        // r = (r+lst-1)%n+1;
        if (l > r) swap(l, r);

        cout << (lst = mat[r].query(l, r)) << "\n";
    }
}

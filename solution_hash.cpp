#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX = 5002;
const int MOD = 1e9+7, X = 137LL;

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

int add(int a, int b) {
    ll ans = 1LL*a+b;
    return ans >= MOD ? ans-MOD : ans;
}

int mul(int a, int b) {
    ll ans = 1LL*a*b;
    return ans >= MOD ? ans%MOD : ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    string s;
    cin >> n >> q;
    map<int, int> h_lst;
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
            int h = 0;
            for (int j = i; j < s.size(); ++j) {
                h = add(mul(h, X), s[j]);
                if (h_lst.find(h) != h_lst.end()) {
                    mat[k].update(h_lst[h], -1);
                }
                h_lst[h] = k;
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

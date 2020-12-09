#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD[] = {(ll) (1e9+7), (ll) (1e9+9)}, X[] = {137LL, 139LL};

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
    vector<string> arr(n);
    vector<vector<ll>> mat(n, vector<ll>(n, 0));
    for (auto &s : arr) cin >> s;

    unordered_set<ll> hashes;
    for (int l = 0; l < n; ++l) {
        hashes.clear();
        for (int r = l; r < n; ++r) {
            string &s = arr[r];
            for (int i = 0; i < s.size(); ++i) {
                h[0] = h[1] = 0;
                for (int j = i; j < s.size(); ++j) {
                    for (int k = 0; k < 2; ++k) {
                        h[k] = add(mul(h[k], X[k], MOD[k]), s[j], MOD[k]);
                    }
                    ll val = (1LL*h[0]<<32LL) + h[1];
                    hashes.insert(val);
                }
            }
            mat[l][r] = hashes.size();
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

        cout << (lst = mat[l-1][r-1]) << "\n";
    }
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<string> arr(n+1);
    for (int i = 1; i <= n; ++i) cin >> arr[i];

    int lst = 0;
    set<string> sub;
    while (q--) {
        int l, r;
        cin >> l >> r;

        // TODO: enable for online only
        // l = (l+lst-1)%n+1;
        // r = (r+lst-1)%n+1;
        if (l > r) swap(l, r);

        sub.clear();
        for (int k = l; k <= r; ++k) {
            string &s = arr[k];
            for (int i = 0; i < s.size(); ++i) {
                for (int j = i; j < s.size(); ++j) {
                    sub.insert(s.substr(i, j-i+1));
                }
            }
        }
        cout << (lst = sub.size()) << "\n";
    }
}

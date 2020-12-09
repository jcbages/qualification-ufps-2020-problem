#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node {
    int edges[26];
    node() { memset(edges, 255, sizeof(edges)); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, h[] = {0, 0};
    string s;
    cin >> n >> q;
    vector<string> arr(n);
    vector<vector<ll>> mat(n, vector<ll>(n, 0));
    for (auto &s : arr) cin >> s;

    vector<node> trie;
    for (int l = 0; l < n; ++l) {
        trie.clear();
        trie.push_back(node());
        for (int r = l; r < n; ++r) {
            string &s = arr[r];
            for (int i = 0; i < s.size(); ++i) {
                int curr = 0;
                for (int j = i; j < s.size(); ++j) {
                    int c = s[j]-'a';
                    int p = trie[curr].edges[c];
                    if (p == -1) {
                        p = trie[curr].edges[c] = trie.size();
                        trie.push_back(node());
                        ++mat[l][r];
                    }
                    curr = p;
                }
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

        cout << (lst = mat[l-1][r-1]) << "\n";
    }
}

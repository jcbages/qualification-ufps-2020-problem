#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int LET = 26;

struct node {
    int lst;
    vector<int> edges;
    node() { edges.assign(LET, -1); lst = 0; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, h[] = {0, 0};
    string s;
    cin >> n >> q;
    vector<string> arr(n);
    for (auto &s : arr) cin >> s;

    int lst = 0;
    vector<node> trie;
    while (q--) {
        int l, r;
        cin >> l >> r;

        // TODO: enable for online only
        // l = (l+lst-1)%n+1;
        // r = (r+lst-1)%n+1;
        if (l > r) swap(l, r);

        trie.clear();
        trie.push_back(node());
        for (int p = l; p <= r; ++p) {
            string &s = arr[p-1];
            for (int i = 0; i < s.size(); ++i) {
                int curr = 0;
                for (int j = i; j < s.size(); ++j) {
                    int c = s[j]-'a';
                    int p = trie[curr].edges[c];
                    if (p == -1) {
                        p = trie[curr].edges[c] = trie.size();
                        trie.push_back(node());
                    }
                    curr = p;
                }
            }
        }

        cout << (lst = trie.size()-1) << "\n";
    }
}

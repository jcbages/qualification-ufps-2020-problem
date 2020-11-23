#include <bits/stdc++.h>
using namespace std;

const int MAX = 5002;

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

struct node {
    int edges[26], lst;
    node() { memset(edges, 255, sizeof(edges)); lst = 0; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    string s;
    cin >> n >> q;
    vector<node> trie = {node()};
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
            int curr = 0;
            for (int j = i; j < s.size(); ++j) {
                int c = s[j]-'a';
                int p = trie[curr].edges[c];
                if (p == -1) {
                    p = trie[curr].edges[c] = trie.size();
                    trie.push_back(node());
                } else {
                    mat[k].update(trie[p].lst, -1);
                }
                trie[p].lst = k;
                mat[k].update(k, 1);
                curr = p;
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

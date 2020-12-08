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
    cout << n << " " << q << "\n"; // print again for final case
    vector<node> trie = {node()};
    vector<BIT> mat(n+1);
    for (int k = 1; k <= n; ++k) {
        cin >> s;
        cout << s << "\n"; // print again for final case
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

        // we need to fetch and A, B such that:
        // l = (A+lst-1)%n+1
        // r = (B+lst-1)%n+1
        // Lets try some A=1, B=1 and calculate the l', r'
        // each 1 unit we add in A will inc l' by one so we have two cases:
        // Case 1: l' < l, so add diff=l-l' to A
        // Case 2: l' > l so add diff=(n-l')+l to A
        // Same applies for B
        int A = 1;
        int lp = (A+lst-1)%n + 1;
        if (lp < l) A += l-lp;
        else A += (n-lp)+l;
        if (A > n) A = (A-1)%n + 1;
        lp = (A+lst-1)%n + 1;

        int B = 1;
        int rp = (B+lst-1)%n + 1;
        if (rp < r) B += r-rp;
        else B += (n-rp)+r;
        if (B > n) B = (B-1)%n + 1;
        rp = (B+lst-1)%n + 1;

        assert(l <= r);
        assert(A >= 1 && A <= n && B >= 1 && B <= n);
        assert(l == lp && r == rp);
        cout << A << " " << B << "\n";

        lst = mat[r].query(l, r);
    }
}

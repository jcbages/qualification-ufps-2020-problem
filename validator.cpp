#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

// define all bounds
const char MINC = 'a', MAXC = 'z';
const int MINN = 1, MAXN = 5000;
const int MINQ = 1, MAXQ = 1000000;
const int MINS = 1, MAXS = 5000;
const int MINLR = 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    // validate n & q
    if (n < MINN || n > MAXN) return -1;
    if (q < MINQ || q > MAXQ) return -1;

    // validate total string length
    int total_len = 0;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        // validate lowercase english letters only (a-z)
        for (char &c : s) if (c < MINC || c > MAXC) return -1;

        // validate individual string length
        int len = s.size();
        if (len < MINS || len > MAXS) return -1;
        total_len += len;
    }
    if (total_len < MINS || total_len > MAXS) return -1;

    // validate each query
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        if (l < MINLR || l > n) return -1;
        if (r < MINLR || r > n) return -1;
    }

    // if we're here, everything was good
    return 0;
}

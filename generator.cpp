// ************************************************
// ********* Usage ./generator <seed> *************
// ************************************************

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

// define all bounds
// (use small values for run_test cases and large for final cases)
const char MINC = 'a', MAXC = 'z';

// SMALL SIZE SETTINGS
// const int MINN = 1, MAXN = 50;
// const int MINQ = 1, MAXQ = 10;
// const int MINS = 1, MAXS = 100;

// MEDIUM SIZE SETTINGS
// const int MINN = 100, MAXN = 800;
// const int MINQ = 1000, MAXQ = 100000;
// const int MINS = 1, MAXS = 3300;

// LARGE SIZE SETTINGS
// const int MINN = 900, MAXN = 5000;
// const int MINQ = 300000, MAXQ = 1000000;
// const int MINS = 1, MAXS = 5000;

int random_int(int l, int r) {
    int v = rand() % (r-l+1); // 0 <= v <= r-l
    return v+l; // l <= v+l <= r
}

// a-z lowercase english letters
string random_string(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        char c = (char) random_int(MINC, MAXC);
        assert(c >= MINC && c <= MAXC);
        s.push_back(c);
    }
    assert(s.size() == len);
    return s;
} 

int main(int argc, char **argv) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // read the seed from input
    if (argc != 2) {
        cerr << "Usage ./generator <seed>" << endl;
        return -1;
    }
    int seed = atoi(argv[1]);
    srand(seed);

    // generate n and q
    int n = random_int(MINN, MAXN);
    int q = random_int(MINQ, MAXQ);
    assert(n >= MINN && n <= MAXN);
    assert(q >= MINQ && q <= MAXQ);
    cout << n << " " << q << "\n";

    // generate n strings
    int total_len = 0, avg_len = MAXS / n;
    for (int i = n; i > 0; --i) {
        int rem = MAXS - total_len - (i-1)*MINS;
        assert(rem >= MINS);

        int len = random_int(
            max(MINS, min(rem, (int) (avg_len * 0.75))),
            min(rem, (int) (avg_len * 1.25))
        );
        assert(len >= max(MINS, 1) && len <= MAXS);

        string s = random_string(len);
        cout << s << "\n";
        total_len += len;
    }
    assert(total_len >= 1 && total_len <= MAXS);

    // generate q queries
    for (int i = 0; i < q; ++i) {
        int l = random_int(1, n);
        int r = random_int(1, n);
        assert(l >= 1 && l <= n);
        assert(r >= 1 && r <= n);
        cout << l << " " << r << "\n";
    }

    // test case finished!
    return 0;
}

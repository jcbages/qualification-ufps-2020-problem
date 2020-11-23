import java.io.*;
import java.util.*;

class Main {
    final int MAX = 5002;

    class BIT {
        int[] arr;
        BIT(int sz) { arr = new int[sz+3]; }
        void update(int p, int v) {
            while (p < arr.length) {
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

    class Node {
        int lst;
        int[] edges;
        Node() {
            lst = 0;
            edges = new int[26];
            Arrays.fill(edges, -1);
        }
    };

    Main(BufferedReader in, PrintWriter out) throws Exception {
        int n, q;
        String s;
        
        String[] vals = in.readLine().split(" ");
        n = Integer.parseInt(vals[0]);
        q = Integer.parseInt(vals[1]);

        List<Node> trie = new ArrayList<Node>();
        trie.add(new Node());
        BIT[] mat = new BIT[n+1];
        for (int k = 1; k <= n; ++k) {
            s = in.readLine();
            mat[k] = new BIT(MAX);
            if (k-1 > 0) {
                for (int i = 1; i <= MAX; ++i) {
                    mat[k].update(i, mat[k-1].query(i, i));
                }
            }
            for (int i = 0; i < s.length(); ++i) {
                int curr = 0;
                for (int j = i; j < s.length(); ++j) {
                    int c = s.charAt(j)-'a';
                    int p = trie.get(curr).edges[c];
                    if (p == -1) {
                        p = trie.get(curr).edges[c] = trie.size();
                        trie.add(new Node());
                    } else {
                        mat[k].update(trie.get(p).lst, -1);
                    }
                    trie.get(p).lst = k;
                    mat[k].update(k, 1);
                    curr = p;
                }
            }
        }
        int lst = 0;
        while (q-- > 0) {
            int l, r;
            vals = in.readLine().split(" ");
            l = Integer.parseInt(vals[0]);
            r = Integer.parseInt(vals[1]);

            // TODO: enable for online only
            // l = (l+lst-1)%n+1;
            // r = (r+lst-1)%n+1;
            if (l > r) {l ^= r; r ^= l; l ^= r;}

            out.println(lst = mat[r].query(l, r));
        }
    }

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out), false);
        new Main(in, out);
        out.close();
    }
}

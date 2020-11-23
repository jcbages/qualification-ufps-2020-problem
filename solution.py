MAX = 5002

class BIT(object):
    def __init__(self, sz):
        self.arr = [0 for _ in range(sz+3)]
    def update(self, p, v):
        while p < len(self.arr):
            self.arr[p] += v
            p += (p&-p)
    def _query(self, p):
        ans = 0
        while p > 0:
            ans += self.arr[p]
            p -= (p&-p)
        return ans
    def query(self, l, r):
        return self._query(r) - self._query(l-1)

class Node(object):
    def __init__(self):
        self.edges = [-1 for _ in range(26)]
        self.lst = 0

def main():
    n, q = map(int, input().split())
    trie = [Node()]
    mat = [None for _ in range(n+1)]
    for k in range(1, n+1):
        mat[k] = BIT(MAX)
        if k-1 > 0:
            for i in range(1, MAX+1):
                mat[k].update(i, mat[k-1].query(i, i))
        s = input()
        for i in range(len(s)):
            curr = 0
            for j in range(i, len(s)):
                c = ord(s[j]) - ord('a')
                p = trie[curr].edges[c]
                if p == -1:
                    trie[curr].edges[c] = len(trie)
                    p = len(trie)
                    trie.append(Node())
                else:
                    mat[k].update(trie[p].lst, -1)
                trie[p].lst = k
                mat[k].update(k, 1)
                curr = p
    lst = 0
    ans = []
    for _ in range(q, 0, -1):
        l, r = map(int, input().split())

        # TODO: enable for online only
        # l = (l+lst-1)%n+1
        # r = (r+lst-1)%n+1
        if l > r: l, r = r, l

        lst = mat[r].query(l, r)
        ans.append(lst)
    print('\n'.join(map(str, ans)))

main()

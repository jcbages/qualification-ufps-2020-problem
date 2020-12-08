import random

random.seed(987654321)

PATH = '../cases'
ALPHA = [1, 2, 4, 8, 10, 20, 25]
MAXN = 5000
MAXQ = 10 ** 6
CHARS = list('abcdefghijklmnopqrstuvwxyz')

for N in ALPHA:
    with open('{}/disjoint_{}'.format(PATH, N), 'w') as f:
        L = MAXN // N
        Q = N * (N + 1) // 2
        assert(Q <= MAXQ)
        f.write('{} {}\n'.format(N, Q))

        random.shuffle(CHARS)
        chars = CHARS[:N]
        assert(len(chars) == N)

        lines = list(map(lambda c : c*L, chars))
        f.write('{}\n'.format('\n'.join(lines)))

        queries = []
        for l in range(1, N+1):
            for r in range(l, N+1):
                queries.append((l, r))
        random.shuffle(queries)
        for l, r in queries: f.write('{} {}\n'.format(l, r))

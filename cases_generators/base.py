import random

random.seed(987654321)

PATH = '../cases'
SIZES = [1, 2500, 5000] + [1, 2, 3, 4, 5] + [70, 60, 50, 40, 30]
LEN = [1, 2, 1] + [5000, 2500, 1666, 1250, 1000] + [70, 83, 100, 125, 166]
MAXQ = 10 ** 6
CHARS = list('abcdefghijklmnopqrstuvwxyz')

for N, L in zip(SIZES, LEN):
    with open('{}/base_{}_{}'.format(PATH, N, L), 'w') as f:
        Q = min(N * (N + 1) // 2, MAXQ)
        f.write('{} {}\n'.format(N, Q))

        lines = [
            ''.join(random.choice(CHARS) for _ in range(L))
            for _ in range(N)
        ]
        f.write('{}\n'.format('\n'.join(lines)))

        if Q != MAXQ:
            queries = []
            for l in range(1, N+1):
                for r in range(l, N+1):
                    queries.append((l, r))
            random.shuffle(queries)
            for l, r in queries: f.write('{} {}\n'.format(l, r))
        else:
            queries = set([])
            for _ in range(Q):
                l = -1
                r = -1
                while l == -1 or (l, r) in queries:
                    l = random.randint(1, N)
                    r = random.randint(l, N)
                queries.add((l, r))
                f.write('{} {}\n'.format(l, r))

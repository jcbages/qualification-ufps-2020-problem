import random

random.seed(987654321)

PATH = '../cases'

FILENAME = ['sm', 'md', 'lg']
MINN_RANGE = [1, 100, 900]
MAXN_RANGE = [50, 800, 5000]
PER_SIZE = 20
MAXQ = 10 ** 6
MAXL = 5000
CHARS = list('abcdefghijklmnopqrstuvwxyz')

for FN, MINN, MAXN in zip(FILENAME, MINN_RANGE, MAXN_RANGE):
    for REP in range(PER_SIZE):
        N = random.randint(MINN, MAXN)
        total_len = 0
        avg_len = MAXL // N
        with open('{}/random_{}_{}'.format(PATH, FN, REP), 'w') as f:
            Q = min(N * (N + 1) // 2, MAXQ)
            f.write('{} {}\n'.format(N, Q))

            lines = []
            for i in range(N, 0, -1):
                rem = MAXL - total_len - (i-1)
                assert(rem >= 1)

                L = random.randint(
                    max(1, min(rem, int(avg_len * 0.75))),
                    min(rem, int(avg_len * 1.25))
                )
                total_len += L
                lines.append(''.join(random.choice(CHARS) for _ in range(L)))
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

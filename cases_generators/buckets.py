import random

random.seed(987654321)

PATH = '../cases'
BUCKETS = [2, 5, 8]
REPS = [(5, 50, 100, 1250), (4, 20, 100, 250), (10, 31, 62, 124)]
LEN = [5000, 5000, 4960]
CHARS = list('abcdefghijklmnopqrstuvwxyz')
MAXQ = 1000000

for TL, B, R_GROUP in zip(LEN, BUCKETS, REPS):
    for R in R_GROUP:
        with open('{}/bucket_{}_{}'.format(PATH, B, R), 'w') as f:
            N = B * R
            assert(TL % (B * R) == 0)
            L = TL // (B * R)
            Q = min(N * (N + 1) // 2, MAXQ)
            f.write('{} {}\n'.format(N, Q))

            bucket_lines = [
                ''.join(random.choice(CHARS) for _ in range(L))
                for _ in range(B)
            ]
            for _ in range(R):
                f.write('{}\n'.format('\n'.join(bucket_lines)))
                random.shuffle(bucket_lines)

            if Q != MAXQ:
                for l in range(1, N+1):
                    for r in range(l, N+1):
                        f.write('{} {}\n'.format(l, r))
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

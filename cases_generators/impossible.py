import random

random.seed(987654321)

PATH = '../cases'
MAXL = 5000
MAXN = 2501
MAXQ = 10 ** 6
CHARS = list('abcdefghijklmnopqrstuvwxyz')

N = MAXN
Q = MAXQ
with open('{}/impossible_{}'.format(PATH, N), 'w') as f:
    f.write('{} {}\n'.format(N, Q))

    # First 2500 lines have 1 char
    lines = [random.choice(CHARS) for _ in range(N-1)]

    # Last line has 2500 chars
    lines.append(''.join(random.choice(CHARS) for _ in range(N-1)))

    assert(sum(map(len, lines)) <= MAXL)
    f.write('{}\n'.format('\n'.join(lines)))

    queries = set([])
    for _ in range(Q):
        l = -1
        r = -1
        while l == -1 or (l, r) in queries:
            l = random.randint(1, N)
            r = random.randint(l, N)
        queries.add((l, r))
        f.write('{} {}\n'.format(l, r))

import random

random.seed(987654321)

PATH = '../cases'
CHLEN = [(1, 3), (4, 11), (12, 17)]
PER_CH_RANGE = [500, 50, 30]
PER_LEN = [10, 6, 4]
MAXN = 5000
MINN = 30
MAXL = 5000
MAXQ = 10 ** 6
CHARS = list('abcdefghijklmnopqrstuvwxyz')

def insert_chunk(set_lines, chunk, separator):
    pos = [i for i in range(len(set_lines))]
    random.shuffle(pos)
    for i in pos:
        offset = list(set_lines[i].keys())
        random.shuffle(offset)
        for j in offset:
            if j-1+len(chunk) in set_lines[i] and all(set_lines[i][k] == separator for k in range(j, j + len(chunk))):
                for k in range(j, j + len(chunk)): set_lines[i][k] = chunk[k-j]
                return True
    return False

for CNT, C_RANGE, PER_CH in zip(PER_LEN, CHLEN, PER_CH_RANGE):
    CL, CR = C_RANGE
    SIZES = [random.randint(max(1, MAXN // ((CR+CL) * MINN)), MAXN // CR) for _ in range(CNT)]
    for N in SIZES:
        with open('{}/chunks_{}_{}_{}'.format(PATH, CL, CR, N), 'w') as f:
            Q = min(N * (N + 1) // 2, MAXQ)
            f.write('{} {}\n'.format(N, Q))

            separator = random.choice(CHARS)
            chars = [c for c in CHARS if c != separator]
            assert(len(chars) == len(CHARS) - 1)

            L = MAXL // N
            set_lines = [
                {i: separator for i in range(L)}
                for _ in range(N)
            ]
            assert(sum(map(len, set_lines)) <= MAXL)

            chunks = [
                ''.join(random.choice(chars) for _ in range(C))
                for C in range(CL, CR+1)
                for _ in range(PER_CH)
            ]
            random.shuffle(chunks)
            for chunk in chunks: assert(insert_chunk(set_lines, chunk, separator))

            lines = [
                ''.join(d[i] for i in range(L))
                for d in set_lines
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

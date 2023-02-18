import numpy
def process():
    lines = open('code.txt').readlines()
    ans = []
    for line in lines:
        if line.find('^') != -1:
            idx_end = line.find('^') - 5
            idx_start = line.find('+') + 2
            ans.append(line[idx_start:idx_end])
    ans = '\n'.join(ans)
    open('ans.txt', mode='w').write(ans)

def add():
    a1 = [line.strip() for line in open('xor.txt').readlines()]
    a2 = [line.strip() for line in open('ans.txt').readlines()]
    a3 = [str(hex(int(i, 16) + int(j, 16))) for i, j in zip(a1, a2)]
    open('key.txt', 'w').write('\n'.join(a3))

add()
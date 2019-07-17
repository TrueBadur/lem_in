import re

f = open('out', 'r')
r = re.compile(r'L1-(.{4})')
res = []

for s in f.readlines():
    m = r.match(s)
    if m != None:
        res.append(m.group(1))

print(' '.join(res))
print('\n\n')

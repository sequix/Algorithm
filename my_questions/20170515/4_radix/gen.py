#!/usr/bin/env python3
# -*- coding: utf8 -*-

from random import randint

inputs = {}
inputs[2] = [randint(0, 1) for i in range(randint(1, 1000))]

for i in range(3, 1000):
    inputs[i] = []
    isMultiple = (randint(0, 1) == 1)
    x = randint(1, i**randint(1, 999))
    if isMultiple:
        x -= x % (i-1)
    elif x % i == 0:
        x += randint(1, i-2)
    while x != 0:
        inputs[i].append(x % i)
        x //= i

with open('input', 'w') as f:
    for k, v in inputs.items():
        if len(v) <= 0: continue
        f.write('%d %d\n' %(k, len(v)))
        for d in v[:-1]:
            f.write('%d ' % d)
        f.write('%d\n' % v[-1])

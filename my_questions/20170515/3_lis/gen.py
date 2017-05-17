#!/usr/bin/env python3
# -*- coding: utf8 -*-

from random import randint

T = 6
N = int(1e6)

inputs = []

inputs.append([4, 1, 6, 9, 2, 3])
inputs.append([1 for i in range(10)])
inputs.append([i for i in range(11)])
inputs.append([i for i in range(10, 0, -1)])

for i in range(T - len(inputs)):
    inputs.append([randint(-2**31, 2**31-1) for _ in range(N)])

with open('input', 'w') as f:
    for case in inputs:
        f.write('%d\n' % len(case))
        for elem in case[:-1]:
            f.write('%d ' % elem)
        f.write('%d\n' % case[-1])

#!/usr/bin/env python3
# -*- coding: utf8 -*-

import sys
from random import randint, shuffle
from math import log, floor

T = int(1e6)

cases = [
    (0, 0), (0, 1), (1, 0), (1, 1),
]

for B in range(2, 10000):
    maxValidA = pow(B, floor(log(1e18, B)))
    if maxValidA+1 > 1e18: continue
    cases.append((maxValidA-1, B))
    cases.append((maxValidA, B))
    cases.append((maxValidA+1, B))

for B in range(2, 100):
    for A in [pow(B, x) for x in range(1, 100) if pow(B, x) <= 1e18]:
        cases.append((A, B))

for i in range(T - len(cases)):
    cases.append((randint(0, 1e18), randint(0, 1e18)))

shuffle(cases)

answers = []

for A, B in cases:
    if B == 0:
        answers.append(1 if A == 0 else 0)
    elif A in [0, 1]:
        answers.append(A)
    else:
        ans = log(A, B) - floor(log(A, B))
        ans = 1 if ans == 0.0 else 0
        answers.append(ans)

with open('input', 'w') as f:
    f.write('%d\n' % len(cases))
    for A, B in cases:
        f.write('%d %d\n' % (A, B))

with open('output', 'w') as f:
    for ans in answers:
        f.write('%d\n' % ans)

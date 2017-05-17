#!/usr/bin/env python3
# -*- coding: utf8 -*-

from math import factorial
from random import randint

N = 200

inputs = []
inputs.append([1])
inputs.append([1, 2, 3])
inputs.append([1] * N)
inputs.append([2**63-1] * N)
inputs.append([i for i in range(1, N+1)])
inputs.append([2*i+1 for i in range(N)])
inputs.append([2*i+1 for i in range(N//2)] * 2)
inputs.append([i**2+1 for i in range(N)])
inputs.append([(i+1)**2+1 for i in range(N)])

#inputs.append([i**3+1 for i in range(N)])
#inputs.append([(i+1)**3+1 for i in range(N)])

inputs.append([i**4+1 for i in range(N)])
inputs.append([(i+1)**4+1 for i in range(N)])
inputs.append([i**5+1 for i in range(N)])
inputs.append([(i+1)**5+1 for i in range(N)])
inputs.append([i*(i-1)+1 for i in range(N)])
inputs.append([i*(i+1)+1 for i in range(N)])
inputs.append([factorial(i) for i in range(1, 21)])
inputs.append([randint(1, 2**63-1) for _ in range(N)])

with open('input', 'w') as f:
    f.write('%d\n' % len(inputs))
    for case in inputs:
        f.write('%d\n' % len(case))
        for elem in case[:-1]:
            f.write('%d ' % elem)
        f.write('%d\n' % case[-1])

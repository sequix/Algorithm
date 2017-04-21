#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from itertools import permutations

with open('input', 'w') as f:
    for p in list(permutations('012345678')):
        s = ''.join(p)
        print(s, file=f)

""" Justin Thoreson
CPSC 3400
HW6 Part 1: Regular Expressions
30 May 2021
"""

a = r'[0-46-9]*5[0-46-9]*5[0-46-9]*'
b = r'([1-9]|1[0-2]):[0-5]\d [AP]M'
c = r'([a-zA-Z_]\w*)?|([a-zA-Z_]\w*, )+[a-zA-Z_]\w*'
d = r'(?P<left>\w+) *<(?P<equal>=?) *(?P<right>\w+)'
d_sub = r'\g<right> >\g<equal> \g<left>'

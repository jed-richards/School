import math
from fractions import Fraction

t, s = [int(x) for x in input().split()]


diag = 0
k = 0

if s%3 == 0:
    k = int(s/3)
    for i in range(0, k):
        diag = diag + 3*i + 1

elif s%3 == 1:
    k = math.floor(s/3)
    for i in range(0, k):
        diag = diag + 3*i + 2

elif s%3 == 2:
    k = math.floor(s/3)
    for i in range(0, k):
        diag = diag + 3*i + 3

d_taxi = 2*(t**2 - t) + (4*t + 1)
d_spidey = 2*(s**2 - s) + (4*s + 1) + (4*diag)
#print(d_taxi)
#print(d_spidey)

gcd = math.gcd(d_taxi, d_spidey)

d_taxi /= gcd
d_spidey /= gcd

d_taxi = int(d_taxi) 
d_spidey = int(d_spidey)

if d_spidey == 1:
    print(d_taxi)

elif d_taxi/d_spidey >= 1:
    print(1)

else:
    #print(str(Fraction(d_taxi, d_spidey)))
    print(f'{d_taxi}/{d_spidey}')

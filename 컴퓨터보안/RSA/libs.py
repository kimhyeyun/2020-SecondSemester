import random
import sys

sys.setrecursionlimit(2048)

"""
GCD(assume a>=0, b>=0)
"""
def gcd(a,b):
    if a < b:
        a, b = b, a
    if a == b:
        return a
    elif b == 0:
        return a
    else:
        return gcd(b, a % b)


"""
Extended Euclidean Algorithm (Iterative version)

return (x,y,r) a*x+b*y=gcd(a,b)
"""
def extended_euclid(a,b):
    if a == b:
        return 1,0,a
    elif b == 0:
        return 1,0,a
    else:
        x_1 = 1
        y_1 = 0
        r_1 = a

        x_2 = 0
        y_2 = 1
        r_2 = b

        while r_2 != 0:
            q = r_1 // r_2

            r_t = r_1 - q * r_2
            x_t = x_1 - q * x_2
            y_t = y_1 - q * y_2

            x_1, y_1, r_1 = x_2, y_2, r_2
            x_2, y_2, r_2 = x_t, y_t, r_t

        return x_1, y_1, r_1


"""
Multiplicative Inverse
X = a^-1 mod n
a*x mod n =1
"""

def m_inv(a,n):
    x, y, r = extended_euclid(n, a % n)
    print(x,y,r)
    if r != 1:
        print("No multiplicative inverse")
        return
    else:
        return y % n

"""
int_to_bin
"""

def int_to_bin(num):
    return list(bin(num))[2:]

"""
Modular exponentiation
returns a ^ b mod n
"""

def exp(a, b, n):
    c = 0
    f = 1
    bin_b = int_to_bin(b)
    k = len(bin_b)

    for i in range(k):
        c = 2 * c
        f = (f*f) % n

        if bin_b[i] == '1':
            c = c + 1
            f = (f * a) % n

    return f



"""miller-rabin prime test
"""

Prime = 0
Composite = 1

def miller_rabin(n, s):
    if n == 2:
        return Prime
    elif n % 2 == 0:
        return Composite

    for _ in range(s):
        a = random.randint(1,n-1)
        if test(a,n) == True:
            return Composite

    return Prime


def test(a,n):
    bits = int_to_bin(n-1)
    k = len(bits) - 1
    t = 0

    while bits[k] == '0':
        t += 1
        k -= 1

    u = (n-1) >> t
    x = exp(a, u, n)

    for _ in range(t):
        _x = x
        x = (_x * _x) % n
        if x == 1 and _x != 1 and _x != n-1:
            return True
    if x != 1:
        return True
    else:
        return False

from libs import *

"""
RSA key pair generation
"""

def keygen(len):
    #Implement your keygen

    bound = 1 << (len//2)

    p = 2 * random.randint(bound//4 + 1, bound//2) - 1
    while miller_rabin(p,50) == Composite:
        p = 2 * random.randint(bound//4 + 1, bound//2) - 1

    q = 2 * random.randint(bound//4 + 1, bound//2) - 1
    while miller_rabin(q,50) == Composite:
        q = 2 * random.randint(bound//4 + 1, bound//2) - 1

    n = p * q
    phi_n = (p-1) * (q-1)
    
    e = 2*random.randint(1,phi_n//2) - 1

    while gcd(phi_n,e) != 1:
        e = 2*random.randint(1,phi_n//2) - 1

    d = m_inv(e,phi_n)
    
    return (e, d, n)


"""
RSA encryption
e, n: public key
M : plaintext < n
"""

def encrypt(M, e, n):
    return exp(M, e, n)



"""
RSA decryption
d, n : private key
C : ciphertext < n
"""

def decrypt(C, d, n):
    return exp(C, d, n)


if __name__ == "__main__":
    print(m_inv(235,352))
    e, d, n = keygen(128)
    M = 88
    C = encrypt(M, e, n)
    MM = decrypt(C, d, n)

    if M == MM:
        print("Success")
        print("M={}, PU=({},{}), PR=({},{}), C={}, MM={}"
              .format(M,e,n,d,n,C,MM))

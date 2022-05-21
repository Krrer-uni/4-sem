from operator import truediv
from random import randrange
from Crypto.Util import number
import time
import random

def gcd(p,q):
    while q != 0:
        p, q = q, p%q
    return p

def is_coprime(x, y):
    return gcd(x, y) == 1

n = 128
print(number.getPrime(n))
primes = []
size = 2000

bits_tested = [128, 256, 512, 1024, 1536, 2048]
length = len(bits_tested)
# [128, 256, 512, 1024, 1536, 2048, 3072, 4096]
for n in bits_tested:
    print(n)
    primes.append([])
    for x in range(size ):
        rand = number.getPrime(n)
        while not is_coprime(rand -1 ,65537) :
            rand = number.getPrime(n)
        primes[len(primes)-1].append(number.getPrime(n))


one = open("p_3072.txt","r")
two = open("p_4096.txt","r")
print("3072")
numbers_3072 = []
while 1==1 :
    c = one.readline()
    if c == "" :
        break
    numbers_3072.append(int(c))
primes.append([])
while len(primes[len(primes)-1]) < size  :
    primes[len(primes)-1].append(numbers_3072[random.randint(0,len(numbers_3072)-1)])

print("4096")
numbers_4096 = []
while 1==1 :
    c = two.readline()
    if c == "" :
        break
    numbers_4096.append(int(c))
primes.append([])
while len(primes[len(primes)-1]) < size  :
    primes[len(primes)-1].append(numbers_4096[random.randint(0,len(numbers_4096)-1)])

bits_tested.append(3072)
bits_tested.append(4096)
times = [[[],[]]]
length = len(bits_tested)

for n in range(length):
    print(bits_tested[n])
    times.append([[],[]])
    for x in range(int(len(primes[n])/2)):
        
        p = primes[n][x]
        q = primes[n][x + int(len(primes[n])/2)]
        o = p * q
        d = pow(65537, -1, (q-1)*(p-1))
        dp = d%(p-1)
        dq = d%(q-1)
        qi = pow(q,-1,p)
        msg = randrange(2,o-1)
        start = time.time()
        x = pow(msg,p,o)
        end = time.time()
        times[n][0].append(end-start)
        start = time.time()
        yp = pow(msg,dp,p)
        yq = pow(msg,dq,q)
        x = (yq +(yp-yq)*qi*q)%(p*q)
        end = time.time()
        times[n][1].append(end-start)


    f = open("results.txt", "w")

for n in range(len(bits_tested)):
    msg = "times for " + str(bits_tested[n] ) + "bits\n"
    f.write(msg)
    f.write(str(sum(times[n][0])/len(times[n][0])) + '\n')
    f.write(str(sum(times[n][1])/len(times[n][1])) + '\n')
    print(msg)
    print(sum(times[n][0])/len(times[n][0]))
    print(sum(times[n][1])/len(times[n][1]))
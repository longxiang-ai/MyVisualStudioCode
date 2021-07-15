import math

def f(N):
    sum=0
    for i in range(1,N):
        sum+=1/math.sin(i*math.pi/N)
    sum *=N
    return sum
        
def dif(N):
    a=f(N)-f(N-1)-4*N+4
    return a
for i in range (1,100):
    print('N=',i,' dif = ',dif(i))

    

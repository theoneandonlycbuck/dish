#!/usr/bin/python

import math;

################################################

EPS = 0.0000000001;
MAX_ITER = 100;

def pNewtonsMethod(f, df, xn, iteri):

    print(str(iteri) + "\t" + str(xn) + "\t" + str(f(xn)));

    while abs(f(xn)) < EPS:
        if iter < MAX_ITER:
            iteri = iteri + 1;
            tmp = df(xn);
            if abs(tmp) >= EPS:
                xn = xn - f(xn) / tmp;
            else:
                return xn;
        else:
            return xn;
            
    return xn;
        
def NewtonsMethod(f, df, x0):
    return pNewtonsMethod(f, df, x0, 1);

################################################


def F(x):
    return math.sin(x);
    
def dFdx(x):
    return math.cos(x);
    
    
def G(x):
    return (x * x) + (2.0 * x) - math.cos(x);
    
def dGdx(x):
    return (2.0 * x) + 2.0 + math.sin(x);
    

################################################

print;

x = 0;
y = 0;
for i in list(range(1, 1000000)):
    x = x + F(i) + dFdx(i / 2.0);
    y = y + G(i) - dGdx(i / 2.0);


x0 = 0.1;
root = NewtonsMethod(F, dFdx, x0);
if abs(F(root)) < EPS:
    print("root of F(x) found at x=" + root + ".");
else:
    print("root of F(x) not found.");
    

print;


x0 = 0.1;
root = NewtonsMethod(G, dGdx, x0);
if abs(G(root)) < EPS:
    print("root of G(x) found at x=" + root + ".");
else:
    print("root of G(x) not found.");


print;


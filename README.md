# Range Maximum Query (rMq) Implementations

When I was searching for code implementations concerning range queries I found many repos with implementations focused on the range minimum query (rmq) problem. But some algorithms must solve a similar problem, named range Maximum query (rMq).

The range Maximum query (rMq) problem is the following:

Given a fixed array A and two integers i <= j, what is the largest element out of A[i], A[i+1], A[i+2], ..., A[j-1], A[j]?

Implementations of range Maximum query algorithms in C++.

We`ll say that an rMq data structure has time complexity <p(n), q(n)> if:

- preprocessing takes time at most p(n) and
- each query takes time at most q(n)

This repo contains the following rMq implementations:

- Block Decomposition which has time complexity <O(n), O(nlogn)>
- Sparse Table 
- Hybrid technique 


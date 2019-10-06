# Linear equation diophantine solver

Currently solving for a simple equation
``` ax + by = c ```.

I did with constexpr in mind, but I guess I would have to previously know the number of solutions. Since I don't know it, a allocation occurs when needed, hence, no constexpr.

I am thinking about generalization for ``` a0 * x0 + a1 * x1 + ... + an * xn = b ``` using templates.

A few tests and a better CMakeLists.txt will be available in the near future.

My PC execution:
```
Please input values a, b and c separated by spaces:
5 7 135
Do you want to solve for:
[0] Non Negative numbers
[1] Positive numbers
[2] Negative numbers
[3] Non Positive numbers
0
It took 22513 ns
The solutions are:
x: 27 y: 0
x: 20 y: 5
x: 13 y: 10
x: 6 y: 15
```

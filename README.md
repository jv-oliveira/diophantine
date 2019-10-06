# Linear equation diophantine solver

Currently solving for a simple equation
``` ax + by = c ```

I did with constexpr in mind, but I guess I would have to previously know the number of solutions. Since I don't know it, a allocation occurs when needed, hence, no constexpr.

I am thinking about generalization for ``` a0 * x0 + a1 * x1 + ... + an * xn = b ``` using templates

A few tests and a better CMakeLists.txt will be available in the near future.

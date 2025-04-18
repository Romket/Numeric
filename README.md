# Numeric

This is a collection of numerical methods for solving differential equations.

## Installation

To install the program, use the [TI-Connect CE](\https://education.ti.com/en/products/computer-software/ti-connect-ce-sw)
or [TILP](https://www.ticalc.org/archives/files/fileinfo/374/37481.html) 
software and follow instructions for each.

### Building manually

Make sure you have [tibasic](https://github.com/miselin/tibasic) installed.

To build the program manually, use the following commands:

```bash
$ git clone https://github.com/Romket/Numeric.git
$ cd Numeric
$ make
```

This will generate a `NUMERIC.8xp` file in the `build/bin` directory that can
be loaded into TI-Connect CE or TILP.

## Usage

Once installed, run like any other program.

The program will prompt you for the following:

- The number of equations to solve
- The order of each equation
- The initial conditions for each equation
- The step height
- The `t` value to evaluate the function at

The program will then show a menu to select the method to use.

## Methods

Currently, the following methods are supported:

- `Euler`: Euler's method
- `Improved Euler`: Improved Euler's method
- `RK4`: Runge-Kutta 4th order method
- `ABM`: Adams-Bashforth method with Adams-Moulton correction

**Note:** The `ABM` method will prompt for a method to use to solve the first
four steps. Any single-step method that can be used on its own will work.

There are also some more advanced methods and can be found in the `More` menu:

- `Custom RK`: Custom Runge-Kutta method: asks for the coefficients and order

## Output

The program will output the solution to the console at the final value given.

Some other values will be saved to lists and matrices.
- Intermediate `t` values will be saved to list `L1`
- Intermediate `y` values will be saved to matrix `[V]`
- Intermediate `y'` values will be saved to matrix `[W]`
- Intermediate `y''` values will be saved to matrix `[X]`
- Intermediate `y'''` values will be saved to matrix `[Y]`
- Intermediate `y''''` values will be saved to matrix `[Z]`
- Unfortunately, any equation with of order greater than 4 won't save all the
  intermediate values.

For Runge-Kutta methods, the program will also save k-values:
- Intermediate `k1` values will be saved to matrix `[K]`
- Intermediate `k2` values will be saved to matrix `[L]`
- Intermediate `k3` values will be saved to matrix `[M]`
- Intermediate `k4` values will be saved to matrix `[N]`
- Intermediate `k5` values will be saved to matrix `[O]`
- Any Runge-Kutta method with of order greater than 5 won't save all the
  intermediate k-values.

## License

This program is licensed under the Gnu General Public License v3.0.

See [LICENSE](LICENSE) for more information.

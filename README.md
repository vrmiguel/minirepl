# miniREPL

A work-in-progress small arithmetic REPL written in C++.

## Usage

An example follows:
```Python3
miniREPL -- github.com/vrmiguel/minirepl
>>> -2^3 - 4*5
-28
>>> 4*7^2
196
>>> 6*8 - 2*3
42
```

The REPL currently only deals in integers, has no parenthesis or variable support.


## Building

Build with the following command:
```qmake && make```

and then run the REPL with `./minirepl`.

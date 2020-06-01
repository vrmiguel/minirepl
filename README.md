# miniREPL

A work-in-progress small arithmetic REPL written in C++.

## Usage

An example follows:
```Python3
miniREPL -- github.com/vrmiguel/minirepl
>>> myVar = -2^3 - 4*5
-28
>>> myVar
-28
>>> 4*7^2
196
>>> 6*8 - 2*3
42
```

The REPL currently only deals in integers and has no parenthesis support yet.
Variables can be created with any combination of upper and lower-case characters, but can't be called into an arithmetic expression yet.

```C
>>> c = 2 ^ 4 - 7              // Works!
9
>>> 2 + c                      // Unimplemented.
```

## Building

Build with the following command:
```qmake && make```

and then run the REPL with `./minirepl`.

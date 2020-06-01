# miniREPL

A work-in-progress small arithmetic REPL written in pure C++11.

## Usage

An example follows:
```C
miniREPL -- github.com/vrmiguel/minirepl
>>> myVar = -2^3 - 4*5
-28
>>> myVar
-28
>>> 4*7^2
196
>>> 6*8 - 2*3
42
>>> a = 2
2
>>> b=a^a
4
>>> b^a + a^b
32
```

The REPL currently only deals in integers and has no parenthesis support yet.
Variables can be created with any combination of upper and lower-case characters, but currently cannot be updated.

```C
>>> c = 2 ^ 4 - 7              // Works!
9
>>> c + 2                      // Works
11
>>> c = c + 4                  // Unimplemented
>>> c = 2                      // Unimplemented
```

## Building

Build running ```qmake && make``` and then run the REPL with `./minirepl`.

The QMake version used here is 3.1.

A compiler supporting at least C++11 is needed.

No extra dependencies are needed.


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
>>> a = 2*b
8
```

The REPL currently only deals in integers and has no parenthesis support yet.
Variables can be created with any combination of upper and lower-case characters.

## Building

### With QMake

On the root folder, run ```qmake && make```. 

Start the REPL with `./minirepl`.

The QMake version used here is 3.1.
A compiler supporting at least C++11 is needed, with no extra dependencies

### A more lengthy way

On the root folder, run ```g++ -c -pipe -std=gnu++11 -Wall -W -fPIC -I. Sources/main.cpp Sources/interp.cpp Sources/_os.cpp Sources/token.cpp```, followed by ```g++ -Wl,-O1 -o minirepl main.o interp.o _os.o token.o```.

The `-std=gnu++11` flag can be freely switched to `-std=c++11` if so wished.

# TISC    (MAJOR WORK IN PROGRESS)

The "Tiny Machine" computer was created by Kenneth C. Louden from "Compiler Construction: Principles and Practice" and the original TM code is attributed to him. This is merely a refactoring (and hopefully a re-engineering) of his original code.

![dependency graph of the original tm.c](https://i.imgur.com/L5ShNJy.png)

## Testing

There is a testing suite that can be run by typing `make test`. It runs a shell script
that runs TISC against every testing file with automatic input, then compares it against
known correct output. The tests are bootstrapped against the original "TinyMachine" source
code by Kenneth L. so that if you were to ever add more test cases, the output would
automatically be generated.

To run tests with `valgrind`, run `make test TESTARG="-v"` (it's clunky I know, but
I did it with my CI pipeline in mind).

## TODO

- Allow for a C-minus compiler pipeline so that instead of taking .tm files and then
comparing output, instead allowing the compiler to create the .tm files.

## Resources

[The TM Machine Specification](https://faculty.chas.uni.edu/~wallingf/teaching/cs4550/compiler/specification-tm.html)

[Tiny Machine Visual Simulator](http://david-white.net/tmvs.html#references)

[Tiny Resources](https://github.com/ejacky/tiny)

## Attribution

Test files from the C-Minus projects were taken from the following GitHub users:

- DanielGabric
- Kersheh
- LonPi
- neivin

# This is a program that takes an integer as input and returns the corresponding word (in danish)

## Using the program
* numbers.c accepts a struct, as defined in numbers.h
* It has the following properties:
```
struct NumberFormat
{
    occurence og;
    occurence e;
    occurence et;
};
```
* It also uses the following enum:
```
typedef enum
{
    NEVER,
    EVERY,
    LAST
} occurence;
```
* The program *should* adapt to any of the occurences changing to any of the enum values.
* Have fun finding all the bugs!

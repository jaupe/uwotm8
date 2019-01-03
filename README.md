# uwotm8
A toy vector-algebra calculator for calculations using extreme brevity. It's inspired by APL. The name - uwotm8 - comes from a well known British slang derived from mobile phone slang

## Introduction

The uwotm8 performs calculations on vectors and scalars. The biggest difference between conventional programming and uwotm8 is that the latter disregards mathematical operator precedence. It evaluates from left to right (LTR) regardless of operators. The following examples demonstrate the LTR evaluation of uwotm8.

```
uwotm8>2+3*4
``` 

## Primitive types

If you thought that it evaluates to 14, you're wrong. This evaluates to 20 because of the strict LTR evaluation, which is equivalent to (2+3)*4

There are just two primitive types in uwotm8. Vectors are expressed by just separating the numbers by whitespaces

```
uwotm8>1 2 3 4
```

## Examples

```
# Sum of vector
uwotm8>/+1 2 3 4
10
```

```
# Cumulative sum
uwotm8>\+1 2 3 4
1 3 6 10
```

```
# Adding two vectors together
uwotm8>1 2 3+1 2 3
2 4 6
```

```
# Adding a vector to a scalar 
uwotm8>1 2 3+1
2 3 4 
```

```
#Multiplying two vectors
uwotmu8>2 3 4 * 2 3 4
4 9 16
```

```
#Multplying a vector by a scalar
uwotm8>2 3 4*2
4 6 8
```

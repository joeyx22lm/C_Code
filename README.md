# SmallScale
Small-scale code, nothing for production use; all is written by me for various personal or school projects; All code is open source, as in free air. If it is wrong, doesn't compile, causes spontaneous combustion, etc. it's not on me. Miscellaneous code written in C, Java and PHP. Refer to this readme for each program / script description. Refer to each file for logic, credits or any additional information.

# COP - AssignmentOne.c
The goal of this assignment is to write an application that reads in a data file and stores the data as a linked list.

# COP - AssignmentTwo.c
This assignment provides more practical experience parsing data files and creating a linked list and builds upon it with recursion and writing a data file.

# BaseConvert.c
Numeric base converter supporting binary, decimal, octal and hexidecimal. Written in C.

# Factorial.java
Factorial Function by both Iteration and Recursion .. ohh my lawd 

# PrimitiveRoot.php
Function that finds if a is primitive root of p

# hillcipher.java
Java CLI program, encrypts plaintext file based on key file, with hill cipher.
hillcipher.java <keyfilepath> <plaintextfilepath>

# phi.c
Euler's Totient / Phi written in C

# 2014_UCF_LPC_fact
  UCF Local Programming Contest — August 30, 2014<br />
  Factorial Products    Filename: fact     (Difficulty Level: Hard)<br />
  Factorial is just a game of multiplications. Formally, it can be defined as a recurrence relation:<br />
      Fact (0) = 1<br />
      Fact (n) = n * Fact(n-1), for all integers n > 0<br />
    This problem is all about multiplications, more and more multiplications. It is a game of
    multiplications of factorials.<br />
  The Problem:<br />
   You will be given three lists of numbers: A, B and C. You have to take the factorials of all the
    numbers in each list and multiply them to get ProFact(A), ProFact(B), ProFact(C). Then report
    which product is the largest.<br /><br />
    For example, consider the lists A = {2, 4, 7}, B = {0, 1, 9} and C = {2, 3, 5, 5}. Then,<br />
      ProFact(A) = 2! * 4! * 7! = 241, 920<br />
      ProFact(B) = 0! * 1! * 9! = 362, 880<br />
      ProFact(C) = 2! * 3! * 5! * 5! = 172,800<br />
    So, the largest product for this example is ProFact(B).<br /><br /><br />
  The Input:<br />
    The first input line contains a positive integer, n, indicating the number of test cases. Each test
    case consists of four input lines. The first line consists of three positive integers providing,
    respectively, the size for the lists A, B and C. The last three lines contain, respectively, the
    elements (non-negative integers) in lists A, B and C.
    All the values in the input file will be less than 2,501.<br /><br />
  The Output:<br />
    For each test case, output “Case #t: h” in a line, where t is the case number (starting with 1)
    and h is the list name with the highest product. If two or three lists are tied for the highest product,
    print “TIE”. Follow the format illustrated in Sample Output.
    Assume that, if the pairwise product values differ, then the relative difference of these products
    will differ by at least 0.01% of the largest product.<br /><br />
  Sample Input:<br />
    3<br />
    3 3 4<br />
    2 4 7<br />
    0 1 9<br />
    2 3 5 5<br />
    2 2 2<br />
    2 3<br />
    3 2<br />
    2 2<br />
    3 3 3<br />
    1 3 5<br />
    2 4 6<br />
    1 4 7<br /><br />
  Sample Output:<br />
    Case #1: B<br />
    Case #2: TIE<br />
    Case #3: C<br />

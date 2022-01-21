# CPSC 3400 Languages & Computation

The Languages & Computation course touched on details pertaining to the aspects of different programming languages and paradigms. Some of the specific topics covered included Python, F#, regular expressions, context-free gramars, Turing machines, DFAs and NFAs, computability, interpretation, garbage collection, memory, names, variables, types, and compilation. 

For some assignments, parts of the code were provided by the instructor to use either as a foundation for extending the code and completing the assignment or as a simulator to run the students' files.

## HW1 - Python Color Survey: 

Task: Tabulate the results of a survey where people were asked to vote for their top three favorite colors (in order). The results of the survey are stored in an input file that has one or more lines 

Grade: 46/50

## HW2 - Python Time Processor: 

Task: Process times from an input file using Python data structures. Example format: 4 12 AM.

Grade: 46/50

## HW3 - Python Garbage Collector: 

Task: "Create a Python program (hw3.py) that simulates a Mark-Sweep garbage collection algorithm. In this program, named pointers are referred to using variable names such as p, stackPtr, temp3, etc. Heap blocks are referred to using integers."

Grade: 50/50 (Everyone who completed received 50/50 as per instructor)

## HW4 - F# Exercises:

Task: Use functional programming to perform three exercises.

* Exercise 1: "Write a function maxCylinderVolume that takes a list of floating-point tuples that represent dimensions of a cylinder and returns the volume of the cylinder that has the largest volume. Each tuple has two floating point values that are both greater than zero. The first value is the radius r and the second value is the height h."

* Exercise 2: "Write a function elimDuplicates that takes a list of integers and eliminates consecutive duplicates; replacing them with a single instance of the value. Order is preserved and non- consecutive duplicates are unaffected."

* Exercise 3: "Write the following binary search tree functions for a binary search tree of integers. 

    * Use the following type definition for a BST (copy this into your solution):

    ```F#
    // Tree definition for problem 3
    type BST =
      | Empty
      | TreeNode of int * BST * BST
    ```
    
    * Insert value tree: Inserts the value into the tree and returns the resulting tree. The resulting tree does NOT need to be balanced. If the value already exists in the tree, return the tree without inserting the value.

    * Search value tree: Returns true if the value is in the tree and false otherwise.

    * Count func tree: The parameter func is a Boolean function that takes a single parameter and returns true or false. The function tests the value of each node with func and returns the number of nodes that evaluate to true.

    * EvenCount tree: Returns the number of nodes that contain even integers. REQUIREMENT: This function must be a single call to count (part 3C) using a lambda function."

Grade: 50/50

## HW5 - F# Algebraic Simplifier: 

Task: "Write an F# function simplify that simplifies an algebraic expression. The expression is using a similar expression class used for symbolic differentiation in class. It removes the divide and power operators but adds a second variable Y. It is shown below.

```F#
type Expression =
    | X
    | Y
    | Const of float
    | Neg of Expression
    | Add of Expression * Expression
    | Sub of Expression * Expression
    | Mul of Expression * Expression
```

To start, download the hw5_prep.fsx  Download hw5_prep.fsx, rename it to hw5.fsx, and use it as a starting point for your assignment. Edit the initial header comment to have your own name and remarks and then search for all the FIXME strings to see where you need to add materials. Your file hw5.fsx now contains an Expression type, an exprToString function that converts an expression to a more readable string format, and contains tests for the examples shown in this document."

Grade: 50/50

## HW6 - Formal Languages:

Task: Create four regular expressions and three DFAs

Part 1 (REGEX):
* "Create a single regular expression that matches a string of digits and contains exactly two fives. Examples of acceptable strings include: "15445 " , " 55 " , " 05563 " . However, the string is to be rejected if it contains anything other than digits."
* "Create a single regular expression that matches a time expressed in the form '1:45 PM'. The hours part must be a number from 1 to 12, the minutes range from 00 to 59, and the time must indicate either AM or PM (uppercase only and preceded by exactly one space)."
* Create a single regular expression that matches a string representing a comma separated list of variable names such as: hello, get_max, sum3
    * A variable name consists of letters, digits, and underscores but cannot start with a digit.
    * There is exactly one space after every comma. No other spaces are allowed.
    * Commas and spaces are not allowed before the first name and after the last name.
    * An empty string is considered a match.
    * It is not a match if the list is not properly formed or if one of the variable names is invalid."
* "Create a substitution, using a regular expression, that replaces all less than (<) and less than and equal to (<=) expressions with the equivalent greater than (>) or greater than or equal (>=). For instance, "a < b" would be replaced with "b > a".
    * Only swap the "word" before and after the comparison. A word consists of letters, digits, and underscores.
    * Zero or more spaces may separate the comparison operator and the words. When performing the substitution, use one space to separate the comparison operator from the words.
    * Do not perform the substitution if there is comparison does not contain a word before and/or after the comparison. For example, a '<' sign appears at the beginning of the string.
    * You may assume that the string does not contain any chained comparisons like a < b < c."

Part 2 (DFA): "Create DFA for the following language specifications. The DFA must be expressed as files that can be used as inputs for the DFA simulator described in the provided document.
* All strings on 𝝨 = {A, B, C} that contain each letter (A, B, and C) at least once.
* All strings on 𝝨 = {X, Y, Z} that contains two consecutive X's or three consecutive Z's (or both).
* All strings on 𝝨 = {A, B, C, D} that adhere to this Python regular expression:  ```^(A?(B|CD)*A+D)$```"

Grade: 50/50

## HW7 - Turing Machines:
Task: Create two context-free grammars and two turing machines.

Part 1 (CFG):
* "(Filename: cfgA.txt) Create a context-free grammar for the language that accepts all strings in the alphabet T={0,1} where the number of 0s in x is divisible by 3, or the length of x is divisible by 3, or both."
* "(Filename: cfgB.txt) Create a context-free grammar for the language that accepts all strings in the alphabet T={x,y,z} that is equivalent to the regular expression: ```^(xz)*(zy?|xx)+$```"

Part 2 (Turing Machines):
* "(Filename tmA.txt) Design a Turing machine on the input alphabet {d,e,f} that accepts strings represented using this Python regular expression that uses back references: ```r'^([de]*)f\1$'``` For this machine, the final tape output does not matter. You will need to modify the tape in order to complete this exercise."
* "(Filename tmB.txt) Design a Turing machine on the input alphabet {x,y,z}  that removes all z characters from the input such that there are no gaps. If the input string is xzzyxzy, the output should be xyxy. For this machine, it does not matter if the string is accepted or rejected. Hint: The final string does not need to reside on the same part of the tape where it started."

Grade: 50/50

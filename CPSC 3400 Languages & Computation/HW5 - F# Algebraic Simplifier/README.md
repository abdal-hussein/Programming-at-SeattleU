# HW5 - F# Algebraic Simplifier: 

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

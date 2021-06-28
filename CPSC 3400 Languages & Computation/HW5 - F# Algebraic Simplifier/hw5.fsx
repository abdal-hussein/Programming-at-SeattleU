// Justin Thoreson
// CPSC 3400
// hw5.fsx
// 23 May 2021
//
// This program is meant to emulate an algebraic simplifyer. An expression given
// to the simplify function can consist of x, y, constOPant, negation, addition,
// subtraction, and multiplication.
//
// NOTE: Aside from the 20 provided test cases, additional test cases allowed
// extension of functionality to the code. For example, Sub (u, Neg (v)) was not
// provided in the given test cases, but additional ones required it in order to
// be simplified accordingly.


// Algebraic expression
type Expression =
    | X
    | Y
    | Const of float
    | Neg of Expression
    | Add of Expression * Expression
    | Sub of Expression * Expression
    | Mul of Expression * Expression
;;

// Pretty-printer for an algebraic expression
let exprToString expr =

    let rec toStr subexpr enclosingPrecedence =        
        let parenthesize s myPrecedence =
            if myPrecedence <= enclosingPrecedence then s else (sprintf "(%s)" s)

        match subexpr with
        // precedence 0 are x and y literals
        | X -> "x"
        | Y -> "y"

        // precedence 1 is unary negation
        | Neg (Neg v) -> sprintf "-(-%s)" (toStr v 1) // avoid --ex in favor of -(-ex)
        | Neg u -> parenthesize (sprintf "-%s" (toStr u 1)) 1

        // precedence 2 is a constant (this is bumped up to get -(3) instead of -3 for Neg (Const 3.0))
        | Const c -> parenthesize (sprintf "%g" c) 2

        // precedence 3 for multiplicative ops
        | Mul (u, v) -> parenthesize (sprintf "%s * %s" (toStr u 3) (toStr v 3)) 3

        // precedence 4 for additive ops
        | Add (u, v) -> parenthesize (sprintf "%s + %s" (toStr u 4) (toStr v 4)) 4
        | Sub (u, v) -> parenthesize (sprintf "%s - %s" (toStr u 4) (toStr v 4)) 4

    toStr expr 5
;;

// FIXME - replace the following with your own simplify function for HW5
let rec simplify expr =
    match expr with
    | Add (Const c, Const d) -> Const (c + d)                  
    | Add (X, Const 0.0) -> X                                  
    | Add (Y, Const 0.0) -> Y
    | Add (Const 0.0, X) -> X
    | Add (Const 0.0, Y) -> Y
    | Add (X, Const c) when c < 0.0 -> Sub (X, Const -c)
    | Add (X, Const c) -> Add (X, Const c)
    | Add (Y, Const c) when c < 0.0 -> Sub (Y, Const -c)
    | Add (Y, Const c) -> Add (Y, Const c)
    | Add (Const c, X) -> Add (Const c, X)
    | Add (Const c, Y) -> Add (Const c, Y)
    | Add (X, Y) -> Add (X, Y)
    | Add (Y, X) -> Add (Y, X)                                 
    | Add (u, Const 0.0) -> simplify u
    | Add (Const 0.0, v) -> simplify v
    | Add (u, Const c) when c < 0.0 -> simplify (Sub (simplify u, Const -c))
    | Add (u, Const c) ->
                       let newExpr = Add (simplify u, Const c)
                       if newExpr = expr
                          then newExpr
                       else simplify newExpr
    | Add (Const c, v) ->
                       let newExpr = Add (Const c, simplify v)
                       if newExpr = expr
                          then newExpr
                       else simplify newExpr
    | Add (u, X) -> Add (simplify u, X)                        
    | Add (u, Y) -> Add (simplify u, Y)
    | Add (X, v) -> Add (X, simplify v)
    | Add (Y, v) -> Add (Y, simplify v)
    | Add (u, v) ->
                 let newExpr = Add (simplify u, simplify v)
                 if newExpr = expr
                    then newExpr
                 else simplify newExpr
    | Sub (Const c, Const d) -> Const (c - d)                  
    | Sub (X, Const 0.0) -> X                                  
    | Sub (Y, Const 0.0) -> Y
    | Sub (Const 0.0, X) -> Neg X
    | Sub (Const 0.0, Y) -> Neg Y
    | Sub (X, Const c) when c < 0.0 -> simplify (Add (X, Const -c))
    | Sub (X, Const c) -> Sub (X, Const c)
    | Sub (Y, Const c) when c < 0.0 -> simplify (Add (Y, Const -c))
    | Sub (Y, Const c) -> Sub (Y, Const c)
    | Sub (Const c, X) -> Sub (Const c, X)
    | Sub (Const c, Y) -> Sub (Const c, Y)
    | Sub (X, Y) -> Sub (X, Y)
    | Sub (Y, X) -> Sub (Y, X)
    | Sub (X, X) -> Const 0.0
    | Sub (Y, Y) -> Const 0.0                                  
    | Sub (Neg X, Neg (Const c)) -> Add (Neg X, Const c)       
    | Sub (u, Const 0.0) -> simplify u
    | Sub (Const 0.0, v) -> simplify (Neg (simplify v))        
    | Sub (u, Const c) ->
                       let newExpr = Sub (simplify u, Const c)
                       if newExpr = expr
                          then newExpr
                       else simplify newExpr
    | Sub (Const c, v) ->
                       let newExpr = Sub (Const c, simplify v)
                       if newExpr = expr
                          then newExpr
                       else simplify newExpr
    | Sub (u, X) -> Sub (simplify u, X)                        
    | Sub (u, v) when u = v -> Const 0.0
    | Sub (u, Neg (v)) -> simplify (Add (simplify u, simplify v))
    | Sub (u, v) ->
                 let newExpr = Sub (simplify u, simplify v)
                 if newExpr = expr
                    then newExpr
                 else simplify newExpr
    | Mul (Const c, Const d) -> Const (c * d)                  
    | Mul (X, Const 0.0) -> Const 0.0
    | Mul (Y, Const 0.0) -> Const 0.0
    | Mul (Const 0.0, X) -> Const 0.0
    | Mul (Const 0.0, Y) -> Const 0.0
    | Mul (X, Const 1.0) -> X                                  
    | Mul (Y, Const 1.0) -> Y
    | Mul (Const 1.0, X) -> X                                  
    | Mul (Const 1.0, Y) -> Y                                  
    | Mul (X, Const c) -> Mul (X, Const c)
    | Mul (Y, Const c) -> Mul (Y, Const c)
    | Mul (Const c, X) -> Mul (Const c, X)
    | Mul (Const c, Y) -> Mul (Const c, Y)
    | Mul (X, Y) -> Mul (X, Y)                                 
    | Mul (Y, X) -> Mul (Y, X)
    | Mul (u, Const 0.0) -> Const 0.0
    | Mul (Const 0.0, v) -> Const 0.0
    | Mul (u, Const c) -> Mul (simplify u, Const c)            
    | Mul (Const c, v) -> Mul (Const c, simplify v)
    | Mul (u, v) ->
                 let newExpr = Mul (simplify u, simplify v)
                 if newExpr = expr
                    then newExpr
                 else simplify newExpr
    | Neg (Const c) -> Const -c
    | Neg (Neg X) -> X
    | Neg (Neg Y) -> Y
    | Neg X -> Neg X
    | Neg Y -> Neg Y
    | Neg (Neg (u)) -> simplify u
    | Neg (u) ->
              let newExpr = simplify u
              match newExpr with
              | Const c -> Const -c
              | _ -> Neg (newExpr)
    | _ -> expr
;;


;;

let testResults = 
    let test expr expected description =
        let actual = simplify expr
        printfn "\n%s" description
        printfn "simplify (%s)" (exprToString expr)
        printfn "got: %s" (exprToString actual)
        if actual <> expected then
            printfn "but expected: %s\nFAILED" (exprToString expected)
            false
        else
            printfn "passed" 
            true
    [
        test (Add (Const 5.0, Const 3.0)) (Const 8.0) "t1 - addition involving two numbers";
        test (Sub (Const 5.0, Const 3.0)) (Const 2.0) "t2 - subtraction involving two numbers";
        test (Mul (Const 5.0, Const 3.0)) (Const 15.0) "t3 - multiplication involving two numbers";
        test (Neg (Const 4.0)) (Const -4.0) "t4 - negation involving a number";
        test (Neg (Const -9.0)) (Const 9.0) "t5 - negation involving a number";
        test (Add (X, Const 0.0)) X "t6 - addition with zero";
        test (Add (Const 0.0, Y)) Y "t7 - addition with zero";
        test (Sub (X, Const 0.0)) X "t8 - subtraction with zero";
        test (Sub (Const 0.0, Y)) (Neg Y) "t9 - subtraction with zero";
        test (Sub (Y, Y)) (Const 0.0) "t10 - subtraction of identical terms";
        test (Mul (X, Const 0.0)) (Const 0.0) "t11 - multiplication with zero";
        test (Mul (Const 0.0, Y)) (Const 0.0) "t12 - multiplication with zero";
        test (Mul (X, Const 1.0)) X "t13 - multiplication with one";
        test (Mul (Const 1.0, Y)) Y "t14 - multiplication with one";
        test (Neg (Neg X)) X "t15 - double negation";
        test (Sub (Mul (Const 1.0, X), Add (X, Const 0.0))) (Const 0.0) "t16 - recursive simplification";
        test (Add (Mul (Const 4.0, Const 3.0), Sub (Const 11.0, Const 5.0))) (Const 18.0) "t17";
        test (Sub (Sub (Add (X, Const 1.0), Add (X, Const 1.0)), Add (Y, X))) (Neg (Add (Y, X))) "t18";
        test (Sub (Const 0.0, Neg (Mul (Const 1.0, X)))) X "t19";
        test (Mul (Add (X, Const 1.0), Neg (Sub (Mul (Const 2.0, Y), X)))) (Mul (Add (X, Const 1.0), Neg (Sub (Mul (Const 2.0, Y), X)))) "t20"
        // FIXME - add some of your own tests!
        test (Add (Mul (Sub (Neg (Const 3.0), Neg (Const 5.0)), Const 3.0), Const 3.0)) (Const 9.0) "t21 - Personal test 1"
        test (Add (Mul (Sub (Neg X, Neg (Const 5.0)), Const 3.0), X)) (Add (Mul (Add (Neg X, Const 5.0), Const 3.0), X)) "t22 - Personal test 2"
        test (Mul (Add (Const 0.0, X), Sub (Y, Const 0.0))) (Mul(X, Y)) "t23 - Personal test 3"
        test (Add (Sub (Add (Mul (Sub (Neg (Const 3.0), Neg (Const 5.0)), Const 3.0), Const 3.0), X), Y)) (Add (Sub (Const 9.0, X), Y)) "t24 - Personal test 4"
        test (Mul (Mul (Add (Const 4.0, Const 1.0), Const 0.0), Sub (Const 0.0, Y))) (Const 0.0) "t25 - Personal test 5"
        test (Mul (Mul (Const 0.0, Sub (Const 1.0, Const 3.0)), Sub (Const 0.0, Y))) (Const 0.0) "t26 - Personal test 6"
        test (X) (X) "t27 - Personal test 7"
        test (Y) (Y) "t28 - Personal test 8"
        test (Const 999.0) (Const 999.0) "t29 - Personal test 9"
        test (Mul (X, Y)) (Mul (X, Y)) "t30 - Personal test 10"
        test (Mul (Add (Y, Const 0.0), Neg (Neg (X)))) (Mul (Y, X)) "t31 - Personal test 11"
        test (Sub (Add (Neg (Mul (X, Const 7.0)), Sub (Const 13.0, Y)), Add (Neg (Mul (X, Const 7.0)), Sub (Const 13.0, Y)))) (Const 0.0) "t32 - Personal test 12"
        test (Neg (Neg (Add (X, Y)))) (Add (X, Y)) "t33 - Personal test 13"
        test (Neg (Neg (Neg (Y)))) (Neg (Y)) "t34 - Personal test 14"
        test (Neg (Neg (Neg (Neg (Sub (Const 17.0, Const 6.0)))))) (Const 11.0) "t35 - Personal test 15"
        test (Neg (Neg (Neg (Neg (Neg (Mul (Const 37.0, Const 3.0))))))) (Const -111.0) "t36 - Personal test 16"
        test (Add (Sub (Const 1.0, Y),X)) (Add (Sub (Const 1.0, Y), X)) "t37 - Personal test 17"
        test (Neg (Mul (X, Add (Const 2.0, Const 2.0)))) (Neg (Mul (X, Const 4.0))) "t38 - Personal test 18"
        test (Sub (Add (Const 2.0, Mul (Const 0.0, X)), Const 0.0)) (Const 2.0) "t39 - Personal test 19"
        test (Add (Sub (Mul (Add (X, Const 1.0), Neg (Sub (Mul (Const 2.0, Y), Const 12.0))), Const 3.0), Neg (Const 5.0))) (Sub (Sub (Mul (Add (X, Const 1.0), Neg (Sub (Mul (Const 2.0, Y), Const 12.0))), Const 3.0), Const 5.0)) "t40 - Personal test 20"
        test (Add (X, Const -11.0)) (Sub (X, Const 11.0)) "t41 - Personal test 21"
        test (Add (Y, Const -2.0)) (Sub (Y, Const 2.0)) "t42 - Personal test 22"
        test (Sub (X, Const -11.0)) (Add (X, Const 11.0)) "t43 - Personal test 23"
        test (Sub (Y, Const -2.0)) (Add (Y, Const 2.0)) "t44 - Personal test 24"
    ];;

let passes = (List.filter (fun bool -> bool) testResults).Length;;
let failures = testResults.Length - passes;;
printfn "%s" (if failures > 0 then (sprintf "%d FAILURES!" failures) else "all tests passed");;

// Justin Thoreson
// CPSC 3400
// hw4.fsx
// 09 May 2021

// Exercise 1
// Calculates the maximum cylinder volume given a list of tuples (radius, height)
let rec maxCylinderVolume (dimensions : (float * float) list) =
    match dimensions with
    | [] -> 0.0
    | hd :: tl ->
         let r, h = hd
         let vol = System.Math.PI * (r**2.0) * h
         let max = maxCylinderVolume tl
         if max > vol then max
         else vol


// Exercise 2
// Eliminate consecutive duplicates in a list of integer values
let rec elimDuplicates (sequence : int list) =
    match sequence with
    | [] -> []
    | hd :: tl when tl <> [] ->
         let next :: rest = tl
         if hd = next then elimDuplicates tl
         else hd :: elimDuplicates tl
    | hd :: tl -> hd :: tl


// Exercise 3

// Tree definition
type BST =
    | Empty
    | TreeNode of int * BST * BST

// Inserts a new integer value into a BST
let rec insert (value : int) (tree : BST) =
    match tree with
    | Empty -> TreeNode (value, Empty, Empty)
    | TreeNode (v, l, r) ->
               if value < v then TreeNode (v, insert value l, r)
               elif value > v then TreeNode (v, l, insert value r)
               else TreeNode (v, l, r)


// Searches for a provided value in a BST
let rec search (value : int) (tree : BST) =
    match tree with
    | Empty -> false
    | TreeNode (v, l, r) ->
               if value < v then search value l
               elif value > v then search value r
               else true


// Counts each value in a BST if the value satisfies the func condition
let rec count func (tree : BST) =
    match tree with
    | Empty -> 0
    | TreeNode (v, l, r) ->
               if func v then 1 + count func l + count func r
               else count func l + count func r
               

// Counts all even values in a BST via passing a lambda function to count
let evenCount (tree : BST) = count (fun value -> value % 2 = 0) tree

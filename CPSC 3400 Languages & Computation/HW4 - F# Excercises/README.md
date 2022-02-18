# HW4 - F# Exercises:

Utilizes functional programming to perform three exercises.

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

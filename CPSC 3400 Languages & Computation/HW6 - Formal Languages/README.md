# HW6 - Formal Languages:

Created four regular expressions and three DFAs

### Part 1 (REGEX):
* "Create a single regular expression that matches a string of digits and contains exactly two fives. Examples of acceptable strings include: "15445 " , " 55 " , " 05563 " . However, the string is to be rejected if it contains anything other than digits."
* "Create a single regular expression that matches a time expressed in the form '1:45 PM'. The hours part must be a number from 1 to 12, the minutes range from 00 to 59, and the time must indicate either AM or PM (uppercase only and preceded by exactly one space)."
* "Create a single regular expression that matches a string representing a comma separated list of variable names such as: hello, get_max, sum3
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

### Part 2 (DFA):
* "Create DFA for the following language specifications. The DFA must be expressed as files that can be used as inputs for the DFA simulator described in the provided document.
    * All strings on 𝝨 = {A, B, C} that contain each letter (A, B, and C) at least once.
    * All strings on 𝝨 = {X, Y, Z} that contains two consecutive X's or three consecutive Z's (or both).
    * All strings on 𝝨 = {A, B, C, D} that adhere to this Python regular expression:  ```^(A?(B|CD)*A+D)$```"

# HW7 - Turing Machines:
Created two context-free grammars and two turing machines.

### Part 1 (Context-Free Grammars):
* "(Filename: cfgA.txt) Create a context-free grammar for the language that accepts all strings in the alphabet T={0,1} where the number of 0s in x is divisible by 3, or the length of x is divisible by 3, or both."
* "(Filename: cfgB.txt) Create a context-free grammar for the language that accepts all strings in the alphabet T={x,y,z} that is equivalent to the regular expression: ```^(xz)*(zy?|xx)+$```"

### Part 2 (Turing Machines):
* "(Filename tmA.txt) Design a Turing machine on the input alphabet {d,e,f} that accepts strings represented using this Python regular expression that uses back references: ```r'^([de]*)f\1$'``` For this machine, the final tape output does not matter. You will need to modify the tape in order to complete this exercise."
* "(Filename tmB.txt) Design a Turing machine on the input alphabet {x,y,z}  that removes all z characters from the input such that there are no gaps. If the input string is xzzyxzy, the output should be xyxy. For this machine, it does not matter if the string is accepted or rejected. Hint: The final string does not need to reside on the same part of the tape where it started."

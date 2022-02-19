# Simple-Calculator
In this project, I implemented a calculator (Inorder --> Assembly codes).   
  
  
![image](https://user-images.githubusercontent.com/86723888/154808696-8d832452-c058-478b-b5cc-455271b7301c.png)

## Table of Contents
* [Instruction Set Architecture](#Instruction-Set-Architecture)
* [Complete Grammar Rules](#Complete-Grammar-Rules)v
* [Operators and Variables](#Operators-and-Variables)

## Instruction Set Architecture
![image](https://user-images.githubusercontent.com/86723888/154809236-c54a9738-5103-45c8-9b00-96467b925b50.png)  
![image](https://user-images.githubusercontent.com/86723888/154809243-94a3145b-6379-4ac2-b0e1-4f10993b33d6.png)  
![image](https://user-images.githubusercontent.com/86723888/154809225-9dd4f54c-1456-4c4b-bf42-d887927f9eaf.png)  

  

## Complete Grammar Rules

    
![image](https://user-images.githubusercontent.com/86723888/154809349-ab823610-0e89-4b33-ab91-3ab8c3b4246b.png)   
Tokens used in the grammar:  
- INT: integer number 
- ID: variable
- ASSIGN: =
- LPAREN: (
- RPAREN: )
- END: '\n'
- ADDSUB: + or -
- MULDIV: * or /
- INCDEC: ++ or --
- AND: &
- OR: |
- XOR: ^  

## Operators and Variables
For Binary Operators:  
- Operator priority: 　[*, /] > [+, -] > & > ^ > |  
- &, |, ^ are the same as bitwise operators in C.
- The left-hand side of an assignment (=) operator should be a variable.
- Valid examples:  
  x = 5  
  x = y = 3  
  x = (y = 1)    
    
- Invalid examples:  
  5 = x  
  x + y = 1  
  (x + y) = 1  
  
For Unary Operators:
- Two consecutive positive (+) or negative (-) signs should be regarded as a prefix increment/decrement operator. (e.g. ++x)  
- Only two consecutive (no spaces between) signs form an increment/decrement operator, e.g.  
  ++x should be regarded as INC(++) x.  
  + +x should be regarded as POSITIVE(+) POSITIVE(+) x.  

- The operand of an inc/dec operator should be a variable.  
  E.g. y=++5 or y=++(x+6) are both INVALID.   

For Variables:  
- Built-in variables x, y, z have initial values.Initially stored in memory [0], [4], [8] respectively.
- When a NEW variable appears, there are two cases:  
  A variable first appears in the left-hand side of an assignment operator (=):   
    Valid, and it can be used in the future  
      E.g. c = x + 5, aa = bb = 3 * x are both valid.  

- A variable first appears in the right-hand side of an assignment operator (=):  
    Invalid, and you should print EXIT 1  
      E.g. x = cc * 5, if cc is a new variable, it is invalid.  

- A new variable should NOT first appear in: 
  Both side of an assignment operator (=).    
    E.g. aa = aa + 1  
  Prefix increment/decrement expression (++ or --)  
    E.g. x = ++bb  
- Valid variable names may contain a-z, A-Z, numbers, and underscores(_) and may have arbitrary length, but name of a variable should NOT START WITH A NUMBER.













# Software-Project

AsuMathLab is a repository for showing the implementation of a mathematical library software that is similar to Matlab and Octave.

The program supports many operations:

	1-Mathematical Functions 
	
      1.1 Trigonometric "sin-cos-tan"
      1.2 Logarithmic
      1.3 Roots
      1.4 Power
	2-Mathematical Expressions With matrices Expressions
	3-"Rand" to create a matrix filled with random variables
	4-"Eye" to create a matrix with a diagonal of ones and the rest of elements are zeros
	5-"Zeros" to create a matrix filled with zeros
	6-"Ones" to create a matrix filled with ones
  
The program get the input as a string.


If the input is "quit" the program will end.

Here is the deatiled explanation for expressions evaluation:

1] Any mathematical expression can be represented using three types of expressions (Infix, Postfix and Prefix).
We are using infix type of expression in our daily life but the computer uses postfix or prefix type of expression.
 Our program's input is written in infix notation as well.
So, we would convert it to postfix notation where operators are written after their operands.
As Postfix is much easier to translate the complex mathematical expressions to a format that is suitable for direct execution and can be direclty translated to code.

To convert infix expression into postfix expression we can use the following procedure:

-Read all the symbols one by one from left to right in the given Infix Expression.
-If the reading symbol is operand, then directly print it to output (postfix format).
-If the reading symbol is left parenthesis '(', then Push it on to the Stack.
-If the reading symbol is right parenthesis ')', then Pop all the contents of stack until respective left parenthesis is poped and print each poped symbol to the output (postfix).
-If the reading symbol is operator (+ , - , * , / etc..,), then Push it on to the Stack. However, first pop the operators which are already on the stack that have higher or equal precedence than current operator and print them to the result.


To evaluate postfix expression:

1-While reading the expression from left to right, push the element in the stack if it is an operand.

2-Pop the two operands from the stack, if the element is an operator and then evaluate it.

3-Push back the result of the evaluation and repeat it till the end of the expression.

2] Any string matrix input you can enter it as a letter name or as a matrix expression written between square brackets, so we implemented a function to parse the input into certain number of rows and columns and another function to create a matrix with this number of rows and columns and fill it with the elements.


3] Our main function "parseandprint" takes the input as a string and determine either it's a mathematical expression or a matrix expression and call the suitable function the print the output.


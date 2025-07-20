APC - Arbitrary Precision Calculator

This project implements an arbitrary-precision calculator that can add, subtract, multiply, and divide very large integers, including negative numbers. The calculator uses doubly linked lists to store each digit of the operands and performs arithmetic similar to manual pen-and-paper methods.

Features
Handles arbitrarily large integers

Supports:

Addition (+)

Subtraction (-)

Multiplication (x)

Division (/)

Accepts both positive and negative numbers

Internally uses doubly linked lists

Displays result without leading zeroes

🧰 Files
File	Description
main.c	Parses input, handles signs, and triggers arithmetic operations
addition.c	Logic for adding two large numbers
subtraction.c	Logic for subtracting one large number from another
multiplication.c	Logic for multiplying two large numbers
division.c	Logic for dividing two large numbers
apc.h	Header file containing type definitions and function declarations
Makefile	Automates compilation, cleaning, and running the project

🏗️ Compilation
Use the provided Makefile to compile the project.
make
This will generate the executable apc_program.

To clean compiled object files and the executable:
make clean

To compile and run:
make run

🚀 Usage
The program accepts three command-line arguments:

./apc_program <number1> <operator> <number2>
<number1> and <number2>: Operands (can be negative and arbitrarily large)

<operator>: One of +, -, x, /

Note: Ensure all inputs are integers, and the operator is a single character.

📊 Sample Outputs
bash
Copy
Edit
$ ./apc_program 987654321987654321 + 123456789123456789
1111111111111111110

$ ./apc_program -987654321987654321 + 123456789123456789
-864197532864197532

$ ./apc_program 100000000000000000000 x 2
200000000000000000000

$ ./apc_program 100000000000000000000 / 2
50000000000000000000

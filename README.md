# 💡 APC - Arbitrary Precision Calculator

APC (Arbitrary Precision Calculator) is a command-line calculator that performs **addition**, **subtraction**, **multiplication**, and **division** on **very large integers**, including **negative numbers**, using **doubly linked lists**. It is designed to simulate arithmetic operations the way humans do by hand—digit by digit—making it ideal for educational and computational purposes.

---

## 📂 Features

- 🧮 Handles arbitrarily large integers  
- ➕ Addition, ➖ Subtraction, ✖️ Multiplication, ➗ Division support  
- ➕➖ Accepts both **positive** and **negative** numbers  
- 💾 Each digit is stored in a **doubly linked list** node  
- 🧹 Result output omits **leading zeros**  
- ✅ Handles edge cases like zero operands and division by zero  

---

## 📄 Project Structure

| File               | Description                                               |
|--------------------|-----------------------------------------------------------|
| `main.c`           | Parses arguments, handles signs, and routes operations    |
| `addition.c`       | Logic to add two large numbers digit by digit             |
| `subtraction.c`    | Logic to subtract one number from another with borrow     |
| `multiplication.c` | Long multiplication algorithm using shifting and summing  |
| `division.c`       | Long division using repeated subtraction and estimation   |
| `apc.h`            | Type definitions and function prototypes                  |
| `Makefile`         | Build, run, and clean automation script                   |

---

## 🏗️ Compilation

To compile the project using the provided Makefile:

```bash
make

Sample output

$ ./apc_program 987654321987654321 + 123456789123456789
1111111111111111110

$ ./apc_program -987654321987654321 + 123456789123456789
-864197532864197532

$ ./apc_program 100000000000000000000 x 2
200000000000000000000

$ ./apc_program 100000000000000000000 / 2
50000000000000000000

$ ./apc_program 123456789123456789123456789 - 123456789123456789123456789
0

$ ./apc_program 123456789123456789 / 0
Division not possible


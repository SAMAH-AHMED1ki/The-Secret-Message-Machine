# Project 5 — The Secret Message Machine
**Author:** Samah Ahmed Mahmoud Ahmed  
**Email:** [sammahmedzz50@gmail.com](mailto:sammahmedzz50@gmail.com)
## Description
A text processing utility that implements Caesar cipher encryption/decryption, in-place string reversal, vowel counting, palindrome verification, and letter frequency histograms.

## How to Build and Run
1. Open terminal in the project directory.
2. Compile with warnings enabled:
   ```bash
   gcc -Wall -Wextra main.c -o secret_message
Run the executable:

On Windows: .\secret_message.exe

On Linux/Mac: ./secret_message

Explain Why
Why is shifting forward by (26 - key) equivalent to decoding?
Since the English alphabet has 26 letters, reversing a forward shift by key is mathematically identical to moving forward by the remainder (26 - key) under modulo 26 arithmetic, perfectly restoring the original text.

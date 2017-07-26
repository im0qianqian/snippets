# Balala Power!

## **Description**

> Talented Mr.Tang has n strings consisting of only lower case characters. He wants to charge them with Balala Power (he could change each character ranged from a to z into each number ranged from 0 to 25, but each two different characters should not be changed into the same number) so that he could calculate the sum of these strings as integers in base 26 hilariously.
>
> Mr.Tang wants you to maximize the summation. Notice that no string in this problem could have leading zeros except for string "0". It is guaranteed that at least one character does not appear at the beginning of any string.
>
> The summation may be quite large, so you should output it in modulo 109+7.



## **Input**

> The input contains multiple test cases.
>
> For each test case, the first line contains one positive integers n, the number of strings. (1≤n≤100000)
>
> Each of the next n lines contains a string si consisting of only lower case letters. (1≤|si|≤100000,∑|si|≤106)



## **Output**

> For each test case, output "Case #x: y" in one line (without quotes), where x indicates the case number starting from 1 and y denotes the answer of corresponding case.



## **Sample Input**

    1
    a
    2
    aa
    bb
    3
    a
    ba
    abc



## **Sample Output**

    Case #1: 25
    Case #2: 1323
    Case #3: 18221


## **题意**


# Rebuilding Roads

## **Description**

> The cows have reconstructed Farmer John's farm, with its N barns (1 <= N <= 150, number 1..N) after the terrible earthquake last May. The cows didn't have time to rebuild any extra roads, so now there is exactly one way to get from any given barn to any other barn. Thus, the farm transportation system can be represented as a tree. 
>
> Farmer John wants to know how much damage another earthquake could do. He wants to know the minimum number of roads whose destruction would isolate a subtree of exactly P (1 <= P <= N) barns from the rest of the barns.



## **Input**

> Line 1: Two integers, N and P 
>
> Lines 2..N: N-1 lines, each with two integers I and J. Node I is node J's parent in the tree of roads. 



## **Output**

> A single line containing the integer that is the minimum number of roads that need to be destroyed for a subtree of P nodes to be isolated. 



## **Sample Input**

    11 6
    1 2
    1 3
    1 4
    1 5
    2 6
    2 7
    2 8
    4 9
    4 10
    4 11



## **Sample Output**

    2



## **题意**


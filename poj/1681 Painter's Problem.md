# Painter's Problem

## **Description**

> There is a square wall which is made of n×n small square bricks. Some bricks are white while some bricks are yellow. Bob is a painter and he wants to paint all the bricks yellow. But there is something wrong with Bob's brush. Once he uses this brush to paint brick (i, j), the bricks at (i, j), (i-1, j), (i+1, j), (i, j-1) and (i, j+1) all change their color. Your task is to find the minimum number of bricks Bob should paint in order to make all the bricks yellow. 



## **Input**

> The first line contains a single integer t (1 <= t <= 20) that indicates the number of test cases. Then follow the t cases. Each test case begins with a line contains an integer n (1 <= n <= 15), representing the size of wall. The next n lines represent the original wall. Each line contains n characters. The j-th character of the i-th line figures out the color of brick at position (i, j). We use a 'w' to express a white brick while a 'y' to express a yellow brick.



## **Output**

> For each case, output a line contains the minimum number of bricks Bob should paint. If Bob can't paint all the bricks yellow, print 'inf'.



## **Sample Input**

    2
    3
    yyy
    yyy
    yyy
    5
    wwwww
    wwwww
    wwwww
    wwwww
    wwwww



## **Sample Output**

    0
    15
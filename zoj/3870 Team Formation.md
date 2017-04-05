# Team Formation

> For an upcoming programming contest, Edward, the headmaster of Marjar University, is forming a two-man team from N students of his university.
>
> Edward knows the skill level of each student. He has found that if two students with skill level A and B form a team, the skill level of the team will be A ⊕ B, where ⊕ means bitwise exclusive or. A team will play well if and only if the skill level of the team is greater than the skill level of each team member (i.e. A ⊕ B > max{A, B}).
>
> Edward wants to form a team that will play well in the contest. Please tell him the possible number of such teams. Two teams are considered different if there is at least one different team member.



## **Input**

> There are multiple test cases. The first line of input contains an integer T indicating the number of test cases. For each test case:
>
> The first line contains an integer N (2 <= N <= 100000), which indicates the number of student. The next line contains N positive integers separated by spaces. The ith integer denotes the skill level of ith student. Every integer will not exceed 109.



## **Output**

> For each case, print the answer in one line.



## **Sample Input**

    2
    3
    1 2 3
    5
    1 2 3 4 5



## **Sample Output**

    1
    6




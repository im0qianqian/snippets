/*
HDU 1003 Max Sum
*/

#include <iostream>
using namespace std;
int main()
{
    int T,N,n,j =1;
    cin >> T;
    while (T--)
    {
        int max = -1001,sum = 0,temp = 1,first,second;
        cin >> N;
        int *p = new int(N);
        for (int i = 1; i <= N; i++)
        {
            cin >> n;
            sum += n;
            if (max < sum)
            {
                max = sum;
                first = temp;
                second = i;
            }
            if (sum < 0)
            {
                sum = 0;
                temp = i +1;
            }
        }
        cout << "Case " << j++ << ":" << endl;
        cout << max << " " << first << " " << second << endl;
        if(T)cout << endl;
        delete p;
    }
    return 0;
}

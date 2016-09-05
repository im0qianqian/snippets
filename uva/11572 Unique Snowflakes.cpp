/*
UVA 11572 Unique Snowflakes
*/
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
int a[1000005];
int main()
{
    int cases,n;
    cin >> cases;
    while(cases--)
    {
        set<int> s;
        cin>> n;
        for(int i=0; i<n; i++)
            cin >> a[i];
        int left=0,right=0,ans=0;
        while(right<n)
        {
            while(right < n && !s.count(a[right]))
                s.insert(a[right++]);
            ans = max(ans, right-left);
            s.erase(a[left++]);
        }
        cout <<ans<< endl;
    }
    return 0;
}

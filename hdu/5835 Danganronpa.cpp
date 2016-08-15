/*
HDU 5835 Danganronpa
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int t,n,a[15],sum,ans,table,j;
    cin>>t;
    for(int p=1; p<=t; p++)
    {
        cin>>n;
        sum=0;
        for(int i=0; i<n; i++)
        {
            cin>>a[i];
            sum+=a[i];
        }
        sort(a,a+n);
        table = sum/2;
        for(ans=0,j=n-1; ans<=table&&j>=0; j--)
        {
            sum-=a[j];
            if(sum>a[j])ans+=a[j];
            else
            {
                ans+=sum*2;
                break;
            }
        }
        if(ans>table)ans=table;
        cout<<"Case #"<<p<<": "<<ans<<endl;
    }
    return 0;
}

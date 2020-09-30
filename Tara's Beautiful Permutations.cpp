#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
#define mod 1000000007
lli dp[2000][2000][2];
lli arr[10000];
lli solve(int one,int two,int flag)
 {
  if(one==0 && two==0) return (flag==0);
   else if(one<0 || two<0) return 0;
   if(dp[one][two][flag]!=-1) return dp[one][two][flag];
   else
   {
    lli ans=0;
     if(flag)
        {
          ans=(ans+(solve(one-1,two,0)*(one-1))%mod)%mod;
   }
   if(flag==0)
   {
    ans=(ans+(solve(one-1,two,0)*(one))%mod)%mod;
   }
   ans=(ans+(solve(one+1,two-1,1)*two)%mod)%mod;
   dp[one][two][flag]=ans;
   return ans;
   }
 }
int main()
{
 int t;
  cin>>t;
   memset(dp,-1,sizeof dp);
   while(t--)
   {
    vector<lli> arr;
     int n;
    
      cin>>n;
       for(int i=0;i<n;i++)
         {
          int a;
          cin>>a;
          arr.push_back(a);
    }
    sort(arr.begin(),arr.end());
    int one=0,two=0;
    for(int i=0;i<=n-1;)
     {
       //cout<<" comparing "<<arr[i]<<" "<<arr[i+1]<<endl;
      
       if(arr[i]==arr[i+1])
        {
          two++;
          i+=2;
     }
     else
     {
      one++;
      i++;
     }
     
     }
    lli ans=solve(one,two,0);
     cout<<ans<<endl;
   }
  
 
}

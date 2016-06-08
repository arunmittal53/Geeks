// arunmittal53
// map is user for data compression
// we can also do data compression by sorting in another
// temp array and than replacing the origional array with compressed values
#include<bits/stdc++.h>
using namespace std;
#define ll long long int
int smaller[100001]={0},larger[100001]={0};
int dp[400001]={0};
void insert(int st,int ss,int se,int i)
{
	if(ss == se)
	{
		dp[st] ++;
		return ;
	}
	int mid = (ss + se) / 2;
	if(i<=mid)
	{
		insert(2*st,ss,mid,i);
	}
	else
	{
		insert(2*st+1,mid+1,se,i);
	}
	dp[st]=dp[2*st]+dp[2*st +1];
}
int query(int st,int ss,int se,int i,int j)
{
	if(se<ss||ss>j||se<i)
		return 0;
	if(ss>=i&&se<=j)
		return dp[st];
	int mid = (ss + se)/2; 
	int xx=query(2*st,ss,mid,i,j)+query(2*st+1,mid+1,se,i,j);
	//cout<<"xx "<<xx<<"\n";
	return xx;
}
int main()
{
	int n,a[100000],i;
	cin>>n;
	map<int,int> mp;
	for(i=0;i<n;i++){
		cin>>a[i];
		mp[a[i]]++;
	}
	map<int,int>::iterator it;
	i=0;
	it=mp.begin();
	while(it!=mp.end())
	{
		it->second = i;
		i ++;
		it ++;
	}
	for(i = 0 ; i < n ; i ++)
	{
		a[i]=mp[a[i]];
	}
	for(i=0;i<n;i++)
	{
		larger[i] = query(1,0,n-1,a[i]+1,n);
		insert(1,0,n-1,a[i]);
	}
	for(i=0;i<4*n;i++)
		dp[i]=0;
	for(i=n-1;i>=0;i--)
	{
		smaller[i] = query(1,0,n,0,a[i]-1);
		insert(1,0,n,a[i]);
	}
	ll ans=0;
	for(i=0;i<n;i++)
	{
		ans += larger[i]*smaller[i];
	}
	cout<<ans<<"\n";
	return 0;
}



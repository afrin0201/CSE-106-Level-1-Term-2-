#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int max_diff(int arr[],int low, int high, int max){

    if (low<=high){
        int mid= (low+high)/2;
        if (max<arr[high]-arr[low])
        {
            max=arr[high]-arr[low];

        }
        max_diff(arr,low,high-1,max);
        max_diff(arr,low+1,high,max);
    }
    else 
    return max;
}
int main()
{
  int n;
  cin >> n;
  int arr[n];
  for(int i=0;i<n;i++){
    cin>>arr[i];
  }
  cout<<max_diff(arr, 0, n-1, 0);

    return 0;
}
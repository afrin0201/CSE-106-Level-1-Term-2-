#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int binary_search(int arr[], int low , int high, int target){
    if(low>high) return -1;
    int mid=(low+high)/2;
    if (arr[mid]==target) return mid;
    if (arr[mid]>target){
       return binary_search(arr,low, mid-1, target);

    }
    else {
       return  binary_search(arr,mid+1, high, target);
    }
}
int main()
{
  int n;
  cin >> n;
  int arr[n];
  for(int i=0;i<n;i++) cin>>arr[i];
  cout<<binary_search(arr, 0 , n-1, 6);
    return 0;
}
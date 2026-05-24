#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
bool doesWork(vector<ll> tasks, int k, ll maxWorkLoad)
{
    int worker = 1;
    ll current_sum = 0;
    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i] > maxWorkLoad)
            return false;
        if (current_sum + tasks[i] <= maxWorkLoad)
        {
            current_sum = current_sum + tasks[i];
        }
        else
        {
            worker++;
            current_sum = tasks[i];
        }
    }
    return worker <= k;
}

ll minimized_max(vector<ll> tasks, int k)
{
    ll low_bound = *max_element(tasks.begin(), tasks.end());
    ll high_bound = 0;
    for (int i = 0; i < tasks.size(); i++)
    {
        high_bound=high_bound+tasks[i];
    }
    ll result = high_bound;
    while (low_bound <= high_bound)
    {
        ll mid = (low_bound + high_bound) / 2;
        if (doesWork(tasks, k, mid))
        {
            result = mid;
            high_bound = mid - 1;
        }
        else
        {
            low_bound = mid + 1;
        }
    }
    return result;
}
int main()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> tasks(n);
    for (int i = 0; i < n; i++)
    {
        cin >> tasks[i];
    }
    if (n<k){
        cout<<-1<<endl;
        return 0;
    }
    cout << minimized_max(tasks, k) << endl;
    return 0;
}
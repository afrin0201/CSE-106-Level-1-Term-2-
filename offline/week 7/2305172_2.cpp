#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
bool seated_students(int n, int b, vector<int> seats, int m)
{
    int bench_size = n / b;
    vector<bool> blocked(n, false);
    for (int i = 0; i < n; i++)
    {
        int start = (i / bench_size) * bench_size;
        int end = start + bench_size - 1;

        if (seats[i] == 1)
        {
            if (seats[i] == 1)
            {
                if (i + 1 <= end)
                    blocked[i + 1] = true;
            }}
            if (seats[i] == 2)
            {
                if (i - 1 >= start)
                    blocked[i - 1] = true;
                if (i + 1 <= end)
                    blocked[i + 1] = true;
            }
        
    }
    int avail = 0;
    for (int i = 0; i < n; i++)
    {
        if (seats[i] == 0 && blocked[i] == false)
        {
            avail++;
        }
    }

    return avail >= m;
}
int main()
{
    int n, b, m;
    cin >> n >> b;
    vector<int> seats(n);
    for (int i = 0; i < n; i++)
    {
        cin >> seats[i];
    }
    cin >> m;
    bool ans = seated_students(n, b, seats, m);
    if (ans == true)
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }
    return 0;
}
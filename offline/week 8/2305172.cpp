#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
void print(string a, string b, vector<vector<char>>trace,int i ,int j, bool isglobal){
    string aligned_A="",aligned_B="";
   while ((isglobal && (i > 0 || j > 0)) || (!isglobal && trace[i][j] != '0'))
{
         if (trace[i][j] == 'D') {
            aligned_A = a[i - 1] + aligned_A;
            aligned_B = b[j - 1] + aligned_B;
            i--; j--;
        } else if (trace[i][j] == 'U') {
            aligned_A = a[i - 1] + aligned_A;
            aligned_B = '-' + aligned_B;
            i--;
        } else if (trace[i][j] == 'L') {
            aligned_A = '-' + aligned_A;
            aligned_B = b[j - 1] + aligned_B;
            j--;
        } else break;
    }

    cout<<aligned_A<<endl<<aligned_B<<endl;
}
void global(string a, string b, int match, int mismatch, int gap) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    vector<vector<char>> trace(n + 1, vector<char>(m + 1));

    for (int i = 0; i <= n; i++) {
        dp[i][0] = i * gap;
        trace[i][0] = 'U';
    }
    for (int j = 0; j <= m; j++) {
        dp[0][j] = j * gap;
        trace[0][j] = 'L';
    }
    trace[0][0] = '0';
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int scoreD = dp[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? match : mismatch);
            int scoreU= dp[i - 1][j] + gap;
            int scoreL = dp[i][j - 1] + gap;

            dp[i][j] = max({scoreD, scoreU, scoreL});

            if (dp[i][j] == scoreD) trace[i][j] = 'D';
            else if (dp[i][j] == scoreU) trace[i][j] = 'U';
            else trace[i][j] = 'L';
        }
    }

    cout << "\nGlobal Alignment:\n";
    print(a, b, trace, n, m, true);
    cout << "Maximum Score: " << dp[n][m] << "\n";
}
void local(string a, string b, int match, int mismatch, int gap) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<char>> trace(n + 1, vector<char>(m + 1, '0'));

    int maxScore = 0, maxI = 0, maxJ = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int scoreD = dp[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? match : mismatch);
            int scoreU = dp[i - 1][j] + gap;
            int scoreL = dp[i][j - 1] + gap;

            dp[i][j] = max({0, scoreD, scoreU, scoreL});

            if (dp[i][j] == 0) trace[i][j] = '0';
            else if (dp[i][j] == scoreD) trace[i][j] = 'D';
            else if (dp[i][j] == scoreU) trace[i][j] = 'U';
            else trace[i][j] = 'L';

            if (dp[i][j] > maxScore) {
                maxScore = dp[i][j];
                maxI = i;
                maxJ = j;
            }
        }
    }

    cout << "\nLocal Alignment:\n";
    print(a, b, trace, maxI, maxJ, false);
    cout << "Maximum Score: " << maxScore << "\n";
}
int main()
{
   string s1, s2;
   cout<<"Enter the first sequence : ";
   cin>>s1;
   cout<<"Enter the second sequence :" ;
   cin>>s2;
   int match, mismatch, gap;
   cout<<"Enter match score : ";
   cin>>match;
   cout<<"Enter mismatch penalty : ";
   cin>>mismatch;
   cout<<"Enter gap penalty : ";
   cin>>gap;
   global(s1, s2, match, mismatch, gap);
   local(s1, s2, match, mismatch, gap);

    
    return 0;
}
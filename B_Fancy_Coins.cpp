#include <bits/stdc++.h>
using namespace std;
#define int long long
#define letsgooooooooooo            \
  ios_base::sync_with_stdio(false); \
  cin.tie(NULL);                    \
  cout.tie(NULL);
#define test         \
  int Tushars_07;    \
  cin >> Tushars_07; \
  while (Tushars_07--)
#define endl "\n"
#define no cout << "NO \n";
#define yes cout << "YES \n";
#define ub upper_bound  // '>'
#define lb lower_bound  // '<='
const int pi = 3.14159265358979323846;
#define vi vector<int>
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define each(a, x) for (auto &a : x)
#define fi for (int i = 0; i < n; i++)
#define fj for (int j = 0; j < n; j++)

// ASCII values a=97 A=65
//  const ll mod = 1000000007;
//  const ll mod = 998244353;

//! bitwise operators
//&  and
//|  or
//^  XOR
//<< left shift (*2)
//>> right shift (/2)
//~  bitwise not
//__builtin_popcount(uli)  --> to calculate the no of set bits O(1)

//! IMPORTANT FUNCTIONS
// 1. binary_search(startaddress,endaddress, valuetofind) --> true or false

/* //!stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 * Fcking use lli instead of int
 * use map/set instead of unordered map/set whererver possible
 */

int coins(int count2 , int k ){
  int temp = 0 ; 
  temp += count2/k ; 
  
}



int32_t main() {
  letsgooooooooooo cout << fixed << setprecision(7);
  test {
    int m, k, a1, ak;
    cin >> m >> k >> a1 >> ak;
    int count1 = 0;  // kfancy
    int count2 = 0;  // 1fancy
    int flag = 0;
    if (m / k > ak) {
      m = m - ak * k;
      if (m > a1) {
        m = m - a1;
        count1 += m / k;

        count2 += m % k;
        flag = 1;
        cout << "yes"
             << " " << count1 << " " << count2 << endl;
      } else {
      }
    } else {
      m = m % k;
      if (m <= a1) {
      } else {
        count1 = m - a1;
      }
    }
    if (flag) {
      int temp = count2 + a1;
      int temp2 = temp / k;
      cout << "HI" << endl;
      cout << temp << " " << temp2 << endl;
      count1 += temp2;

      temp -= temp2 * k;
      if (temp > a1) {
        count2 = temp - a1;
      } else {
        count2 = 0;
      }
    }

    cout << count1 + count2 << endl;
  }

  return 0;
}

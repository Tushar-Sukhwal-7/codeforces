#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif
#define int long long
using namespace std;

template <typename Node, typename Update>
struct LazySGT {
  vector<Node> tree;
  vector<bool> lazy;
  vector<Update> updates;
  vector<vector<int>> arr;  // type may change
  int n;
  int s;

  LazySGT(int a_len, vector<int> &a) {  // change if type updated
    n = a_len;                          // Corrected initialization
    arr.resize(n, vector<int>(32, 0));
    for (int i = 0; i < n; i++) {
      int j = 0;
      int num = a[i];
      while (num) {
        if (num & 1) {
          arr[i][j]++;
        }
        j++;
        num >>= 1;
      }
    }
    s = 1;
    while (s < 2 * n) {
      s = s << 1;
    }
    tree.resize(s);
    fill(tree.begin(), tree.end(), Node());
    lazy.resize(s);
    fill(lazy.begin(), lazy.end(), false);
    updates.resize(s);
    fill(updates.begin(), updates.end(), Update());
    build(0, n - 1, 1);
  }

  void build(int start, int end, int index) {  // Never change this
    if (start == end) {
      tree[index] = Node(arr[start]);
      return;
    }
    int mid = (start + end) / 2;
    build(start, mid, 2 * index);
    build(mid + 1, end, 2 * index + 1);
    tree[index].merge(tree[2 * index], tree[2 * index + 1]);
  }

  void pushdown(int index, int start, int end) {
    if (lazy[index]) {
      int mid = (start + end) / 2;
      apply(2 * index, start, mid, updates[index]);
      apply(2 * index + 1, mid + 1, end, updates[index]);
      updates[index] = Update();
      lazy[index] = 0;
    }
  }

  void apply(int index, int start, int end, Update &u) {
    if (start != end) {
      lazy[index] = 1;
      updates[index].combine(u, start, end);
    }
    u.apply(tree[index], start, end);
  }

  void update(int start, int end, int index, int left, int right,
              Update &u) {  // Never Change this
    if (start > right || end < left) return;
    if (start >= left && end <= right) {
      apply(index, start, end, u);
      return;
    }
    pushdown(index, start, end);
    int mid = (start + end) / 2;
    update(start, mid, 2 * index, left, right, u);
    update(mid + 1, end, 2 * index + 1, left, right, u);
    tree[index].merge(tree[2 * index], tree[2 * index + 1]);
  }

  Node query(int start, int end, int index, int left,
             int right) {  // Never change this
    if (start > right || end < left) return Node();
    if (start >= left && end <= right) {
      pushdown(index, start, end);
      return tree[index];
    }
    pushdown(index, start, end);
    int mid = (start + end) / 2;
    Node l, r, ans;
    l = query(start, mid, 2 * index, left, right);
    r = query(mid + 1, end, 2 * index + 1, left, right);
    ans.merge(l, r);
    return ans;
  }

  void make_update(int left, int right,
                   int val) {         // pass in as many parameters as required
    Update new_update = Update(val);  // may change
    update(0, n - 1, 1, left, right, new_update);
  }

  Node make_query(int left, int right) {
    return query(0, n - 1, 1, left, right);
  }
};

struct Node1 {
  vector<int> val;  // may change
  Node1() {         // Identity element
    val.resize(32, 0);
  }

  Node1(vector<int> &p1) {  // Actual Node
    val = p1;
  }

  void merge(Node1 &l, Node1 &r) {  // Merge two child nodes
    for (int i = 0; i < 32; i++) {
      val[i] = l.val[i] + r.val[i];
    }
  }
};

struct Update1 {
  int val;     // may change
  Update1() {  // Identity update
    val = 0;
  }

  Update1(int val1) {  // Actual Update
    val = val1;
  }

  void apply(Node1 &a, int start, int end) {  // apply update to given node
    for (int i = 0; i < 32; i++) {
      if ((val & (1 << i)) != 0) {
        a.val[i] = (end - start + 1) - a.val[i];
      }
    }
  }

  void combine(Update1 &new_update, int start, int end) {
    val ^= new_update.val;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) cin >> arr[i];

  int m;
  cin >> m;

  LazySGT<Node1, Update1> lg(n, arr);

  for (int i = 0; i < m; i++) {
    int t;
    cin >> t;

    if (t == 1) {
      int l, r;
      cin >> l >> r;
      l--;
      r--;

      vector<int> ans = lg.make_query(l, r).val;

      int summ = 0;
      for (int i = 0; i < 32; i++) {
        summ += ans[i] * (1 << i);
      }
      cout << summ << endl;

    } else {
      int l, r, x;
      cin >> l >> r >> x;
      l--;
      r--;
      lg.make_update(l, r, x);
    }
  }

  return 0;
}
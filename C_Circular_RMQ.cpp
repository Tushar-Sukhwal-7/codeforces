// Author :- Tushar || 24-08-2024 18:05:14
#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif
#define int long long
using namespace std;
/*
    ∧＿∧
　 (｡･ω･｡)つ━☆・*。
  ⊂/　 /　   ・゜
　しーＪ　　　     °。+ * 。　
　　　　　                .・゜
*/

template <typename Node, typename Update>
struct LazySGT {
  vector<Node> tree;
  vector<bool> lazy;
  vector<Update> updates;
  vector<int> arr;  // type may change
  int n;
  int s;
  LazySGT(int a_len, vector<int> &a) {  // change if type updated
    arr = a;
    n = a_len;
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
  int val;          // may change
  Node1() {         // Identity element
    val = INT_MAX;  // may change
  }
  Node1(int p1) {  // Actual Node
    val = p1;      // may change
  }
  void merge(Node1 &l, Node1 &r) {  // Merge two child nodes
    val = min(l.val, r.val);        // may change
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
  // a.val = val * (end - start + 1);
  void apply(Node1 &a, int start, int end) {  // apply update to given node
    a.val += val ;         
  }
  void combine(Update1 &new_update, int start, int end) {
    val += new_update.val;
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

  LazySGT<Node1, Update1> st(n, arr);

  int m;
  cin >> m;
  cin.ignore();

  for (int i = 0; i < m; i++) {
    string str;
    getline(cin, str);
    stringstream ss(str);
    vector<int> input;
    int t;
    while (ss >> t) {
      input.push_back(t);
    }

    if (input.size() == 2) {
      int l = input[0];
      int r = input[1];

      if (l <= r) {
        cout << st.make_query(l, r).val << endl;
      } else {
        cout << min(st.make_query(0, r).val, st.make_query(l, n - 1).val)
             << endl;
      }
    } else {
      int l = input[0];
      int r = input[1];
      int v = input[2];

      if (l <= r) {
        st.make_update(l, r, v);
      } else {
        st.make_update(0, r, v);
        st.make_update(l, n - 1, v);
      }
    }
  }

  return 0;
}

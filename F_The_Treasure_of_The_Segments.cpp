// Author :- Tushar || 24-08-2024 23:26:38
#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif
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
  int val;    // may change
  Node1() {   // Identity element
    val = 0;  // may change
  }
  Node1(int p1) {  // Actual Node
    val = p1;      // may change
  }
  void merge(Node1 &l, Node1 &r) {  // Merge two child nodes
    val = max(l.val, r.val);        // may change
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
    a.val += val;                             // may change
  }
  void combine(Update1 &new_update, int start, int end) {
    val += new_update.val;
  }
};

int getIndex(vector<int> &arr, int a) {
  return lower_bound(arr.begin(), arr.end(), a) - arr.begin();
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;

    vector<pair<int, int>> query;
    vector<int> arr;

    set<int> st;
    for (int i = 0; i < n; i++) {
      int l, r;
      cin >> l >> r;
      st.insert(l);
      st.insert(r);
      query.push_back({l, r});
    }
    arr.resize(st.size());
    copy(st.begin(), st.end(), arr.begin());

    vector<int> seg(arr.size(), 0);
    LazySGT<Node1, Update1> lg(arr.size(), seg);

    // build
    for (auto it : query) {
      lg.make_update(getIndex(arr, it.first), getIndex(arr, it.second), 1);
    }
    for (auto it : lg.tree) cout << it.val << " ";
    cout << endl;

    int minn = INT_MAX;
    for (auto it : query) {
      minn = min(minn, n - lg.make_query(getIndex(arr, it.first),
                                         getIndex(arr, it.second))
                               .val);
    }
    cout << minn;

    cout << endl;
  }

  return 0;
}

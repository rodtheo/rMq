#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vint;

int ceil_log2(int x) {
  return 32 - __builtin_clz(x - 1);
}

struct RMQ {
  vint& v;
  vector<vint> A;
  RMQ(vint& v) : v(v), A(v.size(), vint(ceil_log2(v.size()) + 1, 0)) {
    int n = v.size();
    int i, j, k;
    for (i = 0; i < n; ++i) {
      A[i][0] = i;
    }
    j = 1;
    k = 1;
    do {
      for (i = 0; i + k < n; ++i) {
        if (v[A[i][j - 1]] > v[A[i + k][j - 1]]) {
          A[i][j] = A[i][j - 1];
        } else {
          A[i][j] = A[i + k][j - 1];
        }
      }
      k <<= 1;
      ++j;
    } while(k < n);
  }

  int query(int i, int j) {
    int k = ceil_log2(j - i + 1) - 1;
    if (v[A[i][k]] > v[A[j - (1 << k) + 1][k]]) {
      return A[i][k];
    } else {
      return A[j - (1 << k) + 1][k];
    }
  }
};

int main() {
  vint v={31, 41, 59, 26, 53, 58, 97, 93, 23, 84, 62, 64, 33, 83, 27};

/*  while (cin >> n) {
    vint v(n);
    int i, j;
    for (i = 0; i < n; ++i) {
      cin >> v[i];
    }
*/
    RMQ solver(v);

  /*  int m;
    cin >> m;
    int k;
    for (k = 0; k < m; ++k) {
      cin >> i >> j;
      cout << solver.rmq(i, j) << endl;
    }
  }
*/

        cout << "SOLVING" << endl;
        cout << "SOLVING RMQ(1,13) = " << solver.query(1,13) << endl;
        cout << "SOLVING RMQ(2,7) = " << solver.query(2,7) << endl;
        cout << "SOLVING RMQ(4,5) = " << solver.query(4,5) << endl;

}

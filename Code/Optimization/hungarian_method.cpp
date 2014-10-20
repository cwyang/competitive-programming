#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <utility>

const int INF = 0x3f3f3f3f;
#define N 50

using namespace std;

class Hungarian {
  private:
    int n;
    int max_match;
    int cost[N*N];
    int costMin[N*N];

    vector<int> lx;
    vector<int> ly;
    vector<int> xy;
    vector<int> yx;
    vector<bool> S;
    vector<bool> T;
    int slack[N];
    int slackx[N];
    vector<int> prev;

    void update_labels() {
      int x, y, delta = INF;
      for (y = 0; y < n; y++) {
        if (!T[y]) {
          delta = min(delta, slack[y]);
        }
      }

      for (x = 0; x < n; x++) {
        if (S[x]) {
          lx[x] -= delta;
        }
      }

      for (y = 0; y < n; y++) {
        if (T[y]) {
          ly[y] += delta;
        }
      }

      for (y = 0; y < n; y++) {
        if (!T[y]) {
          slack[y] -= delta;
         }
      }
    }

    void init_labels() {
      lx.assign(n, 0);
      ly.assign(n, 0);

      for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
          int it = x * n + y;
          lx[x] = max(lx[x], cost[it]);
        }
      }
    }

    void add_to_tree(int x, int prevx) {
      S[x] = true;
      prev[x] = prevx;

      for (int y = 0; y < n; y++) {
        int it = x * n + y;
        if (lx[x] + ly[y] - cost[it] < slack[y]) {
          int it = x * n + y;
          slack[y] = lx[x] + ly[y] - cost[it];
          slackx[y] = x;
        }
      }
    }

    void augment() {
      if (max_match == n) {
        return;
      }

      int x, y, root;
      int q[N], wr = 0, rd = 0;

      S.assign(n, false);
      T.assign(n, false);
      prev.assign(n, -1);

      for (x = 0; x < n; x++) {
        if (xy[x] == -1) {
          q[wr++] = root = x;
          prev[x] = -2;
          S[x] = true;
          break;
        }
      }

      for (y = 0; y < n; y++) {
        int it = root * n + y;
        slack[y] = lx[root] + ly[y] - cost[it];
        slackx[y] = root;
      }

      while (true) {
        while (rd < wr) {
          x = q[rd++];

          for (y = 0; y < n; y++) {
            int it = x * n + y;

            if (cost[it] == lx[x] + ly[y] &&  !T[y]) {
              if (yx[y] == -1) {
                break;
              }

              T[y] = true;
              q[wr++] = yx[y];
              add_to_tree(yx[y], x);
            }
          }

          if (y < n) {
            break;
          }
        }

        if (y < n) {
          break;
        }

        update_labels();
        wr = rd = 0;

        for (y = 0; y < n; y++) {
          if (!T[y] &&  slack[y] == 0) {
            if (yx[y] == -1) {
              x = slackx[y];
              break;
            } else {
              T[y] = true;

              if (!S[yx[y]]) {
                q[wr++] = yx[y];
                add_to_tree(yx[y], slackx[y]);
              }
            }
          }
        }

        if (y < n) {
          break;
        }
      }

      if (y < n) {
        max_match++;

        for (int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty) {
          ty = xy[cx];
          yx[cy] = cx;
          xy[cx] = cy;
        }

        augment();
      }
    }

    int getMax() {
      int ret = 0;
      max_match = 0;
      xy.assign(n, -1);
      yx.assign(n, -1);

      init_labels();
      augment();

      for (int x = 0; x < n; x++) {
        int it = x * n + xy[x];
        ret += cost[it];
      }

      return ret;
    }

    int getMin() {
      int ret = 0;
      max_match = 0;
      xy.assign(n, -1);
      yx.assign(n, -1);

      init_labels();
      augment();

      for (int x = 0; x < n; x++) {
        int it = x * n + xy[x];
        ret += costMin[it];
      }

      return ret;
    }

  public:
    int max_optimal;
    int min_optimal;

    Hungarian(int size, int array[]) {
      n = size;
      int max_value = 0;

      for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
          int it = row * n + col;
          cost[it] = array[it];
          costMin[it] = array[it];
          max_value = max(max_value, array[it]);
        }
      }

      max_optimal = getMax();

      for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
          int it = row * n + col;
          cost[it] = max_value - cost[it];
        }
      }

      min_optimal = getMin();
    }
};

int main() {
  int test_cost[] = { 250, 400, 250,    //  [ 250  400  250 ]
                      400, 600, 250,    //  [ 400  600  250 ]
                      200, 400, 250 };  //  [ 200  400  250 ]
  int n = 3;
  Hungarian hungarian(n, test_cost);

  assert(hungarian.max_optimal == 1100);
  //  [ (250)  400   250  ]
  //  [  400  (600)  250  ]   MAX COST = 1100
  //  [  200   400  (250) ]

  assert(hungarian.min_optimal == 850);
  //  [  250  (400)  250  ]
  //  [  400   600  (250) ]   MIN COST = 850
  //  [ (200)  400   250  ]
}

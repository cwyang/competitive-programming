#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

#define DFS_WHITE -1
#define DFS_BLACK 1

vector<vii> AdjList;

vi dfs_num;
vi dfs_parent;
vi dfs_low;
vi articulation_vertex;

int dfsNumberCounter, dfsRoot, rootChildren;

void articulationPointAndBridge(int u) {
  dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
  for (int j = 0; j < (int)AdjList[u].size(); j++) {
    ii v = AdjList[u][j];
    if (dfs_num[v.first] == DFS_WHITE) {
      dfs_parent[v.first] = u;
      if (u == dfsRoot) rootChildren++;

      articulationPointAndBridge(v.first);

      if (dfs_low[v.first] >= dfs_num[u])
        articulation_vertex[u] = true;
      if (dfs_low[v.first] > dfs_num[u])
        printf(" Edge (%d, %d) is a bridge\n", u, v.first);
      dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
    } else if (v.first != dfs_parent[u])
      dfs_low[u] = min(dfs_low[u], dfs_num[v.first]);
    }
}

int main() {
  /*
  6
  1 1 0
  5 0 0 2 0 3 0 4 0 5 0
  1 1 0
  1 1 0
  2 1 0 5 0
  2 1 0 4 0
  */

  int V, total_neighbors, id, weight;

  scanf("%d", &V);
  AdjList.assign(V, vii());
  for (int i = 0; i < V; i++) {
    scanf("%d", &total_neighbors);
    for (int j = 0; j < total_neighbors; j++) {
      scanf("%d %d", &id, &weight);
      AdjList[i].push_back(ii(id, weight));
    }
  }

  dfsNumberCounter = 0;
  dfs_num.assign(V, DFS_WHITE);
  dfs_low.assign(V, 0);
  dfs_parent.assign(V, -1);
  articulation_vertex.assign(V, 0);

  printf("Bridges:\n");
  for (int i = 0; i < V; i++) {
    if (dfs_num[i] == DFS_WHITE) {
      dfsRoot = i; rootChildren = 0;
      articulationPointAndBridge(i);
      articulation_vertex[dfsRoot] = (rootChildren > 1);
    }
  }

  printf("Articulation Points:\n");
  for (int i = 0; i < V; i++) {
    if (articulation_vertex[i]) {
      printf(" Vertex %d\n", i);
    }
  }

}

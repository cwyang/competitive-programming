#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;


class UnionFind {                                            
private:
  vi p, rank, setSize;                   
  int numSets;
public:
  UnionFind(int N) {
    setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
    p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
  void unionSet(int i, int j) { 
    if (!isSameSet(i, j)) { numSets--; 
    int x = findSet(i), y = findSet(j);
    if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
    else                   { p[x] = y; setSize[y] += setSize[x];
                             if (rank[x] == rank[y]) rank[y]++; } } }
  int numDisjointSets() { return numSets; }
  int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

vector<vii> AdjList;
vi taken;                               
priority_queue<ii> pq;           

void process(int vtx) {   
  taken[vtx] = 1;
  for (int j = 0; j < (int)AdjList[vtx].size(); j++) {
    ii v = AdjList[vtx][j];
    if (!taken[v.first]) pq.push(ii(-v.second, -v.first));
} }                                

int main() {
  int V, E, u, v, w;

  freopen("in_03.txt", "r", stdin);

  scanf("%d %d", &V, &E);
  
  AdjList.assign(V, vii());
  vector< pair<int, ii> > EdgeList;   
  for (int i = 0; i < E; i++) {
    scanf("%d %d %d", &u, &v, &w);     
    EdgeList.push_back(make_pair(w, ii(u, v)));       
    AdjList[u].push_back(ii(v, w));
    AdjList[v].push_back(ii(u, w));
  }
  sort(EdgeList.begin(), EdgeList.end()); 
                      

  int mst_cost = 0;
  UnionFind UF(V);                  
  for (int i = 0; i < E; i++) {             
    pair<int, ii> front = EdgeList[i];
    if (!UF.isSameSet(front.second.first, front.second.second)) {  
      mst_cost += front.first;               
      UF.unionSet(front.second.first, front.second.second);    
  } }                       

  printf("MST cost = %d (Kruskal's)\n", mst_cost);



// prim algotithm
  taken.assign(V, 0);              
  process(0);   
  mst_cost = 0;
  while (!pq.empty()) { 
    ii front = pq.top(); pq.pop();
    u = -front.second, w = -front.first;  
    if (!taken[u])            
      mst_cost += w, process(u); 
  }                                        
  printf("MST cost = %d (Prim's)\n", mst_cost);

  return 0;
}
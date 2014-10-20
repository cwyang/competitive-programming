int main() {
  int visited[202];
  int n, l, x, y;
  vector<vi> v;

  while (cin >> n, n != 0) {
    cin >> l;
    v.clear();
    v.assign(n+1, vi());
    memset(visited, -1, visited(c));

    for (int i=0; i<l; i++) {
      cin >> x >> y;
      v[x].PB(y);
      v[y].PB(x);
    }

    queue<int> q;
    q.push(0);

    bool isBipartite = true;
    visited[0] = 0;
    while(!q.empty() && isBipartite) {
      int node = q.front();
      q.pop();

      for (int i=0; i<v[node].size(); i++) {
        int next = v[node][i];
        if (visited[next] == -1) {
          visited[next] = visited[node] + 1;
          q.push(next);
        } else if ((visited[node] % 2) == (visited[next] % 2)) {
          isBipartite = false;
        }
      }
    }
  }
}

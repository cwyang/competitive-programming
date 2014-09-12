template<class T> unsigned int damerauLevenshteinDistance(const T &s1, const T &s2) {
  const size_t len1 = s1.size(), len2 = s2.size();
  unsigned int d[len1 + 1][len2 + 1], cost;

  for (int i = 0; i <= len1; i++) {
    d[i][0] = i;
  }

  for (int j = 0; j <= len2; j++) {
    d[0][j] = j;
  }

  for (int i = 1; i <= len1; i++) {
    for (int j = 1; j <= len2; j++) {
      cost = s1[i - 1] == s2[j - 1] ? 0 : 1;

      d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1),
                    d[i - 1][j - 1] + cost);

      if ((i > 1) && (j > 1) && (s1[i - 1] == s2[j - 2]) && (s1[i - 2] == s2[j - 1])) {
        d[i][j] = min(d[i][j], d[i - 2][j - 2] + cost);
      }
    }
  }

  return d[len1][len2];
}

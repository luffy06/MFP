#include <algorithm>
#include <chrono>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <pthread.h>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "spfa.h"

int main() {
  // http://acm.hdu.edu.cn/showproblem.php?pid=2544
  while (scanf("%d%d", &n, &m) && n && m) {
    edges.clear();
    edges.reserve(n);
    for (int i = 0; i < n; ++ i) {
      edges.push_back({});
    }
    for (int i = 0; i < m; ++ i) {
      int from, to, cost;
      scanf("%d%d%d", &from, &to, &cost);
      edges[from - 1].push_back({from - 1, to - 1, cost});
      edges[to - 1].push_back({to - 1, from - 1, cost});
    }
    int dis = SPFA(0, n - 1);
    printf("%d\n", dis);
  }
  return 0;
}

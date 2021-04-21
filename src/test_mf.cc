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

#include "max_flow_net.h"

int main() {
  // http://acm.hdu.edu.cn/showproblem.php?pid=3549
  int n_case;
  scanf("%d", &n_case);
  for (int i_case = 1; i_case <= n_case; ++ i_case) {
    int n, m;
    scanf("%d%d", &n, &m);
    FlowNet fn(n);
    for (int i = 0; i < m; ++ i) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      fn.AddEdge(u - 1, v - 1, c);
    }
    int max_flow = fn.MaxFlow(0, n - 1);
    printf("Case %d: %d\n", i_case, max_flow);
  }
  return 0;
}

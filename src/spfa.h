#ifndef SPFA_H
#define SPFA_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int kINF = 0x3fffffff;

struct Edge {
  int from;
  int to;
  int cost;

  Edge(int a, int b, int c) : from(a), to(b), cost(c) { }
};

int n, m;
std::vector<std::vector<Edge>> edges;

int SPFA(int source, int end) {
  std::vector<int> dis;
  std::vector<bool> inq;
  std::queue<int> q;
  dis.reserve(n);
  inq.reserve(n);
  for (int i = 0; i < n; ++ i) {
    dis.push_back(kINF);
    inq.push_back(false);
  }
  dis[source] = 0;
  inq[source] = true;
  q.push(source);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    inq[u] = false;
    for (int i = 0; i < edges[u].size(); ++ i) {
      Edge e = edges[u][i];
      if (dis[e.to] > dis[u] + e.cost) {
        dis[e.to] = dis[u] + e.cost;
        if (!inq[e.to]) {
          q.push(e.to);
          inq[e.to] = true;
        }
      }
    }
  }
  return dis[end];
}

#endif
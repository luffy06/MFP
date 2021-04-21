#ifndef MAX_FLOW_NET_H
#define MAX_FLOW_NET_H

#include <iostream>
#include <cassert>
#include <cstring>
#include <queue>
#include <vector>

const int kINF = 0x3fffffff;

class FlowNet {
public:
  FlowNet(int n) : num_node_(n) {
    edges_.resize(n);
    for (int i = 0; i < n; ++ i) {
      edges_[i].resize(n);
      for (int j = 0; j < n; ++ j) {
        edges_[i][j] = Edge(i, j);
      }
    }
    dis_.resize(n);
    inq_.resize(n);
    path_.resize(n);
    Init();
  }

  void AddEdge(int from, int to, int capacity) {
    edges_[from][to].Add(capacity);
    edges_[to][from].Add(0);
  }

  int SPFA(int source, int end) {
    std::queue<int> q;
    Init();
    dis_[source] = 0;
    inq_[source] = true;
    q.push(source);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      inq_[u] = false;
      for (int v = 0; v < num_node_; ++ v) {
        Edge e = edges_[u][v];
        if (e.exist && e.capacity > e.flow && 
            dis_[v] > dis_[u] + e.capacity - e.flow) {
          dis_[v] = dis_[u] + e.capacity - e.flow;
          path_[v] = u;
          if (!inq_[v]) {
            q.push(v);
            inq_[v] = true;
          }
        }
      }
      if (dis_[end] != kINF) {
        break;
      }
    }
    if (dis_[end] != kINF) {
      int min_flow = kINF;
      for (int i = end; path_[i] != i; i = path_[i]) {
        int u = path_[i];
        int v = i;
        Edge e = edges_[u][v];
        min_flow = std::min(min_flow, e.capacity - e.flow);
      }
      return min_flow;
    }
    return -1;
  }

  int MaxFlow(int source, int end) {
    int max_flow = 0;
    int flow = 0;
    while ((flow = SPFA(source, end)) != -1) {
      max_flow += flow;
      for (int i = end; path_[i] != i; i = path_[i]) {
        int u = path_[i];
        int v = i;
        edges_[u][v].flow += flow;
        edges_[v][u].flow -= flow;
      }
    }
    return max_flow;
  }
private:
  struct Edge {
    int from;
    int to;
    int capacity;
    int flow;
    bool exist;

    Edge() : from(-1), to(-1), capacity(0), flow(0), exist(false) { }

    explicit Edge(int a, int b) : from(a), to(b), capacity(0), flow(0), exist(false) { }

    void Add(int c) {
      capacity += c;
      exist = true;
    }
  };

  void Init() {
    for (int i = 0; i < num_node_; ++ i) {
      dis_[i] = kINF;
      inq_[i] = false;
      path_[i] = i;
    }
  }

  int num_node_;
  std::vector<int> dis_;
  std::vector<bool> inq_;
  std::vector<int> path_;
  std::vector<std::vector<Edge>> edges_;
};

#endif
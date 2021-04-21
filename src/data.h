#ifndef DATA_H
#define DATA_H

#include <algorithm>
#include <chrono>
#include <cstdlib>
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

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

const std::string data_dir = "../data/";

struct MFP {
  int num_node;
  int num_edge;
  int source;
  int sink;
  std::vector<std::pair<int, int>> edges;
  std::vector<int> capacities;

  MFP() { }

  MFP(int a, const std::vector<std::pair<int, int>> &b, 
      const std::vector<int> &c, int d, int e) : num_node(a), 
      num_edge(b.size()), source(d), sink(e) {
    edges.reserve(b.size());
    edges.insert(edges.end(), b.begin(), b.end());
    capacities.reserve(c.size());
    capacities.insert(capacities.end(), c.begin(), c.end());
  }

  void ShowInfo() {
    std::cout << std::string(20, '#') << " Test Case " << std::string(20, '#') 
              << std::endl;
    std::cout << "# of Nodes\t" << num_node << std::endl;
    std::cout << "# of Edges\t" << num_edge << std::endl;
    std::cout << "Source (" << source << ") -> Sink (" 
              << sink << ")" << std::endl;
    int max_capacity = capacities[0];
    int min_capacity = capacities[0];
    for (int i = 0; i < capacities.size(); ++ i) {
      min_capacity = std::min(min_capacity, capacities[i]);
      max_capacity = std::max(max_capacity, capacities[i]);
    }
    std::cout << "Max Capacity\t" << max_capacity << std::endl;
    std::cout << "Min Capacity\t" << min_capacity << std::endl;
    std::cout << std::string(51, '#') << std::endl;
  }
};

template<typename T>
std::string STR(T n) {
  std::stringstream ss;
  ss << std::fixed << n;
  return ss.str();
}

MFP GenerateMFP(int min_num_node, int max_num_node, double edge_ratio, 
                    int max_capacity) {
  std::mt19937_64 gen(std::random_device{}());
  int num_node = std::abs(static_cast<long long>(gen())) 
                  % (max_num_node - min_num_node) + min_num_node;
  int num_edge = int(num_node * num_node * edge_ratio);
  std::vector<std::pair<int, int>> edges;
  std::vector<int> capacities;
  std::vector<int> node_idx;
  std::vector<int> edge_idx;
  edges.reserve(num_edge);
  capacities.reserve(num_edge);
  node_idx.reserve(num_node);
  edge_idx.reserve(num_node * num_node);
  for (int i = 0; i < num_node; ++ i) {
    node_idx.push_back(i);
  }
  for (int i = 0; i < num_node * num_node; ++ i) {
    edge_idx.push_back(i);
  }
  // Shuffle the index
  for (int i = 0; i < num_node; ++ i) {
    int j = std::abs(static_cast<long long>(gen())) % (num_node - i) + i;
    std::swap(node_idx[i], node_idx[j]);
  }
  for (int i = 0; i < num_node * num_node; ++ i) {
    int j = std::abs(static_cast<long long>(gen())) 
            % (num_node * num_node - i) + i;
    std::swap(edge_idx[i], edge_idx[j]);
  }
  int source = node_idx[0];
  int sink = node_idx[1];
  for (int i = 0; i < num_edge; ++ i) {
    int capacity = std::abs(static_cast<long long>(gen())) % max_capacity + 1;
    int u = edge_idx[i] / num_node;
    int v = edge_idx[i] % num_node;
    edges.push_back({u, v});
    capacities.push_back(capacity);
  }
  return MFP(num_node, edges, capacities, source, sink);
}

void WriteData(const MFP &mfp) {
  std::string data_name = std::string("testcase_") + STR<int>(mfp.num_node) + 
                          "_" + STR<int>(mfp.num_node) + ".in";
  std::ofstream out((data_dir + data_name).c_str(), std::ios::out);
  if (!out.is_open()) {
    std::cout << "File " << data_dir + data_name << " does not exist" 
              << std::endl;
    exit(-1);
  }
  out << mfp.num_node << "\t" << mfp.num_edge << "\t" << mfp.source << "\t" 
      << mfp.sink << std::endl;
  for (int i = 0; i < mfp.edges.size(); ++ i) {
    out << mfp.edges[i].first << "\t" << mfp.edges[i].second << "\t" 
        << mfp.capacities[i] << std::endl;
  }
  out.close();
}

void ReadData(std::string path, MFP &mfp) {
  std::ifstream in((data_dir + path).c_str(), std::ios::in);
  if (!in.is_open()) {
    std::cout << "File " << data_dir + path << " does not exist" << std::endl;
    exit(-1);
  }
  in >> mfp.num_node >> mfp.num_edge >> mfp.source >> mfp.sink;
  mfp.edges.reserve(mfp.num_edge);
  mfp.capacities.reserve(mfp.num_edge);
  for (int i = 0; i < mfp.num_edge; ++ i) {
    int u, v;
    int capacity;
    in >> u >> v >> capacity;
    mfp.edges.push_back({u, v});
    mfp.capacities.push_back(capacity);
  }
  in.close();
}

#endif
#include "data.h"
#include "max_flow_net.h"
#include "ortools/graph/max_flow.h"

using namespace operations_research;

void LoadTestCases(std::vector<MFP> &mfps) {
  struct stat s;
  lstat(data_dir.c_str(), &s);
  if (!S_ISDIR(s.st_mode)) {
    std::cout << "The directory named " << data_dir << " does not exist" 
              << std::endl;
    exit(-1);
  }
  struct dirent *filename;
  DIR *dir = opendir(data_dir.c_str());
  if (dir == nullptr) {
    std::cout << "Cannot open " << data_dir << std::endl;
    exit(-1);
  }
  while ((filename = readdir(dir)) != nullptr) {
    if (strcmp(filename->d_name, ".") == 0 || 
        strcmp(filename->d_name, "..") == 0) {
      continue;
    }
    std::string path = std::string(filename->d_name);
    if (path.find("testcase_") != std::string::npos) {
      mfps.emplace_back();
      ReadData(path, mfps[mfps.size() - 1]);
    }
  }
}

void TestEK(const MFP &mfp) {
  auto start_time = std::chrono::high_resolution_clock::now();
  FlowNet fn(mfp.num_node);
  for (int i = 0; i < mfp.num_edge; ++ i) {
    fn.AddEdge(mfp.edges[i].first, mfp.edges[i].second, mfp.capacities[i]);
  }
  int max_flow_ek = fn.MaxFlow(mfp.source, mfp.sink);
  auto end_time = std::chrono::high_resolution_clock::now();
  double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    end_time - start_time).count();
  std::cout << std::fixed << "Use EK\tMax Flow\t" << max_flow_ek 
            << "\tTime\t" << duration << std::endl;  
}

void TestLPSolver(const MFP &mfp) {
  std::vector<std::pair<std::pair<NodeIndex, NodeIndex>, FlowQuantity> > arcs;
  arcs.reserve(mfp.num_edge);
  for (int i = 0; i < mfp.num_edge; ++ i) {
    arcs.push_back({{mfp.edges[i].first, mfp.edges[i].second}, mfp.capacities[i]});
  }
  auto start_time = std::chrono::high_resolution_clock::now();
  StarGraph graph(mfp.num_node, arcs.size());
  MaxFlow max_flow(&graph, mfp.source, mfp.sink);
  for (const auto& it : arcs) {
    ArcIndex arc = graph.AddArc(it.first.first, it.first.second);
    max_flow.SetArcCapacity(arc, it.second);
  }
  max_flow.Solve();
  assert(MaxFlow::OPTIMAL == max_flow.status());
  FlowQuantity max_flow_cvx = max_flow.GetOptimalFlow();
  auto end_time = std::chrono::high_resolution_clock::now();
  double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    end_time - start_time).count();
  std::cout << std::fixed << "Use CVX\tMax Flow\t" << max_flow_cvx 
            << "\tTime\t" << duration << std::endl;  
}

int main() {
  std::vector<MFP> mfps;
  LoadTestCases(mfps);
  for (int i = 0; i < mfps.size(); ++ i) {
    mfps[i].ShowInfo();
    TestEK(mfps[i]);
    TestLPSolver(mfps[i]);
  }
  return 0;
}
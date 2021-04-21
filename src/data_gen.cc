#include "data.h"

struct Config {
  int min_num_node;
  int max_num_node;
  double edge_ratio;
  int max_capacity;

  Config(int a, int b, double c, int d) : min_num_node(a), max_num_node(b), 
          edge_ratio(c), max_capacity(d) { }
};

std::vector<Config> LoadConfig(std::string path) {
  std::ifstream in(path.c_str(), std::ios::in);
  if (!in.is_open()) {
    std::cout << "File " << path << " does not exist" << std::endl;
    exit(-1);
  }
  std::vector<Config> configs;
  while (!in.eof()) {
    int min_num_node;
    int max_num_node;
    double edge_ratio;
    int max_capacity;
    in >> min_num_node >> max_num_node >> edge_ratio >> max_capacity;
    configs.emplace_back(min_num_node, max_num_node, edge_ratio, max_capacity);
  }
  in.close();
  return configs;
}

void GenData(std::string path) {
  std::vector<Config> configs = LoadConfig(path);
  for (int i = 0; i < configs.size(); ++ i) {
    Config c = configs[i];
    MFP mfp = GenerateMFP(c.min_num_node, c.max_num_node, c.edge_ratio, 
                          c.max_capacity);
    WriteData(mfp);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./gen config_file" << std::endl;
    exit(-1);
  }
  GenData(argv[1]);
  return 0;
}
#include "TSP.hpp"
#include "Time.hpp"
#include <iostream>

int main() {
  std::string filename = "ja9847.tsp";
  std::list<Node> cities = TSP::constructCities(filename);
  auto result = Time::timeAndExecute<TSP::Tour, std::list<Node>, size_t>(TSP::nearestNeighbor, cities, 1022);
  result.display();
  // result.summarize();
  return 0;
}
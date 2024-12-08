#include "TSP.hpp"

/**
 * Displays the edges and total distance of the tour.
 * Each edge is printed in the format: "EDGE start_id -> end_id | WEIGHT: weight".
 */
void TSP::Tour::display() const {
  for (size_t i = 1; i < path.size(); i++) {
    std::cout << "EDGE " << path[i-1].id << " -> " << path[i].id << " | WEIGHT : " << weights[i] << std::endl;
  }
  std::cout << "TOTAL DISTANCE: " << total_distance << std::endl;
}

/**
 * Reads a .tsp file and constructs a list of cities as nodes.
 * The file should have a section labeled "NODE_COORD_SECTION" followed by lines with the format: ID x-coordinate y-coordinate.
 * 
 * @param filename The path to the TSP file.
 * @return A list of `Node` objects representing cities and their coordinates.
 * @throws std::runtime_error If the file cannot be read or parsed.
 * 
 * @pre The file specified by `filename` exists and follows the TSP format.
 */
std::list<Node> TSP::constructCities(const std::string& filename) {
  // Read past metadata
  std::ifstream fin(filename);
  if (fin.fail()) {
    std::cerr << "ERROR: Could not read file: " << filename << std::endl;
    throw std::runtime_error("Failed to read file. Terminating.");
  }

  std::string line;
  do { std::getline(fin, line); }
  while (line.find("NODE_COORD_SECTION"));

  // Read data from file into Node list "cities"
  std::list<Node> cities;
  size_t ID;
  double x, y;
  while (!fin.eof()){
    if (!(fin >> ID >> x >> y)) break;
    cities.push_back(Node(ID, x, y));
  }
  return cities;
}
// struct edge{
//   Node city1;
//   Node city2;
//   int DistanceBetweenCities;

//   edge(Node first, Node second,int weight):city1{first},city2{second},DistanceBetweenCities{weight}{};

// };


Node& TSP::findCityBasedOnID(size_t start_id,std::list<Node> &cities){
  for(auto &x:cities){
    if(x.id == start_id){
      return x;
    }
  }
  return *new Node(1,1,1);
}

TSP::Tour TSP::nearestNeighbor(std::list<Node> cities, const size_t& start_id){
  //Return Value
  TSP::Tour returnTour = TSP::Tour();

  std::unordered_set<size_t> vistedCities;
  Node Currentcity = TSP::findCityBasedOnID(start_id,cities);
  vistedCities.insert(Currentcity.id);

  while(vistedCities.size() != cities.size()){
    size_t min = std::numeric_limits<size_t>::max();
    size_t nextcity = -1;
    for(auto &x : cities){
      if(vistedCities.find(x.id) != vistedCities.end()){
        continue;
      }
      else{
        if(x.distance(Currentcity) < min){
          min = x.distance(Currentcity);
          nextcity = x.id;
        }
      }
    }
    returnTour.path.push_back(TSP::findCityBasedOnID(nextcity,cities));
    returnTour.weights.push_back(min);
    returnTour.total_distance += min;
    vistedCities.insert(nextcity);
    Currentcity = TSP::findCityBasedOnID(nextcity,cities);
  }
  returnTour.path.push_back(TSP::findCityBasedOnID(start_id,cities));
  returnTour.weights.push_back(0);
  return returnTour;
}
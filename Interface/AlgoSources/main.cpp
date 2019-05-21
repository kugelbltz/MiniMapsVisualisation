#include <iostream>
#include <stdio.h>
#include <list>
#include <iterator>
#include <tuple>
#include <vector>
#include <map>
#include <climits>
#include <fstream>
#include <cmath>
#include <ctime>
#include <sstream>
#include <chrono>


#include "Position.h"
#include "Label.h"
#include "Cost.h"
#include "Graph.h"
#include "functions.h"
#include "Json.h"


using namespace std;

int main(int argc, char* argv[]){

  long long start_node, end_node;

  double start_time;

  string graph_file("data/graphWalk_c.cr");
  string nodes_file("data/nodes_c.co");
  string in_file("data/userInput.json");
  string out_file("data/output.json");

  ofstream o_file;
  o_file.open(out_file);

  Graph myGraph;
  map<long long,Position> nodes;

  init_graph_complete(myGraph, nodes, graph_file, nodes_file);

  get_start_end(in_file, start_node, end_node, start_time);

  Network myNetwork("data/transports0.txt", "data/pathways.txt");

//  calculate_footpaths(myNetwork.stops, myGraph, nodes, "data/footpaths.txt");


  string result = fusion(myGraph, nodes, myNetwork, start_node, end_node, start_time);
  o_file << result << endl;
  o_file.close();

  return 0;
}

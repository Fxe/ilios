#ifndef ILIOS_KITTENS_RESOURCES_HPP_
#define ILIOS_KITTENS_RESOURCES_HPP_

#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include "core.hpp"

using namespace std;

namespace ilios { namespace kittens {



class Resource {

public:
  string id;
  double amount;
  double baseTick;
  double tick;
  double max;
  double baseMax;
  double update();
};

class ResourceManager {
public:
  ResourceManager();
  ~ResourceManager();
  map<string, Resource*> resources;
  void registerResource(const string id, const double tick, const double amount, const double max);
  void printResources();
  void update();
  ResourceMap getDeficitResources(ResourceMap resources);
  bool hasResources(ResourceMap resources);
  void addResources(ResourceMap resources);
  void removeResources(ResourceMap resources);
  void pickCatnip();
  void craft(string resource);
};



}; };

#endif // ILIOS_KITTENS_RESOURCES_HPP
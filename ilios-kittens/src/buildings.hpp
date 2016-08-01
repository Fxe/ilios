#ifndef ILIOS_KITTENS_BUIDINGS_HPP_
#define ILIOS_KITTENS_BUIDINGS_HPP_


#include <cstdlib>
#include <string>
#include <map>
#include "core.hpp"
#include "resources.hpp"

using namespace std;



namespace ilios { namespace kittens {



class Building {

public:
  string id;
  double ratio;
  int val;
  ResourceMap base;
  EffectMap effect;
  //double tick;
  //double max;
  //double update();
};

class BuildingManager {
public:
  ~BuildingManager();
  map<string, Building*> buildings;
  void addBuilding(const string id, const double ratio, ResourceMap base, EffectMap effect);
  ResourceMap getPrice(const string id);
  void build(const string id);
  Building* getBuilding(const string id);
  //void printResources();
  //void update();
};



}; };

#endif // ILIOS_KITTENS_BUIDINGS_HPP_
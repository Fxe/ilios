#include "resources.hpp"
#include "buildings.hpp"
#include <iostream>

using namespace ilios::kittens;

BuildingManager::~BuildingManager()
{
  cout << "terminate ilios::kittens::BuildingManager" << endl;
}

void BuildingManager::addBuilding(const string id, const double ratio, ResourceMap base, EffectMap effect)
{
  Building* building = new Building();
  building->id = id;
  building->ratio = ratio;
  building->val = 0;
  for (auto p : base)
  {
    building->base[p.first] = p.second;
  }
  for (auto p : effect)
  {
    building->effect[p.first] = p.second;
  }
  this->buildings.insert(pair<string, Building*> (id, building));
}

ResourceMap BuildingManager::getPrice(const string id)
{
  double ratio = this->buildings[id]->ratio;
  int val = this->buildings[id]->val;
  ResourceMap base = this->buildings[id]->base;
  ResourceMap price;
  //cout << "ratio " << ratio << endl;
  for (auto e : base)
  {
    price[e.first] = e.second * pow(ratio, val);
  }
  return price;
}

void BuildingManager::build(const string id)
{
  this->buildings[id]->val++;
}

Building* BuildingManager::getBuilding(const string id)
{
  return this->buildings[id];
}

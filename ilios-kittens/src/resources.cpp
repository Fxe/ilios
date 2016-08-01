#include "resources.hpp"
#include <iostream>

using namespace ilios::kittens;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
  cout << "termine ilios::kittens::ResourceManager" << endl;
}

double Resource::update() {
  this->amount += this->tick;
  double extra = this->max - this->amount;
  if (extra > 0)
  {
    extra = 0;
  }
  this->amount += extra;
  
  return extra;
}



void ResourceManager::registerResource(const string id, const double tick, const double amount, const double max)
{
  Resource* resource = new Resource();
  resource->id = id;
  resource->tick = tick;
  resource->baseTick = tick;
  resource->amount = amount;
  resource->max = max;
  resource->baseMax = max;
  this->resources.insert(pair<string, Resource*>(id, resource));
}

void ResourceManager::printResources()
{
  
  for (auto e : this->resources)
  {
    Resource* resources = e.second;
    double v = resources->amount;
    if (v != 0)
    {
      cout << resources->id << " " << resources->amount << "/" << resources->max << " +" << resources->tick << endl;
    }
  }
  
}

void ResourceManager::update()
{
  for (auto e : this->resources)
  {
    e.second->update();
  }
}

ResourceMap ResourceManager::getDeficitResources(ResourceMap resources)
{
  ResourceMap deficit;
  for (auto e : resources)
  {
    string id = e.first;
    double need = e.second;
    double have = this->resources[id]->amount;
    if (have < need)
    {
      deficit[id] = need - have;
    }
  }
  return deficit;
}

bool ResourceManager::hasResources(ResourceMap resources)
{
  ResourceMap deficit = this->getDeficitResources(resources);

  return deficit.empty();
}

void ResourceManager::addResources(ResourceMap resources)
{
  for (auto e : resources)
  {
    string id = e.first;
    double val = e.second;
    this->resources[id]->amount += val;
  }
}

void ResourceManager::removeResources(ResourceMap resources)
{
  for (auto e : resources)
  {
    string id = e.first;
    double val = e.second;
    this->resources[id]->amount -= val;
  }
}

void ResourceManager::pickCatnip()
{
  this->resources["catnip"]->amount++;
}

void ResourceManager::craft(string resource)
{
  ResourceMap price;
  price["catnip"] = 100;
  ResourceMap product;
  product["wood"] = 1;
  ResourceMap deficit = this->getDeficitResources(price);
  if (deficit.empty())
  {
    this->removeResources(price);
    this->addResources(product);
  }
}

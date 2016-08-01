#include "game.hpp"
#include <iostream>

using namespace ilios::kittens;

Game::Game()
{
  ResourceManager* res = new ResourceManager();
  BuildingManager* bld = new BuildingManager();
  VillageManager*  vlg = new VillageManager();
  this->res = res;
  this->bld = bld;
  this->vlg = vlg;

}

Game::~Game()
{
  cout << "termine ilios::kittens::Game" << endl;
}



double Game::getResourceTick(string resource)
{
  double totalTick = this->res->resources[resource]->baseTick;
  for (auto e : this->bld->buildings)
  {
    //get tick
    Building* building = e.second;
    int val = building->val;
    double tick = building->effect["tick"][resource];
    //cout << e.first << " tick contrib: " << tick << endl;
    totalTick += tick * val;
  }
  for (auto e : this->vlg->working)
  {
    //get tick
    Job* job = this->vlg->jobs[e.first];
    int val = e.second;
    double tick = job->effect["tick"][resource];
    //cout << e.first << " tick contrib: " << tick << endl;
    totalTick += tick * val;
  }

  return totalTick;
}

double Game::getResourceMax(string resource)
{
  double baseMax = this->res->resources[resource]->baseMax;
  for (auto e : this->bld->buildings)
  {
    //get tick
    Building* building = e.second;
    int val = building->val;
    double max = building->effect["max"][resource];
    baseMax += max * val;
  }

  return baseMax;
}

void Game::updateResources()
{
  cout << "START Game::updateResources" << endl;
  for (auto e : this->res->resources)
  {
    string id = e.first;
    double tickValue = this->getResourceTick(id);
    double maxValue = this->getResourceMax(id);
    this->res->resources[id]->tick = tickValue;
    this->res->resources[id]->max = maxValue;
    //cout << id << " tick: " << tickValue << " max: " << maxValue << endl;
  }
  cout << "DONE Game::updateResources" << endl;
  //get tick
  
  //this->bld->getPrice("");
  //add resources
}

void Game::update()
{
  double baseKittensTick = 0.01;
  //updates resource tick value
  //this->updateResources();
  //update resources
  this->res->update();
  //consume
  //catnipPerKitten = -0.85
  //catnip = catnipPerKitten * kittens
  //furs = -0.01 * kittens
  //ivory = -0.007 * kittens
  //spice = -0.001 * kittens
  double catnipPerKitten = -0.85;
  ResourceMap consume;
  
  double kittens = floor(this->res->resources["kittens"]->amount);
  consume["catnip"] = catnipPerKitten * kittens;
  consume["furs"]  = -0.010 * kittens;
  consume["ivory"] = -0.007 * kittens;
  consume["spice"] = -0.001 * kittens;

  this->res->addResources(consume);
  double catnipAmount = this->res->resources["catnip"]->amount;
  //kill 1 kitten if negative catnip
  if (catnipAmount < 0.0)
  {
    cout << "1 kitten killed" << endl;
    this->res->resources["kittens"]->amount--;
    this->res->resources["catnip"]->amount = 0.0;
  }
}

void ilios::kittens::Game::build(string id)
{
  //get price
  ResourceMap price = this->bld->getPrice(id);
  //check resources
  ResourceMap deficit = this->res->getDeficitResources(price);
  if (deficit.empty())
  {
    cout << "built " << id << " cost:" << endl;
    /*
    
    for (auto e : price)
    {
      cout << e.first << ": " << e.second << endl;
    }
    */
    //remove and build
    this->res->removeResources(price);
    this->bld->build(id);
    //action taken update effect
    this->updateResources();
  }
  else
  {
    //warn
    /*
    cout << "missing resources" << endl;
    for (auto e : deficit)
    {
      cout << e.first << ": " << e.second << endl;
    }
    */
  }
}

void Game::assignJob(string jobId)
{
  //get total kittens
  double totalKittens = floor(this->res->resources["kittens"]->amount);
  
  int totalWorking = this->vlg->getWorkingKittens();
  
  if (totalKittens > totalWorking)
  {
    //cout << "work " << jobId << endl;
    this->vlg->addJob(jobId);
    //update resources
    this->updateResources();
  }

  //cout << "Jobs: " << totalWorking << "/" << totalKittens << endl;
}

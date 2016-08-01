#include <iostream>
#include "village.hpp"

using namespace std;
using namespace ilios::kittens;

VillageManager::VillageManager()
{
}

VillageManager::~VillageManager()
{
  cout << "termine ilios::kittens::Village" << endl;
}

void VillageManager::registerJob(const string id, bool unlocked, EffectMap effect)
{
  Job* job = new Job();
  job->id = id;
  job->unlocked = unlocked;
  job->effect = effect;
  this->jobs[id] = job;
  this->working[id] = 0;
}

int VillageManager::getWorkingKittens()
{
  int total = 0;
  for (auto e : this->working)
  {
    total += e.second;
  }

  return total;
}

void VillageManager::addJob(const string jobId)
{
  this->working[jobId]++;
}

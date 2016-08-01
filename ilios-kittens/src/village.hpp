#ifndef ILIOS_KITTENS_VILLAGE_HPP_
#define ILIOS_KITTENS_VILLAGE_HPP_

#include "core.hpp"

using namespace std;

namespace ilios {
namespace kittens {

class Job {
public:
  string id;
  bool unlocked;
  EffectMap effect;
};

class VillageManager {
public:
  map<string, Job*> jobs;
  map<string, int> working;
  VillageManager();
  ~VillageManager();
  void registerJob(const string id, bool unlocked, EffectMap effect);
  void addJob(const string jobId);
  int VillageManager::getWorkingKittens();

};

};
};

#endif
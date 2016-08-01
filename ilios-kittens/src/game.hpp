#ifndef ILIOS_KITTENS_GAME_HPP_
#define ILIOS_KITTENS_GAME_HPP_

#include "resources.hpp"
#include "buildings.hpp"
#include "village.hpp"


namespace ilios { namespace kittens {

class Game
{
public:
  Game();
  ~Game();

  double getResourceTick(string resource);
  double getResourceMax(string resource);
  
  void updateResources();
  void update();
  void build(string id);
  ResourceManager* res;
  BuildingManager* bld;
  VillageManager*  vlg;

  void assignJob(string jobId);

private:

}; //CLASS GAME

};
};

#endif // ILIOS_KITTENS_GAME_HPP_
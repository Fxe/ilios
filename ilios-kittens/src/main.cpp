#include <iostream>
#include <fstream>
#include "buildings.hpp"
#include "village.hpp"
#include "game.hpp"
#include <json\json.h>


ilios::kittens::Game* loadData(const string filename)
{
  std::ifstream config_doc(filename, std::ifstream::binary);
  Json::Value base;
  config_doc >> base;

  ilios::kittens::Game* game = new ilios::kittens::Game();
  
  Json::Value kittensResources = base["resources"];
  for (auto resId : kittensResources.getMemberNames())
  {
    Json::Value resData = kittensResources[resId];
    double tick = resData.get("tick", 0.0).asDouble();
    double amount = resData.get("amount", 0.0).asDouble();
    double max = resData.get("max", 0.0).asDouble();
    cout << "loaded: " << resId << " base tick: " << tick << " " << amount << " " << max << endl;
    game->res->registerResource(resId, tick, amount, max);
  }
  Json::Value kittensBuildings = base["buildings"];
  for (auto bldId : kittensBuildings.getMemberNames())
  {
    Json::Value bldData = kittensBuildings[bldId];
    double ratio = bldData.get("ratio", 2.0).asDouble();
    Json::Value priceJson = bldData["price"];
    Json::Value effectJson = bldData["effect"];
    ilios::kittens::ResourceMap price;
    ilios::kittens::EffectMap effect;
    cout << "loaded: " << bldId << " ratio: " << ratio << endl;
    for (auto resId : priceJson.getMemberNames())
    {
      double value = priceJson.get(resId, 10000000.0).asDouble();
      price[resId] = value;
      cout << resId << ": " << value << endl;
    }
    for (auto type : effectJson.getMemberNames())
    {
      Json::Value etypeJson = effectJson[type];
      for (auto e : etypeJson.getMemberNames())
      {
        double value = etypeJson.get(e, 0.0).asDouble();
        effect[type][e] = value;
        cout << type << " -> " << e << ": " << value << endl;
      }
    }
    game->bld->addBuilding(bldId, ratio, price, effect);
  }

  config_doc.close();

  return game;
}

int main()
{
  ilios::kittens::Game* game = loadData("D:/kittens.json");
  /*
  ilios::kittens::Game* game = new ilios::kittens::Game();
  game->res->registerResource("catnip", 0, 0, 5000);
  game->res->registerResource("wood", 0, 0, 200);
  game->res->registerResource("minerals", 0, 0, 250);
  game->res->registerResource("culture", 0, 0, 100);
  game->res->registerResource("faith", 0, 0, 100);
  game->res->registerResource("manpower", 0, 0, 100);
  game->res->registerResource("uranium", 0, 0, 250);
  game->res->registerResource("kittens", 0.01, 0, 1);
  game->res->registerResource("furs", 0, 0, 0);
  game->res->registerResource("ivory", 0, 0, 0);
  game->res->registerResource("spice", 0, 0, 0);
  game->res->registerResource("science", 0, 0, 1000); */
  /*
  ilios::kittens::ResourceMap fieldBase;
  ilios::kittens::EffectMap fieldEffect;
  fieldBase["catnip"] = 10;
  fieldEffect["tick"]["catnip"] = 0.125;
  game->bld->addBuilding("field", 1.12, fieldBase, fieldEffect);
  ilios::kittens::ResourceMap hutBase;
  ilios::kittens::EffectMap hutEffect;
  hutBase["wood"] = 5;
  hutEffect["max"]["kittens"] = 2;
  game->bld->addBuilding("hut", 2.5, hutBase, hutEffect);
  ilios::kittens::ResourceMap barnBase;
  ilios::kittens::EffectMap barnEffect;
  barnBase["wood"] = 50;
  barnEffect["max"]["catnip"] = 5000;
  barnEffect["max"]["coal"] = 60;
  barnEffect["max"]["gold"] = 10;
  barnEffect["max"]["iron"] = 50;
  barnEffect["max"]["minerals"] = 250;
  barnEffect["max"]["titanium"] = 2;
  barnEffect["max"]["wood"] = 200;
  
  
  game->bld->addBuilding("barn", 1.75, barnBase, barnEffect);
  */

  ilios::kittens::EffectMap woodcutterEffect;
  woodcutterEffect["tick"]["wood"] = 0.015;
  ilios::kittens::EffectMap farmerEffect;
  farmerEffect["tick"]["catnip"] = 100;
  ilios::kittens::EffectMap scholarEffect;
  scholarEffect["tick"]["science"] = 0.05;
  game->vlg->registerJob("woodcutter", true, woodcutterEffect);
  game->vlg->registerJob("farmer", true, farmerEffect);
  game->vlg->registerJob("scholar", true, scholarEffect);

  game->res->pickCatnip();
  game->res->pickCatnip();
  game->res->pickCatnip();
  game->res->pickCatnip();
  game->res->pickCatnip();
  game->res->pickCatnip();
  game->res->pickCatnip();
  game->res->pickCatnip();
  game->res->pickCatnip();
  game->res->pickCatnip();

  for (int i = 0; i < 1000 * 10e0; i++)
  {
    if (!(i % 5000))
    {
      game->res->printResources();

    }
    game->update();
    game->build("field");
    
    game->build("barn");
    game->build("hut");
    double val = game->res->resources["catnip"]->amount;
    double max = game->res->resources["catnip"]->max;
    if (val / max > 0.9)
    {
      game->res->craft("wood");
    }
    if (game->vlg->working["farmer"] > 8)
    {
      game->assignJob("scholar");
    }
    game->assignJob("farmer");
    game->build("library");
  }
  game->res->printResources();
  delete game;

  return 0;
}

#pragma once

#include <vector>

#include "Factory.h"
#include "NPC.h"
#include "Visitor.h"

class NpcManager {
    double mapSize;
    std::vector<std::shared_ptr<NPC>> npcs;

   public:
    NpcManager(double size) : mapSize(size) {}
    void addNPC(const std::string& type, const std::string& name, double x,
                double y);
    void printNPCs() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void startBattle(Visitor& visitor);
    const std::vector<std::shared_ptr<NPC>>& getNPCs() const;
    void moveNpcs();
    void printMap() const;
    double getMapSize() const;
};

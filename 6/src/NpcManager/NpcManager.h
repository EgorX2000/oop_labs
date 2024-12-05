#pragma once

#include <vector>

#include "Factory.h"
#include "NPC.h"
#include "Visitor.h"

class NpcManager {
    std::vector<std::shared_ptr<NPC>> npcs;

   public:
    void addNPC(const std::string& type, const std::string& name, double x,
                double y);
    void printNPCs() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void startBattle(double range, Visitor& visitor);
    const std::vector<std::shared_ptr<NPC>>& getNPCs() const;
};

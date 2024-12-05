#include "NpcManager.h"

#include <fstream>
#include <iostream>

void NpcManager::addNPC(const std::string& type, const std::string& name,
                        double x, double y) {
    npcs.push_back(Factory::createNPC(type, name, x, y));
}

void NpcManager::printNPCs() const {
    for (const auto& npc : npcs) {
        std::cout << npc->getType() << " " << npc->getName() << " ("
                  << npc->getX() << ", " << npc->getY() << ")\n";
    }
}

void NpcManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    for (const auto& npc : npcs) {
        outFile << npc->getType() << " " << npc->getName() << " " << npc->getX()
                << " " << npc->getY() << "\n";
    }
}

void NpcManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    std::string type, name;
    double x, y;
    while (inFile >> type >> name >> x >> y) {
        addNPC(type, name, x, y);
    }
}

void NpcManager::startBattle(double range, Visitor& visitor) {
    visitor.fight(npcs);
}

const std::vector<std::shared_ptr<NPC>>& NpcManager::getNPCs() const {
    return npcs;
}

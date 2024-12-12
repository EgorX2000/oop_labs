#include "NpcManager.h"

#include <fstream>
#include <iostream>

void NpcManager::addNPC(const std::string& type, const std::string& name,
                        double x, double y) {
    npcs.push_back(Factory::createNPC(type, name, x, y));
}

void NpcManager::printNPCs() const {
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            std::cout << npc->getType() << " " << npc->getName() << " ("
                      << npc->getX() << ", " << npc->getY() << ")\n";
        }
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

void NpcManager::startBattle(Visitor& visitor) { visitor.fight(npcs); }

const std::vector<std::shared_ptr<NPC>>& NpcManager::getNPCs() const {
    return npcs;
}

void NpcManager::moveNpcs() {
    for (auto npc : npcs) {
        npc->move();
    }
}
void NpcManager::printMap() const {
    int xSize = int(mapSize);
    int ySize = int(mapSize);

    for (int i = 0; i <= xSize + 2; ++i) {
        std::cout << '-';
    }
    std::cout << '\n';

    for (int i = 0; i <= ySize; ++i) {
        std::cout << '|';
        for (int j = 0; j <= xSize; ++j) {
            bool printed = false;
            for (auto npc : npcs) {
                if (!npc->isAlive()) continue;

                printed = true;
                if ((int)npc->getX() == j && (int)npc->getY() == i) {
                    if (npc->getType() == "Squirrel") {
                        std::cout << '^';
                        break;
                    } else if (npc->getType() == "Werewolf") {
                        std::cout << '*';
                        break;
                    } else if (npc->getType() == "Druid") {
                        std::cout << '@';
                        break;
                    }
                } else {
                    printed = false;
                }
            }
            if (!printed) {
                std::cout << ' ';
            }
        }
        std::cout << '|';
        std::cout << '\n';
    }

    for (int i = 0; i <= xSize + 2; ++i) {
        std::cout << '-';
    }
    std::cout << '\n';
}
double NpcManager::getMapSize() const { return mapSize; }

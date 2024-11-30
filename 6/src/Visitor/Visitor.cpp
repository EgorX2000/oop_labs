#include "Visitor.h"

Visitor::Visitor(double range) : fightRange(range) {}

void Visitor::addObserver(EventObserver* observer) {
    observers.push_back(observer);
}

void Visitor::fightResults(const std::string& event) {
    for (auto observer : observers) {
        observer->handleEvent(event);
    }
}

void Visitor::fight(std::vector<std::shared_ptr<NPC>>& npcs) {
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size();) {
            double distance =
                std::sqrt(std::pow(npcs[i]->getX() - npcs[j]->getX(), 2) +
                          std::pow(npcs[i]->getY() - npcs[j]->getY(), 2));

            if (distance <= fightRange) {
                bool iKillsJ = npcs[i]->kills(*npcs[j]);
                bool jKillsI = npcs[j]->kills(*npcs[i]);

                if (iKillsJ && jKillsI) {
                    fightResults(npcs[i]->getName() + " и " +
                                 npcs[j]->getName() + " убивают друг друга!");
                    npcs.erase(npcs.begin() + j);
                    npcs.erase(npcs.begin() + i);
                    if (i > 0) --i;  // корректируем индекс
                    break;
                } else if (iKillsJ) {
                    fightResults(npcs[i]->getName() + " убивает " +
                                 npcs[j]->getName());
                    npcs.erase(npcs.begin() + j);
                } else if (jKillsI) {
                    fightResults(npcs[j]->getName() + " убивает " +
                                 npcs[i]->getName());
                    npcs.erase(npcs.begin() + i);
                    if (i > 0) --i;  // корректируем индекс
                    break;
                } else {
                    ++j;
                }
            } else {
                ++j;
            }
        }
    }
}

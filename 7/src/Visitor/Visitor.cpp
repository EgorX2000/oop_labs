#include "Visitor.h"

void Visitor::addObserver(EventObserver* observer) {
    observers.push_back(observer);
}

void Visitor::fightResults(const std::string& event) {
    for (auto observer : observers) {
        observer->handleEvent(event);
    }
}

void Visitor::fight(std::vector<std::shared_ptr<NPC>>& npcs) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::uniform_int_distribution dist(1, 6);

    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            auto npc1 = npcs[i];
            auto npc2 = npcs[j];

            if (!npc1->isAlive() || !npc2->isAlive()) {
                continue;
            }

            double distance =
                std::sqrt(std::pow(npc1->getX() - npc2->getX(), 2) +
                          std::pow(npc1->getY() - npc2->getY(), 2));

            bool npc1Won = npc1->kills(*npc2) &&
                           distance <= npc1->getKillDistance() &&
                           dist(rng) > dist(rng);
            bool npc2Won = npc2->kills(*npc1) &&
                           distance <= npc2->getKillDistance() &&
                           dist(rng) > dist(rng);

            if (npc1Won && npc2Won) {
                fightResults(npc1->getName() + " и " + npc2->getName() +
                             " убивают друг друга!");
                npc1->defeated();
                npc2->defeated();
            } else if (npc1Won) {
                fightResults(npc1->getName() + " убивает " + npc2->getName());
                npc2->defeated();
            } else if (npc2Won) {
                fightResults(npc2->getName() + " убивает " + npc1->getName());
                npc1->defeated();
            } else {
                continue;
            }
        }
    }
}

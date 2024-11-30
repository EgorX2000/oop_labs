#pragma once

#include <cmath>
#include <vector>

#include "NPC.h"
#include "Observer.h"

class Visitor {
    double fightRange;
    std::vector<EventObserver*> observers;

    void fightResults(const std::string& event);

   public:
    Visitor(double range);
    void addObserver(EventObserver* observer);
    void fight(std::vector<std::shared_ptr<NPC>>& npcs);
};

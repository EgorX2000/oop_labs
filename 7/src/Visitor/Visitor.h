#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>
#include <vector>

#include "NPC.h"
#include "Observer.h"

class Visitor {
    std::vector<EventObserver*> observers;

    void fightResults(const std::string& event);

   public:
    void addObserver(EventObserver* observer);
    void fight(std::vector<std::shared_ptr<NPC>>& npcs);
};

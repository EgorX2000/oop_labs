#include "NPC.h"

NPC::NPC(const std::string& name, double x, double y, double moveDistance,
         double killDistance)
    : name(name),
      x(x),
      y(y),
      moveDistance(moveDistance),
      killDistance(killDistance) {}

const std::string& NPC::getName() const { return name; }
double NPC::getX() const { return x; }
double NPC::getY() const { return y; }

Squirrel::Squirrel(const std::string& name, double x, double y)
    : NPC(name, x, y, 5, 5) {}
std::string Squirrel::getType() const { return "Squirrel"; }
bool Squirrel::kills(const NPC& other) const {
    return other.getType() == "Werewolf" || other.getType() == "Druid";
}

Werewolf::Werewolf(const std::string& name, double x, double y)
    : NPC(name, x, y, 40, 5) {}
std::string Werewolf::getType() const { return "Werewolf"; }
bool Werewolf::kills(const NPC& other) const {
    return other.getType() == "Druid";
}

Druid::Druid(const std::string& name, double x, double y)
    : NPC(name, x, y, 10, 10) {}
std::string Druid::getType() const { return "Druid"; }
bool Druid::kills(const NPC&) const { return false; }

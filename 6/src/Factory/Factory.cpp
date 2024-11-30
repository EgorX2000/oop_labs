#include "Factory.h"

#include <stdexcept>

std::shared_ptr<NPC> Factory::createNPC(const std::string& type,
                                        const std::string& name, double x,
                                        double y) {
    if (type == "Squirrel") {
        return std::make_shared<Squirrel>(name, x, y);
    } else if (type == "Werewolf") {
        return std::make_shared<Werewolf>(name, x, y);
    } else if (type == "Druid") {
        return std::make_shared<Druid>(name, x, y);
    } else {
        throw std::invalid_argument("Unknown NPC type: " + type);
    }
}

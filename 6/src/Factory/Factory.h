#pragma once

#include "NPC.h"

class Factory {
   public:
    static std::shared_ptr<NPC> createNPC(const std::string& type,
                                          const std::string& name, double x,
                                          double y);
};

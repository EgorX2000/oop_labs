#include <gtest/gtest.h>

#include <memory>
#include <sstream>
#include <vector>

#include "Factory.h"
#include "NPC.h"
#include "NpcManager.h"
#include "Observer.h"
#include "Visitor.h"

TEST(NPCTest, CreateAndAccess) {
    double x = 100;
    double y = 120;
    Druid dr("Druid1", x, y);

    EXPECT_EQ(dr.getType(), "Druid");
    EXPECT_EQ(dr.getName(), "Druid1");
    EXPECT_FLOAT_EQ(dr.getX(), 100.0f);
    EXPECT_FLOAT_EQ(dr.getY(), 120.0f);
}

TEST(FightTest, Fight) {
    NpcManager nm;
    Visitor v(50.0);
    ConsoleObserver co;

    nm.addNPC("Squirrel", "Squirrel1", 10, 20);
    nm.addNPC("Werewolf", "Werewolf1", 15, 25);

    EXPECT_NO_THROW(v.addObserver(&co));
    EXPECT_NO_THROW(nm.startBattle(50.0, v));
}

TEST(FileOperationsTest, SaveAndLoadNPCs) {
    NpcManager nm1;

    nm1.addNPC("Squirrel", "Squirrel1", 10, 20);
    nm1.addNPC("Werewolf", "Werewolf1", 15, 25);

    const std::string filename = "npcs.txt";

    nm1.saveToFile(filename);

    NpcManager nm2;

    nm2.loadFromFile(filename);
    auto loaded_npcs =
        *reinterpret_cast<std::vector<std::shared_ptr<NPC>>*>(&nm2);
    ASSERT_EQ(loaded_npcs.size(), 2);
    EXPECT_EQ(loaded_npcs[0]->getType(), "Squirrel");
    EXPECT_EQ(loaded_npcs[0]->getName(), "Squirrel1");
    EXPECT_EQ(loaded_npcs[1]->getType(), "Werewolf");
    EXPECT_EQ(loaded_npcs[1]->getName(), "Werewolf1");
}
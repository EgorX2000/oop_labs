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
    double x = 50;
    double y = 120;
    Druid dr("Druid1", x, y);

    EXPECT_EQ(dr.getType(), "Druid");
    EXPECT_EQ(dr.getName(), "Druid1");
    EXPECT_FLOAT_EQ(dr.getX(), 50.0f);
    EXPECT_FLOAT_EQ(dr.getY(), 120.0f);
}

TEST(FightTest, Fight) {
    NpcManager nm(50.0);
    Visitor v;
    ConsoleObserver co;

    nm.addNPC("Squirrel", "Squirrel1", 10, 20);
    nm.addNPC("Werewolf", "Werewolf1", 15, 25);

    EXPECT_NO_THROW(v.addObserver(&co));
    EXPECT_NO_THROW(nm.startBattle(v));
}

TEST(FileOperationsTest, SaveAndLoadNPCs) {
    NpcManager nm1(50.0);

    nm1.addNPC("Squirrel", "Squirrel1", 10, 20);
    nm1.addNPC("Werewolf", "Werewolf1", 15, 25);

    const std::string filename = "npcs.txt";

    nm1.saveToFile(filename);

    NpcManager nm2(50.0);

    nm2.loadFromFile(filename);
    auto loaded_npcs = nm2.getNPCs();
    ASSERT_EQ(loaded_npcs.size(), 2);
    EXPECT_EQ(loaded_npcs[0]->getType(), "Squirrel");
    EXPECT_EQ(loaded_npcs[0]->getName(), "Squirrel1");
    EXPECT_EQ(loaded_npcs[1]->getType(), "Werewolf");
    EXPECT_EQ(loaded_npcs[1]->getName(), "Werewolf1");
}
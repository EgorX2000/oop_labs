#include "NpcManager.h"
#include "Observer.h"
#include "Visitor.h"

int main() {
    NpcManager manager;
    Visitor visitor(50.0);
    ConsoleObserver consoleObserver;
    FileObserver fileObserver("log.txt");

    visitor.addObserver(&consoleObserver);
    visitor.addObserver(&fileObserver);

    manager.addNPC("Squirrel", "Squirrel1", 10, 20);
    manager.addNPC("Werewolf", "Werewolf1", 15, 25);
    manager.addNPC("Druid", "Druid1", 100, 120);

    std::cout << "NPCs in dungeon:\n";
    manager.printNPCs();

    manager.startBattle(50.0, visitor);

    std::cout << "\nRemaining NPCs:\n";
    manager.printNPCs();

    manager.saveToFile("dungeon.txt");

    return 0;
}

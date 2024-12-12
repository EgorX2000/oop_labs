#include <array>
#include <atomic>
#include <chrono>
#include <mutex>
#include <random>
#include <shared_mutex>
#include <thread>

#include "NpcManager.h"
#include "Observer.h"
#include "Visitor.h"

std::atomic<bool> gameIsRunning{true};
std::shared_mutex npc_mutex;

int main() {
    NpcManager nm(50.0);
    Visitor visitor;
    ConsoleObserver consoleObserver;
    FileObserver fileObserver("log.txt");

    visitor.addObserver(&consoleObserver);
    visitor.addObserver(&fileObserver);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::uniform_real_distribution dist(0.0, nm.getMapSize());

    std::uniform_int_distribution int_dist(0, 2);

    {
        const char* types[] = {"Squirrel", "Werewolf", "Druid"};
        std::array<int, 3> counters = {0, 0, 0};
        for (int i = 0; i < nm.getMapSize() / 3; ++i) {
            int rand = int_dist(rng);
            std::string type = types[rand];

            nm.addNPC(type, type + " " + std::to_string(counters[rand]++),
                      dist(rng), dist(rng));
        }
    }

    std::cout << "Герои:\n";
    std::cout
        << "------------------------------------------------------------------"
        << std::endl;
    {
        std::shared_lock lock(npc_mutex);
        nm.printNPCs();
    }
    std::cout
        << "------------------------------------------------------------------"
        << std::endl;

    std::thread movement_thread([&]() {
        while (gameIsRunning) {
            {
                std::unique_lock lock(npc_mutex);
                nm.moveNpcs();
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    std::thread battle_thread([&]() {
        while (gameIsRunning) {
            {
                std::unique_lock lock(npc_mutex);
                nm.startBattle(visitor);
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    std::thread display_thread([&]() {
        while (gameIsRunning) {
            {
                std::unique_lock lock(npc_mutex);
                nm.printMap();
            }
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(30));
    gameIsRunning = false;

    movement_thread.join();
    battle_thread.join();
    display_thread.join();

    std::cout << "\nВ живых:\n";
    std::cout
        << "------------------------------------------------------------------"
        << std::endl;
    {
        std::shared_lock lock(npc_mutex);
        nm.printMap();
        nm.printNPCs();
    }
    std::cout
        << "------------------------------------------------------------------"
        << std::endl;

    return 0;
}
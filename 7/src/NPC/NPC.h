#pragma once

#include <chrono>
#include <cmath>
#include <memory>
#include <random>
#include <string>

class NPC {
   protected:
    std::string name;
    double x, y;
    bool alive = true;
    double moveDistance;
    double killDistance;

   public:
    NPC(const std::string& name, double x, double y, double moveDistance,
        double killDistance);
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    const std::string& getName() const;
    double getX() const;
    double getY() const;
    double getKillDistance() const { return killDistance; }

    virtual bool kills(const NPC& other) const = 0;

    bool isAlive() const { return alive; }

    void move() {
        unsigned seed =
            std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng(seed);
        std::uniform_real_distribution dist(-M_PI, M_PI);

        double angle = dist(rng);
        x += moveDistance * cos(angle);
        y += moveDistance * sin(angle);
    }

    void defeated() { alive = false; }

    double distanceTo(const NPC& other) const {
        return std::sqrt((x - other.x) * (x - other.x) +
                         (y - other.y) * (y - other.y));
    }
};

class Squirrel : public NPC {
   public:
    Squirrel(const std::string& name, double x, double y);
    std::string getType() const override;
    bool kills(const NPC& other) const override;
};

class Werewolf : public NPC {
   public:
    Werewolf(const std::string& name, double x, double y);
    std::string getType() const override;
    bool kills(const NPC& other) const override;
};

class Druid : public NPC {
   public:
    Druid(const std::string& name, double x, double y);
    std::string getType() const override;
    bool kills(const NPC&) const override;
};

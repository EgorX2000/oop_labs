#pragma once

#include <memory>
#include <string>

// Базовый класс NPC
class NPC {
   protected:
    std::string name;
    double x, y;

   public:
    NPC(const std::string& name, double x, double y);
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    const std::string& getName() const;
    double getX() const;
    double getY() const;

    virtual bool kills(const NPC& other) const = 0;
};

// Классы конкретных NPC
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

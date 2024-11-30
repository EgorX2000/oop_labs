#pragma once

#include <fstream>
#include <iostream>
#include <string>

class EventObserver {
   public:
    virtual void handleEvent(const std::string& event) = 0;
    virtual ~EventObserver() = default;
};

class ConsoleObserver : public EventObserver {
   public:
    void handleEvent(const std::string& event) override;
};

class FileObserver : public EventObserver {
    std::ofstream logFile;

   public:
    FileObserver(const std::string& filename);
    void handleEvent(const std::string& event) override;
    ~FileObserver();
};

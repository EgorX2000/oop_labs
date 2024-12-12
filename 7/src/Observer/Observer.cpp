#include "Observer.h"

void ConsoleObserver::handleEvent(const std::string& event) {
    std::cout << event << std::endl;
}

FileObserver::FileObserver(const std::string& filename) {
    logFile.open(filename, std::ios::app);
    if (!logFile) {
        throw std::runtime_error("Failed to open log file");
    }
}

void FileObserver::handleEvent(const std::string& event) {
    logFile << event << std::endl;
}

FileObserver::~FileObserver() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

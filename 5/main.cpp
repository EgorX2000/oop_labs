#include <iostream>
#include <string>

#include "Allocator.hpp"
#include "UnidirectionalList.hpp"

struct ComplexType {
    int id;
    std::string name;

    ComplexType(int id, std::string name) : id(id), name(std::move(name)) {}
};

std::ostream& operator<<(std::ostream& os, const ComplexType& obj) {
    return os << "{id: " << obj.id << ", name: \"" << obj.name << "\"}";
}

int main() {
    constexpr size_t blockSize = 64;
    constexpr size_t blockCount = 10;

    FixedMemoryResource memoryResource(blockSize, blockCount);
    std::pmr::memory_resource* resource = &memoryResource;

    UnidirectionalList<int> intList(resource);
    intList.push_front(10);
    intList.push_front(20);
    intList.push_front(30);

    std::cout << "Integer List: ";
    for (const auto& value : intList) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    UnidirectionalList<ComplexType> complexList(resource);
    complexList.push_front({1, "Alice"});
    complexList.push_front({2, "Bob"});
    complexList.push_front({3, "Charlie"});

    std::cout << "ComplexType List: \n";
    for (const auto& value : complexList) {
        std::cout << value << "\n";
    }

    return 0;
}

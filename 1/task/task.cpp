#include "task.h"

long eliminate_unset_bits(std::string number) {
    if (number.empty()) {
        return -1;
    }

    long result = 0;

    for (int i = 0; i < number.length(); i++) {
        if (number[i] == '1') {
            if (result >= std::numeric_limits<long>::max() - result + 1) {
                return -1;
            }
            result = result * 2 + 1;
        } else if (number[i] != '0') {
            return -1;
        }
    }

    return result;
}

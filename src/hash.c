#include "../includes/hash.h"

unsigned int simple_hash(unsigned long input) {
    unsigned int hash = INIT_HASH;

    for (int i = 0; i < 8; ++i) {
        hash ^= (input >> (i * 8)) & 0xFF;  // XOR each byte
        hash = (hash << 3) | (hash >> 5);   // Rotate left by 3 bits
    }
    return hash;
}
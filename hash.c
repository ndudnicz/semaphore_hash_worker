#include "hash.h"

unsigned char simple_hash(unsigned long input) {
    unsigned short hash = INIT_HASH;

    for (int i = 0; i < 8; ++i) {
        hash ^= (input >> (i * 8)) & 0xFFFF;  // XOR each byte
        hash = (hash << 3) | (hash >> 5);   // Rotate left by 3 bits
    }
    return hash;
}
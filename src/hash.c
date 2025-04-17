#include "../includes/hash.h"

unsigned int simple_hash_ulong(unsigned long input) {
    unsigned int hash = INIT_HASH;

    for (int i = 0; i < 8; ++i) {
        hash ^= (input >> (i * 8)) & 0xF;  // XOR each byte
        hash = (hash << 3) | (hash >> 5);   // Rotate left by 3 bits
        hash = (hash * 0x5bd1e995) ^ (hash >> 15); // Mix with a prime
    }
    return hash;
}

unsigned short simple_hash_uint(unsigned int input) {
    unsigned short hash = (unsigned short)INIT_HASH;

    for (int i = 0; i < 4; ++i) {
        hash ^= (input >> (i * 4)) & 0xFF;  // XOR each byte
        hash = (hash << 1) | (hash >> 3);
    }
    return hash;
}
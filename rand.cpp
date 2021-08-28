#include "rand.h"
#include <ctime>

std::mt19937 Random::random(time(0));

int Random::Int(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(random);
}

std::string Random::String(int n) {
    char alphabet[MAX] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                               'H', 'I', 'J', 'K', 'L', 'M', 'N',
                               'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                               'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
                               'c', 'd', 'e', 'f', 'g', 'h', 'i',
                               'j', 'k', 'l', 'm', 'n', 'o', 'p',
                               'q', 'r', 's', 't', 'u', 'v', 'w',
                               'x', 'y', 'z', '0', '1', '2', '3',
                               '4', '5', '6', '7', '8', '9' };

    std::string res = "#";
    for (int i = 0; i < n; i++)
        res = res + alphabet[rand() % MAX];

    return res;

    //    return pool[rand() % poolSize];
}

float Random::Float(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(random);
}

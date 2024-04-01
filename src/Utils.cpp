#include "Utils.h"


//Helper method for RandomFloatNumberGeneration
float RandInRange(float start, float end) {
    // Seed the random num generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(start, end);

    // Generate a random float value within range
    return dis(gen);
}
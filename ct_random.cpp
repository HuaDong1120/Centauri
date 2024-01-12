#include "ct_random.h"
#include <cstdlib>
#include <ctime>

void initRandomSeed();
int Centauri::Random::randomInteger(int low, int high)
{
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (double(high) - low+1);
    return int(floor(low+s));
}

double Centauri::Random::randomReal(double low, double high)
{
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double s = d * (high - low );
    return low+s;
}

bool Centauri::Random::randomChance(double p)
{
    initRandomSeed();
    return randomReal(0, 1) < p;
}

void Centauri::Random::setRandomSeed(int seed)
{
    initRandomSeed();
}
void initRandomSeed()
{
    static bool initalized = false;
    if(!initalized)
    {
        srand(int(time(NULL)));
        initalized = true;
    }
}

#include "randomer.hpp"

#include <random>

std::mt19937 G(time(0)); //Seed dengan time(0)

int randomInt(int min, int max) {
	std::uniform_int_distribution<> D(min, max);
    return D(G);
}

double randomDouble(double min, double max) { //random pakai mersenne_twister
	///Note: Tidak error saat min > max
    std::uniform_real_distribution<> D(min, max);
    return D(G);
}

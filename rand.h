#pragma once

#include <random>

class Random
{
	static std::mt19937 random;
	static const int MAX = 62;

public:
	static int Int(int min, int max);
	static std::string String(int n);
	static float Float(float min, float max);

};


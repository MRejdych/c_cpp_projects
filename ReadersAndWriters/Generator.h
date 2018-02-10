#pragma once

#include <random>

class Generator
{
public:
	static int generateRandom()
	{
		// Wykorzystywany do generowania liczb losowych z zakresu od 0 do 2000
		static std::default_random_engine generator;
		static std::uniform_int_distribution<int> distribution(0, 2000);

		return distribution(generator);
	}
};

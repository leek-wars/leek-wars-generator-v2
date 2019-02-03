#ifndef RANDOM_GENERATOR_HPP_
#define RANDOM_GENERATOR_HPP_

class RandomGenerator {
public:
	long n = 1;

	void seed(long seed);
	double getDouble();
	int getInt(int min, int max);
};

#endif
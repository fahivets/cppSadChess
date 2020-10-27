#ifndef RANDOMGENERATOR_H_INCLUDED
#define RANDOMGENERATOR_H_INCLUDED

#include "NonCopyable.h"
#include "NonMovable.h"

class RandomGenerator : public NonCopyable, public NonMovable
{
public:
	// Functions
	static std::mt19937& getR2D2();
	static int getRandomInt(int from, int to);
	static float getRandomFloat(float from, float to);
	static double getRandomDouble(double from, double to);
	static bool getRandomBool();
	static bool getRandomBoolWhithProb(double prob); // with what probability will be true, probability between 0.0 and 1.0

private:
	std::mt19937 m_R2D2; //Beep bop beep bop!

	// Constructors/Destructors
	RandomGenerator();
	~RandomGenerator() = default;

	// Private functions
	static RandomGenerator& instance();
};

#endif /* end RANDOMGENERATOR_H_INCLUDED */
#include "particle.hpp"
#include "resonance.hpp"
#include <iostream>

int main()
{
	ParticleType const particle{"particella", 2., 3};
	ResonanceType const resonance{"risonanza", 2., 3, 4.};
	particle.Print();
	resonance.Print();
}
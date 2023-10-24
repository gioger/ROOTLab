#include "particle_type.hpp"
#include "resonance_type.hpp"
#include <iostream>

int main()
{
	const ParticleType particle{"particella", 2., 3};
	const ResonanceType resonance{"risonanza", 2., 3, 4.};
	particle.Print();
	resonance.Print();
}
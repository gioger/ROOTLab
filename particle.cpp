#include "particle.hpp"

#include <iostream>

ParticleType::ParticleType(std::string name, double mass, int charge)
	: fName{std::move(name)}, fMass{mass}, fCharge{charge}
{
	if (fMass < 0.)
	{
		std::cerr << "ParticleType::ParticleType: "
				  << "invalid mass value: " << fMass << '\n';
		std::exit(EXIT_FAILURE);
	}
}

void ParticleType::Print() const
{
	std::cout << "Particle type: " << fName << '\n'
			  << "Mass: " << fMass << " MeV/c^2\n" // check units
			  << "Charge: " << fCharge << " e\n";
}
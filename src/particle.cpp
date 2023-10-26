#include "particle.hpp"

#include <algorithm>

Particle::Particle(const std::string& name, double px, double py, double pz) : fPx{px}, fPy{py}, fPz{pz}
{
	fIndex = FindParticle(name);

#include <iostream>
	std::cout << fIndex << '\n';
}

int Particle::FindParticle(const std::string& particleName)
{
	auto it{std::find_if(fParticleType.begin(), fParticleType.end(), [](auto p) { //
		return p->GetName() == particleName;
	})};

	if (it == fParticleType.end())
	{
		std::cerr << "Particle type not found.\n";
		std::exit(EXIT_FAILURE);
	}

	return std::distance(fParticleType.begin(), it); // check if 0 or 1
}
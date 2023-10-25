#include "particle.hpp"

#include <algorithm>

int Particle::FindParticle(const std::string& particleName)
{
	auto it{
		std::find_if(fParticleType.begin(), fParticleType.end(), [](auto p) { return p->GetName() == particleName; })};

	if (it == fParticleType.end())
	{
		std::cerr << "Particle type not found.\n";
		std::exit(EXIT_FAILURE);
	}

	return std::distance(fParticleType.begin(), it); // check if 0 or 1
}
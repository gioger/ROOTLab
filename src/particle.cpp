#include "particle.hpp"

#include <algorithm>
#include <utility>

Particle::Particle(const std::string& name, double px, double py, double pz) : fPx{px}, fPy{py}, fPz{pz}
{
	fIndex = FindParticle(name);
}

int Particle::FindParticle(const std::string& particleName)
{
	auto it{std::find_if(fParticleType.begin(), fParticleType.end(), [&](const auto& p) { //
		return p->GetName() == particleName;
	})};

	if (it == fParticleType.end())
	{
		std::cerr << "Particle type not found.\n";
		std::exit(EXIT_FAILURE);
	}

	return std::distance(fParticleType.begin(), it); // check if 0 or 1
}

void Particle::AddParticleType(const ParticleType& particle)
{
	*(fParticleType[fNParticleType]) = particle;
}
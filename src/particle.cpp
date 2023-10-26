#include "particle.hpp"
#include "resonance_type.hpp"

#include <algorithm>

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

void Particle::AddParticleType(const std::string& name, double mass, int charge, double width)
{
	if (width == 0.)
	{
		fParticleType[fNParticleType] = std::make_unique<ParticleType>(name, mass, charge);
	}
	else
	{
		fParticleType[fNParticleType] = std::make_unique<ResonanceType>(name, mass, charge, width);
	}
}

void Particle::SetIndex(int index)
{
	if (index < fNParticleType)
	{
		fIndex = index;
	}
	else
	{
		std::cerr << "Particle type already existing.\n";
		std::exit(EXIT_FAILURE);
	}
}

void Particle::SetIndex(const std::string& name)
{
	fIndex = FindParticle(name);
}
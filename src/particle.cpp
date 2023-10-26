#include "particle.hpp"
#include "resonance_type.hpp"

#include <algorithm>
#include <cmath>

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

void inline Particle::PrintParticleType()
{
	for (int i{}; i < fMaxNumParticleType; ++i)
	{
		fParticleType[i]->Print();
	}
}

void Particle::PrintParticle() const
{
	const std::string& name{fParticleType[fIndex]->GetName()};
	std::cout << "Particle index: " << fIndex << '\n';
	std::cout << "Particle name: " << name << '\n';
	std::cout << "Particle Px: " << fPx << '\n';
	std::cout << "Particle Py: " << fPy << '\n';
	std::cout << "Particle Pz: " << fPz << '\n';
}

double Particle::Energy() const
{
	const double mass{GetMass()};
	return {sqrt(mass * mass + fPx * fPx + fPy * fPy + fPz * fPz)};
}

double Particle::InvMass(const Particle& particle) const
{
	const double sumEnergy{Energy() + particle.Energy()};
	const double sumPx{fPx + particle.fPx};
	const double sumPy{fPy + particle.fPy};
	const double sumPz{fPz + particle.fPz};

	return {sqrt(sumEnergy * sumEnergy - sumPx * sumPx - sumPy * sumPy - sumPz * sumPz)};
}
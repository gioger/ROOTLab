#include "particle.hpp"
#include "resonance_type.hpp"

#include <cmath>

void Particle::AddParticleType(std::string name, double mass, int charge, double width)
{
	if (fNParticleType >= fMaxNumParticleType)
	{
		std::cerr << "Maximum number of particle types reached.\n";
		std::exit(EXIT_FAILURE);
	}

	fParticleTypes[fNParticleType] = (width != 0) //
										 ? std::make_unique<ResonanceType>(std::move(name), mass, charge, width)
										 : std::make_unique<ParticleType>(std::move(name), mass, charge);

	++fNParticleType;
}

void Particle::PrintParticleType()
{
	for (size_t i{}; i < fMaxNumParticleType; ++i)
	{
		fParticleTypes[i]->Print();
	}
}

Particle::Particle(const std::string& name, double px, double py, double pz) : fPx{px}, fPy{py}, fPz{pz}
{
	fIndex = FindParticle(name);
}

size_t Particle::FindParticle(const std::string& particleName)
{
	for (size_t i{0}; i < fNParticleType; ++i)
	{
		if (fParticleTypes[i]->GetName() == particleName)
		{
			return i;
		}
	}

	std::cerr << "Particle type not found.\n";
	std::exit(EXIT_FAILURE);
}

void Particle::SetIndex(size_t index)
{
	if (index >= fNParticleType)
	{
		std::cerr << "Invalid index.\n";
		std::exit(EXIT_FAILURE);
	}

	fIndex = index;
}

void Particle::SetIndex(const std::string& name)
{
	fIndex = FindParticle(name);
}

void Particle::PrintParticleData() const
{
	const std::string& name{fParticleTypes[fIndex]->GetName()};
	std::cout << "Particle index: " << fIndex << '\n';
	std::cout << "Particle name: " << name << '\n';
	std::cout << "Particle Px: " << fPx << '\n';
	std::cout << "Particle Py: " << fPy << '\n';
	std::cout << "Particle Pz: " << fPz << '\n';
}

double Particle::Energy() const
{
	const double mass{GetMass()};
	return {std::sqrt(mass * mass + fPx * fPx + fPy * fPy + fPz * fPz)};
}

double Particle::InvMass(const Particle& particle) const
{
	const double sumEnergy{Energy() + particle.Energy()};
	const double sumPx{fPx + particle.fPx};
	const double sumPy{fPy + particle.fPy};
	const double sumPz{fPz + particle.fPz};

	return {std::sqrt(sumEnergy * sumEnergy - sumPx * sumPx - sumPy * sumPy - sumPz * sumPz)};
}
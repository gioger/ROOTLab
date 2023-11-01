#include "particle.hpp"
#include "resonance_type.hpp"

#include <cmath>
#include <cstdlib>

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

void Particle::PrintParticleTypes()
{
	for (size_t i{}; i < fNParticleType; ++i)
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
	return std::sqrt(mass * mass + fPx * fPx + fPy * fPy + fPz * fPz);
}

double Particle::InvMass(const Particle& particle) const
{
	const double sumEnergy{Energy() + particle.Energy()};
	const double sumPx{fPx + particle.fPx};
	const double sumPy{fPy + particle.fPy};
	const double sumPz{fPz + particle.fPz};

	return std::sqrt(sumEnergy * sumEnergy - sumPx * sumPx - sumPy * sumPy - sumPz * sumPz);
}

int Particle::Decay2Body(Particle& dau1, Particle& dau2) const
{
	if (GetMass() == 0.0)
	{
		printf("Decayment cannot be preformed if mass is zero\n");
		return 1;
	}

	double massMot = GetMass();
	double massDau1 = dau1.GetMass();
	double massDau2 = dau2.GetMass();

	if (fIndex > -1) // prima fIParticle
	{				 // add width effect

		// gaussian random numbers

		float x1, x2, w, y1;

		double invnum = 1. / RAND_MAX;
		do
		{
			x1 = 2.0 * rand() * invnum - 1.0;
			x2 = 2.0 * rand() * invnum - 1.0;
			w = x1 * x1 + x2 * x2;
		} while (w >= 1.0);

		w = sqrt((-2.0 * log(w)) / w);
		y1 = x1 * w;

		massMot += fParticleTypes[fIndex]->GetWidth() * y1; // prima fIParticle
	}

	if (massMot < massDau1 + massDau2)
	{
		printf("Decayment cannot be preformed because mass is too low in this channel\n");
		return 2;
	}

	double pout = sqrt((massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
					   (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
				  massMot * 0.5;

	double norm = 2 * M_PI / RAND_MAX;

	double phi = rand() * norm;
	double theta = rand() * norm * 0.5 - M_PI / 2.;
	dau1.SetP(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi), pout * cos(theta));
	dau2.SetP(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi), -pout * cos(theta));

	double energy = sqrt(fPx * fPx + fPy * fPy + fPz * fPz + massMot * massMot);

	double bx = fPx / energy;
	double by = fPy / energy;
	double bz = fPz / energy;

	dau1.Boost(bx, by, bz);
	dau2.Boost(bx, by, bz);

	return 0;
}

void Particle::Boost(double bx, double by, double bz)
{

	double energy = Energy();

	// Boost this Lorentz vector
	double b2 = bx * bx + by * by + bz * bz;
	double gamma = 1.0 / sqrt(1.0 - b2);
	double bp = bx * fPx + by * fPy + bz * fPz;
	double gamma2 = b2 > 0 ? (gamma - 1.0) / b2 : 0.0;

	fPx += gamma2 * bp * bx + gamma * bx * energy;
	fPy += gamma2 * bp * by + gamma * by * energy;
	fPz += gamma2 * bp * bz + gamma * bz * energy;
}
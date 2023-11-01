#include "particle.hpp"
#include "resonance_type.hpp"

#include <cmath>
#include <random>

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

void Particle::Decay2Body(Particle& dau1, Particle& dau2) const
{
	if (GetMass() == 0.0)
	{
		std::cerr << "Decayment cannot be preformed if mass is zero\n";
		std::exit(EXIT_FAILURE);
	}

	double massMot{GetMass()};
	const double massDau1{dau1.GetMass()};
	const double massDau2{dau2.GetMass()};

	std::default_random_engine engine{std::random_device{}()};
	std::normal_distribution<double> normDistr{0., 1.};

	const double y1{normDistr(engine)};

	massMot += fParticleTypes[fIndex]->GetWidth() * y1;

	if (massMot < massDau1 + massDau2)
	{
		std::cerr << "Decayment cannot be preformed because mass is too low in this channel\n";
		std::exit(EXIT_FAILURE + 1);
	}

	const double pout{std::sqrt((massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
								(massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
					  massMot * 0.5};

	std::uniform_real_distribution<double> phiDistr{0., M_PI * 2.};
	std::uniform_real_distribution<double> thetaDistr{-M_PI_2, M_PI_2};

	const double phi{phiDistr(engine)};
	const double theta{thetaDistr(engine)};
	const double sinTheta{std::sin(theta)};
	const double cosTheta{std::cos(theta)};
	const double sinPhi{std::sin(phi)};
	const double cosPhi{std::cos(phi)};

	dau1.SetP(pout * sinTheta * cosPhi, pout * sinTheta * sinPhi, pout * cosTheta);
	dau2.SetP(-pout * sinTheta * cosPhi, -pout * sinTheta * sinPhi, -pout * cosTheta);

	const double energy{std::sqrt(fPx * fPx + fPy * fPy + fPz * fPz + massMot * massMot)};

	const double bx{fPx / energy};
	const double by{fPy / energy};
	const double bz{fPz / energy};

	dau1.Boost(bx, by, bz);
	dau2.Boost(bx, by, bz);
}

void Particle::Boost(double bx, double by, double bz)
{

	const double energy{Energy()};

	// Boost this Lorentz vector
	const double b2{bx * bx + by * by + bz * bz};
	const double gamma{1.0 / sqrt(1.0 - b2)};
	const double bp{bx * fPx + by * fPy + bz * fPz};
	const double gamma2{b2 > 0 ? (gamma - 1.0) / b2 : 0.0};

	fPx += gamma2 * bp * bx + gamma * bx * energy;
	fPy += gamma2 * bp * by + gamma * by * energy;
	fPz += gamma2 * bp * bz + gamma * bz * energy;
}
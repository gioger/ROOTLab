#include <TMath.h>
#include <TRandom.h>

#include <algorithm>
#include <vector>

#include "particle.hpp"

void Setup()
{
	gRandom->SetSeed();

	Particle::AddParticleType("pi+", 0.13957, 1);
	Particle::AddParticleType("pi-", 0.13957, -1);
	Particle::AddParticleType("K+", 0.49367, +1);
	Particle::AddParticleType("K-", 0.49367, -1);
	Particle::AddParticleType("p+", 0.93827, +1);
	Particle::AddParticleType("p-", 0.93827, -1);
	Particle::AddParticleType("K*", 0.89166, 0, 0.05);
}

int main()
{
	Setup();

	constexpr size_t numEvents{100'000};
	constexpr size_t numParts{100};

	std::vector<Particle> eventParticles;
	eventParticles.reserve(numParts);

	for (size_t i{0}; i < numEvents; i++)
	{
		eventParticles.clear(); // to check if capacity is affected
		std::generate_n(		//
			std::back_inserter(eventParticles), numParts,
			[&]()
			{
				const double phi{gRandom->Uniform(0., TMath::TwoPi())};
				const double theta{gRandom->Uniform(0., TMath::Pi())};
				const double p{gRandom->Exp(1.)};

				const double sinTheta{TMath::Sin(theta)};
				const double cosTheta{TMath::Cos(theta)};
				const double sinPhi{TMath::Sin(phi)};
				const double cosPhi{TMath::Cos(phi)};

				const double px{p * sinTheta * cosPhi};
				const double py{p * sinTheta * sinPhi};
				const double pz{p * cosTheta};

				const double x{gRandom->Uniform()};

				std::string particleName;
				if (x < 0.4)
				{
					particleName = "pi+";
				}
				else if (x < 0.8)
				{
					particleName = "pi-";
				}
				else if (x < 0.85)
				{
					particleName = "K+";
				}
				else if (x < 0.9)
				{
					particleName = "K-";
				}
				else if (x < 0.945)
				{
					particleName = "p+";
				}
				else if (x < 0.99)
				{
					particleName = "p-";
				}
				else
				{
					particleName = "K*";
				}

				return Particle{particleName, px, py, pz};
			});

		for (const auto& p : eventParticles)
		{
			if (p.GetIndex() == 6) // K*
			{
				const double x{gRandom->Uniform()};

				Particle p1{};
				Particle p2{};

				if (x < 0.5)
				{
					p1.SetIndex("pi+");
					p2.SetIndex("K-");
				}
				else
				{
					p1.SetIndex("pi-");
					p2.SetIndex("K+");
				}

				p.Decay2Body(p1, p2); // Shuold we remove K*?

				eventParticles.push_back(p1);
				eventParticles.push_back(p2);
			}
		}
	}
}
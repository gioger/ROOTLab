#include <TRandom.h>

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
}
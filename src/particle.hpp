#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "particle_type.hpp"

#include <array>
#include <iostream>
#include <memory>

class Particle
{
public:
	Particle(const std::string& name, double px = 0, double py = 0, double pz = 0);
	int GetIndex() const { return fIndex; }

	static void AddParticleType(const std::string& name, double mass, int charge, double width = 0.);

private:
	static constexpr int fMaxNumParticleType = 10;
	inline static std::array<std::unique_ptr<ParticleType>, fMaxNumParticleType> fParticleType{};

	inline static int fNParticleType{};

	int FindParticle(const std::string& particleName);

	int fIndex{};

	double fPx{};
	double fPy{};
	double fPz{};
};

#endif
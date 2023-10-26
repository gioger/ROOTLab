#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "particle_type.hpp"

#include <array>
#include <iostream>
#include <memory>

class Particle
{
public:
	static void AddParticleType(std::string name, double mass, int charge, double width = 0.);
	static void PrintParticleType();

	Particle(const std::string& name, double px = 0., double py = 0., double pz = 0.);
	void PrintParticleData() const;

	size_t GetIndex() const { return fIndex; }
	void SetIndex(size_t index);
	void SetIndex(const std::string& name);

	double GetPx() const { return fPx; }
	double GetPy() const { return fPy; }
	double GetPz() const { return fPz; }
	double GetMass() const { return fParticleType[fIndex]->GetMass(); }

	double Energy() const;
	double InvMass(const Particle& particle) const;

	void SetP(double px, double py, double pz)
	{
		fPx = px;
		fPy = py;
		fPz = pz;
	}

private:
	static constexpr size_t fMaxNumParticleType = 10;
	static inline std::array<std::unique_ptr<ParticleType>, fMaxNumParticleType> fParticleType{};

	static inline size_t fNParticleType{};

	size_t FindParticle(const std::string& particleName);

	size_t fIndex{};

	double fPx{};
	double fPy{};
	double fPz{};
};

#endif
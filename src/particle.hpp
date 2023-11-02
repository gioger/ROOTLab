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
	static void PrintParticleTypes();

	Particle(const std::string& name, double px = 0., double py = 0., double pz = 0.);
	Particle() = default;
	void PrintParticleData() const;

	size_t GetIndex() const { return fIndex; }
	void SetIndex(size_t index);
	void SetIndex(const std::string& name);

	double GetPx() const { return fPx; }
	double GetPy() const { return fPy; }
	double GetPz() const { return fPz; }
	double GetMass() const { return fParticleTypes[fIndex]->GetMass(); }

	void SetP(double px, double py, double pz)
	{
		fPx = px;
		fPy = py;
		fPz = pz;
	}

	double Energy() const;
	double InvMass(const Particle& particle) const;
	void Decay2Body(Particle& dau1, Particle& dau2) const;

private:
	static constexpr size_t fMaxNumParticleType{10};
	static inline std::array<std::unique_ptr<ParticleType>, fMaxNumParticleType> fParticleTypes{};

	static inline size_t fNParticleType{};

	size_t FindParticle(const std::string& particleName);

	void Boost(double bx, double by, double bz);

	size_t fIndex{};

	double fPx{};
	double fPy{};
	double fPz{};
};

#endif
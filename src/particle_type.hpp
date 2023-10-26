#ifndef PARTICLE_TYPE_HPP
#define PARTICLE_TYPE_HPP

#include <string>

class ParticleType
{
public:
	ParticleType(std::string name, double mass, int charge);

	double GetMass() const { return fMass; }
	int GetCharge() const { return fCharge; }
	const std::string& GetName() const { return fName; }
	virtual void Print() const;

private:
	const std::string fName{}; // we'll ask if it's ok to use std::string
	const double fMass{};
	const int fCharge{};
};

#endif // PARTICLE_TYPE_HPP
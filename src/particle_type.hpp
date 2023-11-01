#ifndef PARTICLE_TYPE_HPP
#define PARTICLE_TYPE_HPP

#include <string>

class ParticleType
{
public:
	ParticleType(std::string name, double mass, int charge);
	virtual ~ParticleType() = default;

	double GetMass() const { return fMass; }
	int GetCharge() const { return fCharge; }
	const std::string& GetName() const { return fName; }
	virtual void Print() const;
	virtual double GetWidth() const { return 0; };

private:
	const std::string fName{};
	const double fMass{};
	const int fCharge{};
};

#endif // PARTICLE_TYPE_HPP
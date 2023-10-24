#ifndef RESONANCE_TYPE_HPP
#define RESONANCE_TYPE_HPP

#include "particle.hpp"

class ResonanceType : ParticleType
{
public:
	ResonanceType(std::string name, double mass, int charge, double width);

	double GetWidth() const { return fWidth; }
	void Print() const override;

private:
	double fWidth{};
};

#endif // RESONANCE_TYPE_HPP
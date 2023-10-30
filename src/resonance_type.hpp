#ifndef RESONANCE_TYPE_HPP
#define RESONANCE_TYPE_HPP

#include "particle_type.hpp"

class ResonanceType : public ParticleType
{
public:
	ResonanceType(std::string name, double mass, int charge, double width = 0);
	~ResonanceType() override = default;

	double GetWidth() const { return fWidth; }
	void Print() const override;

private:
	const double fWidth{};
};

#endif // RESONANCE_TYPE_HPP
#include "resonance.hpp"

#include <iostream>

ResonanceType::ResonanceType(std::string name, double mass, int charge, double width)
	: ParticleType{std::move(name), mass, charge}, fWidth{width}
{
	if (fWidth < 0.)
	{
		std::cerr << "ResonanceType::ResonanceType: "
				  << "invalid width value: " << fWidth << '\n';
		std::exit(EXIT_FAILURE);
	}
}

void ResonanceType::Print() const
{
	ParticleType::Print();
	std::cout << "Width: " << fWidth << " MeV/c^2\n"; // check units
}
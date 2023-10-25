#include "particle_type.hpp"
#include "resonance_type.hpp"

#include <array>
#include <iostream>
#include <memory>

int main()
{
	const std::array<std::unique_ptr<ParticleType>, 2> particles{
		std::make_unique<ParticleType>("particella", 2., 3),	//
		std::make_unique<ResonanceType>("risonanza", 2., 3, 4.) //
	};

	for (const auto& p : particles)
	{
		p->Print();
	}
}
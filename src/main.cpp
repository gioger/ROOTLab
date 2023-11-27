#include <TFile.h>
#include <TH1.h>
#include <TMath.h>
#include <TRandom.h>

#include <algorithm>
#include <vector>

#include "particle.hpp"

void Setup()
{
	gRandom->SetSeed();
	// Initialize all particle types
	Particle::AddParticleType("pi+", 0.13957, 1);
	Particle::AddParticleType("pi-", 0.13957, -1);
	Particle::AddParticleType("K+", 0.49367, 1);
	Particle::AddParticleType("K-", 0.49367, -1);
	Particle::AddParticleType("p+", 0.93827, 1);
	Particle::AddParticleType("p-", 0.93827, -1);
	Particle::AddParticleType("K*", 0.89166, 0, 0.05);
}

int main()
{
	Setup();

	// Initialize histograms with the proper axes labels
	auto* hParticleTypes{new TH1I{"hParticleTypes", "Particle types", 7, 0, 7}};
	hParticleTypes->GetXaxis()->SetBinLabel(1, "pi+");
	hParticleTypes->GetXaxis()->SetBinLabel(2, "pi-");
	hParticleTypes->GetXaxis()->SetBinLabel(3, "K+");
	hParticleTypes->GetXaxis()->SetBinLabel(4, "K-");
	hParticleTypes->GetXaxis()->SetBinLabel(5, "p+");
	hParticleTypes->GetXaxis()->SetBinLabel(6, "p-");
	hParticleTypes->GetXaxis()->SetBinLabel(7, "K*");

	auto* hPhi{new TH1D{"hPhi", "Phi Distribution", 500, 0., TMath::TwoPi()}};
	hPhi->GetXaxis()->SetTitle("#phi (rad)");
	hPhi->GetYaxis()->SetTitle("Entries");

	auto* hTheta{new TH1D{"hTheta", "Theta Distribution", 500, 0., TMath::Pi()}};
	hTheta->GetXaxis()->SetTitle("#theta (rad)");
	hTheta->GetYaxis()->SetTitle("Entries");

	auto* hImpulse{new TH1D{"hImpulse", "Impulse", 500, 0., 5.}};
	hImpulse->GetXaxis()->SetTitle("Impulse (GeV/c)");
	hImpulse->GetYaxis()->SetTitle("Entries");

	auto* hTransverseImpulse{new TH1D{"hTransverseImpulse", "Transverse impulse", 100, 0., 4.}};
	hTransverseImpulse->GetXaxis()->SetTitle("Transverse impulse (GeV/c)");
	hTransverseImpulse->GetYaxis()->SetTitle("Entries");

	auto* hEnergy{new TH1D{"hEnergy", "Energy", 500, 0., 5.}};
	hEnergy->GetXaxis()->SetTitle("Energy (GeV)");
	hEnergy->GetYaxis()->SetTitle("Entries");

	auto* hInvMass{new TH1D{"hInvMass", "Invariant mass (all particles)", 500, 0., 6.}};
	hInvMass->GetXaxis()->SetTitle("Invariant mass (GeV/c^2)");
	hInvMass->GetYaxis()->SetTitle("Entries");

	auto* hInvMassSameSign{new TH1D{"hInvMassSameSign", "Invariant mass (same sign particles)", 500, 0., 5.}};
	hInvMassSameSign->GetXaxis()->SetTitle("Invariant mass (GeV/c^2)");
	hInvMassSameSign->GetYaxis()->SetTitle("Entries");

	auto* hInvMassDiscSign{new TH1D{"hInvMassDiscSign", "Invariant mass (discordant sign particles)", 500, 0., 5.}};
	hInvMassDiscSign->GetXaxis()->SetTitle("Invariant mass (GeV/c^2)");
	hInvMassDiscSign->GetYaxis()->SetTitle("Entries");

	auto* hInvMassPiKSame{new TH1D{"hInvMassPiKSame", "Invariant mass (pi-K same sign)", 500, 0., 5.}};
	hInvMassPiKSame->GetXaxis()->SetTitle("Invariant mass (GeV/c^2)");
	hInvMassPiKSame->GetYaxis()->SetTitle("Entries");

	auto* hInvMassPiKDisc{new TH1D{"hInvMassPiKDisc", "Invariant mass (pi-K discordant sign)", 500, 0., 5.}};
	hInvMassPiKDisc->GetXaxis()->SetTitle("Invariant mass (GeV/c^2)");
	hInvMassPiKDisc->GetYaxis()->SetTitle("Entries");

	auto* hInvMassChildren{new TH1D{"hInvMassChildren", "Invariant mass (children)", 500, 0.4, 1.4}};
	hInvMassChildren->GetXaxis()->SetTitle("Invariant mass (GeV/c^2)");
	hInvMassChildren->GetYaxis()->SetTitle("Entries");

	hInvMassSameSign->Sumw2();
	hInvMassDiscSign->Sumw2();
	hInvMassPiKSame->Sumw2();
	hInvMassPiKDisc->Sumw2();

	auto* hInvMassSubAll{new TH1D{
		"hInvMassSubAll", "Invariant mass (difference between same & discordant signs - All particles)", 500, 0., 5.}};
	hInvMassSubAll->GetXaxis()->SetTitle("Invariant mass (GeV/c^2)");
	hInvMassSubAll->GetYaxis()->SetTitle("Entries");

	auto* hInvMassSubPiK{
		new TH1D{"hInvMassSubPiK", "Invariant mass (difference between same & discordant signs - pi-K)", 500, 0., 5.}};
	hInvMassSubPiK->GetXaxis()->SetTitle("Invariant mass (GeV/c^2)");
	hInvMassSubPiK->GetYaxis()->SetTitle("Entries");

	constexpr size_t numEvents{100'000};
	constexpr size_t numParts{100};

	std::vector<Particle> eventParticles;
	eventParticles.reserve(numParts);

	for (size_t i{0}; i < numEvents; i++)
	{
		// Generate particles for each event
		eventParticles.clear();
		std::generate_n( //
			std::back_inserter(eventParticles), numParts,
			[&]()
			{
				const double phi{gRandom->Uniform(0., TMath::TwoPi())};
				const double theta{gRandom->Uniform(0., TMath::Pi())};
				const double p{gRandom->Exp(1.)};

				hPhi->Fill(phi);
				hTheta->Fill(theta);
				hImpulse->Fill(p);

				const double sinTheta{TMath::Sin(theta)};

				const double px{p * sinTheta * TMath::Cos(phi)};
				const double py{p * sinTheta * TMath::Sin(phi)};
				const double pz{p * TMath::Cos(theta)};

				hTransverseImpulse->Fill(std::sqrt(px * px + py * py));

				const double x{gRandom->Uniform()};

				std::string particleName;
				if (x < 0.4)
				{
					particleName = "pi+";
				}
				else if (x < 0.8)
				{
					particleName = "pi-";
				}
				else if (x < 0.85)
				{
					particleName = "K+";
				}
				else if (x < 0.9)
				{
					particleName = "K-";
				}
				else if (x < 0.945)
				{
					particleName = "p+";
				}
				else if (x < 0.99)
				{
					particleName = "p-";
				}
				else
				{
					particleName = "K*";
				}

				Particle particle{particleName, px, py, pz};
				hParticleTypes->Fill(particle.GetIndex());
				hEnergy->Fill(particle.Energy());
				return particle;
			});

		// Handle K* decays
		for (const auto& p : eventParticles)
		{
			if (p.GetName() == "K*")
			{
				// K* decays into pi-K
				const double x{gRandom->Uniform()};

				Particle p1{};
				Particle p2{};

				if (x < 0.5)
				{
					p1.SetIndex("pi+");
					p2.SetIndex("K-");
				}
				else
				{
					p1.SetIndex("pi-");
					p2.SetIndex("K+");
				}

				p.Decay2Body(p1, p2);

				eventParticles.push_back(p1);
				eventParticles.push_back(p2);
				// K* must not be removed from the eventParticles vector
			}
		}

		for (size_t i{0}; i < eventParticles.size(); i++)
		{
			if (eventParticles[i].GetName() == "K*")
			{
				continue;
			}
			for (size_t j{i + 1}; j < eventParticles.size(); j++)
			{
				if (eventParticles[j].GetName() == "K*")
				{
					continue;
				}

				// Calculate the invariant mass of every couple of particles of the event
				// Note that particles of type K* are not considered, as they are decayed
				const double invMass{eventParticles[i].InvMass(eventParticles[j])};

				hInvMass->Fill(invMass);

				// If the product of the charges is > 0, the sign is the same; if it's < 0, the sign is discordant
				if (eventParticles[i].GetCharge() * eventParticles[j].GetCharge() > 0)
				{
					hInvMassSameSign->Fill(invMass);
				}
				else if (eventParticles[i].GetCharge() * eventParticles[j].GetCharge() < 0)
				{
					hInvMassDiscSign->Fill(invMass);
				}
				else
				{
					std::cerr << "A particle with no charge was entered" << std::endl;
				}

				// check if the particles are pi-K, with opposite signs
				if ((eventParticles[i].GetName() == "pi+" && eventParticles[j].GetName() == "K-") ||
					(eventParticles[i].GetName() == "K-" && eventParticles[j].GetName() == "pi+") ||
					(eventParticles[i].GetName() == "pi-" && eventParticles[j].GetName() == "K+") ||
					(eventParticles[i].GetName() == "K+" && eventParticles[j].GetName() == "pi-"))
				{
					hInvMassPiKDisc->Fill(invMass);
				}

				// check if the particles are pi-K, with the same sign
				if ((eventParticles[i].GetName() == "pi+" && eventParticles[j].GetName() == "K+") ||
					(eventParticles[i].GetName() == "K+" && eventParticles[j].GetName() == "pi+") ||
					(eventParticles[i].GetName() == "pi-" && eventParticles[j].GetName() == "K-") ||
					(eventParticles[i].GetName() == "K-" && eventParticles[j].GetName() == "pi-"))
				{
					hInvMassPiKSame->Fill(invMass);
				}
			}
		}

		// Calculate the invariant mass of the 2 children of the K* particles
		for (size_t i{numParts}; i < eventParticles.size(); i += 2)
		{
			const double invMass{eventParticles[i].InvMass(eventParticles[i + 1])};
			hInvMassChildren->Fill(invMass);
		}
	}

	hInvMassSubAll->Add(hInvMassDiscSign, hInvMassSameSign, 1., -1.);
	hInvMassSubPiK->Add(hInvMassPiKDisc, hInvMassPiKSame, 1., -1.);

	// Open a file to save the histograms
	auto* outFile{TFile::Open("histos.root", "RECREATE")};

	hParticleTypes->Write();
	hPhi->Write();
	hTheta->Write();
	hImpulse->Write();
	hTransverseImpulse->Write();
	hEnergy->Write();
	hInvMass->Write();
	hInvMassSameSign->Write();
	hInvMassDiscSign->Write();
	hInvMassPiKSame->Write();
	hInvMassPiKDisc->Write();
	hInvMassChildren->Write();
	hInvMassSubAll->Write();
	hInvMassSubPiK->Write();

	outFile->Close();
}
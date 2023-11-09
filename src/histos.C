#include <TFile.h>
#include <TH1.h>

void histos()
{
	auto* inFile{new TFile{"build/histos.root"}};

	// Load histograms from file
	auto* hParticleTypes{dynamic_cast<TH1I*>(inFile->Get("hParticleTypes"))};
	auto* hPhi{dynamic_cast<TH1D*>(inFile->Get("hPhi"))};
	auto* hTheta{dynamic_cast<TH1D*>(inFile->Get("hTheta"))};
	auto* hImpulse{dynamic_cast<TH1D*>(inFile->Get("hImpulse"))};
	auto* hTransverseImpulse{dynamic_cast<TH1D*>(inFile->Get("hTransverseImpulse"))};
	auto* hEnergy{dynamic_cast<TH1D*>(inFile->Get("hEnergy"))};
	auto* hInvMass{dynamic_cast<TH1D*>(inFile->Get("hInvMass"))};
	auto* hInvMassSameSign{dynamic_cast<TH1D*>(inFile->Get("hInvMassSameSign"))};
	auto* hInvMassDiscSign{dynamic_cast<TH1D*>(inFile->Get("hInvMassDiscSign"))};
	auto* hInvMassPiKSame{dynamic_cast<TH1D*>(inFile->Get("hInvMassPiKSame"))};
	auto* hInvMassPiKDisc{dynamic_cast<TH1D*>(inFile->Get("hInvMassPiKDisc"))};
	auto* hInvMassChildren{dynamic_cast<TH1D*>(inFile->Get("hInvMassChildren"))};
	auto* hInvMassSubAll{dynamic_cast<TH1D*>(inFile->Get("hInvMassSubAll"))};
	auto* hInvMassSubPiK{dynamic_cast<TH1D*>(inFile->Get("hInvMassSubPiK"))};
}
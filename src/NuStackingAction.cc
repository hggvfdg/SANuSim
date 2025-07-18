#include "NuStackingAction.hh"

#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4AnalysisManager.hh"

G4ClassificationOfNewTrack NuStackingAction::ClassifyNewTrack(const G4Track* track)
{
    G4ParticleDefinition* particle = track->GetDefinition();
    G4int pdgID = particle->GetPDGEncoding();

#define CUT_E_GAMMA false
#if CUT_E_GAMMA
    if (pdgID == 11 || pdgID == -11 || pdgID == 22) { return fKill; }
#endif

    if (pdgID == 14 || pdgID == -14 || pdgID == 12 || pdgID == -12 || pdgID == 16 || pdgID == -16)
    {
        G4ThreeVector pos = track->GetPosition();
        G4double KE = track->GetKineticEnergy();

        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillNtupleIColumn(0, 0, pdgID);
        analysisManager->FillNtupleDColumn(0, 1, pos.mag());
        analysisManager->FillNtupleDColumn(0, 2, KE);
        analysisManager->AddNtupleRow(0);

        return fKill;
    }

#if false
    if (pdgID == 11 || pdgID == -11 || pdgID == 22)
    {
        G4int ntupleID;
        if (pdgID == 11) { ntupleID = 1; }
        if (pdgID == -11) { ntupleID = 2; }
        if (pdgID == 22) { ntupleID = 3; }

        G4ThreeVector x = track->GetPosition();
        G4ThreeVector p = track->GetMomentum();

        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillNtupleDColumn(ntupleID, 0, x[0]);
        analysisManager->FillNtupleDColumn(ntupleID, 1, x[1]);
        analysisManager->FillNtupleDColumn(ntupleID, 2, x[2]);
        analysisManager->FillNtupleDColumn(ntupleID, 3, p[0]);
        analysisManager->FillNtupleDColumn(ntupleID, 4, p[1]);
        analysisManager->FillNtupleDColumn(ntupleID, 5, p[2]);
        analysisManager->AddNtupleRow(ntupleID);

        return fKill;
    }
#endif

    return fUrgent;
}
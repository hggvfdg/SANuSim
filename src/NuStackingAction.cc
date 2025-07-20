#include "NuStackingAction.hh"
#include "NuThreadLocalContainer.hh"

#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4AnalysisManager.hh"

NuStackingAction::NuStackingAction()
 : G4UserStackingAction(),
   NuNtuplePDG {14,-14,12,-12,16,-16}
{}

G4ClassificationOfNewTrack NuStackingAction::ClassifyNewTrack(const G4Track* track)
{
    G4double E = track->GetTotalEnergy();
    if (E<10*MeV) { return fKill; }

    G4int pdgID = track->GetDefinition()->GetPDGEncoding();
    for (int i=0;i<6;++i) 
    {
        if (pdgID != NuNtuplePDG[i]) { continue; }
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillNtupleDColumn(i, 0, E);
        analysisManager->FillNtupleDColumn(i, 1, NuThreadLocalContainer::Instance()->GetPrimaryKE());
        analysisManager->AddNtupleRow(i);
        return fKill;
    }
    return fUrgent;
}
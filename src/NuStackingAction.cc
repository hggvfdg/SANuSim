#include "NuStackingAction.hh"
#include "NuThreadLocalContainer.hh"

#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4AnalysisManager.hh"

NuStackingAction::NuStackingAction()
 : G4UserStackingAction(),
 : NuNtuplePDG({14,-14,12,-12,16,-16})
{}

G4ClassificationOfNewTrack NuStackingAction::ClassifyNewTrack(const G4Track* track)
{
    G4int pdgID = track->GetDefinition()->GetPDGEncoding();
    for (int i=0;i<6;++i) 
    {
        if (pdgID != NuNtuplePDG[i]) { continue; }
        auto analysisManager = G4AnalysisManager::Instance();
        G4double KE = track->GetKineticEnergy();
        analysisManager->FillNtupleDColumn(i, 0, KE);
        analysisManager->AddNtupleRow(i);

        NuThreadLocalContainer::Instance()->SetNuCounter(i);
        return fKill;
    }
    return fUrgent;
}
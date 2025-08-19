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
    G4int pdgID = track->GetDefinition()->GetPDGEncoding();
    if (pdgID == 11 || pdgID == -11 || pdgID == 22) { return fKill; }

    for (int i=0;i<6;++i) 
    {
        if (pdgID != NuNtuplePDG[i]) { continue; }
        if (track->GetKineticEnergy()<1*GeV) { return fKill; }
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillNtupleDColumn(i, 0, track->GetKineticEnergy());
        analysisManager->FillNtupleDColumn(i, 1, NuThreadLocalContainer::Instance()->GetPrimaryKE());
        analysisManager->AddNtupleRow(i);
        return fKill;
    }
    return fUrgent;
}
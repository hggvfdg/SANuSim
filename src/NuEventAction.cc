#include "NuEventAction.hh"
#include "NuThreadLocalContainer.hh"

#include "G4AnalysisManager.hh"

void NuEventAction::EndOfEventAction(const G4Event* event)
{
    auto TLContainer = NuThreadLocalContainer::Instance();
    for (int i=0;i<6;++i)
    {
        if (TLContainer->GetNuCounter(i) == 0) { continue; }

        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillNtupleDColumn(6, 0, TLContainer->GetPrimaryKE());
        analysisManager->FillNtupleDColumn(6, 1, TLContainer->GetNuCounter(0));
        analysisManager->FillNtupleDColumn(6, 2, TLContainer->GetNuCounter(1));
        analysisManager->FillNtupleDColumn(6, 3, TLContainer->GetNuCounter(2));
        analysisManager->FillNtupleDColumn(6, 4, TLContainer->GetNuCounter(3));
        analysisManager->FillNtupleDColumn(6, 5, TLContainer->GetNuCounter(4));
        analysisManager->FillNtupleDColumn(6, 6, TLContainer->GetNuCounter(5));
        analysisManager->AddNtupleRow(i);
        TLContainer->ResetNuCounter();

        return;
    }
}
#include "NuRunAction.hh"

#include "G4AnalysisManager.hh"

void NuRunAction::BeginOfRunAction(const G4Run*) 
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(true);
    analysisManager->SetDefaultFileType("root");    // ROOT format

    analysisManager->OpenFile("NuOutPut");    // Output file

    // Create ntuple and columns
    G4int ntupleID = 0;
    ntupleID = analysisManager->CreateNtuple("NuData", "Neutrino initial information");    // Ntuple ID: 0
    analysisManager->CreateNtupleIColumn(ntupleID, "PDG_ID");
    analysisManager->CreateNtupleDColumn(ntupleID, "R_mm");
    analysisManager->CreateNtupleDColumn(ntupleID, "KE_MeV");
    analysisManager->FinishNtuple(ntupleID);

#if false
    ntupleID = analysisManager->CreateNtuple("electron", "electron");    // Ntuple ID: 1
    analysisManager->CreateNtupleDColumn(ntupleID, "x");
    analysisManager->CreateNtupleDColumn(ntupleID, "y");
    analysisManager->CreateNtupleDColumn(ntupleID, "z");
    analysisManager->CreateNtupleDColumn(ntupleID, "p_x");
    analysisManager->CreateNtupleDColumn(ntupleID, "p_y");
    analysisManager->CreateNtupleDColumn(ntupleID, "p_z");
    analysisManager->FinishNtuple(ntupleID);

    ntupleID = analysisManager->CreateNtuple("positron", "positron");    // Ntuple ID: 2
    analysisManager->CreateNtupleDColumn(ntupleID, "x");
    analysisManager->CreateNtupleDColumn(ntupleID, "y");
    analysisManager->CreateNtupleDColumn(ntupleID, "z");
    analysisManager->CreateNtupleDColumn(ntupleID, "p_x");
    analysisManager->CreateNtupleDColumn(ntupleID, "p_y");
    analysisManager->CreateNtupleDColumn(ntupleID, "p_z");
    analysisManager->FinishNtuple(ntupleID);

    ntupleID = analysisManager->CreateNtuple("gamma", "gamma");    // Ntuple ID: 3
    analysisManager->CreateNtupleDColumn(ntupleID, "x");
    analysisManager->CreateNtupleDColumn(ntupleID, "y");
    analysisManager->CreateNtupleDColumn(ntupleID, "z");
    analysisManager->CreateNtupleDColumn(ntupleID, "p_x");
    analysisManager->CreateNtupleDColumn(ntupleID, "p_y");
    analysisManager->CreateNtupleDColumn(ntupleID, "p_z");
    analysisManager->FinishNtuple(ntupleID);
#endif
}

void NuRunAction::EndOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
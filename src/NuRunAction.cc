#include "NuRunAction.hh"
#include "NuThreadLocalContainer.hh"

#include "G4AnalysisManager.hh"

void NuRunAction::BeginOfRunAction(const G4Run*) 
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(true);
    analysisManager->SetDefaultFileType("root");    // ROOT format
    analysisManager->OpenFile("NuOutPut");    // Output file

    // Create ntuples for neutrinos
    std::string nu_name[] = {"nu_mu", "nu_mu_bar", "nu_e", "nu_e_bar", "nu_tau", "nu_tau_bar"};
    G4int ntupleID = 0;
    for (const auto& name : nu_name)
    {
        ntupleID = analysisManager->CreateNtuple(name, name);
        analysisManager->CreateNtupleDColumn(ntupleID, "KE_MeV");
        analysisManager->CreateNtupleDColumn(ntupleID, "Primary_KE_MeV");
        analysisManager->FinishNtuple(ntupleID);
    }

    ntupleID = analysisManager->CreateNtuple("proton", "proton");
    analysisManager->CreateNtupleDColumn(ntupleID, "KE_MeV");
    analysisManager->FinishNtuple(ntupleID);
    // Note: Ntuple ID ranging for 0 to 6 are, nu_mu, nu_mu_bar, nu_e, nu_e_bar, nu_tau, nu_tau_bar and proton respectively

    NuThreadLocalContainer::Instance(); // Create an instance of the NuThreadLocalContainer for the this thread
}

void NuRunAction::EndOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
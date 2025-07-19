#include "NuThreadLocalContainer.hh"

NuThreadLocalContainer::NuThreadLocalContainer()
 : NuCounter{0, 0, 0, 0, 0, 0}
{}

static NuThreadLocalContainer::NuThreadLocalContainer* Instance()
{
    thread_local static NuThreadLocalContainer analysisManager;
    return &analysisManager;
}

void NuThreadLocalContainer::SetPrimaryKE(G4double KE) { PrimaryKE = KE; }

void NuThreadLocalContainer::SetNuCounter(int i) { ++NuCounter[i]; }

void NuThreadLocalContainer::ResetNuCounter() { NuCounter = {0, 0, 0, 0, 0, 0}; }
    
G4double NuThreadLocalContainer::GetPrimaryKE() { return PrimaryKE; };

int NuThreadLocalContainer::GetNuCounter(int i) { return NuCounter[i]; }
#include "NuThreadLocalContainer.hh"

NuThreadLocalContainer::NuThreadLocalContainer()
 : PrimaryKE(0)
{}

NuThreadLocalContainer* NuThreadLocalContainer::Instance()
{
    thread_local static NuThreadLocalContainer analysisManager;
    return &analysisManager;
}

void NuThreadLocalContainer::SetPrimaryKE(G4double KE) { PrimaryKE = KE; }
    
G4double NuThreadLocalContainer::GetPrimaryKE() { return PrimaryKE; };
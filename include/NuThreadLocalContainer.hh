#pragma once

#include <unordered_map>
#include "G4Types.hh"

class NuThreadLocalContainer
{
public:

    NuThreadLocalContainer();
    ~NuThreadLocalContainer() = default;

    static NuThreadLocalContainer* Instance();

    void SetPrimaryKE(G4double);
    void SetNuCounter(int);
    void ResetNuCounter();

    G4double GetPrimaryKE();
    int GetNuCounter(int);

private:

    G4int NuCounter[6];
    G4double PrimaryKE;
};
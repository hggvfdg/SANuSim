#pragma once

#include "G4Types.hh"

class NuThreadLocalContainer
{
public:

    NuThreadLocalContainer();
    ~NuThreadLocalContainer() = default;

    static NuThreadLocalContainer* Instance();

    void SetPrimaryKE(G4double);
    G4double GetPrimaryKE();

private:

    G4double PrimaryKE;
};
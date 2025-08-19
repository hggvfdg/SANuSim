#pragma once

#include "G4VModularPhysicsList.hh"

class NuPhysicsList : public G4VModularPhysicsList
{
public:

    NuPhysicsList();
    ~NuPhysicsList() = default;

    void SetCuts();
};

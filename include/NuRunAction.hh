#pragma once

#include "G4UserRunAction.hh"

class G4Run;

class NuRunAction : public G4UserRunAction
{
public:
    
    NuRunAction() = default;
    ~NuRunAction() = default;

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
};
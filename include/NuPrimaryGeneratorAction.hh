#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4Types.hh"
#include <vector>

class G4Event;
class G4ParticleGun;
class G4ParticleDefinition;

class NuPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:

    NuPrimaryGeneratorAction();
    ~NuPrimaryGeneratorAction();

    void GeneratePrimaries(G4Event*) override;

private:

    G4double E_min, E_max;
    G4ParticleGun* fParticleGun;
};
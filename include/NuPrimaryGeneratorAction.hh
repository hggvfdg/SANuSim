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

    static std::vector<std::vector<G4double>> iniParam;

    NuPrimaryGeneratorAction();
    ~NuPrimaryGeneratorAction();

    void GeneratePrimaries(G4Event*) override;

private:

    std::vector<G4double> x_and_p;
    G4ParticleGun* fParticleGun;
};
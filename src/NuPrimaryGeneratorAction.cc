#include "NuPrimaryGeneratorAction.hh"
#include "NuThreadLocalContainer.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4RandomDirection.hh"
#include "G4SystemOfUnits.hh"

NuPrimaryGeneratorAction::NuPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0), E_min(0.1*GeV), E_max(100*TeV)
{
    fParticleGun  = new G4ParticleGun(1);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("proton");
    fParticleGun->SetParticleDefinition(particle);
}

NuPrimaryGeneratorAction::~NuPrimaryGeneratorAction() { delete fParticleGun; }

void NuPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    G4ThreeVector position_dir = G4RandomDirection();
    fParticleGun->SetParticlePosition(position_dir*2.5*695700*km);

    G4ThreeVector momentum_dir = G4RandomDirection();
    if (position_dir*momentum_dir >= 0) { momentum_dir = -momentum_dir; }
    fParticleGun->SetParticleMomentumDirection(momentum_dir);
    
    G4double KE = E_min * pow(E_max/E_min, G4UniformRand());
    fParticleGun->SetParticleEnergy(KE);
    NuThreadLocalContainer::Instance()->SetPrimaryKE(KE);

    fParticleGun->GeneratePrimaryVertex(event);
}
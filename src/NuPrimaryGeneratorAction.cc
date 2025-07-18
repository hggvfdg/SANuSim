#include "NuPrimaryGeneratorAction.hh"

#include "G4AutoLock.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4RandomDirection.hh"
#include "G4SystemOfUnits.hh"

namespace{ G4Mutex DetLock = G4MUTEX_INITIALIZER; }

std::vector<std::vector<G4double>> NuPrimaryGeneratorAction::iniParam;

NuPrimaryGeneratorAction::NuPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
    G4int nofParticles = 1;
    fParticleGun  = new G4ParticleGun(nofParticles);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("proton");
    fParticleGun->SetParticleDefinition(particle);
}

NuPrimaryGeneratorAction::~NuPrimaryGeneratorAction() { delete fParticleGun; }

void NuPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
#if true

    G4ThreeVector position = G4RandomDirection()*2.5*695700*km;
    fParticleGun->SetParticlePosition(position);

    G4ThreeVector momentumDirection = G4RandomDirection();
    if (position*momentumDirection >= 0) { momentumDirection = -momentumDirection; }
    fParticleGun->SetParticleMomentumDirection(momentumDirection);
    
    fParticleGun->SetParticleEnergy(1*TeV);

    fParticleGun->GeneratePrimaryVertex(anEvent);

#else

    G4AutoLock lock(&DetLock);
    x_and_p = iniParam.back();
    iniParam.pop_back();
    lock.unlock();

    fParticleGun->SetParticlePosition(G4ThreeVector(x_and_p[0], x_and_p[1], x_and_p[2]));
    fParticleGun->SetParticleMomentum(G4ThreeVector(x_and_p[3], x_and_p[4], x_and_p[5]));
    fParticleGun->GeneratePrimaryVertex(anEvent);

#endif
}
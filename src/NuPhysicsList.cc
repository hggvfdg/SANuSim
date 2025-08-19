#include "NuPhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4HadronPhysicsCRMC.hh"
#include "G4ProductionCutsTable.hh"
#include "G4SystemOfUnits.hh"


NuPhysicsList::NuPhysicsList() 
: G4VModularPhysicsList()
{
    // EM physics
    RegisterPhysics(new G4EmStandardPhysics());  

    // Synchroton Radiation & GN Physics
    RegisterPhysics(new G4EmExtraPhysics());

    // Decay physics
    RegisterPhysics(new G4DecayPhysics());
    
    // Hadronic scattering physics
    RegisterPhysics(new G4HadronElasticPhysics());

    // Hadron physics
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT());

    // Stopping Physics
    RegisterPhysics(new G4StoppingPhysics());

    // Ion Physics
    RegisterPhysics(new G4IonPhysics());
    
    // Neutron tracking cut
    RegisterPhysics(new G4NeutronTrackingCut());

    // Radioactive decay
    RegisterPhysics(new G4RadioactiveDecayPhysics());

    // CRMC hadronic models
    G4HadronPhysicsCRMC* crmc = new G4HadronPhysicsCRMC(6);
    crmc->SetEnergyThreshold(100*TeV);
    RegisterPhysics(crmc);
}

void NuPhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(0.01*GeV,10.*PeV);
}



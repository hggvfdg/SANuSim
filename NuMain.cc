#include "G4MTRunManager.hh"
#include "NuDetectorConstruction.hh"
#include "NuPhysicsList.hh"
#include "NuActionInitialization.hh"
#include "G4UImanager.hh"
#include <iostream>

#include <vector>
#include "G4AutoLock.hh"
#include "G4RootAnalysisReader.hh"
#include "NuPrimaryGeneratorAction.hh"

namespace{ G4Mutex DetLock = G4MUTEX_INITIALIZER; }

int main() 
{
    G4MTRunManager* runManager = new G4MTRunManager();
    runManager->SetNumberOfThreads(14);

	runManager->SetUserInitialization(new NuDetectorConstruction());
	runManager->SetUserInitialization(new NuPhysicsList());
	runManager->SetUserInitialization(new NuActionInitialization());

	G4UImanager* UImanager = G4UImanager::GetUIpointer();	// Set verbose level
	UImanager->ApplyCommand("/process/had/verbose 0");
	UImanager->ApplyCommand("/process/em/verbose 0");
	UImanager->ApplyCommand("/material/verbose 0");
	UImanager->ApplyCommand("/cuts/verbose 0");
	UImanager->ApplyCommand("/run/verbose 0");
	UImanager->ApplyCommand("/tracking/verbose 0");

	runManager->Initialize();

	int numberOfEvent = 100000;
    runManager->BeamOn(numberOfEvent);

	delete runManager;
}
#include "G4MTRunManager.hh"
#include "NuDetectorConstruction.hh"
#include "NuPhysicsList.hh"
#include "NuActionInitialization.hh"
#include "G4UImanager.hh"

#include "G4LogicalVolumeStore.hh"

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

	std::cout << "Pause\n";
	std::cin.get();

	int numberOfEvent = 100000;
    runManager->BeamOn(numberOfEvent);

	delete runManager;
}
#include "Randomize.hh"
#include "G4MTRunManager.hh"
#include "NuDetectorConstruction.hh"
#include "NuPhysicsList.hh"
#include "NuActionInitialization.hh"
#include "G4UImanager.hh"
#include <iostream>

int main() 
{
	const auto t_start = std::chrono::high_resolution_clock::now();
	G4Random::setTheEngine(new CLHEP::RanluxEngine);
  	G4Random::setTheSeed(time(0),3);

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
	UImanager->ApplyCommand("/run/verbose 1");
	UImanager->ApplyCommand("/event/verbose 0");
	UImanager->ApplyCommand("/tracking/verbose 0");

	runManager->Initialize();

	int numberOfEvent = 70000;
    runManager->BeamOn(numberOfEvent);

	delete runManager;

	const auto t_end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double, std::milli> t_total = t_end - t_start;
	std::cout << "ToTal time: " << t_total.count()/1000 << " s\n";
}
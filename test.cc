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

	int numberOfEvent = 10000;
#if false
	G4AutoLock lock(&DetLock);
	G4double x, y, z, p_x, p_y, p_z;

	auto analysisReader = G4RootAnalysisReader::Instance();
    analysisReader->SetVerboseLevel(0);
    analysisReader->SetFileName("/home/jimmyma/Software/G4SOLAR/SANuSim/results/100k_100GeV/100k_100GeV_CUT.root");
    G4int ntupleId = analysisReader->GetNtuple("gamma");
	analysisReader->SetNtupleDColumn("x", x);
	analysisReader->SetNtupleDColumn("y", y);
	analysisReader->SetNtupleDColumn("z", z);
	analysisReader->SetNtupleDColumn("p_x", p_x);
	analysisReader->SetNtupleDColumn("p_y", p_y);
	analysisReader->SetNtupleDColumn("p_z", p_z);

	std::cout << "ntupleId: " << ntupleId << "\n";
	std::cin.get();

	while ( analysisReader->GetNtupleRow(ntupleId) )
	{
		++numberOfEvent;
		NuPrimaryGeneratorAction::iniParam.push_back({x, y, z, p_x, p_y, p_z});
	}

	lock.unlock();
	std::cout << "numberOfEvent: " << numberOfEvent << "\n";
	std::cin.get();
#endif
    runManager->BeamOn(numberOfEvent);

	delete runManager;
}
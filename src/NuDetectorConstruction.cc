#include "NuDetectorConstruction.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4AutoLock.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4RootAnalysisReader.hh"
#include "G4Exception.hh"

namespace{ G4Mutex DetLock = G4MUTEX_INITIALIZER; }

G4VPhysicalVolume* NuDetectorConstruction::Construct()
{
    // Parameters to construct the geometry of the sun
    const G4double R_sun = 695700*km;   // Outer radius of the photosphere 
    const G4double H_bot = 2000*km;
    const G4double H_top = 1.5*R_sun;

    // Parameters for the World volume
    const G4int world_z = 1;
    const G4double world_a = 1.008*g/mole;
    const G4double world_density = 1e-25*g/cm3;
    const G4double world_temp = 2.73*kelvin;
    const G4double world_pressure = 3e-18*pascal;
    const G4double world_rmin = R_sun - H_bot - 1.*km; // Inner radius of the world volume
    const G4double world_rmax = R_sun + H_top + 1.*km; // Outer radius of the world volume

    // Parameters for elements
    const G4int zH = 1;
    const G4int zHe = 2;
    const G4int zC = 6;
    const G4int zO = 8;
    const G4double aH = 1.01*g/mole;
    const G4double aHe = 4.002*g/mole;
    const G4double aC = 12.0107*g/mole;
    const G4double aO = 15.999*g/mole;
    const G4double fH = 0.74506678;
    const G4double fHe = 0.24413242;
    const G4double fC = 0.00287807;
    const G4double fO = 0.00792273;

    // Solar elements
    G4Element* elH = new G4Element("Hydrogen", "H" , zH, aH);
    G4Element* elHe = new G4Element("Helium", "He" , zHe, aHe);
    G4Element* elC = new G4Element("Carbon", "C" , zC, aC);
    G4Element* elO = new G4Element("Oxygen", "O" , zO, aO);
    G4int nComponents = 4;
    
    // Construct the world volume
    G4Material* world_mat = new G4Material("world_mat", world_z, world_a, world_density, kStateGas, world_temp, world_pressure);
    G4VSolid* solidWorld = new G4Sphere("World", world_rmin, world_rmax, 0*deg, 360*deg, 0*deg, 180*deg);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "World", 0, false, 0, true);

    // Construct the solar layers
	G4AutoLock lock(&DetLock);  // Ensure only one thread is accessing the file

    auto analysisReader = G4RootAnalysisReader::Instance();
    analysisReader->SetVerboseLevel(0);
    analysisReader->SetFileName("/home/jimmyma/Software/SANuSim/SunLayers.root");
    G4int ntupleId = analysisReader->GetNtuple("LayerParameters");

    G4double InR, OutR, Rho, P, T;
    analysisReader->SetNtupleDColumn("InnerRadius", InR);
    analysisReader->SetNtupleDColumn("OuterRadius", OutR);
    analysisReader->SetNtupleDColumn("Density", Rho);
    analysisReader->SetNtupleDColumn("Pressure", P);
    analysisReader->SetNtupleDColumn("Temperature", T);

    G4int nofRow = 0;
    while ( analysisReader->GetNtupleRow() ) 
    {
        G4Material* material = new G4Material(std::to_string(nofRow), Rho*g/cm3, nComponents, kStateGas, T*kelvin, P*pascal);
		material->AddElement(elH, fH);
		material->AddElement(elHe, fHe);
		material->AddElement(elC, fC);
		material->AddElement(elO, fO);

		// Construct Logic and Physical Volume of the layer
		G4Sphere* solid = new G4Sphere(std::to_string(nofRow), InR*km, OutR*km, 0*deg, 360*deg, 0*deg, 180*deg);
		G4LogicalVolume* LV = new G4LogicalVolume(solid, material, std::to_string(nofRow));
		G4VPhysicalVolume* PV = new G4PVPlacement(0, G4ThreeVector(0,0,0), LV, std::to_string(nofRow), logicWorld, false, nofRow, true);
        ++nofRow;
    }
    analysisReader->CloseFiles();

    lock.unlock();

	return physWorld;
}

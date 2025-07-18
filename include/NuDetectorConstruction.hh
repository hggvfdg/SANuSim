#pragma once

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"

class NuDetectorConstruction : public G4VUserDetectorConstruction 
{
public:

    NuDetectorConstruction() = default;
    ~NuDetectorConstruction() = default;

    G4VPhysicalVolume* Construct() override;
};
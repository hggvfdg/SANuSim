#pragma once

#include "G4UserStackingAction.hh"
#include "G4Types.hh"

class NuStackingAction : public G4UserStackingAction
{
public:

    NuStackingAction();
    ~NuStackingAction() = default;

    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*) override;

private:

    const G4int NuNtuplePDG[6];
};
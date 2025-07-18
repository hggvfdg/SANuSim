#pragma once

#include "G4UserStackingAction.hh"

class NuStackingAction : public G4UserStackingAction
{
public:

    NuStackingAction() = default;
    ~NuStackingAction() = default;

    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*) override;
};
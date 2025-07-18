#include "NuActionInitialization.hh"

#include "NuRunAction.hh"
#include "NuPrimaryGeneratorAction.hh"
#include "NuStackingAction.hh"

void NuActionInitialization::BuildForMaster() const
{
    SetUserAction(new NuRunAction());
}

void NuActionInitialization::Build() const
{
    SetUserAction(new NuPrimaryGeneratorAction());
    SetUserAction(new NuRunAction());
    SetUserAction(new NuStackingAction());
}
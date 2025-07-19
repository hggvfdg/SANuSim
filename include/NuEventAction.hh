#include "G4UserEventAction.hh"

class NuEventAction : public G4UserEventAction
{
public:

    NuEventAction = default;
    ~NuEventAction = default

    void EndOfEventAction(const G4Event*) override;
};
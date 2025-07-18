#pragma once

#include "G4VUserActionInitialization.hh"

class NuActionInitialization : public G4VUserActionInitialization
{
public:

	NuActionInitialization() = default;
	~NuActionInitialization() = default;

  	void BuildForMaster() const;
  	void Build() const;
};
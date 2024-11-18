#ifndef ActionInitialization_HH
#define ActionInitialization_HH

#include "G4VUserActionInitialization.hh"

#include "PrimaryGenerator.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"




class ActionInitialization: public G4VUserActionInitialization
{
public:
	ActionInitialization();
	~ActionInitialization();

	void SetPrimaryParticleEnergy(G4double);

	

	virtual void Build() const;
	virtual void BuildForMaster() const;



private:
	G4double fPrimaryParticleEnergy;

};

#endif



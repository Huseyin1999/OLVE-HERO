#ifndef SteppingAction_HH
#define SteppingAction_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "EventAction.hh"
#include <map>
#include "G4VProcess.hh"

class SteppingAction : public G4UserSteppingAction
{
public:
	SteppingAction(EventAction* eventaction);
	~SteppingAction();

	virtual void UserSteppingAction(const G4Step*);

private:
	EventAction* fEventAction;
	

	
};
#endif



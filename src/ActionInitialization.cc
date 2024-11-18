#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::SetPrimaryParticleEnergy(G4double PrimaryParticleEnergy)
{
	fPrimaryParticleEnergy = PrimaryParticleEnergy;
	//G4cout << G4endl << "fPrimaryParticleEnergy in TGFActionInitialization was set to " << fPrimaryParticleEnergy << G4endl << G4endl;
}





void ActionInitialization::BuildForMaster() const
{
    RunAction* runAction = new RunAction();
    SetUserAction(runAction);

}

void ActionInitialization::Build() const
{
	PrimaryGenerator* generator = new PrimaryGenerator();
	generator->SetPrimaryEnergy(fPrimaryParticleEnergy);
	SetUserAction(generator);

	RunAction* runAction = new RunAction();
	SetUserAction(runAction);

	EventAction* eventAction = new EventAction(runAction);
	SetUserAction(eventAction);

	SteppingAction* steppingAction = new SteppingAction(eventAction);
    SetUserAction(steppingAction);
}



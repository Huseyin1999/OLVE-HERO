#ifndef RunAction_HH
#define RunAction_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"

class RunAction: public G4UserRunAction
{
public:
	RunAction();
	~RunAction();


	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);

};

#endif




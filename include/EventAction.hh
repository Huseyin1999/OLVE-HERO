#ifndef EventAction_HH
#define EventAction_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

#include "RunAction.hh"



class EventAction : public G4UserEventAction
{
public:
	EventAction(RunAction*);
	~EventAction();


	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);


	void AddScinCount() 
	{
		ScinCount += 1; 
	}
	G4int GetScinCount()
	{
		return ScinCount;
	}
	void AddElectronCount()
	{
		ElectronCount++;
	}
	G4int GetElectronCount()
	{
		return ElectronCount;
	}

	std::map<int, std::vector<double>> fScintInfo;


private:
	G4int ScinCount;
	G4int ElectronCount;
};

#endif



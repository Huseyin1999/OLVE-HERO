#include "EventAction.hh"

EventAction::EventAction(RunAction*)
{
    fScintInfo = { {0, {}}, {1, {}},};
}
EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* ev)
{
    ScinCount = 0;
    ElectronCount = 0;

    fScintInfo = { {0, {}}, {1, {}},};
}

void EventAction::EndOfEventAction(const G4Event* ev)
{
    G4int n_event = ev->GetEventID();
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	G4cout << n_event << "End of event "  <<  " ,  ScinCount  =  " << ScinCount<< G4endl << G4endl;

	man->FillNtupleDColumn(0, 0, ScinCount);
	man->AddNtupleRow(0);


    int Scint_info_size = fScintInfo[0].size();
    for (G4int i = 0; i < Scint_info_size; i++)
    {
        man->FillNtupleDColumn(1, 0, fScintInfo[0][i]);     
	    man->FillNtupleIColumn(1, 1, fScintInfo[1][i]);
	    man->FillNtupleIColumn(1, 2, n_event);
        man->AddNtupleRow(1);
    }


}



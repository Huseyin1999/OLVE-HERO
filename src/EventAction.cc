#include "EventAction.hh"

EventAction::EventAction(RunAction*)
{
    //fScintInfo = { {0, {}}, {1, {}}, {2, {}}, {3, {}}, {4, {}}, {5, {}}, {6, {}}, {7, {}},};
    fScintInfo = { {0, {}}, {1, {}}, };
    fAlphaInfo = { {0, {}}, };
}
EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* ev)
{
    ScinCount = 0;
    Dep_Energy = 0.0;
    ElectronCount = 0;

    //fScintInfo = { {0, {}}, {1, {}}, {2, {}}, {3, {}}, {4, {}}, {5, {}}, {6, {}}, {7, {}},};
    fScintInfo = { {0, {}}, {1, {}}, };
    fAlphaInfo = { {0, {}}, };

}

void EventAction::EndOfEventAction(const G4Event* ev)
{
    G4cout << "END OF EVENT" << G4endl;
    G4int n_event = ev->GetEventID();
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	G4cout << n_event << "End of event "  <<  " ,  ScinCount  =  " << ScinCount<< G4endl << G4endl;

	man->FillNtupleIColumn(0, 0, ScinCount);
	man->FillNtupleDColumn(0, 1, Dep_Energy);
	man->AddNtupleRow(0);


    int Scint_info_size = fScintInfo[0].size();
    int Alpha_info_size = fAlphaInfo[0].size();

    for (G4int i = 0; i < Scint_info_size; i++)
    {
        // Writing all data
        /*
        man->FillNtupleDColumn(1, 0, fScintInfo[0][i]);     
	    man->FillNtupleDColumn(1, 1, fScintInfo[1][i]);
	    man->FillNtupleDColumn(1, 2, fScintInfo[2][i]);
	    man->FillNtupleDColumn(1, 3, fScintInfo[3][i]);
	    man->FillNtupleDColumn(1, 4, fScintInfo[4][i]);
	    man->FillNtupleDColumn(1, 5, fScintInfo[5][i]);
	    man->FillNtupleDColumn(1, 6, fScintInfo[6][i]);
	    man->FillNtupleIColumn(1, 7, fScintInfo[7][i]);
	    man->FillNtupleIColumn(1, 8, n_event);
        man->AddNtupleRow(1);
        */
        man->FillNtupleDColumn(1, 0, fScintInfo[0][i]);  
        man->FillNtupleIColumn(1, 1, fScintInfo[1][i]);
	    man->FillNtupleIColumn(1, 2, n_event);
        man->AddNtupleRow(1);
    }

    for (G4int i = 0; i < Alpha_info_size; i++)
    {
        man->FillNtupleDColumn(2, 0, fAlphaInfo[0][i]);
        man->AddNtupleRow(2);
    }

}



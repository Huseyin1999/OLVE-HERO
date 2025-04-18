#include "RunAction.hh"

RunAction::RunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->SetNtupleMerging(true);
	man->CreateNtuple("ScintillationLight", "ScintillationLight");
	man->CreateNtupleIColumn("ScintillationPhotonsCount");
	man->CreateNtupleDColumn("DepEnergy");
	man->FinishNtuple(0);

	man->CreateNtuple("TimeScintillation", "TimeScintillation");
	man->CreateNtupleDColumn("Time");
	/*
	man->CreateNtupleDColumn("X");
	man->CreateNtupleDColumn("Y");
	man->CreateNtupleDColumn("Z");
	man->CreateNtupleDColumn("Px");
	man->CreateNtupleDColumn("Py");
	man->CreateNtupleDColumn("Pz");
	*/

	man->CreateNtupleIColumn("FiberID");
	man->CreateNtupleIColumn("EventID");
	man->FinishNtuple(1);

	man->CreateNtuple("TimeAlpha", "TimeAlpha");
	man->CreateNtupleDColumn("Time");
	man->FinishNtuple(2);

}


RunAction::~RunAction()
{

}


void RunAction::BeginOfRunAction(const G4Run* run)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
	G4int runID = run->GetRunID();
	std::stringstream strRunID;
	strRunID << runID;
	man->OpenFile("output" + strRunID.str() + ".root");
}

void RunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->Write();
	man->CloseFile();
}




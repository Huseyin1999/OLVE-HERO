#include "SteppingAction.hh"


SteppingAction::SteppingAction(EventAction* eventAction)
{
	fEventAction = eventAction;
}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step *aStep)
{
	G4Track* track = aStep->GetTrack();
	
	const G4ParticleDefinition* particleDefinition = track->GetParticleDefinition();
	const G4String& particlename = particleDefinition->GetParticleName();	


	G4VPhysicalVolume * PhysVol	= track->GetVolume();
	G4int VolN = PhysVol->GetCopyNo(); 
	const G4String & PhysName = PhysVol->GetName();
	const G4String LogicalVolName = PhysVol->GetLogicalVolume()->GetName();
	//G4LogicalVolume *LogicVol = PhysVol->GetMotherLogical();
	//G4String LogicName = LogicVol->GetName();
	
	G4ThreeVector ObjectTranslation = PhysVol->GetTranslation();
	
	//const G4VProcess * CreatorProcess = track->GetCreatorProcess();
	//const G4String ProcessName = CreatorProcess->GetProcessName();
	//auto ProcessName = CreatorProcess->GetProcessName();

	//G4ProcessType ProcessType = CreatorProcess->GetProcessType();


	G4double pdgcharge = particleDefinition->GetPDGCharge();
	G4int pdg = particleDefinition->GetPDGEncoding();

	G4int CurrentStepNumber = track->GetCurrentStepNumber();
	G4int track_id = track->GetTrackID();
	G4double globalTime = track->GetGlobalTime();


    // CREATOR PROCESS
	G4String CreatorProcess;
	if (track_id > 1)	CreatorProcess = aStep -> GetTrack() -> GetCreatorProcess() -> GetProcessName();

	const G4DynamicParticle* dParticle = track->GetDynamicParticle();
	//G4double depositEnergy = aStep->GetTotalEnergyDeposit();
	G4double kinEnergy = dParticle->GetKineticEnergy();
	G4double Energy = dParticle->GetTotalEnergy();

	G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
	G4ThreeVector positionParticle = preStepPoint->GetPosition();

	G4double trackLength = track->GetTrackLength();
	G4double stepLength = track->GetStepLength();
	
/*
//#################################################################################### 	
// BORN  
	if (particlename == "opticalphoton" && CurrentStepNumber == 1) 
	{
		fEventAction->AddScinCount();
		fEventAction->fScintInfo[0].push_back(globalTime); //nanoseconds
		fEventAction->fScintInfo[1].push_back(VolN);
		//track->SetTrackStatus(fStopAndKill);
		//return;
	}
*/
//#################################################################################### 	
// HIT IN FIBER 
	if (LogicalVolName == "flogicFiber" && particlename == "opticalphoton") 
	{
		fEventAction->AddScinCount();
		fEventAction->fScintInfo[0].push_back(globalTime); //nanoseconds
		fEventAction->fScintInfo[1].push_back(VolN);
		track->SetTrackStatus(fStopAndKill);
		return;
	}



//#################################################################################### 	
	// All steps info
	/*
	if (pdg == 11 && CurrentStepNumber == 1) 
	{
		fEventAction->AddElectronCount();
	}
	G4int ElectronCount = fEventAction->GetElectronCount();
	if (ElectronCount % 1000 == 0)
	{
		G4cout << ElectronCount << ", CreatorProcess: " << CreatorProcess << G4endl;
	}
	*/
//#################################################################################### 	
	
	/*
	if (CurrentStepNumber == 1)
	{
		G4cout << "track_id: " << track_id << ", energy: " << kinEnergy << G4endl;	
	}
	*/	
	
	/*****************************************************/
	// kill the particle

	if (pdgcharge != 0 && kinEnergy / eV < 6.)
	{
		track->SetTrackStatus(fStopAndKill);
		return;
	}
	
	if (particlename == "opticalphoton")
	{
		if (aStep->IsFirstStepInVolume())
		{
			if (LogicalVolName =="logicCu" || LogicalVolName == "logicPb" || LogicalVolName == "flogicWorld")
			track->SetTrackStatus(fStopAndKill);
			return;
		}
	}
	/*****************************************************/
}





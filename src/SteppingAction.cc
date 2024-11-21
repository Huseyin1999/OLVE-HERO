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

	G4int track_id = track->GetTrackID();

	const G4ParticleDefinition* particleDefinition = track->GetParticleDefinition();
	const G4String& particlename = particleDefinition->GetParticleName();	


	//G4VPhysicalVolume * PhysVol	= track->GetVolume();
/********************************************************************************************** */
	if (track->GetTrackStatus() == 2)
	{
		return;
	}
	G4VPhysicalVolume * PhysVol	= track->GetNextVolume();
	G4int VolN = PhysVol->GetCopyNo(); 
	const G4String & PhysName = PhysVol->GetName();
	const G4String LogicalVolName = PhysVol->GetLogicalVolume()->GetName();
/********************************************************************************************** */



	//G4LogicalVolume *LogicVol = PhysVol->GetMotherLogical();
	//G4String LogicName = LogicVol->GetName();

	G4double pdgcharge = particleDefinition->GetPDGCharge();
	G4int pdg = particleDefinition->GetPDGEncoding();

	G4int CurrentStepNumber = track->GetCurrentStepNumber();
	
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
/*
	if (track_id != 1)
	{
		
	}
*/
	

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

	if (LogicalVolName == "flogicFiber" && particlename == "opticalphoton") // 711031       track_id == 711031
	{
		fEventAction->AddScinCount();
		//G4cout << "prestep_name: " << prestep_name << ", poststep_name: " << poststep_name << ", track_id: " << track_id << ", CurrentStepNumber: " << CurrentStepNumber << ", LogicalVolName: " << LogicalVolName << ", particlename: " << particlename << ", pdg: " << pdg << ", PhysName: " << PhysName << ", nextPhysName: " << nextPhysName << ", CreatorProcess: " << CreatorProcess << G4endl;
		//G4cout << "particlename  = " << particlename << " , PhysVol = " << VolN << " , track_id = " << track_id << G4endl<< G4endl;
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





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


	G4VPhysicalVolume * PhysVolNorm	= track->GetVolume();
/********************************************************************************************** */
	/*
	if (track->GetTrackStatus() == 2)
	{
		//G4cout << "PhysVolNorm  = " << PhysVolNorm->GetName() << " , particlename = " << particlename <<G4endl;
		return;
	}
	*/
	G4VPhysicalVolume * PhysVol	= track->GetVolume();
	//G4VPhysicalVolume * PhysVol	= track->GetNextVolume();
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
	G4double depositEnergy = aStep->GetTotalEnergyDeposit();
	G4double kinEnergy = dParticle->GetKineticEnergy();
	G4double Energy = dParticle->GetTotalEnergy();

	G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint* postStepPoint = aStep->GetPostStepPoint();


	G4ThreeVector positionParticle = postStepPoint->GetPosition();
	G4ThreeVector MomentumParticle = postStepPoint->GetMomentum();


	G4double trackLength = track->GetTrackLength();
	G4double stepLength = track->GetStepLength();
	

//#################################################################################### 	
//   
	if (pdgcharge != 0)
	{
		if (LogicalVolName !="logicCu" && LogicalVolName != "logicPb" && LogicalVolName != "flogicWorld")
		{
			fEventAction->AddDep_Energy(depositEnergy / MeV);
		}
	}



//#################################################################################### 	
// HIT IN FIBER 

	
	if (LogicalVolName == "flogicFiber" && particlename == "opticalphoton") //
	{
		fEventAction->AddScinCount();
		
		//fEventAction->fScintInfo[0].push_back(globalTime); //nanoseconds
		/*
		fEventAction->fScintInfo[1].push_back(positionParticle[0]);
		fEventAction->fScintInfo[2].push_back(positionParticle[1]);
		fEventAction->fScintInfo[3].push_back(positionParticle[2]);
		fEventAction->fScintInfo[4].push_back(MomentumParticle[0]);
		fEventAction->fScintInfo[5].push_back(MomentumParticle[1]);
		fEventAction->fScintInfo[6].push_back(MomentumParticle[2]);
		fEventAction->fScintInfo[7].push_back(VolN);
		*/
		fEventAction->fScintInfo[0].push_back(globalTime); //nanoseconds
		fEventAction->fScintInfo[1].push_back(VolN);

		track->SetTrackStatus(fStopAndKill);
		return;
	}

	if (pdg == 1000020040)
	{
		fEventAction->fAlphaInfo[0].push_back(globalTime); //nanoseconds
	}



//#################################################################################### 	

//#################################################################################### 	
	

	
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





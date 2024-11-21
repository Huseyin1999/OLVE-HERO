#include "PrimaryGenerator.hh"

PrimaryGenerator::PrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);
}

PrimaryGenerator::~PrimaryGenerator()
{
	delete fParticleGun;
}

void PrimaryGenerator::SetPrimaryEnergy(G4double PrimaryEnergy)
{
	fPrimaryEnergy = PrimaryEnergy;
	//G4cout << G4endl << "fPrimaryEnergy in TGFPrimaryGenerator was set to " << fPrimaryEnergy << G4endl << G4endl;
	
}	


void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{

	
	//G4cout << G4endl << "fPrimaryEnergy in TGFPrimaryGenerator was set to " << fPrimaryEnergy*GeV << G4endl << G4endl;

	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4IonTable* Iontable = particleTable->GetIonTable();
	G4ParticleDefinition* particle = particleTable->FindParticle(11);  // electron
	//G4ParticleDefinition* particle = particleTable->FindParticle(2212);  // proton


	G4ThreeVector pos(0.*m,0., -100.*mm); 
    G4ThreeVector mom(0., 0., 1.);

    //G4double PrimaryEnergy = 1*GeV;

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(fPrimaryEnergy*GeV);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}




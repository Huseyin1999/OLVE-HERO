#include "DetectorConstruction.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) :
G4VSensitiveDetector(name)
{
	//inelastic = false;
}
MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory*ROhist)
{





	return true;
}
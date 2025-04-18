#ifndef DetectorConstruction_HH
#define DetectorConstruction_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "tools/colors"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "SensitiveDetector.hh"
#include <math.h>
#include "G4Tubs.hh"



class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	~DetectorConstruction();

	virtual G4VPhysicalVolume *Construct();

	void CreateCalorimeter();
	void CreateAbsorber();
	void CreateFibers();
	void CreateTarget();

	//const static G4int n_layers_withB= 10;
	const static G4int n_layers_withB= 80;
	const static G4int n_layers_withoutB= 20;

private:
	G4LogicalVolume *flogicWorld;
	G4LogicalVolume* flogicBorScin[n_layers_withB][16];
    G4LogicalVolume* flogicPlastScin[n_layers_withoutB][16];
    G4LogicalVolume* flogicFiber;


	

	G4Material *Fiber;
	G4Element *C, *H, *O;

	virtual void ConstructSDandField();

	G4NistManager *nist = G4NistManager::Instance();

};

#endif




#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
	

	G4Material *WorldMat = new G4Material("WorldMat", 1.29e-3 * g/cm3, 3);     
	WorldMat->AddElement(nist->FindOrBuildElement("N"), 75.5 * perCent);
	WorldMat->AddElement(nist->FindOrBuildElement("O"), 23.2 * perCent);
	WorldMat->AddElement(nist->FindOrBuildElement("Ar"), 1.28 * perCent);



	//*******************************************************************************
	// world mat + rindex
	G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
	G4double rindexWorld[2] = {1.000, 1.000}; 

	G4MaterialPropertiesTable *mptworld = new G4MaterialPropertiesTable();
    mptworld -> AddProperty("RINDEX", energy, rindexWorld, 2);
    WorldMat -> SetMaterialPropertiesTable(mptworld);
	//*******************************************************************************


	// World
	G4Box* solidWorld = new G4Box("solidWorld", 400 * mm, 400 * mm, 3000 * mm);
	flogicWorld = new G4LogicalVolume(solidWorld, WorldMat, "flogicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), flogicWorld, "physWorld", 0, false, 0, true);
	
	CreateCalorimeter();
	CreateAbsorber();
	CreateFibers();

	return physWorld;
}

void DetectorConstruction::CreateCalorimeter()
{
	//*******************************************************************************
		//Materials of scintillator 
	//With B
	G4Material *BorScinmat = new G4Material("BorScinmat", 0.98 * g / cm3, 3);
    BorScinmat->AddElement(nist->FindOrBuildElement("C"), 88.26 * perCent);
    BorScinmat->AddElement(nist->FindOrBuildElement("H"), 7.74 * perCent);
    BorScinmat->AddElement(nist->FindOrBuildElement("B"), 4.0 * perCent);
    G4cout <<"Bor          Rad length  = " << BorScinmat->GetRadlen() << "           Bor     nuclear = " << BorScinmat->GetNuclearInterLength () <<G4endl;

	G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
	G4double rindexScin[2] = {1.5, 1.5};
	G4double fraction[2] = {1.0, 1.0};

	G4MaterialPropertiesTable *mptScin = new G4MaterialPropertiesTable();

    mptScin->AddProperty("SCINTILLATIONCOMPONENT1", energy, fraction, 2);
	mptScin->AddProperty("RINDEX", energy, rindexScin, 2);
    mptScin->AddConstProperty("SCINTILLATIONYIELD",10./keV);
    mptScin->AddConstProperty("RESOLUTIONSCALE",1.0);
    mptScin->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 250.*ns);
    mptScin->AddConstProperty("SCINTILLATIONYIELD1",1.);
    BorScinmat->SetMaterialPropertiesTable(mptScin);

	G4Box *solidBorScin = new G4Box("solidBorScin", 6.25*mm, 100.*mm, 3.75*mm);
	
	G4cout << "RARARARARARARARARARARRRRRRRRRRRRRRRRR" <<G4endl;

	for (int i = 0; i < n_layers_withB; i++)
	{
		for (int j = 0; j < 16; j++) 
        {
            flogicBorScin[i][j] = new G4LogicalVolume(solidBorScin, BorScinmat, "flogicBorScin");
			G4VisAttributes * calTubeVisAtt4 = new G4VisAttributes(G4Colour(0.,1.,0.)); 	// Instantiation of a set of visualization attributes with cyan colour
			flogicBorScin[i][j]->SetVisAttributes(calTubeVisAtt4);
		}
	}

	//Without B
	G4Material* Polyvinyltoluene = new G4Material("Polyvinyltoluene", 0.92 * g / cm3, 2); 
    Polyvinyltoluene->AddElement(nist->FindOrBuildElement("C"), 85.6 * perCent);
    Polyvinyltoluene->AddElement(nist->FindOrBuildElement("H"), 14.4 * perCent);
    G4cout <<"Plast         Rad length  = " << Polyvinyltoluene->GetRadlen() << "          Plast    nuclear = " << Polyvinyltoluene->GetNuclearInterLength () <<G4endl;
	
	//RINDEX
	Polyvinyltoluene->SetMaterialPropertiesTable(mptScin);



	G4Box *solidPlastScin = new G4Box("solidPlastScin", 6.25*mm, 100.*mm, 3.75*mm);
	
		for (int i = 0; i < n_layers_withoutB; i++)
	{
		for (int j = 0; j < 16; j++) 
        {
            	//flogicPlastScin[i][j] = new G4LogicalVolume(solidPlastScin, BorScinmat, "flogicPlastScin");
            	flogicPlastScin[i][j] = new G4LogicalVolume(solidPlastScin, Polyvinyltoluene, "flogicPlastScin");
		}
	}
	
	//*******************************************************************************
	//Scintillator Placement 

	double angle = 90.;  // rotation angle

	G4VPhysicalVolume *physBorScin[n_layers_withB][16];  // 1-Количество слоёв, 2-количество стрипов в слое
    G4VPhysicalVolume *physPlastScin[n_layers_withoutB][16];  // 1-Количество слоёв, 2-количество стрипов в слое
	//*******************************************************************************
	//strips without B
	for (int i = 0; i < n_layers_withoutB; i++)
	{
		G4RotationMatrix * RotMat = new G4RotationMatrix();
        RotMat -> rotate((angle * i) *deg, G4ThreeVector(0., 0., 1.));
        RotMat -> invert();
		for (int j = 0; j < 16; j++) 
        {
            physPlastScin[i][j] = new G4PVPlacement(RotMat, G4ThreeVector(((-93.75 + j * 12.5)*(cos ( angle*i * M_PI / 180.0 )))*mm, ((-93.75 + j * 12.5)*(sin ( angle*i * M_PI / 180.0 )))*mm, (3.75 + i * 25.0)*mm), flogicPlastScin[i][j], "physPlastScin " + std::to_string(i*16+j), flogicWorld, false, i*16+j, true);
        }
	}
	//*******************************************************************************
	//strips with B

	for (int i = 0; i < n_layers_withB; i++)
    {
        G4RotationMatrix * RotMat = new G4RotationMatrix();
        RotMat -> rotate((angle * i) *deg, G4ThreeVector(0., 0., 1.));
        RotMat -> invert();
        for (int j = 0; j < 16; j++) 
        {
            physBorScin[i][j] = new G4PVPlacement(RotMat, G4ThreeVector(((-93.75 + j * 12.5)*(cos ( angle*i * M_PI / 180.0 )))*mm, ((-93.75 + j * 12.5)*(sin ( angle*i * M_PI / 180.0 )))*mm, (503.75 + i * 25.0)*mm), flogicBorScin[i][j], "physBorScin" + std::to_string(i*16+j), flogicWorld, false, i*16+j, true);
        }
    }

	
}

void DetectorConstruction ::CreateAbsorber()
{

	G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
	G4double rindexPb[2] = {2.67, 2.67};
	G4double rindexCu[2] = {1.25, 1.25};
	G4double fraction[2] = {1.0, 1.0};
	//*******************************************************************************
	//Pb absorber
	G4Material* Pb = new G4Material("Pb", 11.35 * g / cm3, 1);
    Pb->AddElement(nist->FindOrBuildElement("Pb"), 100 * perCent);
    G4cout <<"Pb          Rad length  = " << Pb->GetRadlen() << "           Pb     nuclear = " << Pb->GetNuclearInterLength () <<G4endl;

	G4MaterialPropertiesTable *mptPb = new G4MaterialPropertiesTable();
    mptPb -> AddProperty("RINDEX", energy, rindexPb, 2);
    Pb -> SetMaterialPropertiesTable(mptPb);

	G4Box *solidPb = new G4Box("solidPb", 100*mm, 100*mm, 1.5*mm);
    G4LogicalVolume *logicPb = new G4LogicalVolume(solidPb, Pb, "logicPb");
    G4VPhysicalVolume *physPb[n_layers_withB+n_layers_withoutB-1];

	for (int i = 0; i < n_layers_withB+n_layers_withoutB-1; i++) 
    {
    	physPb[i] = new G4PVPlacement(0, G4ThreeVector(0., 0., (9.0 + i * 25.)*mm), logicPb, "physPb" + std::to_string(i), flogicWorld, false, i, true);
    }

	//*******************************************************************************
	//Cu absorber
	G4Material* Cu = new G4Material("Cu", 8.96 * g / cm3, 1);
    Cu->AddElement(nist->FindOrBuildElement("Cu"), 100 * perCent);
    G4cout <<"Cu             Rad length  = " << Cu->GetRadlen() << "     Cu    nuclear = " << Cu->GetNuclearInterLength () <<G4endl;

	G4MaterialPropertiesTable *mptCu = new G4MaterialPropertiesTable();
    mptCu -> AddProperty("RINDEX", energy, rindexCu, 2);
    Cu -> SetMaterialPropertiesTable(mptCu);

	G4Box *solidCu = new G4Box("solidCu", 100*mm, 100*mm, 1.0*mm);
    G4LogicalVolume *logicCu = new G4LogicalVolume(solidCu, Cu, "logicCu");
    G4VisAttributes * calTubeVisAtt2 = new G4VisAttributes(G4Colour(0.5,0.5,0.5)); // Instantiation of a set of visualization attributes with cyan colour
    G4VPhysicalVolume *physCu[n_layers_withB+n_layers_withoutB-1];

    for (int i = 0; i < n_layers_withB+n_layers_withoutB-1; i++) 
    {
        physCu[i] = new G4PVPlacement(0, G4ThreeVector(0., 0., (11.5 + i * 25.)*mm), logicCu, "physCu" + std::to_string(i), flogicWorld, false, i, true);
    }


}

void DetectorConstruction::CreateFibers()
{
	G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double rindexFiber[2] = {1.4905, 1.4905};    
	G4double fraction[2] = {1.0, 1.0};
	//Poly(methyl methacrylate) (PMMA) (C5H8O2)n

	C = nist->FindOrBuildElement("C");
    H = nist->FindOrBuildElement("H");
    O = nist->FindOrBuildElement("O");

    Fiber = new G4Material("Fiber", 1.19*g/cm3, 3);
    Fiber->AddElement(C, 5);
    Fiber->AddElement(H, 8);
    Fiber->AddElement(O, 2);

	G4MaterialPropertiesTable *mptFiber = new G4MaterialPropertiesTable();
    mptFiber->AddProperty("RINDEX", energy, rindexFiber, 2);
	Fiber -> SetMaterialPropertiesTable(mptFiber);



	double angle = 90.;

	G4Tubs *solidFiber = new G4Tubs("solidFiber", 0.0*mm, 0.5*mm, 100.*mm,0.0*deg, 360.0*deg);
    flogicFiber = new G4LogicalVolume(solidFiber, Fiber, "flogicFiber");
	G4VPhysicalVolume * physFiber[n_layers_withB+n_layers_withoutB][16];

	for (int i = 0; i <n_layers_withoutB; i++)
    {
        G4RotationMatrix * RotMat = new G4RotationMatrix();
		if(i%2 == 0)
		{
     	   RotMat -> rotate((angle ) *deg, G4ThreeVector(1., 0., 0.));
		}
		else 
		{
     	   RotMat -> rotate((angle ) *deg, G4ThreeVector(0., 1., 0.));
		}
        RotMat -> rotate((angle * (i)) *deg, G4ThreeVector(0., 0., 1.));
        RotMat -> invert();
        for (int j = 0; j < 16; j++) 
        {
            physFiber[i][j] = new G4PVPlacement(RotMat, G4ThreeVector(0.0*mm, 0.0*mm, 0.0*mm), flogicFiber, "physFiber" + std::to_string(i*16+j), flogicPlastScin[i][j], false, i*16+j, true);
        }
    }

	for (int i = 0; i <n_layers_withB; i++)
    {
        G4RotationMatrix * RotMat = new G4RotationMatrix();
        if(i%2 == 0)
		{
     	   RotMat -> rotate((angle ) *deg, G4ThreeVector(1., 0., 0.));
		}
		else 
		{
     	   RotMat -> rotate((angle ) *deg, G4ThreeVector(0., 1., 0.));
		}
        RotMat -> rotate((angle * (i)) *deg, G4ThreeVector(0., 0., 1.));
        RotMat -> invert();
        for (int j = 0; j < 16; j++) 
        {
            physFiber[n_layers_withoutB + i][j] = new G4PVPlacement(RotMat, G4ThreeVector(0.0*mm, 0.0*mm, 0.0*mm), flogicFiber, "physFiber" + std::to_string(n_layers_withoutB*16 + i*16+j), flogicBorScin[i][j], false,n_layers_withoutB*16+i*16+j, true);
        }
    }

}

void DetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector* sensDet = new MySensitiveDetector("SensitiveDetector");
    flogicFiber->SetSensitiveDetector(sensDet);
}







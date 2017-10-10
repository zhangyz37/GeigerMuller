/**
 * @file /Geiger_Muller/sources/GMDetectorConstruction.cc
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Source code to create and place your experiment. 
 * Latest updates of project can be found in README file.
 **/

#include "GMDetectorConstruction.hh"
#include "G4Material.hh"

/// @brief Constructor of Detector construction

GMDetectorConstruction::GMDetectorConstruction()
: G4VUserDetectorConstruction()
{ }

/// @brief Destructor of Detector construction

GMDetectorConstruction::~GMDetectorConstruction()
{ }

/**
 * @brief Construct function to built objects and frame of reference
 * 
 * @return	Placement of world
 * 
 **/

G4VPhysicalVolume* GMDetectorConstruction::Construct()
{  
  
  G4NistManager* nist = G4NistManager::Instance(); /// Get nist material manager
  G4double density, fractionmass;
  G4int ncomponents;
  G4String name;
   
  
  G4bool checkOverlaps = true; /// Option to switch on/off checking of volumes overlaps

/**
 * ... World ...
 * 
 * @param world_sizeXY 		Size of World in X and Y axis
 * @param world_sizeZ 		Size of World in Z axis
 * @param solidWorld		Geometry of World
 * @param world_mat 		Material of World
 * @param logicWorld		Logical volume of World
 * @param physWorld			Physical volume of World
 * 
 **/
 
  G4double world_sizeXY = 0.6*m;
  G4double world_sizeZ  = 0.6*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  
  G4Box* solidWorld = new G4Box("World",     ///its name
       world_sizeXY, world_sizeXY, world_sizeZ);
      
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
                                   
  G4VPhysicalVolume* physWorld = 
  new G4PVPlacement(0,                     ///no rotation
                      G4ThreeVector(),       ///at (0,0,0)
                      logicWorld,            ///its logical volume
                      "World",               ///its name
                      0,                     ///its mother  volume
                      false,                 ///no boolean operation
                      0,                     ///copy number
                      checkOverlaps);        ///overlaps checking
                     
/**
 * ... Anode ...
 * 
 * @param anode_rmin 		Size of Anode (r min)
 * @param anode_rmax 		Size of Anode (r max)
 * @param anode_len			Size of Andoe (length)
 * @param solidAnode		Geometry of Anode
 * @param anode_mat 		Material of Anode
 * @param logicAnode		Logical volume of Anode
 * 
 **/
 
  G4Material* anode_mat = nist->FindOrBuildMaterial("G4_Al");
  G4ThreeVector anode_pos = G4ThreeVector(0, 0*cm, 13.0*cm);
 
  G4double anode_rmin = 0*cm;
  G4double anode_rmax = 1*mm;
  G4double anode_len  = 6*cm;
  G4double anode_deg = 0*deg;
  G4double anode_deg2 = 360*deg;
       
  G4Tubs* solidAnode = new G4Tubs("Anode", anode_rmin, anode_rmax, 0.5*anode_len, anode_deg, anode_deg2);
                
  G4LogicalVolume* logicAnode = new G4LogicalVolume(solidAnode, anode_mat, "Anode");
               
  new G4PVPlacement(0, anode_pos, logicAnode, "Anode", logicWorld, false, 0, checkOverlaps); 
                    
  G4Colour anodeColour( 0.63, 0.16, 0.19, 1.0 ); ///Anode colour
  G4VisAttributes* anodeVisAtt = new G4VisAttributes( anodeColour );
  logicAnode->SetVisAttributes(anodeVisAtt);
  
/**
 * ... Cathode Barrel ...
 * 
 * @param cathodeB_rmin 		Size of Cathode Barrel (r min)
 * @param cathodeB_rmax 		Size of Cathode Barrel (r max)
 * @param cathodeB_len			Size of Cathode Barrel (length)
 * @param solidCathodeB			Geometry of Cathode Barrel
 * @param cathodeB_mat 			Material of Cathode Barrel
 * @param logicCathodeB			Logical volume of Cathode Barrel
 * 
 **/
 
  G4Material* cathodeB_mat = nist->FindOrBuildMaterial("G4_Al");
  G4ThreeVector cbpos = G4ThreeVector(0, 0*cm, 13.0*cm);
      
  G4double cathodeB_rmin = 1.35*cm;
  G4double cathodeB_rmax = 1.45*cm;
  G4double cathodeB_len  = 6*cm;
  G4double cathodeB_deg = 0*deg;
  G4double cathodeB_deg2 = 360*deg;      
  G4Tubs* solidCathodeB = new G4Tubs("Cathode_Barrel", cathodeB_rmin, cathodeB_rmax, 0.5*cathodeB_len, cathodeB_deg, cathodeB_deg2); //its size
                
  G4LogicalVolume* logicCathodeB = new G4LogicalVolume(solidCathodeB, cathodeB_mat, "Cathode_Barrel");           //its name
               
  new G4PVPlacement(0, cbpos, logicCathodeB, "Cathode_Barrel", logicWorld, false, 0, checkOverlaps);
                    
  G4Colour catbarColour( 0.5, 0.5, 0.5, 1.0 ); ///Cathode_barrel colour
  G4VisAttributes* catbarVisAtt = new G4VisAttributes( catbarColour );
  logicCathodeB->SetVisAttributes(catbarVisAtt);
  
/**
 * ... Cathode End ...
 * 
 * @param cathodeE_rmin 		Size of Cathode End (r min)
 * @param cathodeE_rmax 		Size of Cathode End (r max)
 * @param cathodeE_len			Size of Cathode End (length)
 * @param solidCathodeE			Geometry of Cathode End
 * @param cathodeE_mat 			Material of Cathode End
 * @param logicCathodeE			Logical volume of Cathode End
 * 
 **/
 
  G4Material* cathodeE_mat = nist->FindOrBuildMaterial("G4_Al");
  G4ThreeVector cepos = G4ThreeVector(0, 0*cm, 16.05*cm);

     
  G4double cathodeE_rmin = 0*cm;
  G4double cathodeE_rmax = 1.45*cm;
  G4double cathodeE_len  = 0.1*cm;
  G4double cathodeE_deg = 0*deg;
  G4double cathodeE_deg2 = 360*deg;  
      
  G4Tubs* solidCathodeE = new G4Tubs("Cathode_End", cathodeE_rmin, cathodeE_rmax, 0.5*cathodeE_len, cathodeE_deg, cathodeE_deg2);
                
  G4LogicalVolume* logicCathodeE = new G4LogicalVolume(solidCathodeE, cathodeE_mat, "Cathode_End"); 
               
  new G4PVPlacement(0, cepos, logicCathodeE, "Cathode_End", logicWorld, false, 0, checkOverlaps);           
  
  G4Colour catendColour( 0.5, 0.5, 0.5, 1.0 );///Cathode_end colour
  G4VisAttributes* catendVisAtt = new G4VisAttributes( catendColour );
  logicCathodeE->SetVisAttributes(catendVisAtt);
  
/**
 * ... Cathode Front ...
 * 
 * @param cathodeF_rmin 		Size of Cathode Front (r min)
 * @param cathodeF_rmax 		Size of Cathode Front (r max)
 * @param cathodeF_len			Size of Cathode Front (length)
 * @param solidCathodeF			Geometry of Cathode Front
 * @param cathodeF_mat 			Material of Cathode Front
 * @param logicCathodeF			Logical volume of Cathode Front
 * 
 **/
 
  G4Material* cathodeF_mat = nist->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");
  G4ThreeVector cfpos = G4ThreeVector(0, 0*cm, 9.995*cm);
     
  G4double CathodeF_rmin = 0*cm;
  G4double CathodeF_rmax = 1.45*cm;
  G4double CathodeF_len  = 0.01*cm;
  G4double CathodeF_deg = 0*deg;
  G4double CathodeF_deg2 = 360*deg; 
       
  G4Tubs* solidCathodeF = new G4Tubs("Cathode_Front", CathodeF_rmin, CathodeF_rmax, 0.5*CathodeF_len, CathodeF_deg, CathodeF_deg2);
                
  G4LogicalVolume* logicCathodeF = new G4LogicalVolume(solidCathodeF, cathodeF_mat, "Cathode_Front");  
               
  new G4PVPlacement(0, cfpos, logicCathodeF, "Cathode_Front", logicWorld, false, 0, checkOverlaps);           
  
  G4Colour catfrontColour( 1.0, 1.0, 1.0, 0.2 );///Cathode_front colour
  G4VisAttributes* catfrontVisAtt = new G4VisAttributes( catfrontColour );
  logicCathodeF->SetVisAttributes(catfrontVisAtt);
  

/**
 * ... Gas ...
 * 
 * @param gas_rmin 			Size of Gas (r min)
 * @param gas_rmax 			Size of Gas (r max)
 * @param gas_len			Size of Gas(length)
 * @param solidGas			Geometry of Gas
 * @param gas_mat 			Material of Gas
 * @param logicGas			Logical volume of Gas
 * 
 **/
 
  density=1.4*g/cm3;
  G4Material* ar = nist->FindOrBuildMaterial("G4_Ar");
  G4Material* CO2 = nist->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
  G4Material* gas_mat = new G4Material(name="Ar_CO2_80_20", density, ncomponents=2);
  gas_mat->AddMaterial(ar, fractionmass=80*perCent);
  gas_mat->AddMaterial(CO2, fractionmass=20*perCent);
  G4ThreeVector posgas = G4ThreeVector(0, 0*cm, 13*cm);

    
  G4double gas_rmin = 0.1*cm;
  G4double gas_rmax = 1.35*cm;
  G4double gas_len  = 6*cm;
  G4double gas_deg = 0*deg;
  G4double gas_deg2 = 360*deg;
        
  G4Tubs* solidGas = new G4Tubs("Gas", gas_rmin, gas_rmax, 0.5*gas_len, gas_deg, gas_deg2);
                
  G4LogicalVolume* logicGas = new G4LogicalVolume(solidGas, gas_mat, "Gas");
               
  new G4PVPlacement(0, posgas, logicGas, "Gas", logicWorld, false, 0, checkOverlaps);
   
   G4Colour gasColour( 0.5, 0.5, 0.5, 0.0 ); ///Gas colour
   G4VisAttributes* gasVisAtt = new G4VisAttributes( gasColour );
   logicGas->SetVisAttributes(gasVisAtt);

  return physWorld;
}

/// End of file

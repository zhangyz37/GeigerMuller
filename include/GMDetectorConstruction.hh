/**
 * @file /Geiger_Muller/include/GMDetectorConstruction.hh
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Header to create and place your experiment. 
 * Latest updates of project can be found in README file.
 **/

#ifndef GMDetectorConstruction_h
#define GMDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4RotationMatrix.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"

class GMDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    GMDetectorConstruction();
    virtual ~GMDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
};

/// End of file

#endif


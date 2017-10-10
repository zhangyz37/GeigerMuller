/**
 * @file /Geiger_Muller/include/GMRunAction.hh
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. RunAction global.  
 * Latest updates of project can be found in README file.
 **/

#ifndef GMRunAction_h
#define GMRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "GMPrimaryGeneratorAction.hh"
#include "GMDetectorConstruction.hh"
#include "GMRun.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

class GMRunAction : public G4UserRunAction
{
  public:
    GMRunAction();
    virtual ~GMRunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

/// End of file

#endif


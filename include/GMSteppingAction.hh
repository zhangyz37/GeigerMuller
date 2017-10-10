/**
 * @file /Geiger_Muller/include/GMSteppingAction.hh
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Steps.  
 * Latest updates of project can be found in README file.
 **/

#ifndef GMSteppingAction_h
#define GMSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "GMEventAction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"


class GMSteppingAction : public G4UserSteppingAction
{
  public:
    GMSteppingAction(GMEventAction* eventAction);
    virtual ~GMSteppingAction();

    virtual void UserSteppingAction(const G4Step*); /// method from the base class
    G4int trackID;

  private:
    GMEventAction*  fEventAction;

};

/// End of file

#endif

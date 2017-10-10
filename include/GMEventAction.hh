/**
 * @file /Geiger_Muller/include/GMEventAction.hh
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Event, like one gamma from start till leaving the world.
 * It collect event-level information, like total energy deposit of one gamma. 
 * Latest updates of project can be found in README file.
 **/

#ifndef GMEventAction_h
#define GMEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "GMRun.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

class GMEventAction : public G4UserEventAction
{
  public:
    GMEventAction();
    virtual ~GMEventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }
    G4int ptrackID;
	 void EdepinGas(G4double edep) { EdepInEvent += edep; }
	 G4double PreKinEnergy;
    G4double r;
    G4double phiEA;
    G4double Charge;
  private:
    G4double  fEdep;
    G4double EdepInEvent;
    
    
    
    
};

/// End of file

#endif

    

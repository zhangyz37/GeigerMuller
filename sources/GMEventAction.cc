/**
 * @file /Geiger_Muller/sources/GMEventAction.cc
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Event, like one gamma from start till leaving the world.
 * It collect event-level information, like total energy deposit of one gamma. 
 * Latest updates of project can be found in README file.
 **/
 
#include "GMEventAction.hh"
#include "G4SystemOfUnits.hh"


/// @brief Constructor of Event action

GMEventAction::GMEventAction()
: G4UserEventAction()
{} 

/// @brief Destructor of Event action

GMEventAction::~GMEventAction()
{}

/**
 * @brief Beginning of event
 * 
 * @param Current event
 * 
 **/

void GMEventAction::BeginOfEventAction(const G4Event*)
{
  
  fEdep = 0.0;
  ptrackID = 0;
  EdepInEvent=0.0;
  PreKinEnergy=0.0;
  r=0.0;
  phiEA=0.0;
}

/**
 * @brief End of event
 * 
 * @param Current event
 * 
 **/

void GMEventAction::EndOfEventAction(const G4Event*)
{
  Charge=((EdepInEvent*eV)/(30*eV))*(1.6*10.e-19);
  
  GMRun* run = static_cast<GMRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun()); /// accumulate statistics in GMRun
  run->AddEdep(fEdep);
  if(EdepInEvent!=0){///G4cout<<"EdepInEvent "<<evt->GetEventID()<<": "<<EdepInEvent/keV<<" PreKinE:"<<PreKinEnergy/keV<<" r:"<<r/cm<<" phiEA:"<<phiEA<<") "<<G4endl;
	  G4cout<<"ABCDEF"<<" 0 "<<PreKinEnergy/keV<<" "<<r/cm<<" "<<phiEA<<
	  " "<<(-1)*Charge/10.e-18<<G4endl;}
}

/// End of file

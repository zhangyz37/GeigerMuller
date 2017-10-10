/**
 * @file /Geiger_Muller/sources/GMActionInitialization.cc
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. User actions like Run, Event, Stepping,
 * Stacking, PrimaryGenerator for master and threads.  
 * Latest updates of project can be found in README file.
 **/

#include "GMActionInitialization.hh"


/// @brief Constructor of Action initialization

GMActionInitialization::GMActionInitialization()
 : G4VUserActionInitialization()
{}

/// @brief Destructor of Action initialization

GMActionInitialization::~GMActionInitialization()
{}

/// @brief Setting run action 

void GMActionInitialization::BuildForMaster() const
{
  SetUserAction(new GMRunAction);
}

/// @brief Build void 

void GMActionInitialization::Build() const
{
  SetUserAction(new GMPrimaryGeneratorAction);
  SetUserAction(new GMRunAction);
  
  GMEventAction* eventAction = new GMEventAction;
  SetUserAction(eventAction);
  
  SetUserAction(new GMSteppingAction(eventAction));
}  

/// End of file

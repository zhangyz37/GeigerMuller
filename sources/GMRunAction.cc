/**
 * @file /Geiger_Muller/sources/GMRunAction.cc
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. RunAction global.  
 * Latest updates of project can be found in README file.
 **/

#include "GMRunAction.hh"

/// @brief Constructor of Run

GMRunAction::GMRunAction()
: G4UserRunAction()
{ }

/// @brief Destructor of Run

GMRunAction::~GMRunAction()
{}

/// @brief Generation of Runs

G4Run* GMRunAction::GenerateRun()
{
  return new GMRun; 
}

/// @brief Start of Run action

void GMRunAction::BeginOfRunAction(const G4Run*)
{ }

/// @brief End of Run action

void GMRunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;
  
  const GMRun* dERun = static_cast<const GMRun*>(run);
  G4double edepInRuns  = dERun->GetEdep();

  /// Print
  
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  
  G4cout
     << G4endl
     << " The run consists of " << nofEvents << " edep: "<< edepInRuns/keV
     << G4endl;

}

/// End of file

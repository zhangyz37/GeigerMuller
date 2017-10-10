/**
 * @file /Geiger_Muller/sources/GMRun.cc
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Run for threads.  
 * Latest updates of project can be found in README file.
 **/


#include "GMRun.hh"

/// @brief Constructor of Run

GMRun::GMRun()
: G4Run()
{fEdep=0.0;} 

/// @brief Destructor of Run

GMRun::~GMRun()
{} 
 
/// @brief Void Merge

void GMRun::Merge(const G4Run* run)
{
  const GMRun* localRun = static_cast<const GMRun*>(run);
  fEdep  += localRun->fEdep;

  G4Run::Merge(run); 
} 

/// @brief Summarizing Edep

void GMRun::AddEdep (G4double edep)
{
  fEdep  += edep;
}

/// End of file



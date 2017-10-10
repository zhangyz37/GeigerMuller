/**
 * @file /Geiger_Muller/include/GMActionInitialization.hh
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. User actions like Run, Event, Stepping,
 * Stacking, PrimaryGenerator for master and threads.  
 * Latest updates of project can be found in README file.
 **/

#ifndef GMActionInitialization_h
#define GMActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "GMPrimaryGeneratorAction.hh"
#include "GMRunAction.hh"
#include "GMEventAction.hh"
#include "GMSteppingAction.hh"

class GMActionInitialization : public G4VUserActionInitialization
{
  public:
    GMActionInitialization();
    virtual ~GMActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

/// End of file

#endif

    

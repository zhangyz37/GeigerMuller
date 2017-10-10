/**
 * @file /Geiger_Muller/include/GMPhysListEmStandard.hh
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Header to physics list for EM processes. 
 * Latest updates of project can be found in README file.
 **/

#ifndef GMPhysListEmStandard_h
#define GMPhysListEmStandard_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

class GMPhysListEmStandard : public G4VPhysicsConstructor
{
  public: 
    GMPhysListEmStandard(const G4String& name = "standard");
   ~GMPhysListEmStandard();

  public: 
    void ConstructParticle() {};
 
    void ConstructProcess();
};

/// End of file

#endif









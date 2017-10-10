/**
 * @file /Geiger_Muller/include/GMPrimaryGeneratorAction.hh
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. For particle, energy, momentum, position.
 * Latest updates of project can be found in README file.
 **/

#ifndef GMPrimaryGeneratorAction_h
#define GMPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

class GMPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    GMPrimaryGeneratorAction();    
    virtual ~GMPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);
          
  
  private:
    G4ParticleGun*  fParticleGun; /// pointer a to G4 gun class

};

/// End of file

#endif



/**
 * @file /Geiger_Muller/include/GMPhysicsList.hh
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Header to physics list for EM processes. 
 * Latest updates of project can be found in README file.
 **/

#ifndef GMPhysicsList_h
#define GMPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "G4EmConfigurator.hh"
#include "G4EmProcessOptions.hh"


#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLowEPPhysics.hh"
#include "G4DecayPhysics.hh"

#include "G4PAIModel.hh"
#include "G4PAIPhotModel.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Proton.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4LossTableManager.hh"
#include "G4ProductionCutsTable.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4UAtomicDeexcitation.hh"

class G4VPhysicsConstructor;

class GMPhysicsList: public G4VUserPhysicsList
{
public:

  GMPhysicsList(int plType_in,int cut_in);
  virtual ~GMPhysicsList();

   virtual void ConstructParticle();
    
  virtual void SetCuts();
        
  void AddPhysicsList();
  virtual void ConstructProcess();
    

private:
  G4EmConfigurator* fConfig;

  G4VPhysicsConstructor*  fEmPhysicsList;
  G4VPhysicsConstructor*  fDecayPhysicsList;
  std::vector<G4VPhysicsConstructor*> fHadronPhys;
  int plType,cut;
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  G4double cutForProton;
  G4String fEmName;
  
  void  AddPAIModel(const G4String&);
  void  NewPAIModel(const G4ParticleDefinition*, const G4String& modname, 
                    const G4String& procname);

  
};

/// End of file

#endif


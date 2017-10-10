/**
 * @file /Geiger_Muller/sources/GMPhysicsList.cc
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Source code to physics list for EM processes. 
 * Latest updates of project can be found in README file.
 **/

#include "GMPhysicsList.hh"
#include "GMPhysListEmStandard.hh"

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


/**
 * @brief Constructor of Physics list
 * 
 * @param inPhysList	Hadronic physics list
 * @param inCut			Cut for deexcitation
 * 
 **/
 
GMPhysicsList::GMPhysicsList(int inPhysList,int inCut):  G4VUserPhysicsList(),
  fEmPhysicsList(0),
  fDecayPhysicsList(0),
  plType(inPhysList),
  cut(inCut)
{
  fDecayPhysicsList = new G4DecayPhysics(); /// Decay Physics is always defined

  fEmPhysicsList = new GMPhysListEmStandard("local"); /// EM physics

 
  switch(plType){
    
  case 0:
	delete fEmPhysicsList;
	fEmPhysicsList = new GMPhysListEmStandard("local");
	break;
	
	case 1:
	delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option1();
	break;
	
	case 2:
	delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option2();
	break;
	
	case 3:
	delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option3();
	break;
	
	case 4:
	delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option4();
	break;
	
	case 5:
	delete fEmPhysicsList;
    fEmPhysicsList = new G4EmLivermorePhysics();
	break;
	
	case 6:
	delete fEmPhysicsList;
    fEmPhysicsList = new G4EmPenelopePhysics();
	break;
	
	case 7:
	delete fEmPhysicsList;
    fEmPhysicsList = new G4EmLowEPPhysics();
	break;
	
	case 8:
	AddPAIModel("pai");
	break;
	
	case 9:
	AddPAIModel("pai_photon");
	break;
	
	default:
	delete fEmPhysicsList;
	fEmPhysicsList = new GMPhysListEmStandard("local");
	break;
  }

  SetVerboseLevel(1);

}

/// @brief Destructor of Physics list

GMPhysicsList::~GMPhysicsList()
{
  delete fDecayPhysicsList;
  delete fEmPhysicsList;
}

/// @brief Void for Particle construction

void GMPhysicsList::ConstructParticle()
{
  fDecayPhysicsList->ConstructParticle();
}

/// @brief Void for Physics construction

void GMPhysicsList::ConstructProcess()
{
 
  AddTransportation();
  fEmPhysicsList->ConstructProcess();
  fDecayPhysicsList->ConstructProcess();
  
 
  G4double particleCut=1000;
  G4double lowEnergyEnd=1000*eV;
  
  G4VAtomDeexcitation* de = new G4UAtomicDeexcitation(); /// Deexcitation
  de->SetFluo(false);
  de->SetAuger(false);   
  de->SetPIXE(false);
  
  switch(cut){
  case 0:
    particleCut=pow(10,2);
    de->SetFluo(true);
    de->SetAuger(true);   
    de->SetPIXE(true); 
    lowEnergyEnd=1*keV;
    break;
    
  case 1:
    particleCut=pow(10,2);
    de->SetFluo(true);
    de->SetAuger(false);   
    de->SetPIXE(false); 
    lowEnergyEnd=10*keV;
    break;
    
  case 2:
    particleCut=pow(10,3);
    de->SetFluo(true);
    de->SetAuger(false);   
    de->SetPIXE(false); 
    lowEnergyEnd=100*keV;
    break;
    
  case 3:
    particleCut=pow(10,3);
    de->SetFluo(false);
    de->SetAuger(false);   
    de->SetPIXE(false); 
    lowEnergyEnd=100*keV;
    break;

  }
  
  
  G4LossTableManager::Instance()->SetAtomDeexcitation(de);
  
  defaultCutValue = particleCut*micrometer;
  cutForGamma     = defaultCutValue;
  cutForElectron  = defaultCutValue;
  cutForPositron  = defaultCutValue;

    
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowEnergyEnd, 1*GeV);
  
  
  G4EmProcessOptions emOptions;
  emOptions.SetMinEnergy(lowEnergyEnd);        ///default 100 eV   
  emOptions.SetMaxEnergy(10*TeV);       ///default 100 TeV 
  emOptions.SetDEDXBinning(12*10);      ///default=12*7
  emOptions.SetLambdaBinning(12*10);    ///default=12*7
  
  SetCutValue(cutForGamma, "gamma");
  SetCutValue(cutForElectron, "e-");
  SetCutValue(cutForPositron, "e+");

 
}

/// @brief Setting cuts universally

void GMPhysicsList::SetCuts()
{
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100.*eV,1e5);
  if ( verboseLevel > 0 ) { DumpCutValuesTable(); }
}

/// @brief PAI Model addition

void GMPhysicsList::AddPAIModel(const G4String& modname)
{
  auto theParticleIterator = GetParticleIterator();
  theParticleIterator->reset();
  while ((*theParticleIterator)())
  {
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4String partname = particle->GetParticleName();
    if(partname == "e-" || partname == "e+") {
      NewPAIModel(particle, modname, "eIoni");

    } else if(partname == "mu-" || partname == "mu+") {
      NewPAIModel(particle, modname, "muIoni");

    } else if(partname == "proton" ||
              partname == "pi+" ||
              partname == "pi-"   
              ) {
      NewPAIModel(particle, modname, "hIoni");
    }
  }
}

/// @brief PAI model definition

void GMPhysicsList::NewPAIModel(const G4ParticleDefinition* part, 
                              const G4String& modname,
                              const G4String& procname)
{
  G4String partname = part->GetParticleName();
  if(modname == "pai") {
    G4PAIModel* pai = new G4PAIModel(part,"PAIModel");
    fConfig->SetExtraEmModel(partname,procname,pai,"GasDetector",
                              0.0,100.*TeV,pai);
  } else if(modname == "pai_photon") {
    G4PAIPhotModel* pai = new G4PAIPhotModel(part,"PAIPhotModel");
    fConfig->SetExtraEmModel(partname,procname,pai,"GasDetector",
                              0.0,100.*TeV,pai);
  }
}

/// End of file

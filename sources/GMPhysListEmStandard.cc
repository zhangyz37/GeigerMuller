/**
 * @file /Geiger_Muller/sources/GMPhysListEmStandard.cc
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Source code to physics list for EM processes. 
 * Latest updates of project can be found in README file.
 **/

#include "GMPhysListEmStandard.hh"

#include "G4BuilderType.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicsListHelper.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4ionIonisation.hh"

#include "G4MscStepLimitType.hh"

#include "G4SystemOfUnits.hh"

/// @brief Constructor of PhysListEmStandard

GMPhysListEmStandard::GMPhysListEmStandard(const G4String& name)
   :  G4VPhysicsConstructor(name)
{
    SetPhysicsType(bElectromagnetic);

    G4EmParameters* param = G4EmParameters::Instance();
    param->SetDefaults();
	param->SetVerbose(0);
    param->SetMinEnergy(100*eV);
    param->SetMaxEnergy(100*TeV);
    param->SetNumberOfBinsPerDecade(10);
    param->SetMscStepLimitType(fUseSafety);
    param->SetStepFunction(0.2, 100*um);
    param->SetStepFunctionMuHad(0.2, 100*um);
}

/// @brief Destructor of PhysListEmStandard

GMPhysListEmStandard::~GMPhysListEmStandard()
{}

/// @brief Void for Physics construction

void GMPhysListEmStandard::ConstructProcess()
{
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  
  /// Add standard EM Processes

  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  while( (*particleIterator)() ){
    G4ParticleDefinition* particle = particleIterator->value();
    G4String particleName = particle->GetParticleName();
     
    if (particleName == "gamma") {
      /// gamma         
      ph->RegisterProcess(new G4PhotoElectricEffect, particle);
      ph->RegisterProcess(new G4ComptonScattering,   particle);
      ph->RegisterProcess(new G4GammaConversion,     particle);
      
    } else if (particleName == "e-") {
      ///electron
      ph->RegisterProcess(new G4eMultipleScattering, particle);
      ph->RegisterProcess(new G4eIonisation,         particle);
      ph->RegisterProcess(new G4eBremsstrahlung(),   particle);
      
    } else if (particleName == "e+") {
      ///positron
      ph->RegisterProcess(new G4eMultipleScattering, particle);
      ph->RegisterProcess(new G4eIonisation,         particle);
      ph->RegisterProcess(new G4eBremsstrahlung(),   particle);
      ph->RegisterProcess(new G4eplusAnnihilation,   particle);
      
    } else if( particleName == "mu-" || 
               particleName == "mu+"    ) {
      ///muon  
      ph->RegisterProcess(new G4hMultipleScattering, particle);
      ph->RegisterProcess(new G4MuIonisation,        particle);
      ph->RegisterProcess(new G4MuBremsstrahlung,    particle);
      ph->RegisterProcess(new G4MuPairProduction,    particle);
             
    } else if( particleName == "proton" ||
               particleName == "pi-" ||
               particleName == "pi+"    ) {
      ///proton  
      ph->RegisterProcess(new G4hMultipleScattering, particle);
      ph->RegisterProcess(new G4hIonisation,         particle);
      ph->RegisterProcess(new G4hBremsstrahlung,     particle);
      ph->RegisterProcess(new G4hPairProduction,     particle);       
     
    } else if( particleName == "alpha" || 
	       particleName == "He3" || 
	       particleName == "GenericIon" ) {
      ///Ions 
      ph->RegisterProcess(new G4hMultipleScattering, particle);
      ph->RegisterProcess(new G4ionIonisation,       particle);

    } else if ((!particle->IsShortLived()) &&
	       (particle->GetPDGCharge() != 0.0) && 
	       (particle->GetParticleName() != "chargedgeantino")) {
      ///all others charged particles except geantino
      ph->RegisterProcess(new G4hMultipleScattering, particle);
      ph->RegisterProcess(new G4hIonisation,         particle);
    }
  }
}

/// End of file


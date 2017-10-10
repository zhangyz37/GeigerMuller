/**
 * @file /Geiger_Muller/sources/GMPrimaryGeneratorAction.cc
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. For particle, energy, momentum, position.
 * Latest updates of project can be found in README file.
 **/
 
#include "GMPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

/// @brief Constructor of Primary generator action

GMPrimaryGeneratorAction::GMPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;   ///particles per event
  fParticleGun  = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable(); /// default particle kinematic
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(5.*MeV);
}

/// @brief Destructor of Primary generator action

GMPrimaryGeneratorAction::~GMPrimaryGeneratorAction()
{
  delete fParticleGun;
}

/// @brief Generation of Primary Particles 

void GMPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4double  ux, uy, uz, a, b, me=0.05; ///for me: me(x,s)=((s*x^2)/3)*0.01905
  fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));
  fParticleGun->GeneratePrimaryVertex(anEvent);
	a=G4UniformRand();
	b=G4UniformRand();
	if(a>0.5){ux = me*G4UniformRand();}
	else{ux = -me*G4UniformRand();}
	if(b>0.5){uy = me*G4UniformRand();}
	else{uy = -me*G4UniformRand();}
	uz = 1.0;///cosTheta;
	G4ThreeVector Pi_random_axis(ux,uy,uz);
	///~ G4cout<<"u: "<<ux<<" "<<uy<<" "<<uz<<G4endl;
	fParticleGun->SetParticleMomentumDirection(Pi_random_axis);
}

/// End of file


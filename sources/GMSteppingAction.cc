/**
 * @file /Geiger_Muller/sources/GMSteppingAction.cc
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Steps.  
 * Latest updates of project can be found in README file.
 **/

#include "GMSteppingAction.hh"
#include "G4Track.hh"
#include <cmath>


/// Constructor of Stepping action

GMSteppingAction::GMSteppingAction(GMEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{}

/// Destructor of Stepping action

GMSteppingAction::~GMSteppingAction()
{}

/// User Stepping action for collecting datas from steps

void GMSteppingAction::UserSteppingAction(const G4Step* fStep)
{
  
  G4double edepStep = fStep->GetTotalEnergyDeposit(); /// collect energy deposited in this step
  fEventAction->AddEdep(edepStep);  

  G4Track * fTrack = fStep->GetTrack();
  trackID=fTrack->GetTrackID();
  
  if(fTrack->GetTrackStatus()!=fAlive) { return; }
  
  G4ParticleDefinition *particle=fTrack->GetDefinition();

  G4VPhysicalVolume* prevolume  =
    fStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  G4VPhysicalVolume* postvolume  =
    fStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume();

  G4double preX = fStep->GetPreStepPoint()->GetPosition().x();
  G4double preY = fStep->GetPreStepPoint()->GetPosition().y();
  G4double preZ  = fStep->GetPreStepPoint()->GetPosition().z();
  G4double prekinE  = fStep->GetPreStepPoint()->GetKineticEnergy();

  G4double postX = fStep->GetPostStepPoint()->GetPosition().x();
  G4double postY = fStep->GetPostStepPoint()->GetPosition().y();
  G4double postZ = fStep->GetPostStepPoint()->GetPosition().z();
  G4double postkinE  = fStep->GetPostStepPoint()->GetKineticEnergy();

  G4ThreeVector momentumdirection = fTrack->GetMomentumDirection();
  G4double theta = momentumdirection.theta();

  G4String particleName = particle->GetParticleName();
  G4String procN;
  G4String preName=prevolume->GetName();
  G4String postName=postvolume->GetName();

 if (prevolume->GetName() == "Box" && postvolume->GetName() == "World" && particleName == "gamma")
   {G4cout <<"gammaLeftBox "<< postkinE/keV<<" "<<postX/cm<<" "<<postY/cm<<" "<<postZ/cm<<" "<<theta/deg<<G4endl;}
   
   if (trackID!=1){procN=fTrack->GetCreatorProcess()->GetProcessName();}
  
  
	if((postName=="Gas") && (fEventAction->ptrackID!=trackID) && ((procN=="phot")|(procN=="compt"))){
		
	G4cout <<"INS1DE "<<" "<<particleName<<" "<<trackID<<" "<<procN<<" "<<momentumdirection.x()<<" "
	<< momentumdirection.y()<<" "<< momentumdirection.z()<<" "<< prekinE/keV<<" "<<preX/cm<<" "<<preY/cm<<" "<<preZ/cm<<" "
	<<momentumdirection.theta()<<" "<<momentumdirection.phi()<<" "<<postX/cm<<" "<<postY/cm<<" "<<postZ/cm<<" "
	<<prevolume->GetName()<<" "<<postvolume->GetName()<<G4endl;
	
	
	fEventAction->ptrackID=trackID;
	fEventAction->PreKinEnergy=prekinE;
	fEventAction->r=sqrt((preY*preY));
	
	if(momentumdirection.phi()<0){
		fEventAction->phiEA=momentumdirection.phi()+2.0*M_PI;
								 }
	else{
		fEventAction->phiEA=momentumdirection.phi();
		}
	}
	
	if((preName=="Gas")&&(particleName=="e-")){
		fEventAction->EdepinGas(edepStep); 
		G4cout<<"edep "<<edepStep/keV<<G4endl; 
	}
}

/// End of file


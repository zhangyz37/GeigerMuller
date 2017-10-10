/**
 * @file /Geiger_Muller/GM.cc
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Main file. 
 * Latest updates of project can be found in README file.
 **/

#include "GMDetectorConstruction.hh"
#include "GMActionInitialization.hh"
#include "GMPhysicsList.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "QGSP_BIC_HP.hh"
#include "G4UImanager.hh"
#include "QBBC.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"
#include "Randomize.hh"
#include "QGSP_BIC.hh"

/**
 * @brief Start of main function
 * 
 * @param	argc		Number of command line arguments
 * @param	NoE 		Command line argument for Number of events 
 * @param	PhysList 	Command line argument for Hadronic physics list
 * @param   CutEx       Command line argument for cut of deexcitation
 * 
 **/

int main(int argc,char** argv)
{

  int NoE=0;
  int PhysList=8;
  int CutEx=0;
  if (argc==4){
	  NoE=atoi(argv[1]);
	  PhysList=atoi(argv[2]);
	  CutEx=atoi(argv[3]);
	  }
  
  G4RunManager* runManager = new G4RunManager;
  
  runManager->SetUserInitialization(new GMDetectorConstruction());
  runManager->SetUserInitialization(new GMPhysicsList(PhysList,CutEx));
  runManager->SetUserInitialization(new GMActionInitialization());
  runManager->SetUserInitialization(new QBBC);


  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc==4) { 
    /// batch mode
   runManager->Initialize();
   runManager->BeamOn(NoE);
  }
  else { 
    /// interactive mode
    G4UIExecutive* ui = 0;
    if ( argc == 1 ) {
      ui = new G4UIExecutive(argc, argv);
    }
    UImanager->ApplyCommand("/control/execute gui.mac");
    ui->SessionStart();
    delete ui;
  }
  
  
  delete visManager;
  delete runManager;
}

/// End of file

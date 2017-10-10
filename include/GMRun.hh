/**
 * @file /Geiger_Muller/include/GMRun.hh
 * @authors Balázs Demeter <balazsdemeter92@gmail.com>, Balázs Ujvári <balazs.ujvari@science.unideb.hu>
 * @date 2015/09/31 <creation of 1.0>
 * 
 * @section DESCRIPTION
 * 
 * The Geant4 simulation of a Geiger-Muller counter. Run for threads.  
 * Latest updates of project can be found in README file.
 **/


#ifndef GMRun_h
#define GMRun_h 1

#include "G4Run.hh"
#include "globals.hh"

class GMRun : public G4Run
{
public:
  GMRun();
  virtual ~GMRun();
  
  virtual void Merge(const G4Run*);
  
  void AddEdep (G4double edep); 
  
  G4double GetEdep()  const { return fEdep; }
  
private:
  G4double  fEdep;
};

/// End of file

#endif


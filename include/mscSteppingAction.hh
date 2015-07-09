#ifndef mscSteppingAction_hh
#define mscSteppingAction_hh 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include "TFile.h"
#include "TH1D.h"

class mscSteppingAction : public G4UserSteppingAction
{
public:
  mscSteppingAction(G4int*);
  ~mscSteppingAction();
  
  void UserSteppingAction(const G4Step*);
  
private:
  G4int *evNr;
  TFile *fout;
  TH1D *htst;
  TTree *data;
};

#endif

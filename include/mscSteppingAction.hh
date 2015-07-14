#ifndef mscSteppingAction_hh
#define mscSteppingAction_hh 

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include "TFile.h"
#include "TTree.h"

class mscSteppingAction : public G4UserSteppingAction
{
public:
  mscSteppingAction(G4int*);
  ~mscSteppingAction();
  
  void UserSteppingAction(const G4Step*);
  
private:
  G4int *evNr;
  TFile *fout;
  TTree *tout;

  //tree variables
  G4double pre_pos_x;
  G4double post_pos_x;
  G4double pre_pos_y;
  G4double post_pos_y;
  G4double pre_pos_z;
  G4double post_pos_z;
  G4double pre_mom_x;
  G4double post_mom_x;
  G4double pre_mom_y;
  G4double post_mom_y;
  G4double pre_mom_z;
  G4double post_mom_z;
  G4int trackID;
  G4int parentID;
  G4int particle_Type;

};

#endif

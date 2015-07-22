#include "mscSteppingAction.hh"

#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4String.hh"



mscSteppingAction::mscSteppingAction(G4int *evN)		 
{
  //eventID pointer from the mscEventAction.cc file
  evNr=evN;

  /*Create root file and initialize what I want to put in it*/
  fout=new TFile("o_mscSteppingAction.root","RECREATE");
  tout=new TTree("t","Stepping action event tree");

  tout->Branch("prePosX",&pre_pos_x,"prePosX/D");
  tout->Branch("postPosX",&post_pos_x,"postPosX/D");
  tout->Branch("prePosY", &pre_pos_y,"prePosY/D");
  tout->Branch("postPosY", &post_pos_y,"postPosY/D");
  tout->Branch("prePosZ", &pre_pos_z,"prePosZ/D");
  tout->Branch("postPosZ", &post_pos_z,"prePosZ/D");  
  tout->Branch("preMomX", &pre_mom_x, "preMomX/D");
  tout->Branch("postMomX", &post_mom_x, "postMomX/D");
  tout->Branch("preMomY", &pre_mom_y, "preMomY/D");
  tout->Branch("postMomY", &post_mom_y, "postMomY/D");
  tout->Branch("preMomZ", &pre_mom_z, "preMomZ/D");
  tout->Branch("postMomZ", &post_mom_z, "postMomZ/D");
  tout->Branch("trackID", &trackID, "trackID/i");
  tout->Branch("parentID", &parentID, "parentID/i");
  tout->Branch("particle_Type", &particle_Type, "particle_type/i");
  tout->Branch("Event_Number", &Event_Number, "Event_Number/i");  
  tout->Branch("Material_Number", &Material_Number, "Material_Number/i");
  
}


mscSteppingAction::~mscSteppingAction()
{
  /*Write out root file*/
  fout->cd();
  tout->Write();
  fout->Close();
}


void mscSteppingAction::UserSteppingAction(const G4Step* theStep)
{

  G4Track*              theTrack     = theStep->GetTrack();
  G4ParticleDefinition* particleType = theTrack->GetDefinition();
  G4StepPoint*          thePrePoint  = theStep->GetPreStepPoint();
  G4StepPoint*          thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume*    thePostPV    = thePostPoint->GetPhysicalVolume();
  G4String              particleName = theTrack->GetDefinition()->GetParticleName();
  
  //get material
  G4Material* theMaterial = theTrack->GetMaterial();

  /* if(theMaterial){
    if(theMaterial->GetName().compare("detectorMat")==0){
      G4cout<<" In  detector " << *evNr<<" "
            <<theTrack->GetTrackID()<<" "<< theTrack->GetParentID()<< " " << theTrack->GetCurrentStepNumber()<< " "
	    <<thePrePoint->GetPosition().getX()<<" "
	    <<thePrePoint->GetMomentum().getX()<<" "
	    <<thePostPoint->GetPosition().getY()<<" "
	    <<thePostPoint->GetMomentum().getZ()<<" "
	    <<thePrePoint->GetTotalEnergy()<<" "
	    <<particleType->GetPDGEncoding()<<G4endl;    
    }
    if(theMaterial->GetName().compare("PBA")==0){
      G4cout<<" In  radiator " << *evNr<<" "
            <<theTrack->GetTrackID()<<" "<< theTrack->GetParentID()<< " " << theTrack->GetCurrentStepNumber()<< " "
	    <<thePrePoint->GetPosition().getX()<<" "
	    <<thePrePoint->GetMomentum().getX()<<" "
	    <<thePostPoint->GetPosition().getY()<<" "
	    <<thePostPoint->GetMomentum().getZ()<<" "
	    <<thePrePoint->GetTotalEnergy()<<" "
	    <<particleType->GetPDGEncoding()<<G4endl;   
    }
    } */

  
  /*fill tree*/   

  pre_pos_x = thePrePoint->GetPosition().getX();
  post_pos_x = thePostPoint->GetPosition().getX();
  pre_pos_y = thePrePoint->GetPosition().getY();
  post_pos_y = thePostPoint->GetPosition().getY();
  pre_pos_z = thePrePoint->GetPosition().getZ();
  post_pos_z = thePostPoint->GetPosition().getZ();
  pre_mom_x = thePrePoint->GetMomentum().getX();
  post_mom_x = thePostPoint->GetMomentum().getX();
  pre_mom_y = thePrePoint->GetMomentum().getY();
  post_mom_y = thePostPoint->GetMomentum().getY();
  pre_mom_z = thePrePoint->GetMomentum().getZ();
  post_mom_z = thePostPoint->GetMomentum().getZ();
  trackID = theTrack->GetTrackID();
  parentID = theTrack->GetParentID();
  particle_Type = particleType->GetPDGEncoding();
  Event_Number = *evNr;
  Physical_Volume = *thePostPoint->GetPhysicalVolume();

  Material_Number=9999;
  if(theMaterial){
    if(theMaterial->GetName().compare("detectorMat")==0){
      Material_Number = 1;
    }
    Material_Number=1000;
    if(theMaterial->GetName().compare("PBA")==0){
      Material_Number = 2;
    }
  }

  tout->Fill();


}





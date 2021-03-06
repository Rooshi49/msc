#ifndef mscDetectorConstruction_h
#define mscDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4Box;
class G4VPhysicalVolume;
class G4UniformMagField;
class G4GenericMessenger;

class mscDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  mscDetectorConstruction();
  virtual ~mscDetectorConstruction();
  
  virtual G4VPhysicalVolume* Construct();
  
  void SetRadiatorThickness(G4double thicknessValue){
    radiatorThickness=thicknessValue;
    G4cout<<G4endl<<G4endl<<" ~~~~ Setting radiator thickness to "<<thicknessValue<<G4endl<<G4endl;
  }
  
private:
  // methods
  //
  void DefineMaterials();
  G4VPhysicalVolume* DefineVolumes();

  // data members
  //
  G4double radiatorThickness;

  G4GenericMessenger*  fMessenger; // messenger 
  
  G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


#include "NeuEventMessenger.hh"
#include "NeuSteppingAction.hh"
#include "NeuTrackingAction.hh"
#include "NeuEventAction.hh"
#include "NeuRunAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4ios.hh"

NeuFlux::NeuEventMessenger::NeuEventMessenger(NeuFlux::NeuRunAction* run, NeuFlux::NeuEventAction* event, NeuFlux::NeuTrackingAction* track, NeuFlux::NeuSteppingAction* step)
: fRunAction(run), fEventAction(event), fTrackingAction(track), fSteppingAction(step)
{
     fNeuFluxDir = new G4UIdirectory("/NeuFlux/");
     fNeuFluxDir->SetGuidance("NeuFlux Commands");


       fGeometryDir = new G4UIdirectory("/NeuFlux/Actions/");
       fGeometryDir->SetGuidance("Neuflux Action Commands");
         fEventDir = new G4UIdirectory("/Neuflux/Actions/Event/");
         fEventDir->SetGuidance("Event Action Control");
         fEnableEventAction = new G4UIcmdWithABool("/NeuFlux/Actions/Event/enable");
         fEnableEventAction->SetGuidance("Enable Event Actions");


         fRunDir = new G4UIdirectory("/Neuflux/Actions/Run/");
         fRunDir->SetGuidance("Run Action Control");
         fEnableRunAction = new G4UIcmdWithABool("/NeuFlux/Actions/Run/enable");
         fEnableRunAction->SetGuidance("Enable Run Actions");
         
         fTrackingDir = new G4UIdirectory("/Neuflux/Actions/Tracking/");
         fTrackingDir->SetGuidance("Tracking Action Control");
         fEnableTrackingAction = new G4UIcmdWithABool("/NeuFlux/Actions/Tracking/enable");
         fEnableTrackingAction->SetGuidance("Enable Tracking Actions");

         fSteppingDir = new G4UIdirectory("/Neuflux/Actions/Stepping/");
         fSteppingDir->SetGuidance("Stepping Action Control");
         fEnableSteppingAction = new G4UIcmdWithABool("/NeuFlux/Actions/Stepping/enable");
         fEnableSteppingAction->SetGuidance("Enable Stepping Actions");



}

NeuFlux::NeuEventMessenger::~NeuEventMessenger()
{
  delete fActionDir;
  delete fEventDir;
  delete fEnableEventAction;
  delete fRunDir;
  delete fEnableRunAction;
  delete fTrackingDir;
  delete fEnableTrackingAction;
  delete fSteppingDir;
  delete fEnableSteppinAction;

}

void NeuFlux::NeuEventMessenger::SetNewValue(G4UIcommand * command, G4String newValue)
{
  if(command == fEnableRunAction)
      fRunAction->SetEnabled(  fEnableRunAction->GetNewBoolValue(newValue) );
  if(command == fEnableEventAction)
      fEventAction->SetEnabled(  fEnableEventAction->GetNewBoolValue(newValue) );
  if(command == fEnableTrackingAction)
      fTrackingAction->SetEnabled(  fEnableTrackingAction->GetNewBoolValue(newValue) );
  if(command == fEnableSteppingAction)
      fSteppingAction->SetEnabled(  fEnableSteppingAction->GetNewBoolValue(newValue) );
}

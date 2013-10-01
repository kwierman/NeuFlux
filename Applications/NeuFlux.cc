/*! \file NeuFlux.cc
    \brief The Main Executable for the NeuFlux
    \author Kevin Wierman

    This is a copied example of the standard Geant4 main executable.
    This is to be used for main simulation execution only.
    \warning For testing and debugging purposes, other executables should be used.

    \fn int main(int argc, char **argv)
    \brief The main execution point for the program.
    \param argv The name of a valid macro file, or nothing
    \param argc The usual c++ shenanigans

*/

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif

#include "NeuFlux.hh"

#ifdef G4VIS_USE
#include "NeuFluxVisManager.hh"
#endif

#include "TRandom3.h"

namespace NeuFlux
{

int main(int argc, char **argv)
{
   TRandom3 r3(0);

   UInt_t rSeed   = static_cast<UInt_t> (2147483647.*r3.Rndm());
   std::cout << "Randomization Seed: " << rSeed << std::endl;

   std::cout<<"  Setting up Run Manager"<<std::endl;
   
   G4RunManager* runManager = new G4RunManager;
   NeuWorldGeometry* geometry = new NeuWorldGeometry;

   runManager->SetUserInitialization(geometry);
   runManager->SetUserInitialization(new NeuPhysicsList);

#ifdef G4VIS_USE
   std::cout<<"  Setting up Visualization Manager"<<std::endl;
   G4VisManager *visManager = new NeuVisManager;
   visManager->SetVerboseLevel(0);
   visManager->Initialize();
#endif

   std::cout<<"  Setting up User Action Classes"<<std::endl;
   NeuRunAction* runAction = new NeuRunAction(rSeed);
   runManager->SetUserAction(runAction);
   std::cout<<"    done setting run action"<<std::endl;
   NeuEventAction* eventAction =
       new NeuEventAction(runAction);
   runManager->SetUserAction(NeuEvent);
   runManager->SetUserAction( new NeuPrimaryGeneratorAction(
                       eventAction) );
   NeuTrackingAction* trackingAction =
       new NeuTrackingAction;
   runManager->SetUserAction(trackingAction);
   *runManager->
       SetUserAction(new
                     NeuSteppingAction(eventAction,
					     trackingAction, geometry));

   std::cout<<"  Initializing the G4 kernel"<<std::endl;

   runManager->Initialize();

   G4UImanager *UI = G4UImanager::GetUIpointer();

   if (argc == 1) 
   {
      G4UIsession *session = new G4UIterminal(
      #ifdef G4UI_USE_TCSH
    		  new G4UItcsh
      #endif
    		);

      session->SessionStart();
      delete session;
   } 
   else 
   {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command + fileName);
   }

   delete runManager;
#ifdef G4VIS_USE
   delete visManager;
#endif

   return 0;
}
}
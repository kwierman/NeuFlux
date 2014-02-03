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

#include "QGSP_BIC_HP.hh"
//#include "QGSP_BERT_HP.hh"
//#include "QGSP_BERT_EMV.hh"

#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif

#include "NeuFlux.hh"

#ifdef G4VIS_USE
#include "NeuVisManager.hh"
#endif



int main(int argc, char **argv)
{
    //Setup the Random number singleton
   NeuFlux::NeuRandom::GetInstance();


   G4cout<<"  Setting up Run Manager"<<std::endl;
   
   G4RunManager* runManager = new G4RunManager;
   
   NeuFlux::NeuWorldGeometry* geometry = new NeuFlux::NeuWorldGeometry;

   runManager->SetUserInitialization(geometry);
   
   runManager->SetUserInitialization( new QGSP_BIC_HP);
   //runManager->SetUserInitialization( new QGSP_BERT_HP);
   //runManager->SetUserInitialization( new QGSP_BERT_EMV);

#ifdef G4VIS_USE
   G4cout<<"  Setting up Visualization Manager"<<std::endl;
   G4VisManager *visManager = new NeuFlux::NeuVisManager;
   visManager->SetVerboseLevel(0);
   visManager->Initialize();
#endif

   G4cout<<"  Setting up User Action Classes"<<std::endl;
   NeuFlux::NeuRunAction* runAction = new NeuFlux::NeuRunAction();
   runManager->SetUserAction(runAction);
   G4cout<<"    done setting run action"<<std::endl;
   NeuFlux::NeuEventAction* eventAction =
       new NeuFlux::NeuEventAction();
   runManager->SetUserAction(eventAction);
   runManager->SetUserAction( new NeuFlux::NeuPrimaryGeneratorAction());
   NeuFlux::NeuTrackingAction* trackingAction =
       new NeuFlux::NeuTrackingAction;
   runManager->SetUserAction(trackingAction);
   runManager->
       SetUserAction(new
                     NeuFlux::NeuSteppingAction() ) ;

   G4cout<<"  Initializing the G4 kernel"<<std::endl;

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

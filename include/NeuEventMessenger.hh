
#ifndef NeuEventMessenger_hh_
#define NeuEventMessenger_hh_

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithoutParameter.hh"

namespace NeuFlux
{
	class NeuEventAction;
	class NeuRunAction;
	class NeuTrackingAction;
	class NeuSteppingAction;

	/*!
	  \class NeuEventMessenger
	 
	  \ingroup NeuFlux
	 
	  \brief Messenger Class for Action classes
	 
	  \warning This was incorrectly named, and will be replaced at some point in the future.
	 
	  \author Kevin Wierman
	 
	  \version 1.0
	 
	  \date Oct 1, 2013
	 
	  Contact: kwierman@email.unc.edu

	 */

	class NeuEventMessenger : public G4UImessenger 
	{
	public:
		NeuEventMessenger(NeuFlux::NeuRunAction* run, NeuFlux::NeuEventAction* event, NeuFlux::NeuTrackingAction* track, NeuFlux::NeuSteppingAction* step);
		virtual ~ NeuEventMessenger();

		virtual void SetNewValue(G4UIcommand *, G4String);

	private:
		NeuRunAction* fRunAction;
		NeuEventAction* fEventAction;
		NeuTrackingAction* fTrackingAction;
		NeuSteppingAction* fSteppingAction;

		G4UIdirectory* fNeuFluxDir;
			G4UIdirectory* fActionDir;
				G4UIdirectory* fEventDir;
					G4UIcmdWithABool* fEnableEventAction;
				G4UIdirectory* fRunDir;
					G4UIcmdWithABool* fEnableRunAction;
				G4UIdirectory* fTrackingDir;
					G4UIcmdWithABool* fEnableTrackingAction;
				G4UIdirectory* fSteppingDir;
					G4UIcmdWithABool* fEnableSteppingAction;
	};

}
#endif

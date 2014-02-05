#ifndef NeuMesonProductionCut_h_
#define NeuMesonProductionCut_h_

#include "QGSP_BIC_HP.hh"

#include <vector>
#include <string>

namespace NeuFlux{

	class NeuMesonProductionCut : public  QGSP_BIC_HP
	{
	private:
		double mesonProductionCut;
		std::vector<std::string> particleNames;

	public:
		NeuMesonProductionCut(double cutValue);
		~NeuMesonProductionCut(){}

		void SetCuts(){
			QGSP_BIC_HP::SetCuts();
			for(std::vector<std::string>::iterator i = particleNames.begin(); i!=particleNames.end(); ++i)
				SetCutValue(mesonProductionCut, (*i));
		}
	};
}


#endif //NeuMesonProductionCut_h_



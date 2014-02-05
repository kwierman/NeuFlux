#include "NeuMesonProductionCut.hh"

NeuFlux::NeuMesonProductionCut::NeuMesonProductionCut(double cutValue) : QGSP_BIC_HP(), mesonProductionCut(cutValue){
	particleNames.push_back("k(1460)+");
	particleNames.push_back("k(1460)-");
	particleNames.push_back("k(1460)0");
	particleNames.push_back("pi+");
	particleNames.push_back("pi-");
	particleNames.push_back("pi0");
}



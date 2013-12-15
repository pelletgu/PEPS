#include "stdafx.h"
#include "Wrapper.h"
#include <ctime>
using namespace Engine;

namespace Wrapper {
	//On considère que les options basket
	//void WrapperClass::createBasket(double strike, PnlVect* coeff, Basket *bask){
	//	bask = new Basket(strike, coeff);
	//}

	//void WrapperClass::createBs(int size, double r, double rho, PnlVect *sigma, PnlVect *spot, PnlVect *trend, BS *Bsmod){
	//	Bsmod = new BS(size,r,rho,sigma,spot,trend);
	//}

	//void WrapperClass::createMontecarlo(BS *Bs, Option *Opt, PnlRng* rng, double h, int samples, MonteCarlo *Mc){
	//	Mc = new MonteCarlo(Bs, Opt, rng,h, samples);
	//}

	//void WrapperClass::getPriceOption(double strike, int size, double r, double rho, double h, int samples){
	//	double ic, px;
	//	//Création de l'option
	//	Basket *bask = new Basket();
	//	PnlVect *coeff = pnl_vect_create_from_double(1,1);
	//	createBasket(strike,coeff,bask);
	//	//Création du modèle
	//	BS *bsmod = new BS();
	//	PnlVect *sigma = pnl_vect_create_from_double(1,0.2);
	//	PnlVect *spot = pnl_vect_create_from_double(1,100);
	//	PnlVect *trend = pnl_vect_create_from_double(1,0.4);
	//	createBs(size,r,rho,sigma,spot,trend,bsmod);
	//	//Création de l'objet MonteCarlo
	//	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	//	pnl_rng_sseed(rng, time(NULL));
	//	MonteCarlo *mc = new MonteCarlo(rng);
	//	createMontecarlo(bsmod,bask,rng,h,samples,mc);
	//	//Enfin on price
	//	(*mc).price(px,ic);
	//	this->intConfiance = ic;
	//	this->prix = px;
	//}

	void WrapperClass::getPriceOption(int samples,String ^type, int size, double r, array<double,1> ^ro, double strike, array<double,1> ^sigm){
		double ic = 0;
		double px = 0;
		char* tyype = static_cast<char *>(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(type).ToPointer());
		System::Runtime::InteropServices::Marshal::FreeHGlobal(safe_cast<IntPtr>(tyype));
		double* sigma = new double[sigm->Length];
		sigma[0] = (double)sigm->GetValue(0);
		double* rho = new double[ro->Length];
		rho[0] = (double)ro->GetValue(0);
		price(px, ic, samples, tyype, size, r, rho, strike, sigma);
		this->intConfiance = ic;
		this->prix = px;
	}


}
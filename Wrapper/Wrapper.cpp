#include "stdafx.h"
#include "Wrapper.h"
#include <ctime>
using namespace Engine;

namespace Wrapper {
	//On consid�re que les options basket
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
	//	//Cr�ation de l'option
	//	Basket *bask = new Basket();
	//	PnlVect *coeff = pnl_vect_create_from_double(1,1);
	//	createBasket(strike,coeff,bask);
	//	//Cr�ation du mod�le
	//	BS *bsmod = new BS();
	//	PnlVect *sigma = pnl_vect_create_from_double(1,0.2);
	//	PnlVect *spot = pnl_vect_create_from_double(1,100);
	//	PnlVect *trend = pnl_vect_create_from_double(1,0.4);
	//	createBs(size,r,rho,sigma,spot,trend,bsmod);
	//	//Cr�ation de l'objet MonteCarlo
	//	PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
	//	pnl_rng_sseed(rng, time(NULL));
	//	MonteCarlo *mc = new MonteCarlo(rng);
	//	createMontecarlo(bsmod,bask,rng,h,samples,mc);
	//	//Enfin on price
	//	(*mc).price(px,ic);
	//	this->intConfiance = ic;
	//	this->prix = px;
	//}

	void WrapperClass::getPriceOption(String ^type_sharp, int size, array<double> ^spot_sharp, 
double strike, double maturity, array<double> ^sigma_sharp, double r, array<double> ^rho_sharp, array<double> ^coeff_sharp, int timeStep, int samples){
		double ic = 0;
		double px = 0;
		int i = 0;

		char* type = static_cast<char *>(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(type_sharp).ToPointer());
		System::Runtime::InteropServices::Marshal::FreeHGlobal(safe_cast<IntPtr>(type));
		
		double* spot = new double[size];
		for (i = 0; i < size; i++)
			spot[i] = (double)spot_sharp->GetValue(i);

		double* sigma = new double[size];
		for (i = 0; i < size; i++)
			sigma[i] = (double)sigma_sharp->GetValue(i);
		
		int rho_size = (size-1)*size/2;
		double* rho = new double[rho_size];
		for (i = 0; i < rho_size; i++)
			rho[i] = (double)rho_sharp->GetValue(i);
		
		double* coeff = new double[size];
		for (i = 0; i < size; i++)
			coeff[i] = (double)coeff_sharp->GetValue(i);

		price(px, ic, type, size, spot, strike, maturity, sigma, r, rho, coeff, timeStep, samples);

		this->intConfiance = ic;
		this->prix = px;
	}


}
#include "pricer.h"
using namespace std;

/*!
 * \file pricer.cpp
 * \brief Fichier de test pour le price d'option à t=0
 * \author equipe 11
 */

void Engine::price(double &prix, double &ic, int samples,char *type, int size, double r, double rho[], double strike, double sigma[])//, PnlVect *sigma)
{
  PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
  pnl_rng_sseed(rng, time(NULL));
  PnlVect *sigm = pnl_vect_create(1);//
  pnl_vect_set(sigm,0,sigma[0]);
  PnlVect *spot = pnl_vect_create_from_double(1,100);
  PnlVect *trend = pnl_vect_create_from_double(1,0.4);
  PnlVect *coeff = pnl_vect_create_from_double(1,1);


  //Parser mon_parser = Parser(argv[1]);
    BS bs(size, r, rho, sigm, spot, trend);
  //if (!strcmp("basket", type)){
	Playlist play(1,52,size,strike);
	MonteCarlo mc(&bs, &play, rng, 0.1,samples);
	mc.price(prix, ic);
	pnl_rng_free(&rng);
}

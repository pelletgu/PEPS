# include "Option.h"
# include "Basket.h"
# include <pnl/pnl_mathtools.h>

/*!
 * \file Basket.cpp
 * \brief Option panier
 * \author Equipe 11
 */

Basket :: Basket() : Option() {
  strike_ = 0;
  Coeff_ = pnl_vect_new();
}

Basket::Basket(double strike, double* coeff, double T, int timeStep, int size) : Option(T, timeStep, size){
	strike_ = strike;
	Coeff_ = pnl_vect_create(size_);
	for (int i = 0; i < size_; i++){
		LET(Coeff_, i) = coeff[i];
	}
}

Basket :: ~Basket(){
  pnl_vect_free(&Coeff_);
}

double Basket :: get_strike() {
  return strike_;
}

PnlVect * Basket :: get_Coeff() {
  return Coeff_;
}

void Basket :: set_strike(double strike) {
  strike_ = strike;
}

void Basket :: set_Coeff(PnlVect *Coeff) {
  Coeff_ = Coeff;
}

double Basket :: payoff (const PnlMat *path) {
  double sum;
  PnlVect* final = pnl_vect_create(path->m);

  //On met dans final la derni�re colonne de Path correspond � la valeur � maturit� des sous-jacents.
  pnl_mat_get_col(final, path, (path->n-1));
  sum = pnl_vect_scalar_prod(final, Coeff_) - strike_;
  pnl_vect_free(&final);
  //On retourne le max entre le r�sultat de la somme et 0
  return MAX(sum, 0);
}

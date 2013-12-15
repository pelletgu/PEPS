# include "option.h"
# include "basket.h"
# include <pnl/pnl_mathtools.h>

/*!
 * \file basket.cpp
 * \brief Option panier
 * \author Equipe 11
 */

Basket :: Basket() : Option() {
  Strike_ = 0;
  Coeff_ = pnl_vect_new();
}

//Basket :: Basket(Parser& pars):Option(pars){
//  Strike_ = pars.getDouble("strike");
//  Coeff_ = pnl_vect_copy(pars.getVect("payoff coefficients"));
//}
Basket::Basket(double strike, const PnlVect *coeff):Option(1,100,1){
	Strike_ = strike;
	Coeff_ = pnl_vect_copy(coeff);
}

Basket :: ~Basket(){
  pnl_vect_free(&Coeff_);
}

double Basket :: get_Strike() {
  return Strike_;
}

PnlVect * Basket :: get_Coeff() {
  return Coeff_;
}

void Basket :: set_Strike(double Strike) {
  Strike_ = Strike;
}

void Basket :: set_Coeff(PnlVect *Coeff) {
  Coeff_ = Coeff;
}

double Basket :: payoff (const PnlMat *path) {
  double sum;
  PnlVect* final = pnl_vect_create(path->m);

  //On met dans final la derni�re colonne de Path correspond � la valeur � maturit� des sous-jacents.
  pnl_mat_get_col(final, path, (path->n-1));
  sum = pnl_vect_scalar_prod(final, Coeff_) - Strike_;
  pnl_vect_free(&final);
  //On retourne le max entre le r�sultat de la somme et 0
  return MAX(sum, 0);
}

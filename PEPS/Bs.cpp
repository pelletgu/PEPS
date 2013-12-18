/*!
 *  \file	Bs.cpp
 *  \brief	Impl�mentation de la classe Black-SCholes
 *  \author Equipe 11
 */

#include "Bs.h"
#include <math.h>
#include <cstdio>
#include "montecarlo.h"

using namespace std;
Bs::Bs(){
  size_ = 0;
  r_ = 0.0;
  rho_ = new double();
  sigma_ = pnl_vect_new();
  spot_ = pnl_vect_new();
  trend_ = pnl_vect_new();
  Cho_ = pnl_mat_new();
  Gi_ = pnl_vect_new();
  Ld_ = pnl_vect_new();
}


Bs::Bs(int size, double r, double* rho, double* sigma, double* spot, double* trend){
	(*this).size_ = size;
	(*this).r_ = r;
	(*this).rho_ = rho;
	(*this).sigma_ = pnl_vect_create(size_);
	(*this).spot_ = pnl_vect_create(size_);
	(*this).trend_ = pnl_vect_create(size_);
		(*this).Cho_ = pnl_mat_create_from_double(size_, size_, 1);
	int compteur = -1;
	for (int i = 1; i < size; i++){
		for (int j = 0 ; j < i; j++){
			MLET(Cho_, i, j) = rho_[++compteur];
			MLET(Cho_, j, i) = rho_[compteur];
		}
	}
	for (int i = 0; i < size_; i++){
			LET(sigma_, i) = sigma[i];
			LET(spot_, i) = spot[i];
		if (trend != NULL)
			LET(trend_, i) = trend[i];
		pnl_mat_set_diag(Cho_, 1, i);
	}
	pnl_mat_chol(Cho_);

	Gi_ = pnl_vect_create(size_);
	Ld_ = pnl_vect_create(size_);
}


Bs::~Bs(){
  pnl_vect_free(&sigma_);
  pnl_vect_free(&spot_);
  pnl_vect_free(&trend_);
  pnl_vect_free(&Gi_);
  pnl_vect_free(&Ld_);
  pnl_mat_free(&Cho_);
}

int Bs::get_size(){
  return size_;
}

double Bs::get_r(){
  return r_;
}

double* Bs::get_rho(){
  return rho_;
}

PnlVect * Bs::get_sigma(){
  return sigma_;
}

PnlVect * Bs::get_spot(){
  return spot_;
}

PnlVect * Bs::get_trend(){
  return trend_;
}

PnlMat * Bs::get_cho(){
  return Cho_;
}

PnlVect * Bs::get_gi(){
  return Gi_;
}

PnlVect * Bs::get_ld(){
  return Ld_;
}

void Bs::set_size(int size){
  size_ = size;
}

void Bs::set_r(double r){
  r_ = r;
}


void Bs::set_rho(double* rho){
  rho_ = rho;
}

void Bs::set_sigma(PnlVect *sigma){
  sigma_ = sigma;
}

void Bs::set_spot(PnlVect *spot){
  spot_ = spot;
}

void Bs::set_trend(PnlVect *trend){
  trend_ = trend;
}

void Bs::set_cho(PnlMat *Cho){
  Cho_ = pnl_mat_copy(Cho);
}

void Bs::set_gi(PnlVect *Gi){
  Gi_ = Gi;
}

void Bs::set_ld(PnlVect *Ld){
  Ld_ = Ld;
}

void Bs::asset(PnlMat *path, double T, int N, PnlRng *rng, PnlMat* G, PnlVect* grid){
  //s: double pour la valeur du sous-jacent � la date t_{i+1}
  double s;
  //diff: double t_{i+1}-t_{i}
  double diff;

  //Simulation de la suite (G_i)i>=1 iid de vecteurs gaussiens centr�s de matrice de covariance identit�
  pnl_mat_rng_normal(G, N, size_, rng);
  //Calcul de l'�volution du sous-jacent de chaque actif pour t=t_1 � t=t_N;
  for (int d=0; d<size_; d++){
	for (int i=0; i<N; i++){
	  //S�lection de la ligne de la matrice de Cholesky associ� � l'actif sur lequel on travaille
	  pnl_mat_get_row(Ld_, Cho_, d);
	  //S�lection de la ligne de la matrice de vecteurs gaussiens associ� au temps sur lequel on travaille
	  pnl_mat_get_row(Gi_, G, i);
	  //Calcul de la diff�rence de pas de temps
	  diff = pnl_vect_get(grid, i+1)-pnl_vect_get(grid, i);
	  //Calcul de l'�volution du sous-jacent � l'aide de la formule du mod�le de Bs
	  s = pnl_mat_get(path, d, i)*
		exp((r_-pow(pnl_vect_get(sigma_, d),2.0)/2)*diff +
			pnl_vect_get(sigma_, d)*sqrt(diff)*pnl_vect_scalar_prod(Ld_, Gi_));
	  //Ajout du r�sultat dans path
	  pnl_mat_set(path, d, i+1, s);
	}
  }
}

void Bs::asset(PnlMat *path, double t, int N, double T, PnlRng *rng, const PnlMat *past, int taille, PnlMat* G, PnlVect* grid){
  //s: double pour la valeur du sous-jacent � la date t_{i+1}
  double s;
  //diff: double t_{i+1}-t_{i}
  double diff;

  //Simulation de la suite (G_i)i>=1 iid de vecteurs gaussiens cent�s de matrice de covariance identit�
  pnl_mat_rng_normal(G, N-taille, size_, rng);
  //Calcul de l'�volution du sous-jacent de chaque actif pour t=t_{i+1} � t=t_N;
  for (int d=0; d<size_; d++){
	for (int i=0; i<N-taille; i++){
	  //S�lection de la ligne de la matrice de Cholesky associ� � l'actif sur lequel on travaille
	  pnl_mat_get_row(Ld_, Cho_, d);
	  //S�lection de la ligne de la matrice de vecteurs gaussiens associ� au temps sur lequel on travaille
	  pnl_mat_get_row(Gi_, G, i);
	  //Calcul de la diff�rence de pas
	  diff = pnl_vect_get(grid, i+1)-pnl_vect_get(grid,i);
	  //Si calcul du temps apr�s t
	  //alors on selectionne la valeur du sous-jacent � t dans la matrice past
	  //sinon on s�lectionne � la valeur du sous-jacent � t_{i} dans path
	  if (i==0)
		s = pnl_mat_get(past, d, past->n-1);
	  else
		s = pnl_mat_get(path, d, i+taille);
	  //Calcul de l'�volution du sous-jacent � l'aide de la formule du mod�le de Bs
	  s = s*exp((r_-pow(pnl_vect_get(sigma_, d),2.0)/2)*diff + pnl_vect_get(sigma_, d) * sqrt(diff) * pnl_vect_scalar_prod(Ld_, Gi_));
	  //Ajout du r�sultat dans path
	  pnl_mat_set(path, d, i+taille+1, s);
	}
  }
}


void Bs:: shift_asset (PnlMat *_shift_path, const PnlMat *path,
	int d, double h, double t, double timeStep){
  pnl_mat_clone(_shift_path, path);
  for (int i=0; i<timeStep+1; i++){
	if (i>t){
	  pnl_mat_set(_shift_path, d,i, (1+h)*pnl_mat_get(path, d,i));
	}
  }
}

void Bs:: simul_market (PnlMat* past, int H, double T, PnlRng *rng){
  //Temps: incr�mentation pour chaque date de constation
  double temps = T/H;
  //s: valeur du sous-jacent � la date t_{i+1}
  double s;
  //diff: calcul de la diff�rence de temps entre t_{i+1} et t_{i}
  double diff;
  //G: matrice de dimension H*d pour g�n�rer une suite iid selon la loi normale centr�e r�duite
  PnlMat *G = pnl_mat_create(H, size_);
  //Grid: vecteur de taille H+1 pour g�n�rer la grille de temps (t_0=0, ..., t_N)
  PnlVect *grid = pnl_vect_create(H+1);

  //Calcul des dates de constatation;
  for (int t=0; t<H+1; t++){
	pnl_vect_set(grid, t, temps*t);
  }
  //Ajout de la trajectoire du mod�le dans past
  //Ajout du prix spot dans la premi�re colonne de path
  pnl_mat_set_col(past, spot_, 0);
  //Simulation de la suite (G_i)i>=1 iid de vecteurs gaussiens cent�s de matrice de covariance identit�
  pnl_mat_rng_normal(G, H, size_, rng);
  //Calcul de l'�volution du sous-jacent de chaque actif pour t=tau_1 � t=tau_H;
  //Idem � asset pour t>0 mais on utilise le taux d'int�r�t sous la probabilit� historique
  //et on ajoute les r�sultats dans la matrice past
  for (int d=0; d<size_; d++){
	for (int i=0; i<H; i++){
	  pnl_mat_get_row(Ld_, Cho_, d);
	  pnl_mat_get_row(Gi_, G, i);
	  diff = pnl_vect_get(grid, i+1)-pnl_vect_get(grid, i);
	  s = pnl_mat_get(past, d, i)*
		exp((pnl_vect_get(trend_, d)-pow(pnl_vect_get(sigma_, d),2.0)/2)*diff +
			pnl_vect_get(sigma_, d)*sqrt(diff)*pnl_vect_scalar_prod(Ld_, Gi_));
	  pnl_mat_set(past, d, i+1, s);
	}
  }

  pnl_mat_free(&G);
  pnl_vect_free(&grid);
}

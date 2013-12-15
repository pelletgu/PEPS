# include "Playlist.h"
# include <pnl/pnl_mathtools.h>

/*!
 * \file playlist.cpp
 * \brief Produit structuré
 * \author Equipe 11
 */

Playlist :: Playlist(){
  Size_ = 4;
  T_ = 1;
  TimeSteps_ = 0;
  Strike_ = 0;
}

Playlist :: Playlist(double T, int Timesteps, int size, double Strike){
	T_ = T;
	TimeSteps_ = Timesteps;
	Size_ = size;
	Strike_ = Strike;
}

Playlist :: ~Playlist(){
}

double Playlist :: get_T() {
  return T_;
}

int Playlist :: get_Timesteps() {
  return TimeSteps_;
}

int Playlist:: get_Size(){
	return Size_;
}

double Playlist :: get_Strike() {
  return Strike_;
}

void Playlist :: set_T(double T) {
  T_ = T;
}

void Playlist :: set_Timesteps(int TimeSteps) {
  TimeSteps_ = TimeSteps;
}

void Playlist:: set_Size(int size){
	Size_ = size;
}

void Playlist :: set_Strike(double Strike) {
  Strike_ = Strike;
}

double Playlist :: payoff (const PnlMat *path) {
  //On retourne le max entre le résultat de la somme et 0
  return MAX(pnl_mat_get(path,0,50)-Strike_, 0);
}
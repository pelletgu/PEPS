//#include "parser.h"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"
#ifndef OptionH
#define OptionH

/*!
 *  \file	option.h
 *  \brief	Header de la classe Option
 *  \author Equipe 11
 */

/*!
 * \class option
 * \brief Classe representant la classe mere de tous les types d'options: Option
 */
class Option {

  protected: 
	double T_; /*!< maturite */
	int timeStep_; /*!< nombre de pas de temps de discretisation */
	int size_; /*!< dimension du modele, redondant avec option::size_ */

  public:

	/*!
	 * \brief Constructeur par defaut
	 *
	 * Constructeur par defaut de la classe option
	 */
	Option();

	/*!
	 * \brief Constructeur avec argument
	 *
	 * Constructeur avec argument de la classe option
	 *
	 * \param pars: Liste des donnees relatives a l'option du Parser
	 */
	//Option(Parser pars);



	Option(double T, int timeStep, int size);
	
	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe option
	 */
	virtual ~Option();

	/*!
	 * \brief Accesseur de T_
	 *
	 *  Acceder � la maturite du sous-jacent
	 *
	 * \return la maturite du sous-jacent
	 */
	double get_T();

	/*!
	 * \brief Accesseur de timeStep_
	 *
	 *  Acceder au nombre de pas de temps de discretisation
	 *
	 *  \return le nombre de pas de temps de discretisation
	 */
	int get_timeStep();

	/*!
	 * \brief Accesseur de size_
	 *
	 *  Acceder a la taille du sous-jacent
	 *
	 * \return la taille du sous-jacent
	 */
	int get_size();

	/*!
	 * \brief Mutateur de T_
	 *
	 *  Modifier la maturite du sous-jacent
	 *
	 * \param la nouvelle maturite du sous-jacent
	 */
	void set_T(double T);

	/*!
	 * \brief Mutateur de timeStep_
	 *
	 *  Modifier le nombre de pas de temps de discretisation 
	 *
	 * \param le nouveau nombre de pas de temps de discretisation
	 */
	void set_timeStep(int timeStep);

	/*!
	 * \brief Mutateur de size_
	 *
	 *  Modifier a la taille du sous-jacent
	 *
	 * \param la nouvelle taille du sous-jacent
	 */
	void set_size(int size);


	/*!
	 * \brief Calcule la valeur du payoff sur la trajectoire passee en parametre
	 * 
	 *  \param path (input) est une matrice de taille d x (N+1) contenant une
	 *  trajectoire du modele telle que creee par la fonction asset.
	 *  \return phi(trajectoire)
	 */
	virtual double payoff (const PnlMat * path) = 0;
};
#endif 

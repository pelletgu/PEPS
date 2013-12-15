#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"
#ifndef PlaylistH
#define PlaylistH

/*!
 *  \file	playlist.h
 *  \brief	Header de la classe fille d'Option: playlist
 *  \author Equipe 11
 */

/*!
 * \class Playlist
 * \brief Classe representant le produit structur� Playlist
 */
class Playlist{

  private:
	double T_; /*!< maturite fix� � 1an par d�fault */
	int TimeSteps_; /*!< nombre de pas de temps de discretisation pour 1 ann�e */
	int Size_; /*!< dimension du modele, redondant avec option::size_, fix� � 4 */
	double Strike_; /*!<Valeur d'une part normalement soit 150�*/

  public:

	/*!
	 * \brief Constructeur par defaut
	 *
	 * Constructeur par defaut de la classe basket
	 */
	Playlist();

	/*!
	 * \brief Constructeur avec argument
	 *
	 * Constructeur avec argument de la classe basket
	 *
	 * \param pars: Liste des donnees relatives a l'option du Parser
	 */
	Playlist(double T, int Timesteps, int Size, double Strike);
	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe basket
	 */
	virtual ~Playlist();

	/*!
	 * \brief Accesseur de T__
	 *
	 *  Acceder � la maturit� de l'option
	 *
	 * \return la maturit� de l'option 
	 */
	double get_T();

	/*!
	 * \brief Accesseur de Timesteps_
	 *
	 *  Acceder au nombre de pas de discr�tisation par an de l'option
	 *
	 * \return le nombre de pas de discr�tisation de l'option 
	 */
	int get_Timesteps();

	/*!
	 * \brief Accesseur de Size_
	 *
	 *  Acceder au nombre de sous ajcents de l'option
	 *
	 * \return le nombre de sous jacents de l'option 
	 */
	int get_Size();

	/*!
	 * \brief Accesseur de Strike_
	 *
	 *  Acceder au strike de l'option
	 *
	 * \return le strike de l'option 
	 */
	double get_Strike();

	/*!
	 * \brief Mutateur de T_
	 *
	 * Modifie la valeur de la maturit� de l'option
	 *
	 * \param T: nouvelle maturit�
	 */
	void set_T(double T);

	/*!
	 * \brief Mutateur de TimeSteps
	 *
	 * Modifie la valeur du nombre de discr�tisation de l'option
	 *
	 * \param Timesteps : nouveau nombre de dsicr�tisation
	 */
	void set_Timesteps(int TimeSteps);

	/*!
	 * \brief Mutateur de Size_
	 *
	 * Modifie la valeur du nombre de sous jacents de l'option
	 *
	 * \param Size: nouveau nombre de sous jacent
	 */
	void set_Size(int Size);

	/*!
	 * \brief Mutateur de Strike_
	 *
	 * Modifie la valeur du strike de l'option
	 *
	 * \param Strike: nouveau strike
	 */
	void set_Strike(double Strike);

	/*!
	 * \brief Payoff option panier
	 *
	 * Calcul la valeur du payoff de l'option panier sur la trajectoire passee en parametre
	 *
	 * \param path: matrice de taille d x (N+1) contenant une trajectoire du modele telle que creee par la fonction asset
	 * \return payoff de l'option panier
	 */
	 double payoff (const PnlMat * path);
}; 
#endif 
#include <pnl/pnl_vector.h>
#include <string.h>

#ifndef TYPEVALH
#define TYPEVALH

/*!
 *  \filetypeval.h
 *  \brief Header de la structure TypeVal
 *  \author Equipe 11
 */



// liste des types
typedef enum {
  T_NULL,
  T_INT,
  T_DOUBLE,
  T_VECTOR,
  T_STRING
} T_type;

/*!
 * \struct TypeVal
 * \brief Structure des types utilis�s dans le parser
 */
struct TypeVal
{
  bool is_set; /*!< La valeur de la cl� existe */
  T_type type; /*!< Type de la valeur de la cl� */
  union {
    double V_double; /*!< Valeur r�elle de la cl� */
    int V_int; /*!< Valeur enti�re de la cl� */
    char *V_string; /*!< Valeur d'une cha�ne de caract�res de la cl� */
    PnlVect *V_vector; /*!< Valeur vectorielle de la cl� */
  }; // value
  
  /*!
   * \brief Constructeur par d�faut
   *
   * Constructeur par d�faut d'un objet TypeVal
   */
  TypeVal ();

  /*!
   * \brief Destructeur par d�faut
   *
   * Destructeur par d�faut d'un objet TypeVal
   */
  ~TypeVal ();
};


#endif

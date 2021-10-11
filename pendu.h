# define TAILLE 100
# define PC_COUPS 10
# ifndef __PENDU_H__

# define __PENDU_H__
union U_tmp
{
  char tmp_string[TAILLE];
  int tmp_int;
  char tmp_char;
  double tmp_double;
};
typedef union U_tmp U_tmp;
void menu(int choix);
int wc(const char *file); // la fonction renvoie -1 si le fichier n'a pas pu etre ouvert... sinon la fonction renvoie le nombre de mot(s) du dictionnaire.
char *ws(const int word_nbr);
char *wh(const char *string);
void caract_shower(const char *real_word,char *hiding_word,char caract,int *booleen);
int verif(const char *hiding_word);
int random_number(const int MAX);
void retranche(int *nbr_coup);
void get_char(char *caract);
void str_cat(char *string,char caract);
# endif

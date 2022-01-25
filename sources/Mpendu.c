# include<stdio.h>
# include<stdlib.h>
# include<string.h>
/* ****************************** */
# include"pendu.h"

int main(int argc,char *argv[])
{
  char *hiding_word=NULL,*real_word=NULL,caract=0;
  int booleen=0,bool=0,nbr_coups=PC_COUPS,choix=0; //booleen est un booléen qui nous permettra de savoir si le joueur à trouver ou pas une lettre du mot du dictionnaire choisie par l'utilisateur.
  
  do
    {
      menu(0);
      printf("Quel est votre choix\n");
      scanf("%d",&choix);
      while(choix<1||choix>4)
	{
	  printf("Entrez un nombre compris entre 1 et 4 SVP!\n");
	  scanf("%d",&choix);
	}
      switch(choix)
	{
	case 1:
	  menu(choix);
	  real_word=ws(random_number(wc("../files/dictionnaire.txt")));
	  // *bon*
	  hiding_word=wh(real_word);
	  do
	    {
	      printf("nombre de coup(s) restant: %d coup(s)\n",nbr_coups);
	      //printf("real_word vaut %s\n",real_word);
	      printf("Quel est le mot secret ? %s\n",hiding_word);
	      printf("Entrez une lettre:");
	      get_char(&caract);
	      caract_shower(real_word,hiding_word,caract,&booleen);
	      if(!booleen)
		retranche(&nbr_coups);
	      bool=verif(hiding_word);
	    }while(nbr_coups>0 && !bool);
	  if(bool)
	    {
	      printf("FELICITATION! Le mot mystere était bien %s\n",real_word);
	      nbr_coups=PC_COUPS;
	      free(real_word);
	      free(hiding_word);
	    }
	  else
	    {
	      printf("GAME OVER! Vous avez atteint votre nombre limite de coups\n");
	      printf("Le mot mystere etait: %s\n",real_word);
	      nbr_coups=PC_COUPS;
	      free(real_word);
	      free(hiding_word);
	    }
	  break;
	case 2:
	  menu(choix);
	  break;
	case 3:
	  menu(choix);
	  break;
	case 4:
	  menu(choix);
	  break;
	}
    }while(choix!=4);
  
  return 0; 
}

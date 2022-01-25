# include<stdio.h>
# include<stdlib.h>
# include<time.h>
# include<ctype.h>
# include<string.h>
/* ****************************** */
# include"pendu.h"

void menu(int choix)
{
  int caract=0;
  FILE *P_files=NULL;
  
  switch(choix)
    {
    case 0:
      printf("******************************\n");
      printf("*         JEU DU PENDU       *\n");
      printf("******************************\n");
      printf("\n");
      printf("---> MENU");
      printf("\n\t1.Jouer\n\t2.Aide\n\t3.Apropos du jeu\n\t4.QUITTER\n");
      break;
    case 1:
      printf("\n---> JOUER\n");
      break;
    case 2:
      printf("\n---> AIDE\n");
      P_files=fopen("aide.txt","r");
      if(P_files)
	{
	  do
	    {
	      caract=fgetc(P_files);
	      printf("%c",caract);
	    }while(caract!=EOF);
	  fclose(P_files);
	}
      else
	{
	  printf("Erreur lors de l'ouverture du fichier...\nLe programme va s'arreter!\n");
	  exit(0);
	}
      break;
    case 3:
      printf("\n---> APROPOS\n");
      P_files=fopen("apropos.txt","r");
      if(P_files)
	{
	  do
	    {
	      caract=fgetc(P_files);
	      printf("%c",caract);
	    }while(caract!=EOF);
	  fclose(P_files);
	}
      else
	{
	  printf("Erreur lors de l'ouverture du fichier...\nLe programme va s'arreter!\n");
	  exit(0); // mets fin au programme
	}
      break;
    case 4:
      printf("\n---> QUITTER");
      printf("\n\tMerci d'avoir utilisé notre programme.\nA bientot!!\n");
      break;
    }
}

int wc(const char *file) //file correspond au chemin d'accès du dictionnaire
{
  FILE *P_file=NULL;
  int caract=0,nbr_mots=0;
  
  P_file=fopen(file,"r");
  if(P_file)
    {
      do
	{
	  caract=fgetc(P_file);
	  if(caract=='\n')
	    {
	      nbr_mots++;
	    }
	}while(caract!=EOF);
      fclose(P_file);
    }
  else
    {
      printf("Eureur lors de l'ouverture du fichier dictionnaire.txt\n");
      return -1;
    }
  
  return nbr_mots+1;
}

char *ws(const int word_nbr)
{
  FILE *P_file=NULL;
  int i,caract=0,bool=wc("dictionnaire.txt")-word_nbr,nbr_rligne=0;
  char *string=(char*)malloc(sizeof(char)*TAILLE);

  P_file=fopen("dictionnaire.txt","r");
  if(P_file)
    {
      switch(bool)
	{
	case 0: // ce cas correspond au cas ou c'est le dernier mot qui est choisi...
	  i=0;
	  fseek(P_file,-1,SEEK_END);
	  while(fgetc(P_file)!='\n')
	    {
	      fseek(P_file,-2,SEEK_CUR);
	      i++;
	    }
	  fgets(string,i+1,P_file);
	  break;
	case 113: // ce cas correspond au cas ou c'est le premier mot qui est choisi...
	  i=0;
	  rewind(P_file);
	  do
	    {
	      i++;
	    }while(fgetc(P_file)!='\n');
	  rewind(P_file);
	  fgets(string,i,P_file);
	  break;
	default:
	  rewind(P_file);
	  for(i=0,nbr_rligne=0;nbr_rligne<word_nbr;i++)
	    {
	      caract=fgetc(P_file);
	      if(caract=='\n')
		{
		  nbr_rligne++;
		}
	    }
	  i=0;
	  do
	    {
	      fseek(P_file,-2,SEEK_CUR);
	      caract=fgetc(P_file);
	      i++;
	    }while(caract!='\n');
	  fgets(string,i,P_file); // enregistre le mot dans la variable string
	  // *bon*
	  break;
	}
      fclose(P_file);
    }
  else
    {
      printf("Erreur lors de l'ouverture du fichier/nLe programme va s'arreter\n");
      exit(0);
    }

  return string;
}

char *wh(const char *string)
{
  char *stringh=NULL;
  stringh=(char*)calloc(TAILLE,sizeof(char));
  int i;

  for(i=0;i<strlen(string);i++)
    {
      str_cat(stringh,'*');
    }
  
  return stringh;
}

void caract_shower(const char *real_word,char *hiding_word,char caract,int *booleen)
{
  int i;
  U_tmp tmp={""};
  *booleen=0;

  for(i=0;real_word[i]!='\0';i++)
    {
      //printf("Caract vaut : %c\n",caract);
      if(caract==real_word[i])
	{
	  
	  // printf("la valeur de caract est :%c\n",caract);
	  str_cat(tmp.tmp_string,caract);
	  *booleen=1;
	}
      else
	{
	  if(hiding_word[i]=='*')
	    str_cat(tmp.tmp_string,'*');
	  else
	    str_cat(tmp.tmp_string,hiding_word[i]);
	}
    }
  strcpy(hiding_word,tmp.tmp_string);
}

int verif(const char *hiding_word)
{
  int i,bool=1;

  for(i=0;hiding_word[i]!='\0';i++)
    {
      if(hiding_word[i]=='*')
	bool=0;
    }

  return bool; // 1 signifie que le joueur à gagner et 0 qu'il n'a pas encore gagné.
}

int random_number(const int MAX)
{
  srand(time(NULL));
  return rand()%MAX+1;
}

void retranche(int *nbr_coup)
{
  *nbr_coup-=1; // la décrémentation sous forme x-- ne semble pas marché avec les pointeurs... 
}

void get_char(char *caract)
{
  *caract=getchar(); // getchar permet de récuperer un caractère au clavier
  *caract=toupper(*caract); // toupper permet de transformer une lettre en majuscule
  while(getchar()!='\n'); // le but est d'appeler continuellement getchar jusqu'a ce que le curseur dans le fichier stdin dépasse le caractère '\n'
}

void str_cat(char *string,char caract)
{
  *(string+strlen(string))=caract;
  *(string+strlen(string)+1)='\0';
}

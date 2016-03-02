#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
typedef enum{faux,vrai}Booleen;
/**************** Structure Date ***************
jour	jour de la date en question
mois	mois de la date en question
annee	annee de la date en question

*/
typedef struct
    	{
    	int jour;
    	int mois;
    	int annee;
    	}date;
/**************** Structure Ouvrage ***************
cote	cote de l'ouvrage
categ	categorie de l'ouvrage (BD/ROM/...)
editeur	nom de l'editeur de l'ouvrage
nbexemplaireDispo	nombre de livre actuellement disponnible 
agelimit	age minimum pour emprunter le livre
titre	titre de l'ouvrage
*/
typedef struct
    	{
	char cote[7];
    	char categ[4];
    	char editeur[20];
    	int nbexemplaireDispo;
	int agelimit;
    	char titre[40];
    	}Ouvrage;
/**************** Structure Ouvrage ***************
num	numero de l'emprunt qui s'incremente automatiquement
nom 	nom de l'etudiant
prenom	   prenom de l'etudiant
cote	 cote du l'ouvrage emprunter
debut 	  date de début de l'emprunt
retour     date de retour de l'emprunt qui est nul au départ
*/
typedef struct
    	{
    	int num;
    	char nom[30];
    	char prenom[30];
    	char cote[7];
    	date debut;
    	date retour;
    	}Emp;
/**************** Structure de la Liste ***************
emprunts	structure emprunts
*suiv	     pointeur sur le maillon suivant
*/
typedef struct maillon
    	{
    	Emp emprunts;
    	struct maillon *suiv;
    	}Maillon,*Emprunt;
typedef struct 
    	{
    	char tel[16];
    	}telephone;
/**************** Structure Etudiant ***************
num	numero de l'étudiant
nom	nom de l'etudiant
prenom	prenom de l'etudiant
naissance	date de naissance de l'etudiant
sexe	sexe de l'etudiant
nbEmp	nombre d'emprunts que l'etudiant totalise
nbEmpCour	nombre d'emprunts que l'etudiant possede actuallement
email	email de l'etudiant
p[0]	telephone mobile de l'etudiant
p[1]	telephone fixe de l'etudiant
p[2]	telephone de la personne a contacter en cas d'urgence
adresse	adresse de l'etudiant
*/
typedef struct
    	{
    	int num;
    	char nom[30];
    	char prenom[30];
    	date naissance;
    	char sexe;
    	int nbEmp;
    	int nbEmpCour;
    	char email[30];
    	telephone p[2];  /*tel mobile tel fixe et tel a une personne a contacter*/
    	char adresse[30];
    	}etudiant;
/*Gestion Ouvrage*/
int menuOuvrage (void);
void afficherMenuOuvrage(void);
void globalBiblio(void);
Ouvrage*chargerOuvrage(Ouvrage touvrage[],int *nbmax,int *nbouv);
Ouvrage saisieOuvrage(FILE *flot);
void afouvrage(Ouvrage touvrage[],int nbouv);
int rechOuvrage(Ouvrage touvrage[],char coterech[],int nbouv);
int rechOuvrageInsert(Ouvrage touvrage[],char coterech[],int nbouv);
int insererouv(Ouvrage touvrage[],int nbouv);
int supprimouv(Ouvrage touvrage[],int nbouv);
void afficherMenu(void);
int menu(void);
void sauvegarderOuv (Ouvrage touvrage[],int nbouv);
void affichUnOuvrage(Ouvrage touvrage[],int nbouv);
void affichEditOuvrage(Ouvrage touvrage[],int nbouv);
void modifierouv(Ouvrage touvrage[],int nbouv);
void afficherModOuvrage(void);
int menuModOuv(void);
/*Gestion Etudiant*/
int saisieEtudiant (etudiant *tEtudiant[],int *nbEtudiant,int taillephy); 
void afficheEtud (etudiant Etudiant);
void afficheEtuds (etudiant *tEtudiant[],int nbEtudiant);
void suprimer (etudiant *tEtudiant[],int *nbEtudiant);
void saisir(char nom[],char prenom[]);
void modifierEtudiant(etudiant *tEtudiant[],int nbEtudiant);
int rechEtudiant(char nom[],char prenom[],etudiant *tEtudiant[],int nbEtudiant);
int chargeFEtudiant(etudiant *tEtudiant[],int nbEtudiant,int nbmax);
void sauveTEtudiant( etudiant *tEtudiant[],int nbEtudiant);
void afficherMenuEtudiant(void);
int menuEtudiant(void);
void globalEtudiant(void);
void afficheUnEtudiant (etudiant *tEtudiant[],int nbEtudiant);
int calculAge (date d,date system);
void insererEtud (etudiant *tEtudiant[],int nbEtudiant,int pos,etudiant e);
void supprimer (etudiant *tEtudiant[],int nbEtudiant,int pos);
Booleen presence (etudiant a,char nom[],char prenom[]);
/*Gestion Emprunt*/
date initialiserDate(void);
Booleen testDate(date dat);
date dateJour(void);
Emprunt empVide(void);
Emprunt insererEnTete(Emprunt emp,Emp e);
Emprunt insererEmp(Emprunt emp,Emp e);
void afficherEmprunt(Emprunt emp,int nbEtudiant,etudiant *tEtudiant[]);
int nbJour(Emprunt emp,date jour);
int afficherNonRetour(Emprunt emp,date jour);
Booleen estVide(Emprunt emp);
Emprunt insererEmprunt(Emprunt emp,int *nbEmp,date jour,Ouvrage touvrage[],int nbouv,int nbEtudiant,etudiant *tEtudiant[]);
Emprunt retourEmprunt(Emprunt emp,int *nbEmp,date jour,Ouvrage touvrage[],int nbouv,int nbEtudiant,etudiant *tEtudiant[]);
Emp copieEmprunt(Emprunt emp,char nom[],char prenom[],char cote[]);
Emprunt supprimerEmprunt(Emprunt emp,char nom[],char prenom[],char cote[]);
void sauvegarderEmp (Emprunt emp);
Emprunt chargerEmprunts(Emprunt emp,int *nbEmp);
int menuEmprunt(void);
void afficherMenuEmprunt(void);
/*Statistique*/
void statistique(int nbouv,int nbEtudiant,etudiant *tEtudiant[],Emprunt emp,date jour);
int nbEmpr(Emprunt emp);
int somAges(etudiant *tEtudiant[],int nbEtudiant,date jour);

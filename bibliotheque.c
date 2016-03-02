#include"bibliotheque.h"
/* -----Global du programe----- */
/*
Finalité :
Description: Cette fonction est la fonction global du programme
Paramètre en entrée : aucun
Valeur retournée: aucun
Variables:emp declaration de la liste possedants des emprunts
	  *tEtudiant[1000] tableau de pointeur sur des structures etudiant de taille 1000
	  *touvrage tableau dynamique de structure Ouvrage 
	  jour structure date : stucture servant a contenir la date systeme
	  entier:nbouvmax(nombre d'ouvrage maximum egale a 5 au départ)
		 nbouv(nombre d'ouvrage de la bibliotheque)
		 choixouv,choixmenu,choixetud,choixEmp(entier permettant le choix dans les différent menus)
		 nbEtudiant(nombre d'étudiant egale a 0 au départ)
		 nbEmp(nombre d'emprunts de la bibliotheque)
		 nbRet(entier du code retour de afficherNonRetour permettant l'affichage ou non du message aucun livre en retard)
		 coderetour(code retour de l'insertion d'un etudiant)	 
*/
void globalBiblio(void)
{
	Emprunt emp;
	etudiant *tEtudiant[1000];
	Ouvrage *touvrage;
	date jour;
    	int nbouvmax=5,nbouv=0,choixouv,choixmenu,nbEtudiant=0,choixetud,choixEmp,nbEmp,nbRet,coderetour;
    	emp=empVide();
    	touvrage=(Ouvrage*)malloc(sizeof(Ouvrage)*nbouvmax);
    	if (touvrage==NULL)
		{
        	printf("Probléme de malloc\n");
       		exit(1);
        	}
    	touvrage=chargerOuvrage(touvrage,&nbouvmax,&nbouv);
    	nbEtudiant=chargeFEtudiant(tEtudiant,nbEtudiant,1000);
	emp=chargerEmprunts(emp,&nbEmp);
    	jour=dateJour();
    	printf("Aujourdhui nous somme le %d/%d/%d\n",jour.jour,jour.mois,jour.annee);
	printf("-------------------------------------------------------------------------\n");
    	nbRet=afficherNonRetour(emp,jour);
	if(nbRet==0)
		printf("Aucun emprunt en retard\n");
	printf("-------------------------------------------------------------------------\n");
    	nbEmp=nbEmpr(emp);	
    	if(nbEtudiant==-1)
        	{
		printf("donnee inexistante ou probleme d'ouverture fichier\n"); 
		exit(1);
		}    
	else if(nbEtudiant==-2)
        		{
       			printf("tableau trop petit\n");
        		exit(1);
        		}
    		else if(nbEtudiant==-3)
        			{
        			printf("probleme malloc\n");
        			exit(1);
        			}
    	while(choixmenu!=5)
        	{
        	choixmenu=menu();
        	if(choixmenu==1)
            		{
			choixetud=0;
            		while(choixetud!=6)
                		{
				choixetud=menuEtudiant();
				if (choixetud==1)
                    			{
					coderetour=saisieEtudiant(tEtudiant,&nbEtudiant,1000);
		        		if(coderetour==0)
						printf("Inscription reussi\n");
					else printf("Tableau trop petit\n");
				
					}
				if(choixetud==2)
                    			modifierEtudiant(tEtudiant,nbEtudiant);
                		if(choixetud==3)
                    			suprimer(tEtudiant,&nbEtudiant);
				if(choixetud==4)
                    			afficheEtuds(tEtudiant,nbEtudiant);
				if(choixetud==5)
		    			afficheUnEtudiant(tEtudiant,nbEtudiant);
                		} 
           		}
        	if(choixmenu==2)
            		{
			choixouv=0;
            		while(choixouv!=7)
                		{
                		choixouv=menuOuvrage();
                		if(choixouv==1)
                    			afouvrage(touvrage,nbouv);
                		if(choixouv==2)
                    			nbouv=insererouv(touvrage,nbouv);
                		if(choixouv==3)
                    			nbouv=supprimouv(touvrage,nbouv);
                		if(choixouv==4)
                    			modifierouv(touvrage,nbouv);
                		if(choixouv==5)
                    			affichUnOuvrage(touvrage,nbouv);
                		if(choixouv==6)
                    			affichEditOuvrage(touvrage,nbouv);
                		}
           		 }
        	if(choixmenu==3)
            		{
			choixEmp=0;
                	while(choixEmp!=5)
                		{
				choixEmp=menuEmprunt();
				if (choixEmp==1)
                    			emp=insererEmprunt(emp,&nbEmp,jour,touvrage,nbouv,nbEtudiant,tEtudiant);
				if(choixEmp==2)
                        		emp=retourEmprunt(emp,&nbEmp,jour,touvrage,nbouv,nbEtudiant,tEtudiant);
                		if(choixEmp==3)
                    			afficherEmprunt(emp,nbEtudiant,tEtudiant);
				if(choixEmp==4)
					{
                    			nbRet=afficherNonRetour(emp,jour);
					if(nbRet==0)
						printf("Aucun emprunt en retard\n");
					}
                		}
            		}
        	if(choixmenu==4)
            		statistique(nbouv,nbEtudiant,tEtudiant,emp,jour);
        	}
    	sauvegarderOuv(touvrage,nbouv);
    	sauveTEtudiant(tEtudiant,nbEtudiant);
	sauvegarderEmp(emp);
}
/*--------------------------------*/
/* -----Affichage des Menus----- */
/*
Finalité :
Description: Ces fonctions permettent l'affichage des menus principaux du programme
Paramètre en entrée : aucun
Valeur retournée: aucun
Variables: aucun
*/
void afficherMenuOuvrage(void)
{
	printf("-------------------------------------------------------------------------\n");
        printf("|\t\t\t   Gestion des Ouvrages    \t\t\t|\n");
        printf("-------------------------------------------------------------------------\n");
        printf("1- Afficher la liste des ouvrages de la bibliotheque\n");
        printf("2- Inserer un nouvel ouvrage\n");
        printf("3- Supprimer un ouvrage\n");
        printf("4- Modifier un ouvrage\n");
        printf("5- Rechercher un ouvrage\n");
        printf("6- Afficher la liste des ouvrages d'un editeur\n");
        printf("7- Revenir au menu précedent\n");
        printf(" Que souhaiter vous faire ? :");
}
void afficherMenu(void)
{
        printf("-------------------------------------------------------------------------\n");
        printf("|\t\t\tGestion de la Bibliotheque \t\t\t|\n");
        printf("-------------------------------------------------------------------------\n");
        printf("1- Gestion des Etudiants\n");
        printf("2- Gestion des Ouvrages\n");
        printf("3- Gestion des Emprunts\n");
        printf("4- Statistique\n");
        printf("5- Quitter le programe\n");
        printf(" Que souhaiter vous faire ? :");
}
void afficherMenuEtudiant(void)
{
        printf("-------------------------------------------------------------------------\n");
        printf("|\t\t\t    Gestion des Etudiants     \t\t\t|\n");
        printf("-------------------------------------------------------------------------\n");
        printf("1- Ajouter un etudiant\n");
        printf("2- Modifier un etudiant\n");
        printf("3- Supprimer un etudiant\n");
        printf("4- Afficher liste Etudiant\n");
	printf("5- Afficher un Etudiant\n");
        printf("6- Revenir au menu précedent\n");
	printf(" Que souhaiter vous faire ? :");
}
void afficherMenuEmprunt(void)
{
        printf("-------------------------------------------------------------------------\n");
        printf("|\t\t\t    Gestion des Emprunts     \t\t\t|\n");
        printf("-------------------------------------------------------------------------\n");
        printf("1- Nouvel emprunt\n");
        printf("2- Retourner un emprunt\n");
        printf("3- Rechercher les emprunts d'un etudiant\n");
        printf("4- Afficher la liste des emprunts en retard\n");
        printf("5- Revenir au menu précedent\n");
	printf(" Que souhaiter vous faire ? :");
}
void afficherModOuvrage(void)
{
    	printf("1- Modifier la cote\n");
   	printf("2- Modifier le titre\n");
    	printf("3- Modifier l'editeur\n");
    	printf("4- Modifier la categorie\n");
    	printf("5- Modifier le nombre d'exemplaires\n");
	printf("6- Modifier l'age limite\n");
    	printf("7- Annuler la modification\n");
    	printf(" Que souhaiter vous faire ? :");
}
/*--------------------------------------------------------------------*/
/* -----Affichage des Menus en boucle avec test de valeur saisie----- */
/*
Finalité :
Description: Ces fonctions permettent l'affichage des menus principaux en boucle jusqu'a ce que la saisie soit correcte
Paramètre en entrée : aucun
Valeur retournée: entier choix
Variables: choix(entier contenant le choix de l'utilisateur du programme)
*/
int menu(void)
{
    int choix;
    afficherMenu();
    scanf("%d%*c",&choix);
    while(choix <1 || choix >5)
        {
        printf("Erreur: Choix non compris entre 1 et 5, veillez resaisir\n");
        afficherMenu();
        scanf("%d%*c",&choix);
        }	
    return choix;
}
int menuEtudiant(void)
{
    	int choix;
    	afficherMenuEtudiant();
    	scanf("%d%*c",&choix);
    	while(choix <1 || choix >6)
        	{
        	printf("Erreur: Choix non compris entre 1 et 6, veillez resaisir\n");
        	afficherMenuEtudiant();
        	scanf("%d%*c",&choix);
        	}	
    	return choix;
}
int menuOuvrage (void)
{ 	
    	int choix;
    	afficherMenuOuvrage();
    	scanf("%d%*c",&choix);
    	while(choix <1 || choix >7)
        	{
        	printf("Erreur: Choix non compris entre 1 et 7, veillez resaisir\n");
        	afficherMenuOuvrage();
        	scanf("%d%*c",&choix);
        	}	
    	return choix;
}
int menuEmprunt(void)
{
    	int choix;
    	afficherMenuEmprunt();
    	scanf("%d%*c",&choix);
    	while(choix <1 || choix >5)
        	{
        	printf("Erreur: Choix non compris entre 1 et 5, veillez resaisir\n");
        	afficherMenuEmprunt();
        	scanf("%d%*c",&choix);
        	}	
    	return choix;
}
int menuModOuv(void)
{
	int choix;
    	afficherModOuvrage();
    	scanf("%d%*c",&choix);
    	while(choix <1 || choix >7)
        	{
        	printf("Erreur: Choix non compris entre 1 et 7, veillez resaisir\n");
        	afficherModOuvrage();
       		scanf("%d%*c",&choix);
        	}	
    	return choix; 
}
/*------------------------------------------------------*/
/*
Finalité :
Description: Cette fonction lit une ligne du fichier ouvrage.don, et retourne une structure ouvrage avec les informations de cette ligne
Paramètre en entrée : le fichier
Valeur retournée: o structure ouvrage:
				      cote
				      categ
				      editeur
				      nbexemplaireDispo
				      agelimit
				      titre
Variables: o structure ouvrage
*/
Ouvrage saisieOuvrage(FILE *flot)
{
    	Ouvrage o;
    	fscanf(flot,"%s%s%s%d%d%*c",o.cote,o.categ,o.editeur,&o.nbexemplaireDispo,&o.agelimit);
    	fgets(o.titre,40,flot);
    	o.titre[strlen(o.titre)-1]='\0';
    	return o;
}
/*
Finalité :
Description: Cette fonction lit le fichier ouvrage.don, et retourne un tableau contenant des structures ouvrage
Paramètre en entrée : touvrage[] le tableau dynamique de structure ourvage
		      *nbouvmax un pointeur sur le nombre d'ouvrage max
		      *nbouv un pointeur sur le nombre d'ouvrage de la bibliotheque
Valeur retournée: le tableau de structure rempli a partir du fichier
Variables: le fichier flot
*/
Ouvrage*chargerOuvrage(Ouvrage touvrage[],int *nbouvmax,int *nbouv)
{
    	FILE *flot;
    	flot=fopen("ouvrages.don","r");
    	if (flot==NULL)
       		{
        	printf("Probléme d'ouverture du fichier ouvrages.don en lecture\n");
        	exit(1);
        	}
    	Ouvrage ouv,*aux;
    	ouv=saisieOuvrage(flot);
    	while(!feof(flot))
        	{
        	if(*nbouv==*nbouvmax)
            		{
            		aux=(Ouvrage*)realloc(touvrage,(*nbouvmax+5)*sizeof(Ouvrage));
            		(*nbouvmax)=(*nbouvmax)+5;
            		if(aux==NULL)
                		{
                		printf("Probléme de realloc\n");
                		exit(1);
                		}
            		touvrage=aux;
            		}
        	touvrage[*nbouv]=ouv;
        	(*nbouv)=(*nbouv)+1;
        	ouv=saisieOuvrage(flot);
        	}
        fclose(flot);
    	return touvrage;
}
/*
Finalité :
Description: Cette fonction lit le fichier ouvrage.don, et retourne un tableau contenant des structures ouvrage
Paramètre en entrée : touvrage[] le tableau dynamique de structure ourvage
		      nbouv le nombre d'ouvrage de la bibliotheque
Valeur retournée: aucune
Variables: i un entier qui s'incremente avec la boucle for
*/
void afouvrage(Ouvrage touvrage[],int nbouv)
{
    	int i;
    	if(nbouv==0)
        	{
        	printf("Aucun ouvrages\n");
        	return;
        	}
	printf("Titre\tCote\tEditeur\tCategorie\tNombre d'exemplaire disponible\tAge limite\n");
    	for (i=0;i<nbouv;i++)
		{
            	printf("%s\t%s\t%s\t%s\t%d\t",touvrage[i].titre,touvrage[i].cote,touvrage[i].editeur,touvrage[i].categ,touvrage[i].nbexemplaireDispo);
		if(touvrage[i].agelimit!=0)
			printf("%d ans\n",touvrage[i].agelimit);	
		else printf("Tous public\n");
		}
}
/*
Finalité :
Description: Cette fonction recherche la position d'une cote donnée et la retourne
Paramètre en entrée : touvrage[] le tableau dynamique de structure ourvage
		      nbouv le nombre d'ouvrage de la bibliotheque
		      coterech[] une chaine de charactere conenant la cote recherchée
Valeur retournée: la position de la cote recherchée ou -1 si elle n'y est pas
Variables: inf,sup,milieu trois entiers permettant la recherche dichotomique
*/
int rechOuvrage(Ouvrage touvrage[],char coterech[],int nbouv)
{
    	int inf=0,sup,milieu;
    	sup=nbouv-1;
    	while(inf<=sup)
        	{
        	milieu=(inf+sup)/2;
        	if(strcmp(touvrage[milieu].cote,coterech)==0)
            		return milieu;
        	if(strcmp(touvrage[milieu].cote,coterech)>0)
            		sup=milieu-1;
        	else inf=milieu+1;
        	}
    	return -1;
}
/*
Finalité :
Description: Cette fonction recherche la position d'une cote donnée et la retourne
Paramètre en entrée : touvrage[] le tableau dynamique de structure ourvage
		      nbouv le nombre d'ouvrage de la bibliotheque
		      coterech[] une chaine de charactere conenant la cote recherchée
Valeur retournée: la position de la cote recherchée ou ca position d'insertion si elle n'y est pas
Variables: inf,sup,milieu trois entiers permettant la recherche dichotomique
*/
int rechOuvrageInsert(Ouvrage touvrage[],char coterech[],int nbouv)
{
    	int inf=0,sup,milieu;
    	sup=nbouv-1;
    	while(inf<=sup)
        	{
        	milieu=(inf+sup)/2;
        	if(strcmp(touvrage[milieu].cote,coterech)==0)
            		return milieu;
        	if(strcmp(touvrage[milieu].cote,coterech)>0)
            		sup=milieu-1;
        	else inf=milieu+1;
        	}
    	return inf;
}
/*
Finalité :
Description: Cette fonction insert un ouvrage dans le tableau a partir de la saisi de l'utilisateur
Paramètre en entrée : touvrage[] le tableau dynamique de structure ourvage
		      nbouv le nombre d'ouvrage de la bibliotheque
Valeur retournée: le nouveau nombre d'ouvrage de la bibliotheque
Variables: pos un entier contenant la position d'insertion
	   i un entier permettant la boucle for
	   ouv une structure ouvrage
	   reponse un charactere permettant la reponse o/n de l'utilisateur
*/
int insererouv(Ouvrage touvrage[],int nbouv)
{
    	int pos,i;
    	Ouvrage ouv;
	char reponse;
    	printf("Quelle est la cote de cet ouvrage ?");
    	scanf("%s%*c",ouv.cote);
    	pos=rechOuvrageInsert(touvrage,ouv.cote,nbouv);
    	if(strcmp(touvrage[pos].cote,ouv.cote)==0)
        	{
        	printf("Livre déja existant\n");
        	return;
        	}
    	printf("Quelle est l'editeur de cet ouvrage ?");
    	scanf("%s%*c",ouv.editeur);
    	printf("Quelle est la categorie de cet ouvrage ?");
    	scanf("%s%*c",ouv.categ);
    	printf("combien y a t-il d'exemplaires de cet ouvrage ?");
    	scanf("%d%*c",&ouv.nbexemplaireDispo);
    	printf("Quelle est le titre de cet ouvrage ?");
    	fgets(ouv.titre,40,stdin);
    	ouv.titre[strlen(ouv.titre)-1]='\0';
	printf("Il y as t-il un age limite? (o/n) ");
    	scanf("%c%*c",&reponse);
    	if(reponse=='o' || reponse=='O')
		{
		printf("Quel est l'age limite de cet ouvrage : ");
		scanf("%d%*c",&ouv.agelimit);		
		}
  	else ouv.agelimit=0;
    	for(i=nbouv-1;i>=pos;i--)
        	touvrage[i+1]=touvrage[i];
    	touvrage[pos]=ouv;
    	return nbouv+1;
}
/*
Finalité :
Description: Cette fonction supprime un ouvrage a partir d'une cote
Paramètre en entrée : touvrage[] le tableau dynamique de structure ourvage
		      nbouv le nombre d'ouvrage de la bibliotheque
Valeur retournée: le nouveau nombre d'ouvrage de la bibliotheque
Variables: pos la position du livre dans le tableau ou -1 sinon
	   i un entier permettant la boucle for
	   cote[7] une chaine de charactere dans laqu'elle sera mise la cote saisie par l'utilisateur
*/
int supprimouv(Ouvrage touvrage[],int nbouv)
{
    	int pos,i;
    	char cote[7];
    	printf("Quelle est la cote de l'ouvrage à supprimer ?");
    	scanf("%s%*c",cote);
    	pos=rechOuvrage(touvrage,cote,nbouv);
    	if(pos==-1)
        	{
        	printf("Livre Inexistant\n");
        	return nbouv;
        	}
    	for(i=pos;i<nbouv-1;i++)
        	touvrage[i]=touvrage[i+1];
    	return nbouv-1;
}
/*
Finalité :
Description: Cette fonction sauvegarde le tableau d'ouvrage dans le fichier ouvrage.don a la fermeture du programe
Paramètre en entrée : touvrage[] le tableau dynamique de structure ourvage
		      nbouv le nombre d'ouvrage de la bibliotheque
Valeur retournée: aucune
Variables: i un entier permettant la boucle for
	   flot le fichier
*/
void sauvegarderOuv (Ouvrage touvrage[],int nbouv)
{
	int i;
	FILE *flot;
	flot=fopen("ouvrages.don","w");
	for(i=0;i<nbouv;i++)
		fprintf(flot,"%s\t%s\t%s\t%d\t%d\t%s\n",touvrage[i].cote,touvrage[i].categ,touvrage[i].editeur,touvrage[i].nbexemplaireDispo,touvrage[i].agelimit,touvrage[i].titre);
        fclose(flot);
}
/*
Finalité :
Description: Cette fonction affiche les information concernant un ouvrage a partir de sa cote
Paramètre en entrée : touvrage[] le tableau dynamique de structure ourvage
		      nbouv le nombre d'ouvrage de la bibliotheque
Valeur retournée: le nouveau nombre d'ouvrage de la bibliotheque
Variables: pos la position du livre dans le tableau ou -1 sinon
	   cote[7] une chaine de charactere dans laqu'elle sera mise la cote saisie par l'utilisateur
*/
void affichUnOuvrage(Ouvrage touvrage[],int nbouv)
{
    	char cote[7];
    	int pos;
    	printf("Quelle est la cote de l'ouvrage recherché ?");
    	scanf("%s%*c",cote);
    	pos=rechOuvrage(touvrage,cote,nbouv);
    	if(pos==-1)
        	{
        	printf("Ouvrage inexistant\n");
        	return;
        	}
    	printf("Titre: %s\nCote: %s\nEditeur: %s\nCategorie: %s\nNombre d'exemplaire disponible: %d\n",touvrage[pos].titre,touvrage[pos].cote,touvrage[pos].editeur,touvrage[pos].categ,touvrage[pos].nbexemplaireDispo);
	if(touvrage[pos].agelimit==0)
		printf("Age limite : Tous public\n");
    	else printf("Age limite : %d\n",touvrage[pos].agelimit);
}
/*
Finalité :
Description: Cette fonction affiche les information concernant les ouvrages a partir d'un editeurs
Paramètre en entrée : touvrage[] le tableau dynamique de structure ourvage
		      nbouv le nombre d'ouvrage de la bibliotheque
Valeur retournée: le nouveau nombre d'ouvrage de la bibliotheque
Variables: i un entier permettant le parcour du tableau
	   editeur[20] une chaine de charactere dans laqu'elle sera mise le nom de l'editeur saisie par l'utilisateur
*/
void affichEditOuvrage(Ouvrage touvrage[],int nbouv)
{
    	int i;
    	char editeur[20];
    	printf("Quelle est le nom de l'editeur ?");
    	scanf("%s%*c",editeur);
    	printf("Titre\tCote\tEditeur\tCategorie\tNombre d'exemplaire disponible\tAge limite\n");
    	for(i=0;i<nbouv;i++)
        	{
        	if (strcmp(editeur,touvrage[i].editeur)==0)
            	printf("%s\t%s\t%s\t%s\t%d\t",touvrage[i].titre,touvrage[i].cote,touvrage[i].editeur,touvrage[i].categ,touvrage[i].nbexemplaireDispo);
		if(touvrage[i].agelimit==0)
			printf("Tous public\n");
    		else printf("%d\n",touvrage[i].agelimit);	
        	}
}
/*
Finalité :
Description: Cette fonction permet de modifier une information d'un ouvrage dans le tableau touvrage
Paramètre en entrée : touvrage[] le tableau dynamique de structure ourvage
		      nbouv le nombre d'ouvrage de la bibliotheque
Valeur retournée: aucune
Variables: ouv une structure ouvrage
	   i un entier permettant le parcour du tableau
	   choix un entier contenant le choix de modification
	   pos un entier contenant la position de l'ouvrage a modifier
	   posi un entier contenant la nouvelle position si modification de cote de l'ouvrage
	   nb un entier contenant le nouveau nombre d'exemplaire
	   age un entier contenant la nouvelle limite d'age de l'ouvrage
	   editeur[20] une chaine de charactere dans laqu'elle sera mise le nom de l'editeur saisie par l'utilisateur
	   cote[7] une chaine de charactere dans laqu'elle sera mise la cote saisie par l'utilisateur
	   categ[4] une chaine de charactere dans laqu'elle sera mise la nouvelle categorie saisie par l'utilisateur
	   titre[20] une chaine de charactere dans laqu'elle sera mise le nouveaux titre saisie par l'utilisateur
	   cotemod[20] une chaine de charactere dans laqu'elle sera mise la nouvelle cote saisie par l'utilisateur
	   co un charactere permettant la confirmation de la modification
*/
void modifierouv(Ouvrage touvrage[],int nbouv)
{
    	Ouvrage ouv;
    	char cote[7],categ[4],editeur[20],titre[40],cotemod[7];
    	char co;
    	int i,choix,pos,posi,nb,age;
    	printf("Quelle est la cote de l'ouvrage a mofifier ?");
    	scanf("%s%*c",cote);
    	pos=rechOuvrage(touvrage,cote,nbouv);
    	if(pos==-1)
        	{
        	printf("Ouvrage inexistant\n");
        	return;
        	}
    	choix=menuModOuv();
    	if(choix==1)
        	{
        	printf("La cote actuelle de l'ouvrage %s, quel est la nouvelle cote ?",cote);
        	scanf("%s%*c",cotemod);
        	printf("\n");
        	printf("Confirmez-vous que le nouvel editeur est %s ? (o/n)",cotemod);
        	scanf("%c%*c",&co);
        	printf("\n");
        	if(co=='o')
           		{
            		ouv=touvrage[pos];
            		strcpy(ouv.cote,cotemod);
            		for(i=pos;i<nbouv-1;i++)
                		touvrage[i]=touvrage[i+1];
            		posi=rechOuvrage(touvrage,cotemod,nbouv-1);
            		if(posi!=-1)
                		{
                		printf("Cote deja utiliser pour un autre ouvrage\n");
                		return;
                		}
            		posi=rechOuvrageInsert(touvrage,cotemod,nbouv-1);
            		for(i=nbouv-2;i>=posi;i--)
                		touvrage[i+1]=touvrage[i];
            		touvrage[posi]=ouv;
            		}
        	}
    	if(choix==2)
        	{
        	printf("Le titre actuel de l'ouvrage %s est %s, quel est le nouveau titre ?",cote,touvrage[pos].titre);
        	fgets(titre,40,stdin);
        	titre[strlen(titre)-1]='\0';
        	printf("\n");
        	printf("Confirmez-vous que le nouveau titre est %s ? (o/n)",titre);
        	scanf("%c%*c",&co);
        	printf("\n");
        	if(co=='o')
           		strcpy(touvrage[pos].titre,titre); 
        	}
    	if(choix==3)
        	{
        	printf("L'editeur actuel de l'ouvrage %s est %s, quel est le nouvel editeur ?",cote,touvrage[pos].editeur);
        	scanf("%s%*c",editeur);
        	printf("\n");
        	printf("Confirmez-vous que le nouvel editeur est %s ? (o/n)",editeur);
        	scanf("%c%*c",&co);
        	printf("\n");
        	if(co=='o')
           		strcpy(touvrage[pos].editeur,editeur); 
        	}
    	if(choix==4)
        	{
        	printf("La categorie actuelle de l'ouvrage %s est %s, quelle est la nouvelle categorie ?",cote,touvrage[pos].categ);
        	scanf("%s%*c",categ);
        	printf("\n");
        	printf("Confirmez-vous que la nouvelle categorie est %s ? (o/n)",categ);
        	scanf("%c%*c",&co);
        	printf("\n");
        	if(co=='o')
           		strcpy(touvrage[pos].categ,categ); 
        	}
    	if(choix==5)
        	{
        	printf("Il y a actuellement %d ouvrages dont la cote est %s ,quel est le nouveau nombre d'ouvrage ?",touvrage[pos].nbexemplaireDispo,cote);
        	scanf("%d%*c",&nb);
        	printf("\n");
        	printf("Confirmez-vous que le nouveau nombre d'exemplaire est %d ? (o/n)",nb);
        	scanf("%c%*c",&co);
        	printf("\n");
        	if(co=='o')
            		touvrage[pos].nbexemplaireDispo=nb;
        	}
	if(choix==6)
		{
		printf("L'age limite de cette ouvrage est actuellement de %d,quel est la nouvelle age limite : ",touvrage[pos].agelimit);
		scanf("%d%*c",&age);
		printf("\n");
		printf("Confirmez-vous que l'age limite de cette ouvrage est de %d ? (o/n) ",age);
		scanf("%c%*c",&co);
		printf("\n");
		if(co=='o')
			touvrage[pos].agelimit=age;
		}
    	if(choix==7)
        	return;
}
/*
Finalité : 
Description: Saisit les differentes informations d'un etudiant puis l'insere grâce a la fonction d'insertion

Paramètre en entrée :	   tEtudiant Tableau de pointeurs sur des structures Etudiant
			   *nbEtudiant pointeur sur des Entier qui represente le nombre d'etudiant present dans le tableau
			   taillephy Entier qui represente le taille physique du tableau tEtudiant
		 
Valeur retournée: 0 si la saisie c'est bien passer
		  -2 si le tableau était trop grand pour inscrire la personne

Variables: saisi structure etudiant
						num
 						nom[30]
 					        prenom[30]
					        naissance  (jour,mois,annee)
  						sexe
 						nbEmp
 						nbEmpCour
 						email[30]
 						telephone p[3]  (tel)
 						adresse[30]
	 Entier:res: position de l'etudiant ou position d'insertion de l'etudiant
*/
int saisieEtudiant (etudiant *tEtudiant[],int *nbEtudiant,int taillephy)
{
	etudiant saisi; 
	int res;	
	if (*nbEtudiant==taillephy) /*sert a rien de saisir si tableau trop petit*/
		return -2;    
	saisir(saisi.nom,saisi.prenom);
	res=rechEtudiant(saisi.nom,saisi.prenom,tEtudiant,*nbEtudiant);
	if(res!=*nbEtudiant)	
		if(presence(*tEtudiant[res],saisi.nom,saisi.prenom))
		{	
			printf("Erreur:etudiant deja existant pour %s %s\n",saisi.nom,saisi.prenom);	
			while(res!=*nbEtudiant && presence(*tEtudiant[res],saisi.nom,saisi.prenom))
			{
				printf("Retapez:\n");
				saisir(saisi.nom,saisi.prenom);
				res=rechEtudiant(saisi.nom,saisi.prenom,tEtudiant,*nbEtudiant);
			}
		}
	saisi.num=*nbEtudiant;
	printf("Date de naissance (FORMAT : JJ/MM/AAAA) : ");
	scanf("%d/%d/%d%*c",&saisi.naissance.jour,&saisi.naissance.mois,&saisi.naissance.annee);
	while(saisi.naissance.jour<1 || saisi.naissance.jour>31 || saisi.naissance.mois<1 || saisi.naissance.mois>12 || saisi.naissance.annee<1950 || saisi.naissance.annee>2015)
		{
		printf("erreur de saisi de la date \nRetapez : ");
		printf("\nDate de naissance (FORMAT : JJ/MM/AAAA) : ");
		scanf("%d/%d/%d%*c",&saisi.naissance.jour,&saisi.naissance.mois,&saisi.naissance.annee);
		}
	printf("Quel est le sexe de l'Etudiant (H/F)");
	scanf("%c%*c",&saisi.sexe);
	printf("Quel est l'email de l'Etudiant ? : ");
	scanf("%s%*c",saisi.email); /*pas d'espace pour les emails*/
	printf("Quel est le numero telephone mobile de L'Etudiant ? ");
	fgets(saisi.p[0].tel,16,stdin);	
	saisi.p[0].tel[strlen(saisi.p[0].tel)-1]='\0';
	printf("Quel est le numero telephone fixe de l'Etudiant ? ");
	fgets(saisi.p[1].tel,16,stdin);
	saisi.p[1].tel[strlen(saisi.p[1].tel)-1]='\0';
	printf("Quel est le numero telephone de la personne a contacte en cas d'urgence ? ");
	fgets(saisi.p[2].tel,16,stdin);
	saisi.p[2].tel[strlen(saisi.p[2].tel)-1]='\0';
	
	printf("Quelle est l'adresse de l'Etudiant ? ");
	fgets(saisi.adresse,30,stdin);
	saisi.adresse[strlen(saisi.adresse)-1]='\0';
	saisi.nbEmp=0;
	saisi.nbEmpCour=0;
	insererEtud(tEtudiant,*nbEtudiant,res,saisi);
	*nbEtudiant=*nbEtudiant+1;
	return 0;
}
/*
Finalité :
Description: Cette fonction va afficher tout les attribut associé a chaque etudiant sauf le nombre d'emprunts en cours et le nombre d'emprunt effectuer au total
Paramètre en entrée : Etudiant structure etudiant
						num
 						nom[30]
 					        prenom[30]
					        naissance  (jour,mois,annee)
  						sexe
 						nbEmp
 						nbEmpCour
 						email[30]
 						telephone p[3]  (tel)
 						adresse[30]
Valeur retournée: aucun

Variables: aucun
*/
void afficheEtud (etudiant Etudiant)
{
	printf("%d\t%s\t%s\t%d/%d/%d\t%c\t%d\t%s\t%s\t%s\t%s\t%s\n",Etudiant.num,Etudiant.nom,Etudiant.prenom,Etudiant.naissance.jour,Etudiant.naissance.mois,Etudiant.naissance.annee,Etudiant.sexe,Etudiant.nbEmpCour,Etudiant.email,Etudiant.p[0].tel,Etudiant.p[1].tel,Etudiant.p[2].tel,Etudiant.adresse);
}
/*
Finalité :
Description: Cette fonction va afficher tout les etudiant si il y en a
Paramètre en entrée : tEtudiant Tableau de pointeurs sur des structures Etudiant
	              nbEtudiant Entier qui represente le nombre d'etudiant present dans le tableau
Valeur retournée: aucun

Variables: Entier:i:parcours de tableau
*/
void afficheEtuds (etudiant *tEtudiant[],int nbEtudiant)
{
	int i;
	if(nbEtudiant>0)
		{	
		printf("N°\tnom\tprenom\tDate de naissance\tSexe\tNombre d'emprunts en cours\temail\tTelephone portable\tTelephone fixe\tTelephone de la personne a contacter\tadresse\n");
		for(i=0;i<nbEtudiant;i++)
			afficheEtud(*tEtudiant[i]);
		}
	else
		printf("aucun etudiant\n");
}
/*
Finalité :
Description: cette fonction va effectuer une recherche dicotomique dans le tableau par rapport au nom et prenom que l'on as donné en entrée 
Paramètre en entrée : Chaine de caractere : nom : nom de l'etudiant a chercher dans le tableau
		      Chaine de caractere : prenom : prenom de l'etudiant a chercher dans le tableau
		      tEtudiant Tableau de pointeurs sur des structures Etudiant
	              nbEtudiant Entier qui represente le nombre d'etudiant present dans le tableau
Valeur retournée:  milieu si l'etudiant est present 
		   inf si l'etudiant n'est pas present

Variables: Entier:inf: debut de la partie où on recherche l'etudiant
           Entier:sup:fin de la partie où on recherche l'etudiant
	   Entier:milieu: milieu de la partie où on recherche l'etudiant
*/
int rechEtudiant(char nom[],char prenom[],etudiant *tEtudiant[],int nbEtudiant)
{
	int inf=0,sup,milieu,comparprenom;
	sup=nbEtudiant-1;
	while(inf<=sup)
		{
		milieu=(inf+sup)/2;
		comparprenom=strcmp(tEtudiant[milieu]->prenom,prenom);
		if(strcmp(tEtudiant[milieu]->nom,nom)==0)
			{			
			if(comparprenom==0)
				return milieu;
			if(comparprenom>0)
				sup=milieu-1;
			else inf=milieu+1;		
			}	
		if(strcmp(tEtudiant[milieu]->nom,nom)>0)
			sup=milieu-1;
		else if(strcmp(tEtudiant[milieu]->nom,nom)<0)
				inf=milieu+1;
		}
	return inf; 
}
/*
Finalité :
Description: Cette fonction permet de modifier tous les informations que l'on connait sur l'etudiant nom/prenom/date de naissance / sexe / email / telephone mobile,fixe et de la personne a contacter en cas d'urgence
Paramètre en entrée : tEtudiant Tableau de pointeurs sur des structures Etudiant
	              nbEtudiant Entier qui represente le nombre d'etudiant present dans le tableau
Valeur retournée: aucun

Variables: Entier:pos: position de l'etudiant dans le tableau
	   Entier:choix: numero  auquel est associer un attribut (nom,prenom etc...)
	   Entier:changement: permet de savoir si l'on as effectuer un changement dans le nom ou le prenom et donc si il y a eu changement de trier le tableau en consequence
	   Entier:pos1: position d'insertion de l'etudiant dont le nom ou le prenom a été modifier
	   t structure telephone
				tel
	   test structure etudiant
					num
 					nom[30]
 				        prenom[30]
				        naissance  (jour,mois,annee)
  					sexe
 					nbEmp
					nbEmpCour
					email[30]
					telephone p[3]  (tel)
					adresse[30]
	   Chaine de caractere : nom : nom de l'etudiant a modifier dans le table
           Chaine de caractere : prenom : prenom de l'etudiant a modifier dans le tableau
*/
void modifierEtudiant(etudiant *tEtudiant[],int nbEtudiant) /*modifier nom modifier tableau*/
{
	int pos,choix=0,changement=0,pos1;
	telephone t;
	etudiant test;	
	char nom[30],prenom[30];
	saisir(nom,prenom);
	pos=rechEtudiant(nom,prenom,tEtudiant,nbEtudiant);
	if(pos==nbEtudiant || ! presence(*tEtudiant[pos],nom,prenom))	
		{	
			printf("Erreur:etudiant inexistant pour %s %s\n",nom,prenom);	
			while(pos==nbEtudiant || ! presence(*tEtudiant[pos],nom,prenom))	
			{
				printf("retapez:\n");
				saisir(nom,prenom);
				pos=rechEtudiant(nom,prenom,tEtudiant,nbEtudiant);
			}
		}
	test=*tEtudiant[pos];
	while(choix != 10)
	{	
		afficheEtud(test);
		printf("quel partie voulez vous mofifier?\n 1.\tNom\t\t\t 5.\tEmail \n 2.\tPrenom \t\t\t 6.\tTel mobile\n 3.\tDate de naissance\t 7.\tTel fixe \n 4.\tSexe\t\t\t 8.\tTel contacte\n 9.\tAdresse\t\t\t 10.\tModification fini\n");
		scanf("%d%*c",&choix);
		if(choix==1)
			{		
			printf("Quel est le nouveau nom");
			fgets(test.nom,30,stdin);
			test.nom[strlen(test.nom)-1]='\0';
			changement=1;			
			}
		if(choix==2)
			{
			printf("Quel est le nouveau prenom");
			fgets(test.prenom,30,stdin);
			test.prenom[strlen(test.prenom)-1]='\0';
			changement=1;			
			}
		if(choix==3)
			{
			printf("Date de naissance (FORMAT : JJ/MM/AAAA) : ");
			scanf("%d/%d/%d%*c",&test.naissance.jour,&test.naissance.mois,&test.naissance.annee);
			}
		if(choix==4)
			{
			if(test.sexe=='f' || test.sexe=='F') 
				test.sexe='H';
			else
				test.sexe='F';
			}			
		if(choix==5)
			{
			printf("Quel est le nouveau email");
			fgets(test.email,30,stdin);
			test.email[strlen(test.email)-1]='\0';
			}
		if(choix==6)
			{
			printf("Quel est le nouveau numero de telephone portable");
			fgets(test.p[0].tel,30,stdin);
			test.p[0].tel[strlen(test.p[0].tel)-1]='\0';
			}
		if(choix==7)
			{
			printf("Quel est le nouveau numero de telephone fixe");
			fgets(test.p[1].tel,30,stdin);
			test.p[1].tel[strlen(test.p[1].tel)-1]='\0';
			}
		if(choix==8)
			{
			printf("Quel est le nouveau numero telephone de la personne a apeller en cas d'urgence");
			fgets(test.p[2].tel,16,stdin); /*attention*/
			test.p[2].tel[strlen(test.p[2].tel)-1]='\0';
			}
		if(choix==9)
			{
			printf("Quel est la nouvelle adresse");
			fgets(test.adresse,30,stdin);
			test.adresse[strlen(test.adresse)-1]='\0';
			}
	}
	if(changement==0)
		*tEtudiant[pos]=test;
	else
		{
		pos1=rechEtudiant(test.nom,test.prenom,tEtudiant,nbEtudiant);
		if(pos1!=nbEtudiant)	
			if(presence(*tEtudiant[pos1],test.nom,test.prenom))
				{				
				printf("Etudiant deja present\n");
				return;
				}
		if(pos1==pos)
			*tEtudiant[pos]=test;
		else
			{
			supprimer(tEtudiant,nbEtudiant,pos);
			insererEtud(tEtudiant,nbEtudiant,pos1-1,test); /*vu que j'ai decaler de 1 il est neccesaire de faire -1 */
			}
		}
}
/*
Finalité :
Description: cette fonction va supprimer un Etudiant, elle libere d'abord l'espace memoire reservé a un etudiant puit decale dans le tableau les etudiants
Paramètre en entrée : tEtudiant Tableau de pointeurs sur des structures Etudiant
	              nbEtudiant Entier qui represente le nombre d'etudiant present dans le tableau
		      pos Entier qui represente la position dans le tableau ou se trouve l'etudiant a supprimer
Valeur retournée: aucun

Variables: Entier:i:parcours de tableau
*/
void supprimer (etudiant *tEtudiant[],int nbEtudiant,int pos)
{
	int i;
	free(tEtudiant[pos]);
	for(i=pos;i<nbEtudiant-1;i++)
		tEtudiant[i]=tEtudiant[i+1];
}
/*
Finalité :
Description: Saisi le nom et prenom d'un Etudiant
Paramètre en entrée : Chaine de caractere : nom : nom de l'etudiant a saisir
		      Chaine de caractere : prenom : prenom de l'etudiant a saisir
Valeur retournée: aucun

Variables: aucun
*/
void saisir(char nom[],char prenom[])
{
	printf("Quel est le nom de l'Etudiant? ");
	fgets(nom,30,stdin);
	nom[strlen(nom)-1]='\0';
	printf("Quel est le prenom de l'Etudiant? ");
	fgets(prenom,30,stdin);
	prenom[strlen(prenom)-1]='\0';
}
/*
Finalité :
Description: cette fonction va demander quelle est l'etudiant a supprimer puis va faire une recherche dicotomique, si l'etudiant est present la fonction va appeler la fonction supprimer sinon la personne doit retapez le nom
Paramètre en entrée :	   tEtudiant Tableau de pointeurs sur des structures Etudiant
			   *nbEtudiant Pointeur sur des Entier qui represente le nombre d'etudiant present dans le tableau
Valeur retournée: aucun

Variables:Entier:pos: position de l'etudiant a supprimer
*/	
void suprimer (etudiant *tEtudiant[],int *nbEtudiant)
{
	int pos;
	char nom[30],prenom[30];
	saisir(nom,prenom);
	pos=rechEtudiant(nom,prenom,tEtudiant,*nbEtudiant);
	if(pos==*nbEtudiant || ! presence(*tEtudiant[pos],nom,prenom))	
		{	
		printf("Erreur:etudiant inexistant pour %s %s\n",nom,prenom);	
		while(pos==*nbEtudiant || ! presence(*tEtudiant[pos],nom,prenom))	
			{
			printf("retapez:\n");
			saisir(nom,prenom);
			pos=rechEtudiant(nom,prenom,tEtudiant,*nbEtudiant);
			}
		}
	supprimer(tEtudiant,*nbEtudiant,pos);
	*nbEtudiant=*nbEtudiant-1;
}
/*
Finalité :
Description:cette fonction va lire le fichier etud.bin pour ainsi inserer dans le tableau tEtudiant tout les etudiant inscrit dans le fichier, on compte aussi le nombre d'etudiant qui sont present dans le fichier

Paramètre en entrée :	   tEtudiant Tableau de pointeurs sur des structures Etudiant
			   nbEtudiant Entier qui represente le nombre d'etudiant present dans le tableau
			   nbmax Entier qui represente le taille physique du tableau tEtudiant
		
Valeur retournée: Entier nbEtudiant ombre d'etudiant 
		  -1 si la lecture du fichier est impossible
		  -2 si le tableau d'etudiant est trop petit pour contenir tous les etudiant issu du fichier 
		  -3 si il y a un problème dans l'allocation dynamique (malloc) 

Variables: Entier:i: parcours de tableau
	   Fichier:flot: fichier des Etudiant
*/	
int chargeFEtudiant(etudiant *tEtudiant[],int nbEtudiant,int nbmax)
{
	int i=0;	
	FILE *flot;
	etudiant m;
	flot=fopen("etud.bin","rb");
	if(flot==NULL)
		return -1;
	fread(&m,sizeof(etudiant),1,flot);
	while(!feof(flot))
	{
		if(nbEtudiant==nbmax)
			return -2;
		tEtudiant[i]=(etudiant*)malloc(sizeof(etudiant));
		if(tEtudiant[i]==NULL)
			return -3; /*problème malloc*/
		*tEtudiant[i]=m;
		nbEtudiant++;
		i++;		
		fread(&m,sizeof(etudiant),1,flot);
	}
	fclose(flot);
	return nbEtudiant;
}
/*
Finalité :
Description:Cette fonction permet d'ecrire dans le fichier(etud.bin) toute le structure dans le tableau de tEtudiant
Paramètre en entrée :	   tEtudiant Tableau de pointeurs sur des structures Etudiant
			   nbEtudiant Entier qui represente le nombre d'etudiant present dans le tableau
Valeur retournée: aucun

Variables: Entier:i: parcours de tableau
	   Fichier:flot: fichier des Etudiant
*/
void sauveTEtudiant( etudiant *tEtudiant[],int nbEtudiant)
{
	FILE *flot;
	int i;
	flot=fopen("etud.bin","wb");
	if(flot==NULL)
		{
		printf("problème d'ouverture fichier");
		exit(1);
		}
	for(i=0;i<nbEtudiant;i++)	
		fwrite(tEtudiant[i],sizeof(etudiant),1,flot);
	fclose(flot);
}
/*
Finalité :
Description:le but est de savoir si le nom et prenom est identique grace a cela on peut savoir si l'etudiant est present dans le tableau ou nom
Paramètre en entrée : a structure etudiant
						num
 						nom[30]
 					        prenom[30]
					        naissance  (jour,mois,annee)
  						sexe
 						nbEmp
 						nbEmpCour
 						email[30]
 						telephone p[3]  (tel)
 						adresse[30]
		      chaine de caractere:nom
		      chaine de caractere:prenom
Valeur retournée: vrai si l'etudiant est present 
		  faux si l'etudiant est absent

Variables: aucun
*/	
Booleen presence (etudiant a,char nom[],char prenom[])
{
	
		if(strcmp(nom,a.nom)==0)
			if(strcmp(prenom,a.prenom)==0)
				return vrai;
		if(strcmp(prenom,a.prenom)==0)
			if(strcmp(nom,a.nom)==0)
				return vrai;
		return faux;
}
/*
Finalité :
Description:cette fonction va tous d'abord demander le nom et le prenom de la personne a afficher, avec une recherche dicotomique on arrive a trouver la position ou ce situe l'etudiant dans le tableau et donc on l'affiche, mais si l'etudiant n'est pas dans le tableau il est nécessaire de retaper le nom et prenom de l'etudiant
Paramètre en entrée : tEtudiant Tableau de pointeurs sur des structures Etudiant
			   nbEtudiant Entier qui represente le nombre d'etudiant present dans le tableau
Valeur retournée: aucun

Variables: Entier:pos:pour connaitre la position de l'etudiant
	   chaine:nom:le nom de l'etudiant a rechercher
	   chaine:prenom: prenom de l'etudiant a rechercher
*/	

void afficheUnEtudiant (etudiant *tEtudiant[],int nbEtudiant)
{
	int pos;
	char nom[30],prenom[30];
	saisir(nom,prenom);
	pos=rechEtudiant(nom,prenom,tEtudiant,nbEtudiant);
	if(pos==nbEtudiant || ! presence(*tEtudiant[pos],nom,prenom))	
		{	
			printf("Erreur:etudiant inexistant pour %s %s\n",nom,prenom);	
			while(pos==nbEtudiant || ! presence(*tEtudiant[pos],nom,prenom))	
			{
				printf("retapez:\n"); 
				saisir(nom,prenom);
				pos=rechEtudiant(nom,prenom,tEtudiant,nbEtudiant);
			}
		}
	afficheEtud(*tEtudiant[pos]);
}
/*
Finalité :
Description:cette fonction va calculer le nombre d'annee qui separe la date de naissance et la date du jour
Paramètre en entrée : d structure date 
					jour
					mois
					annee
			system structure date
					jour 
					mois
					annee
Valeur retournée: annee l'age calculée

Variables: annee Entier 
*/
int calculAge (date d,date system)
{
	int annee;
	annee=system.annee-d.annee;
	if(system.mois<d.mois)
		annee=annee-1;
	if(system.mois==d.mois)
		if(system.jour<d.jour)
			annee=annee-1;
	return annee;
}
/*
Finalité :
Description:Cette fonction va decaler vers la droite toute les adresse des structures puis reserver un espaces memoire a la position pos pour y inserer la structure 
Paramètre en entrée :
			   tEtudiant Tableau de pointeurs sur des structures Etudiant
			   nbEtudiant Entier qui represente le nombre d'etudiant present dans le tableau
			   pos Entier  
			   e structure etudiant
						num
 						nom[30]
 					        prenom[30]
					        naissance  (jour,mois,annee)
  						sexe
 						nbEmp
 						nbEmpCour
 						email[30]
 						telephone p[3]  (tel)
 						adresse[30]
			
Valeur retournée: aucun

Variables: Entier i parcours du tableau

*/
void insererEtud (etudiant *tEtudiant[],int nbEtudiant,int pos,etudiant e)
{
	int i;
	for(i=nbEtudiant-1;i>=pos;i--)
    	    tEtudiant[i+1]=tEtudiant[i];
	tEtudiant[pos]=(etudiant*)malloc(sizeof(etudiant));
	if(tEtudiant[nbEtudiant]==NULL)
		{
		printf("problème malloc inserer\n");
		exit(1);
		}
	*tEtudiant[pos]=e;
}
/*
Finalité :
Description: Cette fonction initialise une structure date en mettant tout les entier la composant à 0(cela permet de savoir si un ouvrage est retourner ou non)
Paramètre en entrée : aucun
Valeur retournée: dater une structure date avec jour=0,mois=0,annee=0
Variables: dater uns structure date
*/
date initialiserDate(void)
{
    	date dater;
    	dater.jour=0;
    	dater.mois=0;
    	dater.annee=0;
    	return dater;
}
/*
Finalité :
Description: Cette fonction test si une structure date est egale a 0(que jour=0,mois=0,annee=0)
Paramètre en entrée : dat une structure date
Valeur retournée: un booleen vrai ou faux
Variables: aucune
*/
Booleen testDate(date dat)
{
    	if(dat.jour==0 && dat.mois==0 && dat.annee==0)
        	return vrai;
    	return faux;
}
/*
Finalité :
Description: Cette fonction remplit une structure date avec la date systeme
Paramètre en entrée : aucune
Valeur retournée: d une structure date contenant la date systeme
Variables: d une structure date
	   timestamp une structure time_t
*/
date dateJour(void)
{
    	date d;
	time_t timestamp;
	struct tm *t; 
	timestamp = time(NULL);
	t = localtime(&timestamp);
	d.jour=t->tm_mday;
	d.mois=t->tm_mon+1;
	d.annee=t->tm_year+1900;
    	return d;
}
/*
Finalité :
Description: Cette fonction initialise une liste emp a NULL
Paramètre en entrée : aucune
Valeur retournée: une liste Emprunt emp
Variables: mp declaration de la liste possedants des emprunt
*/
Emprunt empVide(void)
{
    	Emprunt emp;
    	emp=NULL;
    	return emp;
}
/*
Finalité :
Description: Cette fonction insere un emprunt e en tete de la liste emp
Paramètre en entrée : emp la liste des emprunt
		      e une structure Emp (un emprunt)
Valeur retournée: une liste Emprunt emp
Variables: *m un pointeur sur un maillon
*/
Emprunt insererEnTete(Emprunt emp,Emp e)
{
    	Maillon *m;
    	m=(Maillon*)malloc(sizeof(Maillon));
      	if(m==NULL)
        	{
        	printf("Probleme de malloc\n");
        	exit(1);
        	}
   	m->emprunts=e;
    	m->suiv=emp;
    	return m;
}
/*
Finalité :
Description: Cette fonction insere un emprunt e a la bonne place trier par numero d'emprunt
Paramètre en entrée : emp la liste des emprunt
		      e une structure Emp (un emprunt)
Valeur retournée: une liste Emprunt emp
Variables: aucune
*/
Emprunt insererEmp(Emprunt emp,Emp e)
{
   	if(emp==NULL)
		return insererEnTete(emp,e);
	if((emp->emprunts).num>e.num)
        	return insererEnTete(emp,e);
   	emp->suiv=insererEmp(emp->suiv,e);
    	return emp;
}
/*
Finalité :
Description: Cette fonction affiche les emprunt d'un etudiant saisie par l'utilisateur
Paramètre en entrée : emp la liste des emprunt
		      nbEtudiant le nombre d'étudiant de la bibliotheque
		      *tEtudiant[] le tableau de pointeur sur des structure etudiant
Valeur retournée: aucune
Variables: pos un entier contenant la position de l'etudiant 
	   nom[30] une chaine de charactere contenant le nom de l'etudiant saisi par l'utilisateur
	   prenom[30] une chaine de charactere contenant le prenom de l'etudiant saisi par l'utilisateur
*/
void afficherEmprunt(Emprunt emp,int nbEtudiant,etudiant *tEtudiant[])
{
    	int pos;
        char nom[30],prenom[30];
	printf("Quel est le nom de l'etudiant ?");
	fgets(nom,30,stdin);
	nom[strlen(nom)-1]='\0';
	printf("Quel est le prenom de l'etudiant ?");
	fgets(prenom,30,stdin);
	prenom[strlen(prenom)-1]='\0';
	pos=rechEtudiant(nom,prenom,tEtudiant,nbEtudiant);
	if(pos==nbEtudiant || ! presence(*tEtudiant[pos],nom,prenom))
		{
		printf("L'etudiant n'est pas enregistrer\n");
		return;
		}
	while(emp!=NULL)
        	{
		if(strcmp((emp->emprunts).nom,nom)==0 && strcmp((emp->emprunts).prenom,prenom)==0)
			{
        		if(testDate((emp->emprunts).retour))
            			printf("%d\t%s %s\t%s\t%d/%d/%d\tOuvrage non retourne\n",(emp->emprunts).num,(emp->emprunts).nom,(emp->emprunts).prenom,(emp->emprunts).cote,(emp->emprunts).debut.jour,(emp->emprunts).debut.mois,(emp->emprunts).debut.annee);
        		else printf("%d\t%s %s\t%s\t%d/%d/%d\t%d/%d/%d\t\n",(emp->emprunts).num,(emp->emprunts).nom,(emp->emprunts).prenom,(emp->emprunts).cote,(emp->emprunts).debut.jour,(emp->emprunts).debut.mois,(emp->emprunts).debut.annee,(emp->emprunts).retour.jour,(emp->emprunts).retour.mois,(emp->emprunts).retour.annee);
			}
        	emp=emp->suiv;
		}
}
/*
Finalité :
Description: Cette fonction calcule le nombre de jour entre la date systeme et la date d'emprunt des ouvrage, si ce nombre est supperieur a 21 alors l'emprunt est rendu en retard, au dessus de 2 mois le message change
Paramètre en entrée : emp la liste des emprunt
		      jour une structure date contenant la date systeme
Valeur retournée: nb le nombre de jour entre ces deux date
Variables: nb un entier contenant le nombre de jour d'emprunt du livre
	   nbmois[12] un tableau d'entier contenant le nombre de jour par mois pour calculer le nombre exacte de jour
*/
int nbJour(Emprunt emp,date jour)
{
    	int nb;
    	int nbmois[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    	if(jour.mois==(emp->emprunts).debut.mois)
        	nb=(jour.jour-((emp->emprunts).debut.jour))+1;
   	else if(jour.mois-((emp->emprunts).debut.mois)==1 || jour.mois-((emp->emprunts).debut.mois)==-11)
		nb=(nbmois[((emp->emprunts).debut.mois)-1]-((emp->emprunts).debut.jour)+1)+jour.jour;
        	else return -1;
    	return nb;
}
/*
Finalité :
Description: Cette fonction affiche les emprunt qui on depasser les 21 jours
Paramètre en entrée : emp la liste des emprunt
		      jour une structure date contenant la date systeme
Valeur retournée: nbRet le nombre d'emprunts en retard
Variables: nb un entier contenant le nombre de jour d'emprunt du livre
	   nbRet un entier contenant le nombre d'emprunt dont les 21 jours d'emprunts on été depassé
*/
int afficherNonRetour(Emprunt emp,date jour)
{
	int nb,nbRet=0;
    	while(estVide(emp))
        	{
        	nb=nbJour(emp,jour);
        	if(nb==-1)
			{           
			printf("L'emprunt numero %d de l'etudiant %s %s a depassee les 2 mois\n",(emp->emprunts).num,(emp->emprunts).nom,(emp->emprunts).prenom);
			nbRet=nbRet+1;
			}
        	else if(nb>=21)
				{
                		printf("L'emprunt numero %d de l'etudiant %s %s a depassee les 21 jours pour retourner son emprunt: %d jours\n",(emp->emprunts).num,(emp->emprunts).nom,(emp->emprunts).prenom,nb); 
				nbRet=nbRet+1;
				}       
		emp=emp->suiv;
       		 }
	return nbRet;
}
/*
Finalité :
Description: Cette fonction test si la liste emp est NULL
Paramètre en entrée : emp la liste des emprunt
Valeur retournée: un booleen vrai ou faux
Variables: aucune
*/
Booleen estVide(Emprunt emp)
{
    	if(emp==NULL)
        	return faux;
    	else return vrai;
}
/*
Finalité :
Description: Cette fonction insere un emprunt dans la liste emp en le placant au bon endroit
Paramètre en entrée : emp la liste des emprunt
		      jour une structure date contenant la date systeme
	              *nbEmp un pointeur sur le nombre d'emprunt
		      nbEtudiant le nombre d'étudiant de la bibliotheque
		      nbouv le nombre d'ouvrage de la bibliotheque
		      *tEtudiant[] le tableau de pointeur sur des structure etudiant
		      touvrage[] le tableau de structure des ouvrages
Valeur retournée:  emp la liste des emprunt
Variables: npos un entier contenant la position de l'etudiant fesant l'emprunt
	   nouv une structure etudiant pour copier l'etudiant
	   e une structure Emp(un emrpunt)
*/
Emprunt insererEmprunt(Emprunt emp,int *nbEmp,date jour,Ouvrage touvrage[],int nbouv,int nbEtudiant,etudiant *tEtudiant[])
{
	Emp e;
	etudiant nouv;
	int pos,rech;
	e.retour=initialiserDate();
	e.num=*nbEmp+1;
	saisir(e.nom,e.prenom);
	pos=rechEtudiant(e.nom,e.prenom,tEtudiant,nbEtudiant);
	if(pos==nbEtudiant || ! presence(*tEtudiant[pos],e.nom,e.prenom))
		{
		printf("L'etudiant n'est pas enregistrer\n");
		return emp;
		}
	nouv=*tEtudiant[pos];
	if(nouv.nbEmpCour>4)
		{
		printf("Nombre maximum d'emprunts atteint\n");
		return emp;
		}
	printf("Quelle est la cote de l'ouvrage ?");
	scanf("%s%*c",e.cote);
	rech=rechOuvrage(touvrage,e.cote,nbouv);
	if(rech==-1)
		{
		printf("Ouvrage inexistant\n");
		return emp;
		}
	if(calculAge(nouv.naissance,jour)<touvrage[rech].agelimit)
		{
		printf("L'etudiant n'à pas l'age limite pour emprunter l'ouvrage\n");
		return emp;
		}
	if(touvrage[rech].nbexemplaireDispo<1)
		{
		printf("Cette exemplaire n'est actuellement pas disponible\n");
		return emp;
		}
	e.debut=jour;
	emp=insererEmp(emp,e);
	*nbEmp=*nbEmp+1;
	nouv.nbEmp=(nouv.nbEmp)+1;
	nouv.nbEmpCour=(nouv.nbEmpCour)+1;
	touvrage[rech].nbexemplaireDispo=touvrage[rech].nbexemplaireDispo-1;
	*tEtudiant[pos]=nouv;
	return emp;
}
/*
Finalité :
Description: Cette fonction saisi le retour d'un emprunt
Paramètre en entrée : emp la liste des emprunt
		      jour une structure date contenant la date systeme
	              *nbEmp un pointeur sur le nombre d'emprunt
		      nbEtudiant le nombre d'étudiant de la bibliotheque
		      nbouv le nombre d'ouvrage de la bibliotheque
		      *tEtudiant[] le tableau de pointeur sur des structure etudiant
		      touvrage[] le tableau de structure des ouvrages
Valeur retournée:  emp la liste des emprunt
Variables: npos un entier contenant la position de l'etudiant fesant l'emprunt
	   nouv une structure etudiant pour copier l'etudiant
	   e une structure Emp(un emrpunt)
	   cote[7] une chaine de charactere dans laqu'elle sera mise la cote saisie par l'utilisateur
	   nom[30] une chaine de charactere dans laqu'elle sera mit le nom saisie par l'utilisateur
	   prenom[30] une chaine de charactere dans laqu'elle sera mit le prenom saisie par l'utilisateur
*/	 
Emprunt retourEmprunt(Emprunt emp,int *nbEmp,date jour,Ouvrage touvrage[],int nbouv,int nbEtudiant,etudiant *tEtudiant[])
{
	Emp e;
	etudiant nouv;
	int pos;
        char nom[30],prenom[30],cote[7];
	printf("Quel est le nom de l'etudiant ?");
	fgets(nom,30,stdin);
	nom[strlen(nom)-1]='\0';
	printf("Quel est le prenom de l'etudiant ?");
	fgets(prenom,30,stdin);
	prenom[strlen(prenom)-1]='\0';
	pos=rechEtudiant(nom,prenom,tEtudiant,nbEtudiant);
	if(pos==nbEtudiant || ! presence(*tEtudiant[pos],nom,prenom))
		{
		printf("L'etudiant n'est pas enregistrer\n");
		return emp;
		}
	nouv=*tEtudiant[pos];
	printf("Quelle est la cote de l'ouvrage ?");
	scanf("%s%*c",cote);
	if(rechOuvrage(touvrage,cote,nbouv)==-1)
		{
		printf("Ouvrage inexistant\n");
		return emp;
		}
        e=copieEmprunt(emp,nom,prenom,cote);
        if(e.num==-1)
                {
                printf("Emprunt inexistant\n");
		return emp;
                }
        emp=supprimerEmprunt(emp,nom,prenom,cote);
	e.retour=jour;
	emp=insererEmp(emp,e);
	nouv.nbEmpCour=(nouv.nbEmpCour)-1;
	touvrage[rechOuvrage(touvrage,e.cote,nbouv)].nbexemplaireDispo=touvrage[rechOuvrage(touvrage,e.cote,nbouv)].nbexemplaireDispo+1;
	*tEtudiant[pos]=nouv;
	return emp;
}
/*
Finalité :
Description: Cette fonction copie un emprunt de la liste dans une structure Emp
Paramètre en entrée : emp la liste des emprunt
		      cote[7] une chaine de charactere dans laqu'elle sera mise la cote saisie par l'utilisateur
	   	      nom[30] une chaine de charactere dans laqu'elle sera mit le nom saisie par l'utilisateur
	   	      prenom[30] une chaine de charactere dans laqu'elle sera mit le prenom saisie par l'utilisateur
Valeur retournée:  e un emprunt
Variables: e une structure Emp(un emrpunt)
*/
Emp copieEmprunt(Emprunt emp,char nom[],char prenom[],char cote[])
{
        Emp e;
        e.num=-1;
        while(emp!=NULL)
                {
                if(strcmp((emp->emprunts).nom,nom)==0 && strcmp((emp->emprunts).prenom,prenom)==0 && strcmp((emp->emprunts).cote,cote)==0)
                        {
                        e.num=(emp->emprunts).num;
                        strcpy(e.nom,(emp->emprunts).nom);
                        strcpy(e.prenom,(emp->emprunts).prenom);
                        strcpy(e.cote,(emp->emprunts).cote);
                        e.debut=(emp->emprunts).debut;
                        e.retour=(emp->emprunts).retour;
                        return e;
                        }
                emp=emp->suiv;
                }
        return e;
}
/*
Finalité :
Description: Cette fonction supprime un emprunt de la liste a partir du nom, prenom et de la cote
Paramètre en entrée : emp la liste des emprunt
		      cote[7] une chaine de charactere dans laqu'elle sera mise la cote saisie par l'utilisateur
	   	      nom[30] une chaine de charactere dans laqu'elle sera mit le nom saisie par l'utilisateur
	   	      prenom[30] une chaine de charactere dans laqu'elle sera mit le prenom saisie par l'utilisateur
Valeur retournée:  emp la liste des emprunt
Variables: aucune
*/
Emprunt supprimerEmprunt(Emprunt emp,char nom[],char prenom[],char cote[])
{
	if(emp==NULL)
		return emp;
	if(strcmp((emp->emprunts).nom,nom)==0 && strcmp((emp->emprunts).prenom,prenom)==0 && strcmp((emp->emprunts).cote,cote)==0)
		return emp->suiv;
	emp->suiv=supprimerEmprunt(emp->suiv,nom,prenom,cote);
	return emp;
}
/*
Finalité :
Description: Cette fonction sauvegarde la liste emp dans le fichier emprunt.bin
Paramètre en entrée : emp la liste des emprunt
Valeur retournée:  aucune
Variables: flot le fichier
*/
void sauvegarderEmp (Emprunt emp)
{
	FILE *flot;
	flot=fopen("emprunt.bin","wb");
	if(flot==NULL)
		{
		printf("probleme d'ouverture fichier");
		exit(1);
		}
	while(emp!=NULL)
		{
		fwrite(emp,sizeof(Emp),1,flot);
		emp=emp->suiv;
		}
	fclose(flot);
}
/*
Finalité :
Description: Cette fonction charger le fichier emprunt.bin dans la liste emp
Paramètre en entrée : emp la liste des emprunt
		      *nbEmp un pointeur sur le nombre d'emprunt
Valeur retournée:  emp la liste des emprunt
Variables: e un emprunt(Emp)
	   flot le fichier
*/
Emprunt chargerEmprunts(Emprunt emp,int *nbEmp)
{
	*nbEmp=0;	
	FILE *flot;
	Emp e;
	flot=fopen("emprunt.bin","rb");
	if(flot==NULL)
		{
		printf("probleme d'ouverture du fichier emprunt.bin en lecture\n");
		exit(1);
		}
	fread(&e,sizeof(Emp),1,flot);
	while(!feof(flot))
		{
		emp=insererEmp(emp,e);
		*nbEmp=*nbEmp+1;		
		fread(&e,sizeof(Emp),1,flot);
		}
	fclose(flot);
	return emp;
}
/*
Finalité :
Description: Cette fonction affiche les statisque de la bibliotheque ( nombre de livre, etuddiant, emprunt ainsi que moyenne age et nombre emprunts/etudiant)
Paramètre en entrée : nbEtudiant le nombre d'étudiant de la bibliotheque
		      nbouv le nombre d'ouvrage de la bibliotheque
		      *tEtudiant[] le tableau de pointeur sur des structure etudiant
		      emp la liste des emprunt de la bibliotheque
		      jour une structure date contenant la date systeme
Valeur retournée: aucune
Variables: nbEmp un entier contenant le nombre d'emprunt passer
	   somAge un entier contenant la somme des ages des etudiant de la bibliotheque permettant le calcule de la moyenne d'age des etudiants
*/
void statistique(int nbouv,int nbEtudiant,etudiant *tEtudiant[],Emprunt emp,date jour)            
{
        int nbEmp,somAge;
        nbEmp=nbEmpr(emp);
        somAge=somAges(tEtudiant,nbEtudiant,jour);
        printf("-------------------------------------------------------------------------\n");
        printf("|\t\t\t\tStatistique \t\t\t\t|\n");
        printf("-------------------------------------------------------------------------\n");
        printf(" Nombre d'etudiants inscrits: %d\n",nbEtudiant);
        printf(" Nombre d'ouvrages inscrits: %d\n",nbouv);
        printf(" Nombre total d'emprunts: %d\n",nbEmp);
        if(nbEtudiant>0)
                {
                printf(" Moyenne d'age des etudiants inscrits: %d\n",somAge/nbEtudiant);
                printf(" Nombre moyen d'emprunts par etudiant: %d\n",nbEmp/nbEtudiant);
                }
}
/*
Finalité :
Description: Cette fonction calcule le nombre d'emprunt de la bibliotheque
Paramètre en entrée : emp la liste des emprunt de la bibliotheque
Valeur retournée: nbEmp le nombre d'emprunt
Variables: nbEmp un entier contenant le nombre d'emprunt passer
*/
int nbEmpr(Emprunt emp)
{
        int nbEmp=0;
        while(estVide(emp))
                {
                nbEmp=nbEmp+1;
                emp=emp->suiv;
                }
        return nbEmp;
}
/*
Finalité :
Description: Cette fonction calcule la somme des ages des etudiants de la bibliotheque
Paramètre en entrée : *tEtudiant[] le tableau de pointeur sur des structure etudiant
		      nbEtudiant le nombre d'étudiant de la bibliotheque
		      jour une structure date contenant la date systeme
Valeur retournée: somAge la somme des ages
Variables: samAge un entier contenant la somme des ages des etudiants
	   i un entier permetant le parcour du tableau *tEtudiant[]
*/
int somAges(etudiant *tEtudiant[],int nbEtudiant,date jour)
{
    	int somAge=0,i;
    	for(i=0;i<nbEtudiant;i++)
       		somAge=somAge+(calculAge (tEtudiant[i]->naissance,jour));
    	return somAge;
}

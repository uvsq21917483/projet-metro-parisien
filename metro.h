#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
	int distmin;
	int used;
	int pere;
	}DJIKSTRA;


typedef struct{
	int  nb_stations;
	int  nb_lignes;
	}CPT;


typedef struct{
	char * station;
	int  num_ligne;
	}ONE_STATION;


typedef struct{
	ONE_STATION * stations;
	int ** mat;
	}METROS;

CPT compter_nbr_statios(char *nom_fic);

METROS allocation(METROS M,CPT n);

METROS  read_fic(char *nom_fic,CPT n);

void desallocations(METROS M,CPT n,DJIKSTRA *x);

void affichage(METROS M,CPT n);

int get_station_number(METROS M,char * la_station,int metro,CPT cpt);
	
int minim(DJIKSTRA * x,int n);

DJIKSTRA * plus_court_chemin(char * depart,int md,char * arrivee,METROS M,CPT n);
	

int compare(char * x,char * y);


void interpreter_djikstra(DJIKSTRA * j,char * dp,char * ar,METROS m,CPT n,int metro);


void un_parcours(int f,int s,METROS M,int metro,CPT n);

#include "metro.h"
		

CPT compter_nbr_statios(char *nom_fic){
	CPT cpt;
	int n=0;
	char L[100];
	FILE *f=fopen(nom_fic,"r");
	fgets(L,100,f);
	fgets(L,100,f);
	fgets(L,100,f);
	fscanf(f,"%s",L);
	char l[10];
//	int lgns=0;
	
	while(strcmp(L,"V")==0){
		n++;
		fscanf(f,"%s",l);
		fscanf(f,"%s",l);
	//	if (atoi(l)>lgns) lgns=atoi(l);
		fgets(L,100,f);
		fscanf(f,"%s",L);
		}
	fclose(f);
	//free(f);
	
	cpt.nb_stations=n;
	//cpt.nb_lignes=lgns;
	
	return cpt;
	}
	
	
METROS allocation(METROS M,CPT n){
	
	M.stations=malloc(sizeof(ONE_STATION)*n.nb_stations);
	for(int i=0;i<n.nb_stations;i++){
		M.stations[i].station=malloc(sizeof(char)*60);
		
		}
	M.mat=malloc(sizeof(int)*n.nb_stations);
	for(int j=0;j<n.nb_stations;j++){
		
		M.mat[j]=malloc(sizeof(int)*n.nb_stations);
		
		}	
	return M;
	}
	
METROS  read_fic(char *nom_fic,CPT n){
	
	METROS M;
	
	M=allocation(M,n);
	
	
	FILE *f=fopen(nom_fic,"r");
	
	int a,o;
	
	char r[100];
	
	
	fgets(r,100,f);
	fgets(r,100,f);
	fgets(r,100,f);
	
	
	for(int i=0;i<n.nb_stations;i++){
		for(int j=0;j<n.nb_stations;j++){
			M.mat[i][j]=0;
			}
		}
		
	fscanf(f,"%s",r);
	char t[10];
	while(fgetc(f)!=EOF){
		if(strcmp(r,"V")==0){
			
			fscanf(f,"%s",r);	
			
			fscanf(f,"%s",t);	
			
			M.stations[atoi(r)].num_ligne=atoi(t);
			fgetc(f);
			fgets(M.stations[atoi(r)].station,60,f);
			
			fscanf(f,"%s",r);
			
			}
		if(strcmp(r,"E")==0){
			fscanf(f,"%s",r);	
			a=atoi(r);
			fscanf(f,"%s",r);	
			o=atoi(r);
			fscanf(f,"%s",r);	
			M.mat[a][o]=atoi(r);
			M.mat[o][a]=atoi(r);
			
			fscanf(f,"%s",r);	
			}
		}
	fclose(f);
	//free(f);
	return M;
}
void desallocations(METROS M,CPT n,DJIKSTRA * x){
	for(int i=0;i<n.nb_stations;i++){
		free(M.mat[i]);
		free(M.stations[i].station);
	}
	free(M.mat);
	free(M.stations);
	free(x);
}


void affichage(METROS M,CPT n){
	for(int i=0;i<n.nb_stations;i++){
		printf("%s ",M.stations[i].station);
		printf("%d ",M.stations[i].num_ligne);
		}
	for(int i=0;i<n.nb_stations;i++){
		//for(int j=0;j<n.nb_stations;j++){		
			//if (M.mat[i][j] >0) {
				 printf("\n entre %d et  c'ets %d \n",i,M.mat[337][i]);
		//	}
		//}
	}
}

int compare(char * x,char * y){
	for(int i=0;i<strlen(x);i++){
		if(x[i]!=y[i]){
			if(x[i]=='_' && y[i]==' '){
				continue;
				}else return 1;
			}
		}
	return 0;
	}


int get_station_number(METROS M,char * la_station,int metro,CPT cpt){
				
	for(int i=0;i<cpt.nb_stations;i++){	
		if(compare(la_station,M.stations[i].station)==0){
			if (metro==-1) {
				return i;
					}
			else if (metro==M.stations[i].num_ligne) {
				return i;
			}
			}
		}
	return -1; 	
	}
	
int minim(DJIKSTRA * x,int n){
	int i=0,j=-1;
	int min=999999;
	while(i<n){
		if(x[i].used==0){
			if (x[i].distmin < min ){
					if (x[i].distmin > 0){

				min=x[i].distmin;
				j=i;
				}
			}
		}
		i++;
		}
	
	return j;
	}

DJIKSTRA * plus_court_chemin(char * depart,int md,char * arrivee,METROS M,CPT n){
	
	DJIKSTRA *pcc=malloc(sizeof(DJIKSTRA)*376);
	for(int i=0;i<n.nb_stations;i++){	
	pcc[i].distmin=999999;
	pcc[i].used=0;
	pcc[i].pere=-1;
	}
	int d=get_station_number(M,depart,md,n);
	int a=get_station_number(M,arrivee,-1,n);
	if( (d==-1) || (a==-1)){
			fprintf(stderr,"vous n'avez pas tappé(e) la bonne station d'arrivee ou de depart ");
			exit(EXIT_FAILURE);
		}
		int nv;
		
		pcc[d].distmin=0;
	while(pcc[a].used == 0){
		int i=0;
		while(i<n.nb_stations){
			if (M.mat[d][i]>0){
				if(pcc[i].used==0){
				 nv=M.mat[d][i]+pcc[d].distmin;
				if  (pcc[i].distmin > nv) {
					 pcc[i].distmin=nv;
					 pcc[i].pere=d;
					}	
				}
			} 		
		i++;
		}	
		pcc[d].used=1;
		d=minim(pcc,n.nb_stations);
		
	}
	return pcc;
}

void interpreter_djikstra(DJIKSTRA * j,char * dp,char * ar,METROS m,CPT n,int metro){
	int d=get_station_number(m,dp,metro,n);
	int a=get_station_number(m,ar,metro,n);
	if(m.stations[a].station==m.stations[j[a].pere].station){
	printf("\n à %s prenez la ligne  %d ",m.stations[j[a].pere].station,m.stations[a].num_ligne);
	}else{
		printf("\n à %s prenez la ligne  %d ",m.stations[a].station,m.stations[a].num_ligne);
		}
	int ligne=m.stations[a].num_ligne;
	a=j[a].pere;
	while(a!=d){
		
		if (m.stations[a].num_ligne != ligne){
			printf("en direction de %s \n ",m.stations[a].station);
			
			printf("\n à %s prenez la ligne %d ",m.stations[a].station,m.stations[a].num_ligne);
			ligne=m.stations[a].num_ligne;
				
			}
		a=j[a].pere;
		}
	printf("\n \n en direction de  %s où vous descendez car cous etes arrivez à votre destination \n",m.stations[a].station);
	}

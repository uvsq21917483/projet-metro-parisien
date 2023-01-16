#include "metro.h"
int main(int argc,char ** argv){
	CPT n=compter_nbr_statios(argv[1]);
	METROS M;
	M=read_fic(argv[1],n);
	/*
	char  d[100];
	char  a[100];
	
	int m;
	
	printf("donnez la station de depart ");
	scanf("%s",d);
	
	printf("vous etes dans quel metro,si vous ne savez pas tappez -1 :");
	scanf("%d",&m);
	
	printf("%d",m);
	
	
	printf("donnez la station d'arriver ");
	scanf("%s",a);
	*/
	
	int x=get_station_number(M,argv[4],atoi(argv[3]),n);	
	DJIKSTRA * D=plus_court_chemin(argv[2],atoi(argv[3]),argv[4],M,n);
	
	interpreter_djikstra(D,argv[2],argv[4],M,n,atoi(argv[3]));
	
	printf("\n vous devez arriver dans environs %d minutes \n",1+D[x].distmin/60);
	desallocations(M,n,D);	
	
	
	
	
	
	
	exit(EXIT_SUCCESS);
}

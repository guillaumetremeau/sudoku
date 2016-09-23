#include <stdio.h>
#include <stdlib.h>


#define N 9 /*Taille du jeu*/
#define HORIZ 0 /*Définie le sens de vérification de la fonction verifierLignColonne*/
#define VERT 1


/*Fonction qui initialise toutes les cases de la grille du sudoku
 * grille : matrice carré représentant la grille du sudoku*/
int initialiser(int grille[N][N]);

/*Fonction qui affiche le sudoku
 * grille : matrice carre représentant la grille du sudoku*/
int afficher(int grille[N][N]);

/*Fonction qui génere la grille de départ efface aléatoirement des cases
 * retourne le nombre d'éléments non nuls
 * grille : matrice carre representant la grille du sudoku*/
int generer(int grille[N][N]);

/*Fonction qui permet à l'utilisateur de saisir une valeur dans le sudoku en lui
 * demandant les indices i et j ainsi que la valeur
 * grille : matrice carre représentant la grille du sudoku*/
void saisir(int grille[N][N]);

/*Fonction qui vérifie si la ligne ou la colonne est bien remplie retourne 1 si
 * c'est correct 0 sinon
 * grille : matrice carre représentant la grille du sudoku
 * indice : indice de départ de la vérification
 * sens : sens de verification (horizontale ou verticale)*/
int verifierLigneColonne(int grille[N][N], int indice, int sens);

/*Fonction qui verifie si la région est bien remplie, retourne 1 si c'est
 * correct 0 sinon
 * grille : matrice représentant la grille du sudoku
 * k,l: indices de la région*/
int verifierRegion(int grille[N][N], int k, int l);

/*Fonction qui verifie si la grille est correctement remplie, renvoie 1 si c'est
 * le cas et 0 sinon
 * grille : matrice représentant la grille du sudoku*/
int verifierGrille(int grille[N][N]);


int remplissage = 0;

/*Programme principale du SUDOKU*/
int main(){
	printf("----- SUDOKU -----\n\n");

	int grille[N][N];

	initialiser(grille);
	remplissage = generer(grille);
	while(remplissage<N*N){
		system("clear");
		afficher(grille);
		saisir(grille);
	}
	if(verifierGrille(grille)) printf("\nVous avez gagnez !\n");
	else printf("\nGrille mal remplise");

	printf("\n\nFIN\n----- SUDOKU -----\n");
	return 0;
}

int initialiser(int grille[N][N]){
	int i,j;

	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			grille[i][j] = 0;
		}
	}

	return 0;
}

int afficher(int grille[N][N]){
	int i,j;

	for(i=0;i<N;i++){
		printf("\n");
		for(j=0;j<N;j++){
			if(grille[i][j]==0) printf("  ");
			else printf("%d ",grille[i][j]);
		}
	}

	return 0;
}


int generer(int grille[N][N]){
	int i, j, res;
	for(j=0;j<N; ++j) 
	{
		for(i=0; i<N; ++i){
			if(j!= 3 || i!=7){
				grille[j][i] = (i + j*3 +j /3) %N +1 ; 
				res ++;
			}
		}
	}
	return res;
}

void saisir(int grille[N][N]){
	int i,j,val;
	printf("\nindice i (horizontale) : ");
	scanf("%d",&i);
	printf("\nindice j (verticale) : ");
	scanf("%d",&j);
	printf("\nvaleur : ");
	scanf("%d",&val);

	if(i>=0 && i <N && j>=0 && j<N && val>=1 && val <=N){
		if(grille[i][j]==0){
			remplissage++;
			grille[i][j] = val;
		} else printf("Place déjà occupée");
	}else printf("Saisie invalide");
}

int verifierLigneColonne(int grille[N][N], int indice, int sens){
	int res = 1;
	int tabVer[N];
	int i;

	for(i=0;i<N;i++){
		tabVer[i] = 0;
	}
	/*Compte le nombre de chiffre dans chaque case */
	for(i=0;i<N;i++){
		if(sens) tabVer[grille[i][indice]-1]++;
		else tabVer[grille[indice][i]-1]++;
	}

	for(i=0;i<N;i++){
		if(tabVer[i]>1)res = 0;
	}
	return res;
}

int verifierRegion(int grille[N][N], int k, int l){
	int res = 1;
	int i,j;
	int tabVer[N];

	for(i=0;i<N;i++){
		tabVer[i] = 0;
	}
	for(i=k*3;i<(k*3)+3;i++){
		for(j=l*3;j<(l*3)+3;i++){
			tabVer[grille[i][j]-1]++;
		}
	}
	for(i=0;i<N;i++){
		if(tabVer[i]>1)res = 0;
	}
	return res;
}

int verifierGrille(int grille[N][N]){
	int res = 1;
	int i,j;

	for(i=0;i<N;i++){
		if(!verifierLigneColonne(grille,i,HORIZ)) res = 0;
		if(!verifierLigneColonne(grille,i,VERT)) res = 0;
	}
	for(i=0;i<N/3;i++){
		for(j=0;j<N/3;j++){
			if(!verifierRegion(grille,i,j)) res = 0;
		}
	}
	return res;
}

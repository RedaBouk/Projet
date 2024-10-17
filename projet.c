#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

enum {LONG_PRENOM_MAX = 30,NB_ETU_MAX=100, NB_ABS_MAX=8000};

typedef struct {
	int identifiant, groupe,absence;
	char prenom[LONG_PRENOM_MAX];
} Etudiant ;

typedef struct {
	int id,jour;
	char demi_jour[3];

}Absence;

void sortie(char requete[]) {
	if (strcmp(requete, "exit") == 0) {
		exit(0);
	}
}

int inscription(Etudiant tab[NB_ETU_MAX], int i) {
	char prenom[LONG_PRENOM_MAX];
	int groupe;

	scanf("%s", prenom);
	
	if (strlen(prenom) < LONG_PRENOM_MAX) {
		strcpy(tab[i].prenom, prenom);
		scanf("%d", &groupe);
		for (int j = 0; j < i; ++j) {
			if (groupe == tab[j].groupe && strcmp(prenom,tab[j].prenom)==0) {
				printf("Nom incorrect\n");
				return 0;
			}
		}
		tab[i].groupe = groupe;
		tab[i].identifiant = i;
		tab[i].absence = 0;
		printf("Inscription realisee (%d)\n", tab[i].identifiant+1);
		return 1;  
	}
	else {
		printf("Nom trop long\n");
		return 0;  
	}
}

void absence(Etudiant tab[NB_ETU_MAX], Absence tab2[NB_ABS_MAX], int* nb_absence, int nb_etudiant) {
	int id, jour;
	char demi_jour[3];

	scanf("%d", &id);

	if (id > 0 && id <= nb_etudiant) {
		scanf("%d", &jour);

		if (jour >= 1 && jour <= 40) {
			scanf("%s", demi_jour);
			if ((strcmp(demi_jour, "am") == 0) || (strcmp(demi_jour, "pm") == 0)) {
				
				for (int j = 0; j < *nb_absence; ++j) {
					if (jour == tab2[j].jour && strcmp(demi_jour, tab2[j].demi_jour) == 0 && tab2[j].id == (id - 1)) {
						printf("Absence deja connue\n");
						return;  
					}
				}
				
				tab2[*nb_absence].id = id - 1;
				tab2[*nb_absence].jour = jour;
				strcpy(tab2[*nb_absence].demi_jour, demi_jour);
				(*nb_absence)++;
				printf("Absence enregistree [%d]\n", *nb_absence);
			}
			else {
				printf("Demi-journee incorrecte\n");
			}
		}
		else {
			printf("Date incorrecte\n");
		}
	}
	else {
		printf("Identifiant incorrect\n");
	}
}


void etudiants(Etudiant tab[], int i) {
	int jour;
	scanf("%d", &jour);
	if (jour >= 1 && jour <= 40) {
		if (i == 0) {
			printf("Aucun inscrit\n");
		}
		else {
			
			for (int j = 0; j < i; ++j) {  
				printf("(%d) %s %d %d\n", tab[j].identifiant + 1, tab[j].prenom, tab[j].groupe, tab[j].absence);
			}
		}
	}
	else {
		printf("Date incorrecte\n");
	}
}

int main() {
	char requete[100];
	Etudiant tab[NB_ETU_MAX];
	Absence tab2[NB_ABS_MAX];
	int i = 0;
	int nb_abs = 0;
	while (1) { 
		scanf("%s", requete);
		sortie(requete);

		if (strcmp(requete, "inscription") == 0) {
			if (i >= NB_ETU_MAX) {
				printf("Limite d'inscription atteinte\n");
			}
			else {
				if (inscription(tab, i)) {  
					i++;  
				}
			}
		}
		else if (strcmp(requete, "absence") == 0) {
			absence(tab,tab2,&nb_abs,i);
		}
		else if (strcmp(requete, "etudiants") == 0) {
			etudiants(tab,i);
		}
		
	}
}
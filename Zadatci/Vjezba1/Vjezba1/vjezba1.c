#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 60
// max bod brojeva na kolokviju je 60 

struct Student
{
	char ime[100];
	char prezime[100];
	int bodovi;
};

double rel(int bodovi) // relativni bodovi / postotak)
{
	double x = (double)bodovi / MAX * 100;
	return x;
}

 int ispis(struct Student *studenti, int redovi)
{
	int i;
	for (i = 0; i < redovi; i++)
	{
		printf("%s %s %d %lf \n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, rel(studenti[i].bodovi));
	}
	return 0;
}


 int main()
 {
	 int redovi = 0;

	 FILE *file;
	 file = fopen("info.txt", "r");
	 if (file == NULL)
	 {
		 printf("error");
		 return 1;
	 }
	// int c;              
	//while ((c= fgetc(file)) != EOF)
	// {
	//	if c = "\n";
	//	 redovi++;
	// }


	 char buffer[256];
	 while (fgets(buffer,sizeof(buffer), file) != NULL)
	 {
		 redovi++;
	 }
	 rewind(file);

	 struct Student* studenti = malloc(redovi * sizeof(struct Student));
	 if (studenti == NULL)
	 {
		 printf("error");
		 return 1;
	 }
	 int i;
	 for (i = 0; i < redovi; i++)
	 {
		 fscanf(file,"%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
	 }
	 fclose(file);

	 ispis(studenti, redovi);


	 free(studenti); // oslobadamo memoriju
	 studenti = NULL; //nakon oslobadanja memorije, pointer pokazuje na nevaljani objekt pa ga ukidamo
	 return 0;
}
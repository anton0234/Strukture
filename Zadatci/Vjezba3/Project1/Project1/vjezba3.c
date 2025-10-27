#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NOT_OPENED -1
#define MAX_LINE 1024
#define MAX_LENGTH 128
#define EXIT_SUCCESS 0 
#define ERROR_MALLOC -2
#define ERROR_SCANF -3
#define NOT_FOUND -4


/*2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/



/*3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke.*/

struct _Person;
typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_LENGTH];
	char lastName[MAX_LENGTH];
	int birthYear;
	Position next;
}Person;

//2 zadatak
int addBeginnning(Position);
int printList(Position);
int addtoEnd(Position);
Position findbylastName(Position, char*);
int deletePerson(Position, char*);
Position createPerson();


//3 zadatak
int addafterFoundPerson(Position, char*);
int addbeforeFoundPerson(Position, char*);
int sort(Position);
int addtoFile(Position);
int readfromFile();




int main()
{
	//postavljam head
	Person head = {
		.name = "",
		.lastName = "",
		.birthYear = 0,
		.next = NULL
	};
	int action = -1;
	char surname[MAX_LENGTH] = "";

	printf("Choose Action from the list:\n1 - Add new Person to the top of the list\n2 - Print list\n3 - Add new Person to the end of the list\n4 - Find a Person by surname\n5 - Delete a Person from the list\n6-Add person after the surname\n7- add person before the surname\n 8- Sort through list using surnames\n");

	do {
		printf("Type a number 1-6 for listed actions or 0 to end program: ");
		if (!scanf(" %d", &action)) {
			printf("Scanf error while choosing action\n");
			exit(ERROR_SCANF);
			continue;
		}
		switch (action)
		{
		case 0:
			printf("Program ended by user!\n");
			break;

		case 1:
			addBeginning(&head);
			break;

		case 2:
			printList(&head);
			break;

		case 3:
			addToEnd(&head);
			break;

		case 4:
			printf("Enter surname of a Person to find: ");
			if (!scanf("%s", surname)) {
				printf("Scanf error while entering surname to find\n");
				exit(ERROR_SCANF);
			}
			else
				findbylastName(&head, surname) == NULL;
			findbylastName(&head, surname);
			break;

		case 5:
			printf("Enter surname of a Person to delete: ");
			if (!scanf("%s", surname)) {
				printf("Scanf error while entering surname to delete\n");
				exit(ERROR_SCANF);
			}
			else
				deletePerson(&head, surname);
			break;
		case 6:
			printf("Enter surname of a Person to add char behind him: ");
			if (!scanf("%s", surname)) {
				printf("Scanf error while entering surname to delete\n");
				exit(ERROR_SCANF);
			}
			else
				addafterFoundPerson(&head, surname);
			break;
		case 7:
			printf("Enter surname of a Person to add char before him: ");
			if (!scanf("%s", surname)) {
				printf("Scanf error while entering surname to delete\n");
				exit(ERROR_SCANF);
			}
			else
				addbeforeFoundPerson(&head, surname);
			break;
		case 8:
			sort(&head);
			break;

		default:
			printf("Invalid input! Try again!\n");
			break;
		}

	} while (action != 0);


	return EXIT_SUCCESS;

}



int printList(Position head)
{
	if (head->next == NULL) {
		printf("Prazna je lista!\n");
		return EXIT_SUCCESS;
	}

	//umjesto da koristin uvijek head->next damo mu vraijablu (current)
	Position current = head->next;

	printf("Name\tLastName\tYear\n");
	while (current != NULL) {
		printf("%s\t%s\t%d\n", current->name, current->lastName, current->birthYear);
		current = current->next;
	}
	return EXIT_SUCCESS;
}

int addToEnd(Position head)
{
	Position newPerson = createPerson();

	//klasik test
	if (!newPerson) {
		printf("Memory allocation error\n");
		return ERROR_MALLOC;
	}
	//presaltamo na kraj liste
	while (head->next != NULL)
	{
		head = head->next;
	}
	//newPerson-> next je NULL tj zadnji clan
	newPerson->next = head->next;
	//u listi elemetnu head pointeru next se postavlja vrijednosti newPersona
	head->next = newPerson;
	return EXIT_SUCCESS;
}

Position findbylastName(Position head, char* lastName)
{
	//head je postavljen ka prazan element gleda se iduci( pravi)
	if (head->next == NULL)
	{
		printf("Lista je prazna");
		return NULL;
	}
	//sve dok postoji iduci element
	while (head->next != NULL)
	{
		if (strcmp(head->next->lastName, lastName) == 0)//compare ostavlja vrijednost 0 ako su usporedeni elementi isti<
		{

			printf("pronadena osoba %s", head->next->lastName);
			return head->next;
		}
		else
		{
			head = head->next;
		}

	}

	printf("nije se pronasla osoba");
	return NULL;
}


//nova osoba u listi -> koristi se u drugim funkcijama
Position createPerson()
{
	Position newPerson = malloc(sizeof(Person)); //alociran memoriju za novi person velicine person
	if (newPerson == NULL)
	{
		printf("MALLOC error");
		exit(ERROR_MALLOC);
	}

	printf("New person's name: ");
	if (!scanf(" %s", newPerson->name))
	{
		printf("Scanf error");
		exit(ERROR_SCANF);
	}

	printf("New person's surname: ");
	if (!scanf(" %s", newPerson->lastName))
	{
		printf("Scanf error");
		exit(ERROR_SCANF);
	}

	printf("New person's birth year: ");
	if (!scanf(" %d", &newPerson->birthYear))
	{
		printf("Scanf error");
		exit(ERROR_SCANF);
	}
	newPerson->next = NULL;
	return newPerson;
}
int addBeginning(Position head)
{
	Position newPerson = createPerson();
	if (newPerson == NULL)
	{
		printf("failed memory alloc");
		return ERROR_MALLOC;
	}
	//postavit da je newPerson jednak headu i da imaju iste elemente izad njega
	newPerson->next = head->next;
	//postavit da je iduc element od heada newPerson
	head->next = newPerson;
	return EXIT_SUCCESS;
}
int deletePerson(Position head, char* lastName)
{
	Position localPos = head;
	Position Person = findbylastName(head, lastName);
	if (Person == NULL)
	{
		return NOT_FOUND;
	}
	while (localPos->next != Person)
	{
		localPos = localPos->next;
	}
	if (localPos->next == NULL)
	{
		return NOT_FOUND;
	}


	localPos->next = Person->next;
	free(Person);
	Person = NULL;
	return EXIT_SUCCESS;

}
int addafterFoundPerson(Position head, char* lastName)
{
	Position localPos = head;

	Position found = findbylastName(head, lastName);
	if (found == NULL)
	{
		return ERROR_MALLOC;
	}
	while (localPos!= found)
	{
		localPos = localPos->next;
	}

	Position novi = createPerson();
	if (novi == NULL)
	{
		return ERROR_MALLOC;
	}
	novi->next = localPos->next;
	localPos->next = novi;

	return EXIT_SUCCESS;
}
int addbeforeFoundPerson(Position head, char* lastName)
{
	Position temp = findbylastName(head, lastName);
	if (temp == NULL)
	{
		return NOT_FOUND;
	}

	while (head->next != temp && head->next !=NULL)
	{
		head = head->next;
	}
	Position newPerson = createPerson();
	newPerson->next = temp;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

//sortira listu po prezimenima
int sort(Position head)
{
	int elements=0;
	Position i, j;
	char temp[50];
	for (i = head; i !=NULL; i=i->next)
	{
		for (j = head; j->next !=NULL; j=j->next)
		{
			if (strcmp(j->lastName,j->next->lastName)>0)
			{
				strcpy(temp, j->lastName);
				strcpy(j->lastName, j->next->lastName);
				strcpy(j->next->lastName, temp);
			}
		}
	}
	return EXIT_SUCCESS;


}


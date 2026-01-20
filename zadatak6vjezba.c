#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define FOPEN_ERROR -2


typedef struct date
{
	int year;
	int month;
	int day;

}Date;

struct _item;
typedef struct _item* List;
typedef struct _item
{
	char name[128];
	int price;
	int amount;
	List next;
}Item;




struct _receipt;
typedef struct _receipt* Position;
typedef struct _receipt
{
	Date datum;
	Item item;
	Position next;

}Receipt;
bool isDateLater(Date date1, Date date2)
{
	if (date1.year > date2.year)
	{
		return true;
	}
	else if (date1.year == date2.year && date1.month > date2.month)
	{
		return true;
	}
	else if (date1.year == date2.year && date1.month == date2.month && date1.day > date2.day)
		return true;
	else
	{
		return false;
	}
}
int sortItem(List newitem, List head)
{
	List current = head;
	if (current->next == NULL)
	{
		newitem->next = NULL;
		current->next = newitem;
		return 0;
	}
	List prev = head;
	current = current->next;
	while (current != NULL)
	{
		if (strcmp(newitem->name, current->name) < 0)
		{
			break;
		} 
		current = current->next;
		prev = prev->next;
	}
	prev->next = newitem;
	newitem->next = current;

	return 0;
}
int readFILE(Position head)
{
	FILE* file;
	file = fopen("info.txt", "r");
	if (file == NULL)
	{
		return FOPEN_ERROR;
	}
	int i = 0; int j;
	char buffer[256];
	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		i++;
	}
	rewind(file);
	for (j = 0; j < i; j++)
	{
		Position newReceipt = malloc(sizeof(Receipt));
		
		char filename[256];
		if ((fscanf(file, "%s", filename))!=1)
		{
			return FOPEN_ERROR;
		}
		readReceipt(filename, newReceipt);
		head->next = newReceipt;
		head = head->next;
	}
	fclose(file);
	return 0;
}




int readReceipt(char name[50], Position head)
{
	List HeadItem;
	HeadItem = &head->item;
	FILE* file;
	file = fopen(name, "r");
	if (file == NULL)
	{
		return FOPEN_ERROR;
	}
	
	if ((fscanf(file, "%d-%d-%d", &head->datum.year, &head->datum.month, &head->datum.day)) != 3)
	{
		return FOPEN_ERROR;
	}

	head->item.name[0] = '\0';
	head->item.amount = 0;
	head->item.price = 0;
	head->item.next = NULL;


	while (!feof(file))
	{
		List newitem = malloc(sizeof(Item));
		if (newitem == NULL)
		{
			return FOPEN_ERROR;
		}
		if (fscanf(file, "%s %d %d",newitem->name,&newitem->price,&newitem->amount) != 3)
		{
			return FOPEN_ERROR;
		}
		sortItem(newitem,&head->item);
	}


	fclose(file);
	return 0;
}

int printreceipts(Position head)
{
	Position current = head->next;
	while (current != NULL)
	{
		printf("%d.%d.%d.\n", current->datum.day, current->datum.month, current->datum.year);
		List currentItem = current->item.next;
		while (currentItem != NULL) {
			printf("%s\t%d\t%d\n", currentItem->name, currentItem->amount, currentItem->price);
			currentItem = currentItem->next;
		}
		current = current->next;
		printf("\n");
	}
	return 0;

}
int sort(Position head)
{
	Position current = head->next;
	while (current != NULL)
	{
		    
	}


}




int main()
{

	Receipt head = {
		{0, 0, 0},
		{"", 0, 0.0, NULL},
		NULL
	};

	readFILE(&head);
	printreceipts(&head);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ItemToPurchase.h"


int main(){
ItemToPurchase* Item1 = (ItemToPurchase*) malloc(sizeof(ItemToPurchase));
ItemToPurchase* Item2 = (ItemToPurchase*) malloc(sizeof(ItemToPurchase));
ItemToPurchase* cookieTest = (ItemToPurchase*) malloc(sizeof(ItemToPurchase));

MakeItemBlank(Item1);
MakeItemBlank(Item2);
MakeItemBlank(cookieTest);

cookieTest->itemName = "Chocolate Chips";
cookieTest->itemPrice = 3;
cookieTest->itemQuantity = 1;

printf("Item 1\nEnter the item name:\n");
fgets(Item1->itemName, 50, stdin);
printf("Enter the item price:\n");
scanf("%d", &Item1->itemPrice);
printf("Enter the item quantity:\n");
scanf("%d", &Item1->itemQuantity);

char c = getchar();
strtok(Item1->itemName, "\n");
printf("\n");

printf("Item 2\nEnter the item name:\n");
fgets(Item2->itemName, 50, stdin);
printf("Enter the item price:\n");
scanf("%d", &Item2->itemPrice);
printf("Enter the item quantity:\n");
scanf("%d", &Item2->itemQuantity);
printf("\n");

strtok(Item2->itemName, "\n");

printf("TOTAL COST\n");
PrintItemCost(Item1);
PrintItemCost(Item2);

int total = (Item1->itemQuantity * Item1->itemPrice) + (Item2->itemQuantity * Item2->itemPrice);
printf("\nTotal: $%d\n", total);



return 0;
}

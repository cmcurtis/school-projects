#include "ItemToPurchase.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MakeItemBlank(ItemToPurchase* Item){
Item->itemName = malloc(100);
strcpy(Item->itemName, "none");
Item->itemPrice = 0;
Item->itemQuantity = 0;

}

void PrintItemCost (ItemToPurchase* Item){

printf("%s %d @ $%d = $%d\n", Item->itemName, Item->itemQuantity, Item->itemPrice, Item->itemQuantity* Item->itemPrice);

}

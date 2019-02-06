
typedef struct ItemToPurchase_struct{
char* itemName;
int itemPrice;
int itemQuantity;
} ItemToPurchase;

void MakeItemBlank(ItemToPurchase* Item);

void PrintItemCost (ItemToPurchase* Item);


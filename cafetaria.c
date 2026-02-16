#include "Cafetaria.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>



// Function definitions for food item operations
struct fooditem* fooditemHead = NULL;


void addfooditem(struct fooditem** head , char *name,int id ,float price){
    struct fooditem* newItem = (struct fooditem*)malloc(sizeof(struct fooditem));
    newItem->name = name;
    newItem->id = id;
    newItem->price = price;
    newItem->next = *head;
    *head = newItem;
}
void removefooditem(struct fooditem** head,int id){
    struct fooditem* current = *head;
    struct fooditem* previous = NULL;
    while(current != NULL && current->id != id){
        previous = current;
        current = current->next;
    }
    if(current == NULL){
        printf("Food item with ID %d not found.\n",id);
        return;
    }
    if(previous == NULL){
        *head = current->next;
    }else{
        previous->next = current->next;
    }
    free(current);
}

void updatefooditem(struct fooditem* head,int id ,char* name,float price){
    struct fooditem* current = head;
    while(current != NULL && current->id != id){
        current = current->next;
    }
    if(current == NULL){
        printf("Food item with ID %d not found.\n",id);
        return;
    }
    current->name = name;
    current->price = price;
}

void displayfooditems(struct fooditem* head){
    struct fooditem* current = head;
    if(current == NULL){
        printf("No food items available.\n");
        return;
    }
    printf("Food Items:\n");
    while(current != NULL){
        printf("ID: %d, Name: %s, Price: %.2f\n",current->id,current->name,current->price);
        current = current->next;
    }
}
void freefooditems(struct fooditem* head){
    struct fooditem* current = head;
    struct fooditem* next;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}
void sortfooditemsbyname(struct fooditem* head ,int size){
    if(head == NULL || head->next == NULL){
        return;
    }
    struct fooditem* i;
    struct fooditem* j;
    char* tempName;
    int tempId;
    float tempPrice;
    for(i = head; i != NULL; i = i->next){
        for(j = i->next; j != NULL; j = j->next){
            if(strcmp(i->name, j->name) > 0){
                // Swap names
                tempName = i->name;
                i->name = j->name;
                j->name = tempName;
                // Swap IDs
                tempId = i->id;
                i->id = j->id;
                j->id = tempId;
                // Swap prices
                tempPrice = i->price;
                i->price = j->price;
                j->price = tempPrice;
            }
        }
    }
}
void sortfooditemsbyprice(struct fooditem* head ,int size){
    if(head == NULL || head->next == NULL){
        return;
    }
    struct fooditem* i;
    struct fooditem* j;
    char* tempName;
    int tempId;
    float tempPrice;
    for(i = head; i != NULL; i = i->next){
        for(j = i->next; j != NULL; j = j->next){
            if(i->price > j->price){
                // Swap names
                tempName = i->name;
                i->name = j->name;
                j->name = tempName;
                // Swap IDs
                tempId = i->id;
                i->id = j->id;
                j->id = tempId;
                // Swap prices
                tempPrice = i->price;
                i->price = j->price;
                j->price = tempPrice;
            }
        }
    }
}
// Save food items to file
void saveFoodItemsToFile(struct fooditem *head, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if(!fp) {
        printf("Failed to open file: %s\n", filename);
        return;
    }
    struct fooditem *current = head;
    while(current) {
        fprintf(fp, "%d %s %.2f\n", current->id, current->name, current->price);
        current = current->next;
    }
    fclose(fp);
}

// Load food items from file
struct fooditem* loadFoodItemsFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp) return NULL;

    struct fooditem *head = NULL;
    int id;
    float price;
    char* name;
    name = (char*)malloc(100 * sizeof(char));

    while(fscanf(fp, "%d %99s %f", &id, name, &price) == 3) {
        addfooditem(&head, strdup(name), id, price);
    }
    fclose(fp);
    return head;
}

// Count food items
int countFoodItems(struct fooditem *head) {
    int count = 0;
    struct fooditem *current = head;
    while(current) {
        count++;
        current = current->next;
    }
    return count;
}

// Function definitions for cart item operations





struct fooditem* findFoodById(struct fooditem *menu, int id) {
    while (menu != NULL) {
        if (menu->id == id)
            return menu;
        menu = menu->next;
    }
    return NULL;
}


void addItemToCart(struct cartItem **cart, struct fooditem *item, int quantity) {

    if (item == NULL) {
        printf("Food item not found!\n");
        return;
    }

    struct cartItem *newItem = malloc(sizeof(struct cartItem));
    if (newItem == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    newItem->id = item->id;
    newItem->price = item->price;
    newItem->quantity = quantity;


    newItem->name = malloc(strlen(item->name) + 1);
    if (newItem->name == NULL) {
        free(newItem);
        return;
    }
    strcpy(newItem->name, item->name);

    newItem->next = *cart;
    *cart = newItem;
}

void removeItemFromCart(struct cartItem** cart, int id) {
    struct cartItem* current = *cart;
    struct cartItem* previous = NULL;
    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Cart item with ID %d not found.\n", id);
        return;
    }
    if (previous == NULL) {
        *cart = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
}

void updateCartItemQuantity(struct cartItem* cart, int id, int newQuantity) {
    struct cartItem* current = cart;
    while (current != NULL && current->id != id) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Cart item with ID %d not found.\n", id);
        return;
    }
    current->quantity = newQuantity;
}

void displayCart(struct cartItem* cart) {
    struct cartItem* current = cart;
    if (current == NULL) {
        printf("Cart is empty.\n");
        return;
    }
    printf("Cart Items:\n");
    while (current != NULL) {
        printf("ID: %d, Name: %s, Price: %.2f, Quantity: %d\n",
               current->id, current->name, current->price, current->quantity);
        current = current->next;
    }
}

float calculateTotal(struct cartItem* cart) {
    struct cartItem* current = cart;
    float total = 0.0f;
    while (current != NULL) {
        total += current->price * current->quantity;
        current = current->next;
    }
    return total;
}



void freeCart(struct cartItem* cart) {
    struct cartItem* current = cart;
    struct cartItem* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// Function definitions for menu operations

void displayMenu(struct menu* menu) {
    if (menu == NULL) {
        printf("Menu is empty.\n");
        return;
    }

    printf("Food Items in Menu:\n");
    displayfooditems(menu->items);
}


void freeMenu(struct menu* menu) {
    if (menu != NULL) {
        freefooditems(menu->items);
        free(menu);
    }
}

void updateMenu(struct menu* menu, struct fooditem* newItems, int newSize) {
    if (menu == NULL) {
        printf("Menu is not initialized.\n");
        return;
    }
    freefooditems(menu->items);
    menu->items = newItems;
    menu->size = newSize;
}

// Function definitions for order operations

void OrderFood(struct cartItem* cart, struct order** orders, int* nextOrderId) {
    if (cart == NULL) {
        printf("Cart is empty. Cannot place order.\n");
        return;
    }
    float totalAmount = calculateTotal(cart);
    addorder(orders, (*nextOrderId)++, cart, totalAmount);
    printf("Order placed successfully with Order ID: %d, Total Amount: %.2f\n", (*nextOrderId) - 1, totalAmount);
}

void addorder(struct order** head, int orderId, struct cartItem* items, float totalAmount) {
    struct order* newOrder = (struct order*)malloc(sizeof(struct order));
    newOrder->orderId = orderId;
    newOrder->items = items;
    newOrder->totalAmount = totalAmount;
    newOrder->next = *head;
    *head = newOrder;
}
void cencleOrder(struct order** head, int orderId,float*totalAmount){
    struct order* current = *head;
    struct order* previous = NULL;
    while (current != NULL && current->orderId != orderId) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Order with ID %d not found.\n", orderId);
        return;
    }
    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }
    *totalAmount=current->totalAmount;
    freeCart(current->items);
    free(current);
    printf("Order with ID %d has been canceled.\n", orderId);
}

void Updateorder(struct order* head, int orderId, struct cartItem* items, float totalAmount) {
    struct order* current = head;
    while (current != NULL && current->orderId != orderId) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Order with ID %d not found.\n", orderId);
        return;
    }
    current->items = items;
    current->totalAmount = totalAmount;
}

void displayOrders(struct order* head) {
    struct order* current = head;
    if (current == NULL) {
        printf("No orders available.\n");
        return;
    }
    printf("Orders:\n");
    while (current != NULL) {
        printf("Order ID: %d, Total Amount: %.2f\n", current->orderId, current->totalAmount);
        printf("Items in Order:\n");
        displayCart(current->items);
        current = current->next;
    }
}

void placeOrder(struct cartItem* cart, struct order** orders, int* nextOrderId) {
    if (cart == NULL) {
        printf("Cart is empty. Cannot place order.\n");
        return;
    }
    float totalAmount = calculateTotal(cart);
    addorder(orders, (*nextOrderId)++, cart, totalAmount);
    printf("Order placed successfully with Order ID: %d, Total Amount: %.2f\n", (*nextOrderId) - 1, totalAmount);
}


void freeOrders(struct order* head) {
    struct order* current = head;
    struct order* next;
    while (current != NULL) {
        next = current->next;
        if (current->items != NULL) {
            freeCart(current->items);
        }
        free(current);
        current = next;
    }
}


// Function definitions for employee operations

void displayEmployees(struct employee* head) {
    struct employee* current = head;
    if (current == NULL) {
        printf("No employees available.\n");
        return;
    }
    printf("Employees:\n");
    while (current != NULL) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", current->id, current->name, current->salary);
        current = current->next;
    }
}

void addEmployee(struct employee** head, char* name, int id, float salary) {
    struct employee* newEmployee = (struct employee*)malloc(sizeof(struct employee));
    newEmployee->name = name;
    newEmployee->id = id;
    newEmployee->salary = salary;
    newEmployee->next = *head;
    *head = newEmployee;
}

void updateEmployee(struct employee* head, int id, char* name) {
    struct employee* current = head;
    while (current != NULL && current->id != id) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Employee with ID %d not found.\n", id);
        return;
    }
    current->name = name;
}

void removeEmployee(struct employee** head, int id) {
    struct employee* current = *head;
    struct employee* previous = NULL;
    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Employee with ID %d not found.\n", id);
        return;
    }
    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
}


void freeEmployees(struct employee* head) {
    struct employee* current = head;
    struct employee* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

struct employee* loadEmployeesFromFile(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        return NULL;
    }

    struct employee* head = NULL;
    int id;
    char name[100];  // Use array instead of pointer
    float salary;

    while (fscanf(fp, "%d %99s %f", &id, name, &salary) == 3) {
        struct employee* newEmp = (struct employee*)malloc(sizeof(struct employee));
        if (!newEmp) {
            fclose(fp);
            return head;  // Return whatever we loaded so far
        }

        // Allocate memory for name
        newEmp->name = malloc(strlen(name) + 1);
        if (!newEmp->name) {
            free(newEmp);
            fclose(fp);
            return head;
        }

        // Copy data
        strcpy(newEmp->name, name);
        newEmp->id = id;
        newEmp->salary = salary;
        newEmp->next = head;
        head = newEmp;
    }

    fclose(fp);
    return head;
}
void saveEmployeesToFile(struct employee* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening %s for writing.\n", filename);
        return;
    }

    struct employee* current = head;
    while (current != NULL) {
        fprintf(fp, "%d %s %.2f\n",
                current->id,
                current->name,
                current->salary);
        current = current->next;
    }

    fclose(fp);
}

// Function definitions for table operations
void displayTables(struct Table* head) {
    struct Table* current = head;
    if (current == NULL) {
        printf("No tables available.\n");
        return;
    }
    printf("Tables:\n");
    while (current != NULL) {
        printf("Table Number: %d, Occupied: %s\n", current->tableNumber,
               current->isOccupied ? "Yes" : "No");
        current = current->next;
    }
}
void addTable(struct Table** head, int tableNumber) {
    struct Table* newTable = (struct Table*)malloc(sizeof(struct Table));
    newTable->tableNumber = tableNumber;
    newTable->isOccupied = 0; // Initially available
    newTable->next = *head;
    *head = newTable;
}
void removeTable(struct Table** head, int tableNumber) {
    struct Table* current = *head;
    struct Table* previous = NULL;
    while (current != NULL && current->tableNumber != tableNumber) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Table with Number %d not found.\n", tableNumber);
        return;
    }
    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
}

void reserveTable(struct Table* head, int tableNumber) {
    struct Table* current = head;
    while (current != NULL && current->tableNumber != tableNumber) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Table with Number %d not found.\n", tableNumber);
        return;
    }
    current->isOccupied = 1;
    printf("Table %d reserved.\n", tableNumber);
}

void freeTables(struct Table* head) {
    struct Table* current = head;
    struct Table* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void saveTablesToFile(struct Table* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) return;
    struct Table* current = head;
    while (current) {
        fprintf(fp, "%d %d\n", current->tableNumber, current->isOccupied);
        current = current->next;
    }
    fclose(fp);
}


struct Table* loadTablesFromFile(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return NULL;

    struct Table* head = NULL;
    int tableNumber, isOccupied;

    while (fscanf(fp, "%d %d", &tableNumber, &isOccupied) == 2) {
        struct Table* newTable = (struct Table*)malloc(sizeof(struct Table));
        newTable->tableNumber = tableNumber;
        newTable->isOccupied = isOccupied;
        newTable->next = head;
        head = newTable;
    }

    fclose(fp);
    return head;
}

// Count tables
int countTables(struct Table* head) {
    int count = 0;
    struct Table* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

// Function definitions for payment operations

void processPayment(struct payment** payments, int orderId, float amount, char* paymentMethod) {
    struct payment* newPayment = (struct payment*)malloc(sizeof(struct payment));
    newPayment->orderId = orderId;
    newPayment->amount = amount;
    newPayment->paymentMethod = paymentMethod;
    newPayment->next = *payments;
    *payments = newPayment;
    printf("Payment processed for Order ID: %d, Amount: %.2f, Method: %s\n",
           orderId, amount, paymentMethod);
}

void perintPaymentReceipt(int orderId, float amount, char* paymentMethod) {
    printf("Payment Receipt:\n");
    printf("Order ID: %d\n", orderId);
    printf("Amount Paid: %.2f\n", amount);
    printf("Payment Method: %s\n", paymentMethod);
    printf("Thank you for your payment!\n");
}

void displayPayments(struct payment* head) {
    struct payment* current = head;
    if (current == NULL) {
        printf("No payments available.\n");
        return;
    }
    printf("Payments:\n");
    while (current != NULL) {
        printf("Order ID: %d, Amount: %.2f, Method: %s\n",
               current->orderId, current->amount, current->paymentMethod);
        current = current->next;
    }
}

void freePayments(struct payment* head) {
    struct payment* current = head;
    struct payment* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}






// Function definitions for waiting time operations
struct watingtime* waitingTimeHead = NULL;
void displayWaitingTimes(struct watingtime* head) {
    struct watingtime* current = head;
    if (current == NULL) {
        printf("No waiting times available.\n");
        return;
    }
    printf("Waiting Times:\n");
    while (current != NULL) {
        printf("Table Number: %d, Waiting Time: %d minutes\n",
               current->tableNumber, current->waitingTime);
        current = current->next;
    }
}

void addWaitingTime(struct watingtime** head, int tableNumber,
    int waitingTime) {
    struct watingtime* newWaitingTime = (struct watingtime*)malloc(sizeof(struct watingtime));
    newWaitingTime->tableNumber = tableNumber;
    newWaitingTime->waitingTime = waitingTime;
    newWaitingTime->next = *head;
    *head = newWaitingTime;
}
void removeWaitingTime(struct watingtime** head, int tableNumber) {
    struct watingtime* current = *head;
    struct watingtime* previous = NULL;
    while (current != NULL && current->tableNumber != tableNumber) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Waiting time for Table Number %d not found.\n", tableNumber);
        return;
    }
    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
}
void freeWaitingTimes(struct watingtime* head) {
    struct watingtime* current = head;
    struct watingtime* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void saveWaitingTimesToFile(struct watingtime* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }
    struct watingtime* current = head;
    while (current != NULL) {
        fprintf(fp, "%d %d\n", current->tableNumber, current->waitingTime);
        current = current->next;
    }
    fclose(fp);
}
struct watingtime* loadWaitingTimesFromFile(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return NULL;
    struct watingtime* head = NULL;
    int tableNumber;
    int waitingTime;
    while (fscanf(fp, "%d %d", &tableNumber, &waitingTime) != EOF) {
        struct watingtime* newWaitingTime = (struct watingtime*)malloc(sizeof(struct watingtime));
        newWaitingTime->tableNumber = tableNumber;
        newWaitingTime->waitingTime = waitingTime;
        newWaitingTime->next = head;
        head = newWaitingTime;
    }
    fclose(fp);
    return head;
}

int countWaitingTimes(struct watingtime* head) {
    int count = 0;
    struct watingtime* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;

}

// Function definitions for discount operations

void addDiscount(struct Discount** head, int id, float percentage) {
    struct Discount* newDiscount = (struct Discount*)malloc(sizeof(struct Discount));

    newDiscount->id = id;
    newDiscount->percentage = percentage;
    newDiscount->next = *head;
    *head = newDiscount;
}

void removeDiscount(struct Discount** head, int id) {
    struct Discount* current = *head;
    struct Discount* previous = NULL;
    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Discount with ID %d not found.\n", id);
        return;
    }
    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
}

void freeDiscounts(struct Discount* head) {
    struct Discount* current = head;
    struct Discount* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void displayDiscounts(struct Discount* head) {
    struct Discount* current = head;
    if (current == NULL) {
        printf("No discounts available.\n");
        return;
    }
    printf("Discounts:\n");
    while (current != NULL) {
        printf("ID: %d, Percentage: %.2f%%\n", current->id, current->percentage);
        current = current->next;
    }
}

void updateDiscount(struct Discount* head, int id, float newPercentage) {
    struct Discount* current = head;
    while (current != NULL && current->id != id) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Discount with ID %d not found.\n", id);
        return;
    }
    current->percentage = newPercentage;
}


//food review function definitions

void addFoodReview(struct foodReview** head, int rating, char* comment) {
    struct foodReview* newReview = (struct foodReview*)malloc(sizeof(struct foodReview));
    newReview->rating = rating;
    newReview->comment = comment;
    newReview->next = *head;
    *head = newReview;
}

void displayFoodReviews(struct foodReview* head) {
    struct foodReview* current = head;
    if (current == NULL) {
        printf("No food reviews available.\n");
        return;
    }
    printf("Food Reviews:\n");
    while (current != NULL) {
        printf("Rating: %d, Comment: %s\n", current->rating, current->comment);
        current = current->next;
    }
}

void freeFoodReviews(struct foodReview* head) {
    struct foodReview* current = head;
    struct foodReview* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
void saveFoodReviewsToFile(struct foodReview* head, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file %s for writing.\n", filename);
        return;
    }
    struct foodReview* current = head;
    while (current != NULL) {
        fprintf(fp, "%d %s\n", current->rating, current->comment);
        current = current->next;
    }
    fclose(fp);
}

    struct foodReview* loadFoodReviewsFromFile(const char* filename) {
    FILE*
        fp = fopen(filename, "r");
    if (!fp) return NULL;
    struct foodReview* head = NULL;
    int rating;
    char comment[256];
    while (fscanf(fp, "%d %255s", &rating, comment) !=
              EOF) {
          struct foodReview* newReview = (struct foodReview*)malloc(sizeof(struct foodReview));
          newReview->rating = rating;
          newReview->comment = strdup(comment);
          newReview->next = head;
          head = newReview;
     }
    fclose
(fp);
    return head;
}
    int countFoodReviews(struct foodReview* head) {
    int count = 0;
    struct foodReview* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// admin function definitions
int AdminLogin(const char* username, const char* password) {

    const char* adminUsername = "admin";
    const char* adminPassword = "pas123";

    if (strcmp(username, adminUsername) == 0 && strcmp(password, adminPassword) == 0) {
        return 1; // Login successful
    } else {
        return 0; // Login failed
    }
}
int AddAdmin(const char* username, const char* password) {

    printf("New admin added:\nUsername: %s\nPassword: %s\n", username, password);
    return 1; // Indicate success
}

void Adminmenu(struct employee** employeeHead, struct foodReview** reviewHead) {
    int choice;

    do {
        printf("\nAdmin Menu:\n");
        printf("1. Add Employee\n");
        printf("2. Delete Employee\n");
        printf("3. View Employees\n");
        printf("4. View Food Reviews\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            choice = 0;
            while (getchar() != '\n');
        }

        switch (choice) {
            case 1: {
                char *name = malloc(50 * sizeof(char));
                int id;
                float salary;

                printf("Enter employee name: ");
                scanf("%s", name);

                printf("Enter employee ID: ");
                scanf("%d", &id);

                printf("Enter employee salary: ");
                scanf("%f", &salary);

                char* name_ptr = strdup(name);

                if (name_ptr) {
                    addEmployee(employeeHead, name_ptr, id, salary);
                    saveEmployeesToFile(*employeeHead, "employees.txt");
                    printf("Employee added and saved successfully!\n");
                } else {
                    printf("Memory allocation failed.\n");
                }

                free(name);
                break;
            }

            case 2: {
                int id;
                printf("Enter employee ID to remove: ");
                scanf("%d", &id);
                removeEmployee(employeeHead, id);
                saveEmployeesToFile(*employeeHead, "employees.txt");
                break;
            }

            case 3:
                displayEmployees(*employeeHead);
                break;
            case 4:
                displayFoodReviews(*reviewHead);
                break;
            case 5:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

}

// coustomer function definitions

   int coustomerLogin(const char* username, const char* password) {

    const char* customerUsername = "customer";
    const char* customerPassword = "cust123";
    if (strcmp(username, customerUsername) == 0 && strcmp(password, customerPassword) == 0) {
        return 1; // Login successful
    } else {
        return 0; // Login failed
    }
}


void customerMenu(struct menu* menu, struct Table** tableHead, struct Discount** discountHead, struct cartItem** cart, struct order** orderHead, struct foodReview** reviewHead) { // Corrected parameter types and names to match header
    int choice;
    do {
        printf("\nCustomer Menu:\n");
        printf("1. View Menu\n");
        printf("2.sortitems by name\n");
        printf("3.sortitems by price\n");
        printf("4. Add Item to Cart\n");
        printf("5. Remove Item from Cart\n");
        printf("6. View Cart\n");
        printf("7. Place Order\n");
        printf("8. View Payment Receipt\n");
        printf("9. See Reviews\n");
        printf("10. Write a Review\n");
        printf("11. View Available Discounts\n");
        printf("12. View Waiting Time\n");
        printf("13. View Available Tables\n");
        printf("14. Logout\n");
        printf("15. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            choice = 0; // Set to invalid choice on failure
            while (getchar() != '\n'); // Clear input buffer
        }

        switch (choice) {
            case 1:
                displayMenu(menu);
                break;
            case 2:
                sortfooditemsbyname(menu->items, menu->size);
                printf("Food items sorted by name.\n");
                break;
            case 3:
                sortfooditemsbyprice(menu->items, menu->size);
                printf("Food items sorted by price.\n");
                break;
            case 4:


            int itemId, quantity;
            printf("Enter Food Item ID: ");
            scanf("%d", &itemId);
            printf("Enter Quantity: ");
            scanf("%d", &quantity);
            struct fooditem* item = findFoodById(menu->items, itemId);
            addItemToCart(cart, item, quantity);

                break;
            case 5:

               int removeId;
                printf("Enter Food Item ID: ");
                scanf("%d", &removeId);
                removeItemFromCart(cart, removeId);
                printf("Item with ID %d removed from cart.\n", removeId);
                printf("Item removed from cart.\n");
                break;
            case 6:
                displayCart(*cart);
                break;
            case 7:
                {
                    int nextOrderId = 1;
                    placeOrder(*cart, orderHead, &nextOrderId);
                }
                break;
            case 8:



                int orderId;
                char* paymentMethod;
                printf("Enter Order ID for receipt: ");
                scanf("%d", &orderId);
                printf("Enter Payment Method (e.g., Credit Card, Cash): ");
                scanf("%s", paymentMethod);

                float totalAmount = calculateTotal(*cart);  //total amount from cart

                perintPaymentReceipt(orderId, totalAmount, paymentMethod);

                break;

            case 9:
                displayFoodReviews(*reviewHead);
                break;
            case 10:{

    struct foodReview *reviewHead = NULL; // pointer-only

    // load existing reviews
    reviewHead = loadFoodReviewsFromFile("reviews.txt");

    // user input
    int rating;
    char commentBuffer[256];
    printf("Enter rating (1-5): ");
    scanf("%d", &rating);

    printf("Enter comment: ");
    scanf(" %[^\n]", commentBuffer);

    // add review
    addFoodReview(&reviewHead, rating, strdup(commentBuffer));

    // auto-save
    saveFoodReviewsToFile(reviewHead, "reviews.txt");

    // display reviews
    displayFoodReviews(reviewHead);

    // free memory
    freeFoodReviews(reviewHead);
            }
    break;
            case 11:
                displayDiscounts(*discountHead);
                break;
            case 12:

                  printf("\n--- View Waiting Time ---\n");
                displayWaitingTimes(waitingTimeHead);

                break;
            case 13:
                displayTables(*tableHead);
                break;
            case 14:
                printf("Logging out...\n");
                break;
            case 15:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 12);
}

// manager function definitions
   int managerLogin(const char* username, const char* password) {

    const char* managerUsername = "manager";
    const char* managerPassword = "mgr123";
    if (strcmp(username, managerUsername) == 0 && strcmp(password, managerPassword) == 0) {
        return 1; // Login successful
    } else {
        return 0; // Login failed
    }
}


void managermenu(struct fooditem** foodHead,struct menu* menu,struct Table** tableHead,struct order** orderHead, struct Discount** discountHead, struct watingtime** waitingTimeHead) {
    int choice;
    do {
        printf("\nManager Menu:\n");
        printf("1. Manage Food Items (Add, Remove, Update, Display)\n");
        printf("2. Manage Menu (Update, Display)\n");
        printf("3. Manage Tables (Add, Remove, Display, Reserve)\n");
        printf("4. View/Cancel Orders\n");
        printf("5. Manage Discounts\n");
        printf("6. Manage Waiting Times\n");
        printf("7. Logout\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            choice = 0;
            while (getchar() != '\n');
        }

        switch (choice) {
            case 1: {

                int foodChoice;
                do {
                    printf("\n=== Manage Food Items ===\n");
                    printf("1. Add Food Item\n");
                    printf("2. Remove Food Item\n");
                    printf("3. Update Food Item\n");
                    printf("4. Display Food Items\n");
                    printf("5. Back to Manager Menu\n");
                    printf("Enter choice: ");

                    if(scanf("%d", &foodChoice) != 1) {
                        foodChoice = 0;
                        while(getchar() != '\n');
                    }

                    switch(foodChoice) {
                        case 1:
                        {
    char *name;
    int id;
    float price;

    // Allocate memory for input
    name = (char*)malloc(50 * sizeof(char));
    if(name == NULL) {
        printf("Memory allocation failed!\n");
        break;
    }

    // User input
    printf("Enter Food ID: ");
    scanf("%d", &id);

    printf("Enter Food Name: ");
    scanf(" %[^\n]", name); // allows spaces

    printf("Enter Food Price: ");
    scanf("%f", &price);

    // Add to linked list (pointer to head, deep copy of name)
    addfooditem(foodHead, strdup(name), id, price);

    printf("Food item added successfully!\n");

    // Free temporary input buffer
    free(name);

    // Optional: save immediately to file
    saveFoodItemsToFile(*foodHead, "fooditems.txt");
    printf("Food items saved to file.\n");

    // Display updated list
    displayfooditems(*foodHead);
}

                   break;


                        case 2:  {
                            int id;
                            printf("Enter Food ID to remove: ");
                            scanf("%d", &id);

                            removefooditem(&fooditemHead, id);
                            break;
                        }

                        case 3:  {
                                int id;
                                float price;
                                char *name;

                                name = malloc(50 * sizeof(char));

                                printf("Enter Food ID to update: ");
                                scanf("%d", &id);

                                printf("Enter New Food Name: ");
                                scanf(" %[^\n]", name);

                                printf("Enter New Food Price: ");
                                scanf("%f", &price);

                                updatefooditem(fooditemHead, id, name, price);
                                printf("Food item updated successfully!\n");
                                break;
                            }

                        case 4:
                             printf("\n--- Food Menu ---\n");
                            displayfooditems(fooditemHead);
                            break;
                        case 5:
                            printf("Returning to Manager Menu...\n");
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                    }
                } while(foodChoice != 5);
                break;
            }

            case 2: {

                // Menu Management
                int menuChoice;
                do {
                    printf("\n=== Manage Menu ===\n");
                    printf("1. Update Menu\n");
                    printf("2. Display Menu\n");
                    printf("3. Back to Manager Menu\n");
                    printf("Enter choice: ");

                    if(scanf("%d", &menuChoice) != 1) {
                        menuChoice = 0;
                        while(getchar() != '\n');
                    }

                    switch(menuChoice) {
                        case 1:
                            printf("Update Menu - Replace all items\n");
                            printf("Current menu will be cleared. Continue? (y/n): ");
                            char confirm;
                            scanf(" %c", &confirm);
                            if(confirm == 'y' || confirm == 'Y') {

                                freefooditems(menu->items);
                                menu->items = NULL;
                                menu->size = 0;


                                menu->items = *foodHead;
                                struct fooditem* temp = *foodHead;
                                int count = 0;
                                while(temp != NULL) {
                                    count++;
                                    temp = temp->next;
                                }
                                menu->size = count;
                                printf("Menu updated with %d items\n", count);
                            }
                            break;
                        case 2:
                            displayMenu(menu);
                            break;
                        case 3:
                            printf("Returning to Manager Menu...\n");
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                } while(menuChoice != 3);
                break;
            }

            case 3: {
                // Table Management
                int tableChoice;
                do {
                    printf("\n=== Manage Tables ===\n");
                    printf("1. Add Table\n");
                    printf("2. Remove Table\n");
                    printf("3. Display Tables\n");
                    printf("4. Reserve Table\n");
                    printf("5. Back to Manager Menu\n");
                    printf("Enter choice: ");

                    if(scanf("%d", &tableChoice) != 1) {
                        tableChoice = 0;
                        while(getchar() != '\n');
                    }

                    switch(tableChoice) {
                        case 1:
                        struct Table *tableHead = NULL; // single pointer

// Load tables from file
tableHead = loadTablesFromFile("tables.txt");
if (!tableHead) {
    printf("No tables loaded from file.\n");
}

// Manager menu option: add table
int tableNumber;
printf("Enter table number to add: ");
scanf("%d", &tableNumber);

// Pointer-only add
addTable(&tableHead, tableNumber);

// Display tables
displayTables(tableHead);

// Auto-save tables
saveTablesToFile(tableHead, "tables.txt");

// At program exit: free memory
freeTables(tableHead);
                            break;


                        case 2: {
                            int tableNumber;
printf("Enter table number to remove: ");
scanf("%d", &tableNumber);

// pointer-only call
removeTable(&tableHead, tableNumber);

                        }
                            break;
                        case 3:
                            displayTables(tableHead);
                            break;
                        case 4: {
                            int tableNumber;
                            printf("Enter table number to reserve: ");
                            scanf("%d", &tableNumber);
                            reserveTable(tableHead, tableNumber);
                            break;
                        }
                        case 5:
                            printf("Returning to Manager Menu...\n");
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                } while(tableChoice != 5);
                break;
            }

            case 4: {
                // Order Management
                int orderChoice;
                do {
                    printf("\n=== Manage Orders ===\n");
                    printf("1. View All Orders\n");
                    printf("2. Cancel an Order\n");
                    printf("3. Back to Manager Menu\n");
                    printf("Enter choice: ");

                    if(scanf("%d", &orderChoice) != 1) {
                        orderChoice = 0;
                        while(getchar() != '\n');
                    }

                    switch(orderChoice) {
                        case 1:
                            displayOrders(*orderHead);
                            break;
                        case 2: {
                            int orderId;
                            float refundAmount = 0.0;

                            printf("Enter Order ID to cancel: ");
                            scanf("%d", &orderId);

                            struct order* current = *orderHead;
                            int found = 0;
                            while(current != NULL) {
                                if(current->orderId == orderId) {
                                    found = 1;
                                    break;
                                }
                                current = current->next;
                            }

                            if(found) {
                                cencleOrder(orderHead, orderId, &refundAmount);
                                printf("Order %d cancelled. Refund amount: %.2f\n", orderId, refundAmount);
                            } else {
                                printf("Order ID %d not found.\n", orderId);
                            }
                            break;
                        }
                        case 3:
                            printf("Returning to Manager Menu...\n");
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                } while(orderChoice != 3);
                break;
            }

            case 5: {
                // Discount Management
                int discountChoice;
                do {
                    printf("\n=== Manage Discounts ===\n");
                    printf("1. Add Discount\n");
                    printf("2. Remove Discount\n");
                    printf("3. Update Discount\n");
                    printf("4. Display Discounts\n");
                    printf("5. Back to Manager Menu\n");
                    printf("Enter choice: ");

                    if(scanf("%d", &discountChoice) != 1) {
                        discountChoice = 0;
                        while(getchar() != '\n');
                    }

                    switch(discountChoice) {
                        case 1: {
                            int id;
                            float percentage;

                            printf("Enter Discount ID: ");
                            scanf("%d", &id);
                            printf("Enter Discount Percentage: ");
                            scanf("%f", &percentage);

                            addDiscount(discountHead, id, percentage);
                            printf("Discount added successfully!\n");
                            break;
                        }
                        case 2: {
                            int id;
                            printf("Enter Discount ID to remove: ");
                            scanf("%d", &id);
                            removeDiscount(discountHead, id);
                            break;
                        }
                        case 3: {
                            int id;
                            float newPercentage;

                            printf("Enter Discount ID to update: ");
                            scanf("%d", &id);
                            printf("Enter new percentage: ");
                            scanf("%f", &newPercentage);

                            updateDiscount(*discountHead, id, newPercentage);
                            printf("Discount updated successfully!\n");
                            break;
                        }
                        case 4:
                            displayDiscounts(*discountHead);
                            break;
                        case 5:
                            printf("Returning to Manager Menu...\n");
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                } while(discountChoice != 5);
                break;
            }

            case 6: {
                // Waiting Time Management
                int waitingChoice;
                do {
                    printf("\n=== Manage Waiting Times ===\n");
                    printf("1. Add Waiting Time\n");
                    printf("2. Remove Waiting Time\n");
                    printf("3. Display Waiting Times\n");
                    printf("4. Back to Manager Menu\n");
                    printf("Enter choice: ");

                    if(scanf("%d", &waitingChoice) != 1) {
                        waitingChoice = 0;
                        while(getchar() != '\n');
                    }

                    switch(waitingChoice) {
                        case 1: {
                            int tableNumber, waitingTime;

                            printf("Enter Table Number: ");
                            scanf("%d", &tableNumber);
                            printf("Enter Waiting Time (minutes): ");
                            scanf("%d", &waitingTime);

                            addWaitingTime(waitingTimeHead, tableNumber, waitingTime);
                            printf("Waiting time added for table %d\n", tableNumber);
                            break;
                        }
                        case 2: {
                            int tableNumber;
                            printf("Enter Table Number to remove waiting time: ");
                            scanf("%d", &tableNumber);
                            removeWaitingTime(waitingTimeHead, tableNumber);
                            break;
                        }
                        case 3:
                            displayWaitingTimes(*waitingTimeHead);
                            break;
                        case 4:
                            printf("Returning to Manager Menu...\n");
                            break;
                        default:
                            printf("Invalid choice.\n");
                    }
                } while(waitingChoice != 4);
                break;
            }

            case 7:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
}

// function for facultay and staff login

   int facultyAndStaffLogin(const char* username, const char* password) {

    const char* facultyUsername = "faculty";
    const char* facultyPassword = "fac123";
    if (strcmp(username, facultyUsername) == 0 && strcmp(password, facultyPassword) == 0) {
        return 1; // Login successful
    } else {
        return 0; // Login failed
    }
}

void facultyAndStaffMenu(struct menu* menu, struct cartItem** cart, struct order** order, struct foodReview** review, struct Table** table, struct Discount** discount, struct watingtime** waitingTime) {
    int choice;
    do {
        printf("\nFaculty/Staff Menu:\n");
        printf("1. View Menu\n");
        printf("2. sortitems by name\n");
        printf("3. sortitems by price\n");
        printf("4. Add Item to Cart\n");
        printf("5. Remove Item from Cart\n");
        printf("6. View Cart\n");
        printf("7. Place Order\n");
        printf("8. View Payment Receipt\n"); // Corrected text
        printf("9. See Reviews\n");
        printf("10. Write a Review\n");
        printf("11 View Available Discounts\n");
        printf("12 View Waiting Time\n");
        printf("13. View Available Tables\n");
        printf("14. Logout\n");
        printf("15. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            choice = 0;
            while (getchar() != '\n');
        }
        switch (choice) {
            case 1:
                displayMenu(menu);
                break;

            case 2:
                sortfooditemsbyname(menu->items, menu->size);
                printf("Food items sorted by name.\n");
                break;

            case 3:
                sortfooditemsbyprice(menu->items, menu->size);
                printf("Food items sorted by price.\n");
                break;

            case 4:
                 int itemId, quantity;
            printf("Enter Food Item ID: ");
            scanf("%d", &itemId);
            printf("Enter Quantity: ");
            scanf("%d", &quantity);
            struct fooditem* item = findFoodById(menu->items, itemId);
            addItemToCart(cart, item, quantity);
                break;
            case 5:
                // Placeholder
               int removeId;
                printf("Enter Food Item ID: ");
                scanf("%d", &removeId);
                removeItemFromCart(cart, removeId);

                break;
            case 6:
                displayCart(*cart);
                break;
            case 7:
                {
                    int nextOrderId = 1; // Placeholder for next order ID
                    placeOrder(*cart, order, &nextOrderId);
                }
                break;
            case 8:
               int orderId;
                char* paymentMethod;
                printf("Enter Order ID for receipt: ");
                scanf("%d", &orderId);  // semicolon added
                printf("Enter Payment Method (e.g., Credit Card, Cash): ");
                scanf("%s", paymentMethod);

                float totalAmount = calculateTotal(*cart);  // pointer passed

                perintPaymentReceipt(orderId, totalAmount, paymentMethod);

                break;
            case 9:
                displayFoodReviews(*review);
                break;
            case 10:
                {
                    int rating;
                    char* comment;
                    printf("Enter your rating (1-5): ");
                    scanf("%d", &rating);
                    printf("Enter your comment (single word for now): ");
                    scanf("%s", comment);
                    char* comment_ptr = strdup(comment);
                    if (comment_ptr) {
                        addFoodReview(review, rating, comment_ptr);
                    } else {
                        printf("Memory allocation failed.\n");
                    }
                }
                break;
            case 11:
                displayDiscounts(*discount);
                break;
            case 12:
                displayWaitingTimes(*waitingTime);
                break;
            case 13:
                displayTables(*table);
                break;

            case 14:
                printf("Logging out...\n");
                break;
            case 15:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 12);


}

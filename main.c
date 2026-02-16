#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include<time.h>
#include "cafetaria.h"

int main() {
    struct employee* employeeHead = NULL;
    struct foodReview* reviewHead = NULL;
    struct fooditem* foodHead = NULL;
    struct menu cafeteriaMenu = {NULL, 0};
    struct Table* tableHead = NULL;
    struct order* orderHead = NULL;
    struct Discount* discountHead = NULL;
    struct watingtime* waitingTimeHead = NULL;
    struct cartItem* cartHead = NULL;

    //  FOOD ITEMS
    foodHead = loadFoodItemsFromFile("fooditems.txt");
    if (foodHead == NULL) {
        addfooditem(&foodHead, strdup("Burger"), 101, 500.00);
        addfooditem(&foodHead, strdup("Fries"), 102, 200.00);
        addfooditem(&foodHead, strdup("Coke"), 103, 150.00);
        saveFoodItemsToFile(foodHead, "fooditems.txt");
    }

    cafeteriaMenu.items = foodHead;
    cafeteriaMenu.size = countFoodItems(foodHead);

    tableHead = loadTablesFromFile("tables.txt");
    if (tableHead == NULL) {
        addTable(&tableHead, 1);
        addTable(&tableHead, 2);
    }

    employeeHead = loadEmployeesFromFile("employees.txt");

    reviewHead = loadFoodReviewsFromFile("reviews.txt");
    if (reviewHead == NULL) {
        addFoodReview(&reviewHead, 5, "Great food!");
    }

    addDiscount(&discountHead, 1, 10.0);

    printf("Welcome to the EWU Cafeteria\n");
    int choice;

    while (1) {
        printf("\nPlease login to continue:\n");
        printf("1. Admin\n");
        printf("2. Customer\n");
        printf("3. Manager\n");
        printf("4. Faculty/Staff\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");


        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            // Clear invalid input
            while (getchar() != '\n');
            continue;
        }

        // Clear the newline character after reading integer
        while (getchar() != '\n');

        switch(choice) {
            case 1: {
                char *username;
                char *password;
                username = (char*)malloc(50 * sizeof(char));
                password = (char*)malloc(50 * sizeof(char));

                printf("\nAdmin Login\n");

                printf("Username: ");
                scanf("%49s", username);
                printf("Password: ");
                scanf("%49s", password);

                if(AdminLogin(username, password)) {
                    printf("\nAdmin login successful!\n");
                    Adminmenu(&employeeHead, &reviewHead);
                } else {
                    printf("\nInvalid username or password. Please try again.\n");
                }
                // Clear input buffer
                while (getchar() != '\n');
                break;
            }

            case 2: {
                char *username;
                char *password;
                username = (char*)malloc(50 * sizeof(char));
                password = (char*)malloc(50 * sizeof(char));
                printf("\nCustomer Login\n");

                printf("Username: ");
                scanf("%49s", username);
                printf("Password: ");
                scanf("%49s", password);

                if(coustomerLogin(username, password)) {
                    printf("\nCustomer login successful!\n");
                    customerMenu(&cafeteriaMenu, &tableHead, &discountHead, &cartHead, &orderHead, &reviewHead);
                } else {
                    printf("\nInvalid username or password. Please try again.\n");
                }
                // Clear input buffer
                while (getchar() != '\n');
                break;
            }

            case 3: {
                char *username;
                char *password;
                username = (char*)malloc(50 * sizeof(char));
                password = (char*)malloc(50 * sizeof(char));

                printf("\nManager Login\n");

                printf("Username: ");
                scanf("%49s", username);
                printf("Password: ");
                scanf("%49s", password);

                if(managerLogin(username, password)) {
                    printf("\nManager login successful!\n");
                    managermenu(&foodHead, &cafeteriaMenu, &tableHead, &orderHead, &discountHead, &waitingTimeHead);
                } else {
                    printf("\nInvalid username or password. Please try again.\n");
                }
                // Clear input buffer
                while (getchar() != '\n');
                break;
            }

            case 4: {
                char *username;
                char *password;
                username = (char*)malloc(50 * sizeof(char));
                password = (char*)malloc(50 * sizeof(char));

                printf("\nFaculty/Staff Login\n");

                printf("Username: ");
                scanf("%49s", username);
                printf("Password: ");
                scanf("%49s", password);

                if(facultyAndStaffLogin(username, password)) {
                    printf("\nFaculty/Staff login successful!\n");
                    facultyAndStaffMenu(&cafeteriaMenu, &cartHead, &orderHead, &reviewHead, &tableHead, &discountHead, &waitingTimeHead);
                } else {
                    printf("\nInvalid username or password. Please try again.\n");
                }
                // Clear input buffer
                while (getchar() != '\n');
                break;
            }

            case 5:
                printf("\nExiting EWU Cafeteria System...\n");
                printf("Goodbye!\n");

                // Free allocated memory
                freeEmployees(employeeHead);
                freeFoodReviews(reviewHead);
                freeMenu(&cafeteriaMenu);
                freeTables(tableHead);
                freeOrders(orderHead);

                freeWaitingTimes(waitingTimeHead);
                freeCart(cartHead);
                return 0;

            default:
                printf("\nInvalid choice. Please select 1-5.\n");
                break;
        }
    }

    return 0;
}

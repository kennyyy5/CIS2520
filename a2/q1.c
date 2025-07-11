#include "q1.h"

/*
 * A basic menu based structure has been provided
 */

int main()
{

    // Our three Linked Lists
    struct car *available_head = NULL;
    struct car *rented_head = NULL;
    struct car *repair_head = NULL;

    int choice;

    int mileage, return_date;
    double charge;
    char plate[7];
    struct car *transfer;

    read_file_into_list("available.txt", &available_head);
    read_file_into_list("rented.txt", &rented_head);
    read_file_into_list("repair.txt", &repair_head);

    do
    {
        prompt();

        printf("Enter a Choice: ");
        scanf("%d", &choice);

        /*
         * You will need to add all the cases
         * Call the appropriate functions
         * You would also need to save data to disc upon exit
         * File Format: plate,mileage,return_date
         * Error Handling needs to happen too
         */

        switch (choice)
        {
        case 1:
            printf("Enter plate number: ");
            scanf("%s", plate);
            if (!is_valid_plate(plate) || is_plate_in_list(available_head, plate)) // do is_valid_plate
            {
                printf("Invalid or duplicate plate number.\n");
                break;
            }
            printf("Enter mileage: ");
            scanf("%d", &mileage);

            insert_to_list(&available_head, plate, mileage, -1);
            sort_list(&available_head, true, false); // Sort by mileage
            printf("Car added to available-for-rent list.\n");
            break;

        case 2:
            printf("Enter Plate Number: ");
            scanf("%s", plate);
            printf("Enter mileage: ");
            scanf("%d", &mileage);

            transfer = remove_car_from_list(&rented_head, plate);
            if (!transfer || mileage < transfer->mileage)
            {
                printf("Invalid car or mileage.\n");
                break;
            }

            charge = profit_calculator(transfer->mileage, mileage);
            printf("Car returned. The charge: $%.2f\n", charge);

            transfer->mileage = mileage;
            insert_to_list(&available_head, transfer->plate, transfer->mileage, -1);
            sort_list(&available_head, true, false); // Sort by mileage
            free(transfer);
            break;

        case 3:
            printf("Enter Plate Number: ");
            scanf("%s", plate);
            printf("Enter mileage: ");
            scanf("%d", &mileage);

            transfer = remove_car_from_list(&rented_head, plate);
            if (!transfer || mileage < transfer->mileage)
            {
                printf("Invalid car or mileage.\n");
                break;
            }

            charge = profit_calculator(transfer->mileage, mileage);
            printf("Car returned and sent to repair. Charge: $%.2f\n", charge);

            transfer->mileage = mileage;
            insert_to_list(&repair_head, transfer->plate, transfer->mileage, -1);
            sort_list(&repair_head, true, false); // Sort by mileage
            free(transfer);
            break;

        case 4:
            printf("Enter Plate Number: ");
            scanf("%s", plate);

            transfer = remove_car_from_list(&repair_head, plate);
            if (!transfer)
            {
                printf("Car not found in repair list.\n");
                break;
            }

            insert_to_list(&available_head, transfer->plate, transfer->mileage, -1);
            sort_list(&available_head, true, false); // Sort by mileage
            printf("Car transferred from repair to available-for-rent list.\n");
            free(transfer);

            break;

        case 5:
            if (available_head == NULL)
            {
                printf("No cars available for rent.\n");
                break;
            }

            printf("Enter return date (YYMMDD): ");
            scanf("%d", &return_date);
            if (!is_valid_date(return_date)) // do is_valid_date
            {
                printf("Invalid return date.\n");
                break;
            }

            transfer = remove_first_from_list(&available_head);
            transfer->return_date = return_date;
            insert_to_list(&rented_head, transfer->plate, transfer->mileage, transfer->return_date);
            sort_list(&rented_head, false, true); // Sort by return date
            printf("Car rented. Plate: %s, Return Date: %d\n", transfer->plate, return_date);
            free(transfer);
            break;

        case 6:
            printf("\nAvailable-for-rent cars:\n");
            print_list(available_head);
            printf("\nRented cars:\n");
            print_list(rented_head);
            printf("\nCars in repair:\n");
            print_list(repair_head);
            break;

        case 7:
            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);
            printf("Data saved. Exiting...\n");
            free_list(&available_head);
            free_list(&rented_head);
            free_list(&repair_head);
            return 0;

        default:
            printf("Pls pick a valid choice.");
            break;
        }
    } while (true);

    return 0;
}
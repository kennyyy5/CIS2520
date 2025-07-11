#include "q1.h"

/* function will display the primary user interface
    This is already done for you*/
void prompt()
{

    printf("1. Add a new car to the available-for-rent list,\n");
    printf("2. Add a returned car to the available-for-rent list,\n");
    printf("3. Add a returned car to the repair list,\n");
    printf("4. Transfer a car from the repair list to the available-for-rent list,\n");
    printf("5. Rent the first available car,\n");
    printf("6. Print all the lists,\n");
    printf("7. Quit.\n");
    printf("Enter your choice: ");
}

/**
 * Inserts a new car into the linked list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @param mileage Integer representing the car's mileage.
 * @param return_date Integer representing the car's return date, you can have -1 represent no return date.
 * @return Pointer to the newly added car in the list.
 */
void insert_to_list(struct car **head, const char *plate, int mileage, int return_date)
{
    struct car *new = malloc(sizeof(struct car));
    if (new == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(new->plate, plate);
    new->mileage = mileage;
    new->return_date = return_date;
    new->next = *head; // Insert at the beginning of the list
    *head = new;
}

/**
 * Prints all the cars in the list.
 * @param head Pointer to the head of the list.
 * This function prints out the car details, it should not print return date if it does not exist.
 */
void print_list(struct car *head)
{
    struct car *curr = head;
    while (curr != NULL)
    {
        printf("Plate Number: %s, Mileage: %d", curr->plate, curr->mileage);
        if (curr->return_date != -1)
        {
            printf(", Return Date: %d\n", curr->return_date);
        }
        else
        {
            printf("\n");
        }
        curr = curr->next;
    }
}

/**
 * Checks if a car's plate is already in the list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Boolean value indicating if the plate is found.
 */
bool is_plate_in_list(struct car *head, char plate[])
{
    struct car *curr = head;
    while (curr != NULL)
    {
        if (strcmp(curr->plate, plate) == 0)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

/**
 * Swaps two cars in the list.
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * Swaps the plate, mileage, and return date of two cars.
 */
void swap(struct car *a, struct car *b)
{
    char temp_plate[7];
    int temp_mileage;
    int temp_return_date;

    strcpy(temp_plate, a->plate);
    strcpy(a->plate, b->plate);
    strcpy(b->plate, temp_plate);

    temp_mileage = a->mileage;
    a->mileage = b->mileage;
    b->mileage = temp_mileage;

    temp_return_date = a->return_date;
    a->return_date = b->return_date;
    b->return_date = temp_return_date;
    return;
}

/**
 * Sorts the list of cars based on mileage or return date.
 * @param head Pointer to the head of the list.
 * @param sort_by_mileage Boolean to sort by mileage.
 * @param sort_by_return_date Boolean to sort by return date.
 */
void sort_list(struct car **head, bool sort_by_mileage, bool sort_by_return_date)
{
    if (*head == NULL)
    {
        return;
    }
    bool swapped;
    struct car *curr;
    struct car *ptr = NULL;

    // optimised Bubble sort for linked list
    do
    {
        swapped = false;
        curr = *head;

        while (curr->next != ptr)
        {
            if ((sort_by_mileage && curr->mileage > curr->next->mileage) ||
                (sort_by_return_date && curr->return_date > curr->next->return_date))
            {
                swap(curr, curr->next);
                swapped = true;
            }
            curr = curr->next;
        }
        ptr = curr;
    } while (swapped);
}

/**
 * Removes a car from the list by its plate number.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Pointer to the removed car.
 */
struct car *remove_car_from_list(struct car **head, char plate[])
{
    struct car *curr = *head;
    struct car *prev = NULL;

    while (curr != NULL && strcmp(curr->plate, plate) != 0)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        printf("Car %s not found.\n", plate);
        return NULL;
    }
    if (prev == NULL)
    {
        *head = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }

    return curr;
}

/**
 * Removes the first car from the list.
 * @param head Pointer to the head of the list.
 * @return Pointer to the removed car.
 */
struct car *remove_first_from_list(struct car **head)
{
    if (*head == NULL)
    {
        printf("List is empty\n");
        return NULL;
    }
    struct car *car_to_remove = *head;
    *head = (*head)->next;
    car_to_remove->next = NULL;
    return car_to_remove;
}

/**
 * Calculates the profit based on the mileage difference.
 * @param initial_mileage Integer representing the car's starting mileage.
 * @param final_mileage Integer representing the car's final mileage.
 * @return Double value representing the calculated profit.
 */
double profit_calculator(int initial_mileage, int final_mileage)
{
    int distance = final_mileage - initial_mileage;
    double profit;
    if (distance <= 200)
    {
        profit = 80.00;
    }
    else
    {
        profit = 80.00 + (0.15 * (distance - 200));
    }

    return profit;
}

/**
 * Writes the list of cars to a file.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Writes the details of each car in the list to a file.
 */
void write_list_to_file(char *filename, struct car *head)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file!");
        return;
    }
    struct car *temp = head;
    while (temp != NULL)
    {
        fprintf(file, "%s %d %d\n", temp->plate, temp->mileage, temp->return_date);
        temp = temp->next;
    }
    fclose(file);

    return;
}

/**
 * Reads car details from a file and adds them to the list.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Reads data from the file and inserts each car into the list.
 */
void read_file_into_list(char *filename, struct car **head)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char plate[7]; // Buffer for plate (6 characters + null terminator)
    int mileage, return_date;

    // Loop until end of file
    while (fscanf(file, "%7[^,],%d,%d\n", plate, &mileage, &return_date) == 3) // Read with format
    {

        struct car *new = malloc(sizeof(struct car));
        if (new == NULL)
        {
            printf("Memory Allocation Error!\n");
            fclose(file);
            return;
        }

        // Copy the plate and assign values
        strcpy(new->plate, plate);

        new->mileage = mileage;
        new->return_date = return_date;
        new->next = NULL;

        // Insert into the linked list
        insert_to_list(head, new->plate, new->mileage, new->return_date); // Insert the new car
    }

    fclose(file);
}

/**
 * Prints the date in the format of year/month/day.
 * @param date Integer representing the date in YYMMDD format.
 */
void date(int date)
{
    int year = date / 10000;        // Extract year
    int month = (date / 100) % 100; // Extract month
    int day = date % 100;           // Extract day

    printf("%02d/%02d/%02d\n", year, month, day);
}

/**
 * Frees all the memory allocated for the cars in the list.
 * @param head Pointer to the head of the list.
 * Frees each car node in the list.
 */
void free_list(struct car **head)
{
    struct car *current = *head;
    struct car *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

bool is_valid_plate(char plate[])
{
    int length = strlen(plate);

    // Check if length is within valid range
    if (length < 2 || length > 8)
    {
        return false;
    }

    // Check if all characters are alphanumeric
    for (int i = 0; i < length; i++)
    {
        if (!isalnum(plate[i]))
        {
            return false;
        }
    }

    return true;
}

bool is_valid_date(int date)
{
    int year = date / 10000;        // Extract year
    int month = (date / 100) % 100; // Extract month
    int day = date % 100;           // Extract day

    // Check for valid month
    if (month < 1 || month > 12)
    {
        return false;
    }
    if (day < 1 || day > 31)
    {
        return false;
    }
    if (month == 2) // February
    {
        if ((year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) && day > 29) || day > 28)
        {
            return false;
        }
    }
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    {
        return false;
    }

    // Add any necessary year validation
    if (year > 2024)
    {
        return false;
    }

    return true;
}
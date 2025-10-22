#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOCATION_LENGTH 100
#define MAX_TRAVEL_TYPE_LENGTH 50 // Could be replaced with constants but using define helps with speed (Run in preprocessor)

typedef struct {
    char destination[MAX_LOCATION_LENGTH]; 
    char travel_type[MAX_TRAVEL_TYPE_LENGTH];
    int duration_days;
    double travel_cost;
    double accommodation_cost;
    double food_cost;
    double total_cost;
    double cost_per_person;
} TravelPlan;

//Require buffer for character input, unknown how long string will be
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
//String input function
void get_string_input(char *prompt, char *buffer, int max_length) {
    printf("%s: ", prompt);
    fgets(buffer, max_length, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

// Function for getting posotive number for input
double get_positive_double(char *prompt) {
    double value;
    char input[50];
    
    while (1) {
        printf("%s: $", prompt);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%lf", &value) == 1 && value >= 0) {
                return value;
            }
        }
        printf("Please enter a valid positive number.\n"); // Saftey
    }
}

int get_positive_int(char *prompt) {
    int value;
    char input[50];
    
    while (1) {
        printf("%s: ", prompt);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if (sscanf(input, "%d", &value) == 1 && value > 0) {
                return value;
            }
        }
        printf("Please enter a valid positive number.\n");
    }
}

//Math.h not required, all costs must be added then dived by participants
void calculate_costs(TravelPlan *plan) {
    plan->total_cost = plan->travel_cost + plan->accommodation_cost + plan->food_cost;
    plan->cost_per_person = plan->total_cost / 2.0; //Default now is set to 2, this means two people split the trip evenly in the end
}

void display_trip_summary(TravelPlan *plan) {
    printf("\n===============================================\n");
    printf("                TRAVEL PLAN SUMMARY\n");
    printf("===============================================\n");
    
    printf("Destination:         %s\n", plan->destination);
    printf("Duration:            %d days\n", plan->duration_days);
    printf("\n");
    
    printf("COST BREAKDOWN:\n");
    printf("Travel Cost:         $%.2f\n", plan->travel_cost);
    printf("Accommodation:       $%.2f\n", plan->accommodation_cost);
    printf("Food (Projected):    $%.2f\n", plan->food_cost);
    printf("-----------------------------------------------\n");
    printf("TOTAL COST:          $%.2f\n", plan->total_cost);
    printf("Cost per person:     $%.2f\n", plan->cost_per_person);
    printf("\n");
    printf("Daily budget per person: $%.2f\n", plan->cost_per_person / plan->duration_days);
    printf("===============================================\n");
}

int main() {
    TravelPlan trip;
    char continue_choice;
    
    printf("Welcome to the Interactive Travel Planner!\n");
    printf("This program will help you plan and budget your trip for two people.\n\n");
    
    //Do while ensures that the print enters the loop at least once providing output to user
    do {
        printf("Please enter your travel details:\n\n");

        get_string_input("Destination", trip.destination, MAX_LOCATION_LENGTH);
        trip.travel_cost = get_positive_double("Travel cost (flights, gas, etc.)");
        trip.accommodation_cost = get_positive_double("Accommodation cost (hotels, rentals, etc.)");
        trip.food_cost = get_positive_double("Projected food cost");

        calculate_costs(&trip);
        display_trip_summary(&trip);

        printf("\nWould you like to plan another trip? (y/n): ");
        scanf(" %c", &continue_choice);
        clear_input_buffer();
        printf("\n");

    } while (continue_choice == 'y' || continue_choice == 'Y');
    
    printf("Thank you for using the Travel Planner! Safe travels!\n");
    return 0;
}

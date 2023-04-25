/*
 * Author:      Denys Tiasko
 * Created:     23/04/2023
 *
 * Description: This is the basecode that works as a platform for movie search and management of movie description or reviews.
 * 
 * User's input requirements: Name of the main file, name of the movies data file, name of the reviews data file.
 *                            
 */

#include <stdio.h>
#include <stdlib.h>

#include "files_handler.h"
#include "logger.h"
#include "menu_functions.h"
#include "management.h"


int main(int argc, char* argv[]) {

    LoggerSetOutputName("log.txt");
    LoggerSetLevel(INFO);
    Logger(INFO, "Program started");
    
    int num_movies = 0;
    int num_reviews = 0;
    Movie* movies;
    Review* reviews;

    // Check command-line arguments
    if (argc == 1) {
        // Read movies data
        movies = read_movies_file("movies.csv", &num_movies);
        // Read reviews data
        reviews = read_reviews_file("reviews.csv", &num_reviews);
    } else if (argc == 3) {
        // Read movies data
        movies = read_movies_file(argv[1], &num_movies);
        // Read reviews data
        reviews = read_reviews_file(argv[2], &num_reviews);
    } else {
        printf("Usage: %s movies.csv reviews.csv (or your files)\n", argv[0]);
        Logger(ERROR, "Invalid number of arguments");
        exit(EXIT_FAILURE);
    }
    
    int choice;
    char input[MAX_STR_LEN];
    do {
        printf("\nMenu:\n");
        printf("1. Display all data\n");
        printf("2. Edit movie year\n");
        printf("3. Edit rating reviewer status\n");
        printf("4. Find movies by length\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%s", input);
        if (is_integer(input)) {
            choice = atoi(input);
        switch (choice) {
            case 1:
                display(movies, num_movies, reviews, num_reviews);
                break;
            case 2:
                edit_movie_year(movies, num_movies);
                break;
            case 3:
                edit_reviewer_status(reviews, num_reviews);
                break;
            case 4:
                calculate_avg_rating(movies, num_movies, reviews, num_reviews);
                selection_sort(movies, num_movies);
                find_movies(movies, num_movies);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                Logger(WARNING, "Invalid input in main menu.");
                break;
        }}
        else {
            printf("Invalid input type. Please enter an integer.\n");
            Logger(WARNING, "Invalid input type in main menu.");
        }
    } while (choice != 5);

    // Free memory
    free_movies(movies, num_movies);
    free_reviews(reviews, num_reviews);
    Logger(INFO, "Program finished");
    return 0;
}





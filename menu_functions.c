#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "math.h"

#include "menu_functions.h"
#include "logger.h"
#include "files_handler.h"
#include "management.h"

// Displays all data
void display(Movie* movies, int num_movies, Review* reviews, int num_reviews)
{
    int i, j;
    for (i = 0; i < num_movies; i++)
    {
        printf("\n%d, %s, %d, %d, %s\n", movies[i].code, movies[i].name, movies[i].year, movies[i].length, movies[i].director);
        for (j = 0; j < num_reviews; j++)
        {
            if (movies[i].code == reviews[j].movie_code)
            {
                printf("    %d, %d, %s, %s, %.2f\n", reviews[j].review_id, reviews[j].movie_code, reviews[j].reviewer_name, reviews[j].status, reviews[j].points);
            }
        }
    }
    Logger(INFO, "Movies and reviews displayed");
}

// Finds movies by the length
void find_movies(Movie* movies, int num_movies)
{
    int minLength, maxLength, choice;
    char input[MAX_STR_LEN];
    do {
        printf("\nDisplay movies with length:\n");
        printf("1. Shorter than 'x'\n");
        printf("2. Longer than 'x'\n");
        printf("3. Between 'x' and 'y'\n");
        printf("4. Quit\n");
        printf("Enter your choice(1-4): ");
        scanf("%s", input);
        if (!is_integer(input)) {
            printf("Invalid input. Please enter a number.\n");
            Logger(WARNING, "Invalid input in secondary menu. ");
            continue;
        }
        choice = atoi(input);
        switch (choice) {
            case 1:
                printf("Enter maximum length of the movie\n> ");
                scanf("%s", input);
                if (!is_integer(input)) {
                    printf("Invalid input. Please enter a number.\n");
                    Logger(WARNING, "Invalid input for maximum length. ");
                    break;
                }
                maxLength = atoi(input);
                filter_movies(movies, num_movies, MIN_LENGTH, maxLength);
                break;
            case 2:
                printf("Enter minimum length of the movie\n> ");
                scanf("%s", input);
                if (!is_integer(input)) {
                    printf("Invalid input. Please enter a number.\n");
                    Logger(WARNING, "Invalid input for minimum length. ");
                    break;
                }
                minLength = atoi(input);
                filter_movies(movies, num_movies, minLength, MAX_LENGTH);
                break;
            case 3:
                printf("Enter minimum length of the movie\n> ");
                scanf("%s", input);
                if (!is_integer(input)) {
                    printf("Invalid input. Please enter a number.\n");
                    Logger(WARNING, "Invalid input for minimum length. ");
                    break;
                }
                minLength = atoi(input);
                printf("Enter maximum length of the movie\n> ");
                scanf("%s", input);
                if (!is_integer(input)) {
                    printf("Invalid input. Please enter a number.\n");
                    Logger(WARNING, "Invalid input for maximum length. ");
                    break;
                }
                maxLength = atoi(input);
                filter_movies(movies, num_movies, minLength, maxLength);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                Logger(WARNING, "Invalid input in secondary menu. ");
                break;
        }
    } while (choice != 4);
}

// Finds movies by the limitations of user input
void filter_movies(Movie* movies, int num_movies, int minLength, int maxLength) {
    printf("Movie code - Movie name - Year - Length - Average rating - Director\n");
    for (int i = 0; i < num_movies; i++) {
        if (movies[i].length >= minLength && movies[i].length <= maxLength) {
            if (isnan(movies[i].avg_rating)) {
                movies[i].avg_rating = 0;
            }
            printf("%d, %s, %d, %d, %.2lf, %s", movies[i].code, movies[i].name, movies[i].year, movies[i].length, movies[i].avg_rating, movies[i].director);
    }}}

// Edits movie year by the movie code in the structure
void edit_movie_year(Movie* movies, int num_movies) {
    int movie_code, year;
    bool found = false;
    printf("Enter movie code\n> ");
    while (scanf("%d", &movie_code) != 1 || movie_code < 0 || movie_code >= num_movies) {
        // Clear the input buffer
        while (getchar() != '\n');
        printf("Invalid input. Please enter a valid movie code.(0-%d)\n> ", num_movies);
        Logger(WARNING, "Invalid input for movie code. ");        
    }
    printf("Enter new year\n> ");
    while (scanf("%d", &year) != 1 || year < 0 || year > 2023) {
        // Clear the input buffer
        while (getchar() != '\n');
        printf("Invalid input. Please enter a valid year (0-2023).\n> ");
        Logger(WARNING, "Invalid input for new year. ");
    }
    for (int i = 0; i < num_movies; i++) {
        if (movies[i].code == movie_code) {
            movies[i].year = year;
            found = true;
            update_year("movies.csv", movie_code, year);
            break;
        }
    }
    if (!found) {
        printf("Movie code was not found\n");
        Logger(WARNING, "Invalid input for movie code.");
    }
}

// Writes changes for the year to the file
void update_year(char *filename, int code, int new_year) {
    FILE *fp, *temp;
    char buffer[MAX_STR_LEN];
    char *token;
    char temp_filename[] = "temp.csv";
    int code_col = 0;
    bool is_header = true;  // flag to keep track of whether we're processing the header line

    fp = fopen(filename, "r");
    temp = fopen(temp_filename, "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file\n");
        Logger(ERROR, "Error opening file.");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (is_header) {  // skip the header line
            fprintf(temp, "%s", buffer);
            is_header = false;
            continue;
        }
        
        char *line = strdup(buffer);  // create a duplicate string to modify
        int col_num = 0;

        // split the line into tokens
        token = strtok(line, ",");
        while (token != NULL) {
            if (col_num == code_col) {
                int code_val = atoi(token);
                if (code_val == code) {
                    // movie code matches user input, update year
                    fprintf(temp, "%d", code_val);  // write code
                    fprintf(temp, ",");  // write separator
                    token = strtok(NULL, ",");  // skip name
                    fprintf(temp, "%s", token);  // write name
                    fprintf(temp, ",");  // write separator
                    token = strtok(NULL, ",");  // read original year
                    fprintf(temp, "%d", new_year);  // write new year
                    fprintf(temp, ",");  // write separator
                    token = strtok(NULL, ",");  // read length
                    fprintf(temp, "%s", token);  // write length
                    fprintf(temp, ",");  // write separator
                    token = strtok(NULL, ",");  // read director
                    fprintf(temp, "%s", token);  // write director
                
                }
                else {
                    // movie code doesn't match, write the original line
                    fprintf(temp, "%s", buffer);   
                } 
            }

            col_num++;
            token = strtok(NULL, ",");
        }

        free(line);
    }
    fclose(fp);
    fclose(temp);

    // replace the original file with the temporary file
    remove(filename);
    rename(temp_filename, filename);
    Logger(INFO, "Updated movie year.");
}

// Edits reviewer status by review_ID in the structure
void edit_reviewer_status(Review* reviews, int num_reviews)
{
    int review_id;
    char status[MAX_STR_LEN];
    bool found = false;
    printf("Enter review ID\n> ");
    while (scanf("%d", &review_id) != 1 || review_id < 1 || review_id > num_reviews) {
        printf("Invalid input. Please enter a valid review ID between 1 and %d\n> ", num_reviews);
        Logger(WARNING, "Invalid input for review ID. ");
        // clear input buffer
        while (getchar() != '\n');
    }
    printf("Enter new status\n> ");
    while (scanf("%s", status) != 1 || (strcmp(status, "user") != 0 && strcmp(status, "critic") != 0)) {
        printf("Invalid input. Please enter a valid status (user or critic)\n> ");
        Logger(WARNING, "Invalid input for status. ");
        // clear input buffer
        while (getchar() != '\n');
    }
    for (int i = 0; i < num_reviews; i++) {
        if (reviews[i].review_id == review_id) {
            strcpy(reviews[i].status, status);
            found = true;
            update_review_status("reviews.csv", review_id, status);
            break;
        }
    }
    if (!found) {
        printf("Review ID was not found\n");
        Logger(WARNING, "Invalid input for review ID.");
    }
}

// Writes changes for the status to the file
void update_review_status(char *filename, int review_id, char *new_status) {
    FILE *fp, *temp;
    char buffer[MAX_STR_LEN];
    char *token;
    char temp_filename[] = "temp.csv";
    int review_id_col = 0;

    fp = fopen(filename, "r");
    temp = fopen(temp_filename, "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file\n");
        Logger(ERROR, "Error opening file.");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        char *line = strdup(buffer);  // create a duplicate string to modify
        int col_num = 0;

        // split the line into tokens
        token = strtok(line, ",");
        while (token != NULL) {
            if (col_num == review_id_col && atoi(token) == review_id) {
                // review_id matches user input, update status
                fprintf(temp, "%d", atoi(token));  // write review_id
                fprintf(temp, ",");  // write separator
                token = strtok(NULL, ",");  // read movie_code
                fprintf(temp, "%s", token);  // write movie_code
                fprintf(temp, ",");  // write separator
                token = strtok(NULL, ",");  // read reviewer name
                fprintf(temp, "%s", token);  // write reviewer name
                fprintf(temp, ",");  // write separator
                token = strtok(NULL, ",");  // read original status
                fprintf(temp, "%s", new_status);  // write new status
                fprintf(temp, ",");  // write separator
                token = strtok(NULL, ",");  // read points
                fprintf(temp, "%s", token);  // write points
            } 
            else {
                // review_id doesn't match, write the original line
                fprintf(temp, "%s", token);

                if (col_num != 4) {
                    // not the last column, write comma separator
                    fprintf(temp, ",");
                } 
               
            }

            col_num++;
            token = strtok(NULL, ",");
        }

        free(line);
    }

    fclose(fp);
    fclose(temp);

    // replace the original file with the temporary file
    remove(filename);
    rename(temp_filename, filename);
    Logger(INFO, "Updated rating reviewer status.");
}

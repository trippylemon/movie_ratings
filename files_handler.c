#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files_handler.h"
#include "logger.h"

//reads the movies file and returns a pointer to a dynamic array of movies
Movie* read_movies_file(const char* filename, int* num_movies) {
    // Open file for reading
    FILE* file = fopen(filename, "r");

    // Check if file was opened successfully
    if (file == NULL) {
        printf("Error: Could not open file '%s'.\n", filename);
        Logger(ERROR, "Cannot open file with movies");
        exit(EXIT_FAILURE);
    }
    Logger(INFO, "Movies file opened");

    // Allocate memory for dynamic array
    Movie* movies = malloc(sizeof(Movie));
    *num_movies = 0;

    char buffer[MAX_STR_LEN];
    fgets(buffer, MAX_STR_LEN, file);

    // Read data from file
    char line[MAX_STR_LEN];
    while (fgets(line, MAX_STR_LEN, file) != NULL) {
        // Split line into fields
        char* token = strtok(line, ",");
        Movie movie;

        // Parse movie fields
        movie.code = atoi(token);
        token = strtok(NULL, ",");
        movie.name = strdup(token);
        token = strtok(NULL, ",");
        movie.year = atoi(token);
        token = strtok(NULL, ",");
        movie.length = atoi(token);
        token = strtok(NULL, ",");
        movie.director = strdup(token);

        // Add movie to dynamic array
        (*num_movies)++;
        Movie *temp = realloc(movies, (*num_movies) * sizeof(Movie));

        if (temp == NULL) {
            // handle the error
            printf("Error: Failed to allocate memory\n");
            Logger(ERROR, "Failed to reallocate memory for movies");
            exit(EXIT_FAILURE);
        }
        movies = temp;
        movies[*num_movies - 1] = movie;
    }

    // Close file
    fclose(file);
    Logger(INFO, "Movies file successfull read and closed");
    return movies;
}

//reads the reviews file and returns a pointer to a dynamic array of reviews
Review* read_reviews_file(const char* filename, int* num_reviews) {
    
    // Open file for reading
    FILE* file = fopen(filename, "r");

    // Check if file was opened successfully
    if (file == NULL) {
        printf("Error: Could not open file '%s'.\n", filename);
        Logger(ERROR, "Cannot open reviews file");
        exit(EXIT_FAILURE);
    }
    Logger(INFO, "Reviews file opened");

    // Allocate memory for dynamic array
    Review* reviews = malloc(sizeof(Review));
    *num_reviews = 0;

    char buffer[MAX_STR_LEN];
    fgets(buffer, MAX_STR_LEN, file);

    // Read data from file
    char line[MAX_STR_LEN];
    while (fgets(line, MAX_STR_LEN, file) != NULL) {
        // Split line into fields
        char* token = strtok(line, ",");
        Review review;

        // Parse review fields
        review.review_id = atoi(token);
        token = strtok(NULL, ",");
        review.movie_code = atoi(token);
        token = strtok(NULL, ",");
        review.reviewer_name = strdup(token);
        token = strtok(NULL, ",");
        review.status = strdup(token);
        token = strtok(NULL, ",");
        review.points = strtof(token, NULL);

        // Add review to dynamic array
        (*num_reviews)++;
        Review *temp = realloc(reviews, (*num_reviews) * sizeof(Review));

        if (temp == NULL) {
            // handle the error
            printf("Error: Failed to allocate memory\n");
            Logger(ERROR, "Failed to reallocate memory for reviews");
            exit(EXIT_FAILURE);
        }

        reviews = temp;
        reviews[*num_reviews - 1] = review;
    }

    // Close file
    fclose(file);
    Logger(INFO, "Reviews file successfull read and closed");
    return reviews;
}

//frees the memory allocated for the movies dynamic array
void free_movies(Movie* movies, int num_movies) {
    for (int i = 0; i < num_movies; i++) {
        free(movies[i].name);
        free(movies[i].director);
    }
    free(movies);
    Logger(INFO, "Movies memory freed");
}

//frees the memory allocated for the reviews dynamic array
void free_reviews(Review* reviews, int num_reviews) {
    for (int i = 0; i < num_reviews; i++) {
        free(reviews[i].reviewer_name);
        free(reviews[i].status);
    }
    free(reviews);
    Logger(INFO, "Reviews memory freed");
}

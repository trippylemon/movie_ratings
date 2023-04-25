#include <stdbool.h>

#include "logger.h"
#include "files_handler.h"
#include "management.h"

// Calculates average rating points for each movie
void calculate_avg_rating(Movie* movies, int num_movies, Review* reviews, int num_reviews) 
{
    int i, j;
    
    for (i = 0; i < num_movies; i++) {
        float sum = 0;
        int count = 0;
        for (j = 0; j < num_reviews; j++) {
            if (movies[i].code == reviews[j].movie_code) {
                sum += reviews[j].points;
                count++;
            }
        }
        movies[i].avg_rating = (double)sum / count;
    }
    Logger(INFO, "Average rating points calculated");
}

// Checks if a string is an integer
bool is_integer(const char* str) {
    if (*str == '\0') {
        return false;
    }
    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            return false;
        }
        ++str;
    }
    return true;
}

// Sorts movies array by average rating in descending order
void selection_sort(Movie* movies, int num_movies) {
    // Sort movies array by average rating in descending order
    for (int i = 0; i < num_movies - 1; i++) {
        for (int j = i + 1; j < num_movies; j++) {
            if (movies[i].avg_rating > movies[j].avg_rating) {
                // Swap movies[i] and movies[j]
                Movie temp = movies[i];
                movies[i] = movies[j];
                movies[j] = temp;
            }}}
    Logger(INFO, "Movies sorted by average rating. ");
    }   


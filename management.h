#ifndef management_h
#define management_h

#include <stdbool.h>

/*
 * Description: calculates average review points for each movie.
 * 
 * Parameter: movies - pointer to array of movie structures.
 * Parameter: num_movies - number of movies in the array.
 * Parameter: reviews - pointer to array of review structures.
 * Parameter: num_reviews - number of reviews in the array.
 */
void calculate_avg_rating(Movie* movies, int num_movies, Review* reviews, int num_reviews);

/* 
 * Description: checks if string is an integer.
 *
 * Parameter: str - pointer to string.
 * 
 * Return: true if string is an integer, false otherwise.
 */
bool is_integer(const char* str);

/* 
 * Description: Sorts movies by average rating in descending order.
 * 
 * Parameter: movies - pointer to array of movie structures.
 * Parameter: num_movies - number of movies in the array.
 */
void selection_sort(Movie* movies, int num_movies);

#endif /* management_h */
#ifndef menu_functions_h
#define menu_functions_h

#define MIN_LENGTH 0
#define MAX_LENGTH 250

#include "files_handler.h"

/* 
 * Description: displays movies and reviews.
 * 
 * Parameter: movies - pointer to array of movie structures.
 * Parameter: num_movies - number of movies in the array.
 * Parameter: reviews - pointer to array of review structures.
 * Parameter: num_reviews - number of reviews in the array.
 */
void display(Movie* movies, int num_movies, Review* reviews, int num_reviews);

/* 
 * Description: Contains menu for user choice to find movies with length shorter than 'x', longer than 'x' or between 'x' and 'y'.
 *              Calls other functions to find movies by the length.
 * 
 * Parameter: movies - pointer to array of movie structures.
 * Parameter: num_movies - number of movies in the array.
 */
void find_movies(Movie* movies, int num_movies);

/* 
 * Description: filters movies by length.
 * 
 * Parameter: movies - pointer to array of movie structures.
 * Parameter: num_movies - number of movies in the array.
 * Parameter: minLength - minimum length of the movie.
 * Parameter: maxLength - maximum length of the movie.
 */
void filter_movies(Movie* movies, int num_movies, int minLength, int maxLength);

/* 
 * Description: Changes the year of the movie in the movies array. Calls other function to write changes in the file.
 * 
 * Parameter: movies - pointer to array of movie structures.
 * Parameter: num_movies - number of movies in the array.
 */
void edit_movie_year(Movie* movies, int num_movies);

/* 
 * Description: Changes the rating reviewier status. Calls other function to write changes in the file.
 * 
 * Parameter: reviews - pointer to array of review structures.
 * Parameter: num_reviews - number of reviews in the array.
 */
void edit_reviewer_status(Review* reviews, int num_reviews);

/* 
 * Description: Changes the year of the movie in the movies file.
 * 
 * Parameter: filename - name of the file to be modified.
 * Parameter: code - code of the movie to be modified.
 * Parameter: new_year - new year of the movie.
 */
void update_year(char *filename, int code, int new_year);

/* 
 * Description: Changes the status of the review in the reviews file.
 * 
 * Parameter: filename - name of the file to be modified.
 * Parameter: review_id - ID of the review to be modified.
 * Parameter: new_status - new status of the review.
 */
void update_review_status(char *filename, int review_id, char *new_status);

#endif /* menu_functions_h */
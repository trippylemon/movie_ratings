#ifndef files_handler_h
#define files_handler_h

#define MAX_STR_LEN 256

//structure for movie
typedef struct {
    int code;
    char* name;
    int year;
    int length;
    char* director;
    double avg_rating;
} Movie;

//structure for review
typedef struct {
    int review_id;
    int movie_code;
    char* reviewer_name;
    char* status;
    float points;
} Review;

/*
 * Description: reads movies from file specified by filename parameter.
 * 
 * Parameter: filename - name of the file to read movies from.
 * Parameter: num_movies - pointer to variable that will store number of movies read from file.
 */
Movie* read_movies_file(const char* filename, int* num_movies);

/*
 * Description: reads reviews from file specified by filename parameter.
 * 
 * Parameter: filename - name of the file to read reviews from.
 * Parameter: num_reviews - pointer to variable that will store number of reviews read from file.
 */
Review* read_reviews_file(const char* filename, int* num_reviews);

/* 
 * Description: frees te memory allocated for movies array.
 * 
 * Parameter: movies - pointer to array of movie structures.
 * Parameter: num_movies - number of movies in the array.
 */
void free_movies(Movie* movies, int num_movies);

/* 
 * Description: frees te memory allocated for reviews array.
 * 
 * Parameter: reviews - pointer to array of review structures.
 * Parameter: num_reviews - number of reviews in the array.
 */
void free_reviews(Review* reviews, int num_reviews);



#endif /* files_handler_h */
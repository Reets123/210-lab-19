// Lab 18: Movie Reviews
// COMSC-210 - Ibrahim Alatig 

//      UML
//    ReviewNode    
//
// - rating: double 
// - comment: string
// - next: ReviewNode* 
//
                
//   ReviewList     
//
// - head: ReviewNode* 
// - tail: ReviewNode* 
// - count: int        
// ------------------
// + ReviewList()     
// + addAtHead(rating: double, comment: string) 
// + addAtTail(rating: double, comment: string) 
// + outputReviews()  
// + ~ReviewList()    

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include <iomanip>

using namespace std;

struct ReviewNode {
    double rating;
    string comment;
    ReviewNode* next;
};

class ReviewList {
private:
    ReviewNode* head;
    int count;

public:
    ReviewList() : head(nullptr), count(0) {}

    void addAtHead(double rating, const string& comment) {
        ReviewNode* newNode = new ReviewNode{rating, comment, head};
        head = newNode;
        count++;
    }

    void outputReviews() {
        ReviewNode* current = head;
        double totalRating = 0;

        cout <<  "Outputting all reviews:" << endl;
        for (int i = 1; current != nullptr; i++) {
            cout << "    > Review #" << i << ": " << fixed << setprecision(1) << current->rating << ": " << current->comment << endl;
            totalRating += current->rating;
            current = current->next;
        }

        double average = (count > 0) ? (totalRating / count) : 0;
        cout << "    > Average: " << average << endl;
    }
     
     ~ReviewList() {
        ReviewNode* current = head;
        while (current != nullptr) {
            ReviewNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

class Movie {
private:
    string title;
    ReviewList reviews;

public:
    Movie(const string& title) : title(title) {}

    void addReview(double rating, const string& comment) {
        reviews.addAtHead(rating, comment);
    }

     void outputReviews() {
        cout << "Reviews for " << title << ":" << endl;
        reviews.outputReviews();
    }


double generateRandomRating() {
    return (rand() % 41) / 10.0 + 1.0;
}

void populateMovieFromFile(Movie& movie, const string& filename) {
    ifstream infile(filename);
    string comment;

    if (infile.is_open()) {
        while (getline(infile, comment)) {
            double rating = generateRandomRating();
            movie.addReview(rating, comment);
        }
        infile.close();
    } else {
        cerr << "Error opening file, Check files name " << filename << endl;
    }
}


int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    vector<Movie> movies;
    
    // Creating Movie Objects and populating them from files
    Movie movie1("Inception");
    populateMovieFromFile(movie1, "inception_reviews.txt");
    movies.push_back(movie1);

    Movie movie2("The Matrix");
    populateMovieFromFile(movie2, "matrix_reviews.txt");
    movies.push_back(movie2);

    // Output all movie reviews
    for (const auto& movie : movies) {
        movie.outputReviews();
        cout << endl;
    }

    return 0;
}
   
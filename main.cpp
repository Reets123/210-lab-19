// Lab 19: Abstract & Automate Lab 18
// COMSC-210 - Ibrahim Alatig 

//      UML              
//   ReviewList     
//
// - head: ReviewNode* 
// - count: int        
// ------------------
// + ReviewList()     
// + addAtHead(rating: double, comment: string) 
// + outputReviews()  
// + ~ReviewList()    

//      Movie   
//
// - title: string 
// - ratingsAndReviews: ReviewList 
// --------------------------------
// + Movie(string)
// + addReview(string)
// + outputReviews()
// + populateFromFile(string)
// + generateRandomRating(): double

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

    void outputReviews() const {
        ReviewNode* current = head;
        double totalRating = 0;

        cout << "Outputting all reviews:" << endl;
        int i = 1;
        while (current != nullptr) {
            cout << "    > Review #" << i++ << ": " << fixed << setprecision(1) 
                 << current->rating << ": " << current->comment << endl;
            totalRating += current->rating;
            current = current->next;
        }

        double average = (count > 0) ? (totalRating / count) : 0;
        cout << "    > Average Rating: " << fixed << setprecision(1) << average << endl;
    }

    ~ReviewList() {
        // Properly delete all nodes in the list
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
    ReviewList ratingsAndReviews;

public:
    Movie(const string& title) : title(title) {}

    // Add a review with a random rating and a given comment
    void addReview(const string& comment) {
        double rating = generateRandomRating();
        ratingsAndReviews.addAtHead(rating, comment);
    }

    // Output all movie reviews
    void outputReviews() const {
        cout << "Reviews for " << title << ":" << endl;
        ratingsAndReviews.outputReviews();
        cout << endl;
    }

    // Populate reviews from a file
    void populateFromFile(const string& filename) {
        ifstream infile(filename);
        if (!infile.is_open()) {
            cerr << "Error opening file, Check files name " << filename << endl;
            return;
        }

        string comment;
        while (getline(infile, comment)) {
            addReview(comment); // Add review with random rating
        }
        infile.close();
    }

    static double generateRandomRating() {
        return (rand() % 41) / 10.0 + 1.0; // Generates a random rating between 1.0 and 5.0
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    vector<Movie*> movies; // Container for Movie objects

    // Create Movie objects and populate them from files
    Movie* movie1 = new Movie("Dune2");
    movie1->populateFromFile("Dune2_reviews.txt");
    movies.push_back(movie1);

    Movie* movie2 = new Movie("Stanford prison experiment");
    movie2->populateFromFile("Stanford_reviews.txt");
    movies.push_back(movie2);

    // Output all movie reviews
    for (const auto& movie : movies) {
        movie->outputReviews();
    }

    // Clean up allocated memory
    for (const auto& movie : movies) {
        delete movie;
    }

    return 0;
}
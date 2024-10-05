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
    ReviewList ratings;

int main() {
    ReviewList reviews;
    int choice;

    cout << "Which linked list method should we use?" << endl;
    cout << "    [1] New nodes are added at the head of the linked list" << endl;
    cout << "    [2] New nodes are added at the tail of the linked list" << endl;
    cout << "    Choice: ";
    cin >> choice;

    char moreReviews;
    do {
        double rating;
        string comment;

        cout << "Enter review rating 0-5: ";
        cin >> rating;

        cout << "Enter review comments: ";
        cin.ignore(); // Clear input buffer
        getline(cin, comment);

        if (choice == 1) {
            reviews.addAtHead(rating, comment);
        } else {
            reviews.addAtTail(rating, comment);
        }

        cout << "Enter another review? Y/N: ";
        cin >> moreReviews;

    } while (tolower(moreReviews) == 'y');

    reviews.outputReviews();
    
    return 0;
}
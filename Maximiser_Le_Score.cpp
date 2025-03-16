#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <utility>
#include <algorithm>
#include <iomanip>
#define LL long long
using namespace std;

typedef pair<LL, LL> pairs; // Pair type to store ball's value and its sum of digits

/*--------------Defined Class--------------*/
// Build and manage priority queue with heap
class Heap {
    private:
        bool digitSum; // Determine the method to pick a ball
        vector<pairs> balls = {}; // Store balls' values and their sums of digits in pair

        void shiftUp(LL i); // Move ball up the heap
        void shiftDown(LL i); // Move ball down the heap
        LL parent(LL i) {return (i - 1) / 2;}
        LL leftChild(LL i) {return (2 * i) + 1;}
        LL rightChild(LL i) {return (2 * i) + 2;}

    public:
        Heap() {};
        Heap(vector<pairs> ballsVal, bool d); // User-defined constructor
        ~Heap() {};

        pairs pickBall(); // Pick ball with highest priority
        void removeBall(pairs ball); // Remove ball from heap
};

// User-defined constructor - Generate priority queue in a vector using heap
Heap::Heap(vector<pairs> ballsVal, bool d) {
    digitSum = d;
    for (auto n : ballsVal) {
        balls.push_back(n);
        shiftUp(balls.size() - 1);
    }
}

// Move ball with higher priority up the heap
void Heap::shiftUp(LL i) {
    if (!digitSum) { // If priority is determined according to the value on the ball
       while (i > 0 && balls[parent(i)].first < balls[i].first) {
            swap(balls[parent(i)], balls[i]);
            i = parent(i);
       } 
    }
    else { // If priority determined according to the sum of digits
        while(i > 0 && ((balls[parent(i)].second < balls[i].second) || 
        (balls[parent(i)].second == balls[i].second && balls[parent(i)].first < balls[i].first))) {
            swap(balls[parent(i)], balls[i]);
            i = parent(i);
        }
    }
}

// Move ball with lower priority down the heap
void Heap::shiftDown(LL i) {
    LL track = i;
    LL left = leftChild(i);
    LL right = rightChild(i);

    if (!digitSum) { // If priority is determined according to the value on the ball    
        if (left < balls.size() && balls[left].first > balls[track].first) {track = left;}
        if (right < balls.size() && balls[right].first > balls[track].first) {track = right;}
    }
    // If priority is determined according to the sum of digits
    // However, if two balls have the same sum of digits, the priority is then determined by their values
    else {    
        if (left < balls.size() && ((balls[left].second > balls[track].second) ||
        (balls[left].second == balls[track].second && balls[left].first > balls[track].first))) {track = left;}
        if (right < balls.size() && ((balls[right].second > balls[track].second) ||
        (balls[right].second == balls[track].second && balls[right].first > balls[track].first))) {track = right;}
    }

    if (i != track) {
        swap(balls[i], balls[track]); // Shift balls
        shiftDown(track); // Recursion
    }
}

// Pick ball with the highest priority and remove it from the heap before rearranging the order
pairs Heap::pickBall() {
    pairs picked = balls[0]; // First ball in the vector will always be the most prioritised ball
    balls[0] = balls[balls.size() - 1]; // Move last ball to the front
    balls.pop_back(); // Remove last element in vector
    shiftDown(0); // Rearrange order

    return picked;
}

// Remove ball that has been taken out during the last round from the heap
// To avoid the same ball from being picked in the next round
void Heap::removeBall(pairs ball) {
    // Find the position of the ball to be removed in the vector
    LL i;
    auto it = find(balls.begin(), balls.end(), ball);
    if (it != balls.end()) {
        i = it - balls.begin();
    }
    
    // Change the value of the ball to the largest in order to move it to the top of the heap
    if (!digitSum) {balls[i].first = balls[0].first + 1;}
    else {balls[i].second = balls[0].second + 1;}
    shiftUp(i);
    pickBall(); // Remove ball
}

/*--------------Main Program's Functions--------------*/
// Find the sum of digits on the ball
LL sumOfDigits(LL n) {
    LL sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

// Run the game
void runGame(Heap &first, Heap &second, LL &score1, LL &score2, LL nBalls, LL nTurns) {
    while (nBalls > 0) { // While there are balls remaining to be picked
        for (LL i = 0; i < nTurns && nBalls != 0; i++) { // First player's round
            pairs picked = first.pickBall();
            score1 += picked.first; // Update score
            second.removeBall(picked); // Remove ball from second's player heap
            nBalls--;
        }
        for (LL i = 0; i < nTurns && nBalls != 0; i++) { // Second player's round
            pairs picked = second.pickBall();
            score2 += picked.first;
            first.removeBall(picked); // Remove ball from first player's heap
            nBalls--;
        }
    }
}

// Generate heaps and determine who to start the game
pairs score(LL nBalls, LL nTurns, string start, vector<pairs> balls) {
    LL scottScore = 0, rustyScore = 0;
    Heap scottHeap(balls, false);
    Heap rustyHeap(balls, true);

    if (start == "HEADS") {runGame(scottHeap, rustyHeap, scottScore, rustyScore, nBalls, nTurns);}
    else {runGame(rustyHeap, scottHeap, rustyScore, scottScore, nBalls, nTurns);}

    return make_pair(scottScore, rustyScore);    
}

/*--------------Main Program--------------*/
int main(int argc, char *argv[])
{ifstream inFile;
 inFile.open(string(argv[1])); // Get file name from command line
 if (!inFile) {cout << "Failed to open input file." << endl;}

 LL nCases; // Number of test cases
 LL nBalls; // Number of balls
 LL nTurns; // Maximum number of turns allowed
 string start; //Result of toss

 // Read file
 inFile >> nCases; 
 for (LL i = 0; i < nCases; i++) { // Step through every case
     double startTime = clock(); // Start time
     inFile >> nBalls >> nTurns;
     vector<pairs> balls = {};
     for (LL j = 0; j < nBalls; j++) {
         LL val;
         inFile >> val;
         balls.push_back(make_pair(val, sumOfDigits(val))); // Store value and sum of digits of each ball
     }
     inFile >> start;

     pairs scores = score(nBalls, nTurns, start, balls); // Find maximum scores for both players
     double cpuTime = clock() - startTime; // End time

     cout << "Scott's score = " << scores.first << "; Rusty's score = " << scores.second;
     cout << "; CPU Time = " << fixed << setprecision(6) << cpuTime / CLOCKS_PER_SEC << "s" << endl;   
 }

 return 0;
}
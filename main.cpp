// Afham Bashir 
// CISC 230

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// Class for finding execution time.
//	Usage:
//		Timer t; // Create a Timer object
//		some_stuff(); // Your code
//		double elapsed_time = t.seconds(); // Get executation time
class Timer {
private:
	clock_t clock_start;
public:
	Timer() { reset(); }
	void reset() { clock_start = clock(); }
	double seconds()
		{ return (double(clock()) - double(clock_start)) / CLOCKS_PER_SEC; }
};

unsigned int randInt();
unsigned int randInt(unsigned int max);
unsigned int randInt(unsigned int min, unsigned int max);

void algorithm1(vector<unsigned int>& v);
void algorithm2(vector<unsigned int>& v);
void algorithm3(vector<unsigned int>& v);
bool verify_values(const vector<unsigned int>& v);
bool check_vector_alg1(vector<unsigned int>& v, unsigned int n, int size);   // funcion prototype for function called by alg1 


int main(int argc, char* argv[]) {
	// Set precision for timer output.
	cout << fixed << setprecision(5);

	// Get algorithm from command line if provided, else prompt for it
	int algo;
	if (argc > 1)
		algo = atoi(argv[1]);
	else {
		cout << "Enter algorithm (1, 2, or 3): ";
		cin >> algo;
	}

	// Get size of vector from command line if provided, else prompt for it
	size_t size = 0;
	if (argc > 2)
		size = size_t(atoi(argv[2]));
	if (!size) {
		cout << "Enter vector size: ";
		cin >> size;
	}

	// Create vector of the given size
	vector<unsigned int> v(size);

	// Fill vector with a random permutation of values from 1 through size
	Timer t;
	switch (algo) {
	case 1: algorithm1(v); break;
	case 2: algorithm2(v); break;
	case 3: algorithm3(v); break;
	default:
		cout << "Invalid algorithm entered." << endl;
	}
	double exec_time = t.seconds();

	// Verify that the vector, in fact, contains the desired values
	cout << "Values in the vector are " <<
		(verify_values(v) ? "valid" : "NOT VALID") << ".\n";
	if (v.size() <= 25) {
		for (size_t i = 0; i < v.size(); i++)
			cout << (i ? " " : "") << v[i];
		cout << endl;
	}

	// Report the run time
	cout << "Run time: " << t.seconds() << " seconds\n";

#ifdef _MSC_VER // If Microsoft Visual C++ compiler version is defined
	system("pause");
#endif

	return 0;
}

// randInt - Generates a random integer, three versions:
//	- Random integer (with RNG initialization)
//	- Random integer from 1 through max inclusive
//	- Random integer from min through max inclusive
unsigned int randInt() {
	static bool init = true; // Initialize RNG?
	if (init) {
		srand(unsigned(int(time(NULL))));
		init = false;
	}
#if RAND_MAX == 32767
	return rand() * rand();
#else
	return rand();
#endif
}

unsigned int randInt(unsigned int max) { return randInt() % max + 1; }

unsigned int randInt(unsigned int min, unsigned int max) {
	return min <= max ?
		randInt(max - min + 1) + min - 1 : randInt(max, min);
}

// verify_values - Verifies that the given vector contains the values 1
//	through the size of the vector.
bool verify_values(const vector<unsigned int>& v) {
	vector<bool> used(v.size(), false);
	for (size_t i = 0; i < v.size(); i++)
		if (v[i] && v[i] <= v.size())
			used[v[i] - 1] = true;
	for (size_t i = 0; i < v.size(); i++)
		if (!used[i])
			return false;
	return true;
}

bool check_vector_alg1(vector<unsigned int>& v, unsigned int n, int size) { //function called by alg1 to check if the number is already present in the vector, uses the reference for the vector and is passed the random number being serached for, and the size of the vector to search through. 
  for (size_t i = 0; i < size; i++) {  //this for loop is used for sequential search of the vector. 
    if( n == v[i]) {
      return 0;} }   //is the number is alrady present in the vector, function returns false. 
  return 1;          //if the number is not present and the search is completed, returns a true; 
} 

// algorithm1 - Fill the given vector with the values 1 through
//	the size of the vector, with values arranged in some random permutation.
//	Uses algorithm #1 to fill the vector.
void algorithm1(vector<unsigned int>& v){
	for (size_t i =  0; i < v.size(); i++) { //starts a for loop that will generate enough valid random numbers to fill the vector
    int check;    //creates a variable that is used by in the conditional statement of the do while loop. 
    do{           //using a do while allows the function generate another random integer untill its valid. 
      unsigned int n = randInt(1, v.size());   //generates a random variable between 1 and the size of the vector
      check = check_vector_alg1(v, n, i);     //calls the check function to see if the generated random variable is already in the vector. 
      if ( check == true) { //if the generated randint isnt in the vector already, it can be added to the vector. 
      v[i]= n;}
      }while (check == 0); //keep generateing a random loop untill a valid one is made. 
  }
}

// algorithm2 - Fill the given vector with the values 1 through
//	the size of the vector, with values arranged in some random permutation.
//	Uses algorithm #2 to fill the vector.
void algorithm2(vector<unsigned int>& v) {
  int size = v.size();  //used for the size of the used vector. 
  vector<unsigned int> used(size, 0);    //used to intialize a second vector that will track random variables already used, the vectors intialize values are all set to zero. 
  for (size_t i = 0; i < v.size(); i++) { //for loop to insert random values into the vector
    int check = 0;                //used a value to control the while loop. 
    do{   //using a do while allows the function generate another random integer untill its valid. 
    unsigned int ran = randInt(1, v.size());  
    if(used[ran]==false){   //if the random number generated is not already in the used vector
      v[i]= ran;             //the random intger is added to the vector 
      used[ran]=true;        //now sets the integer that was just added to the used vector
      check = true;          // if the integer was valid and added, then there is not need to generate another number of that index of the vector, and can exit the while loop. 
    } } while(check == false); 
  }
}
                                               

// algorithm3 - Fill the given vector with the values 1 through
//	the size of the vector, with values arranged in some random permutation.
//	Uses algorithm #3 to fill the vector.
void algorithm3(vector<unsigned int>& v) {
	for (size_t i = 0; i < v.size(); i++) {
		v[i] = i + 1;}   //for loop that sequentially fills the vector up untill it reaches the end of the vector.
  for (int i= 0; i<v.size(); i++) { //creates a for loop that swaps indexes 
    swap( v[i], v[randInt(0, i)]); //swap function swaps the (i) index with another index within the vector that is randomly determined using the randInt function. 
  }
}

 
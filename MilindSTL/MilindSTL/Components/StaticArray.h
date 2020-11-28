/*
	Milind Singh | ms10997@nyu.edu | Matician Coding Challenge
   ============================================================

	SUMMARY:
	1. From my understanding , the problem asks me to design an efficient system which can apply a convolution matrix filter and return the results.
	2. There are also a few extra design considerations which I need to take care of for the outputs.
	3. But the computational bulk of this program lies in the matrix operations which I need to design efficiently.

	APPROACH:
	Make a class that could do the following
	1. Read m and n (no of rows, no of columns) from CLI
	2. Fill matrix data structure with random 8 bit unsigned integers
	3. Apply convolution matrix filter and store two additional matrices
		-- It makes sense to create a specialized class/struct to hold the matrices for the operations.
		-- I will need to choose fast data structures , might be possible to do this with a 1D-Array.
	4. Build functions to get min and max of matrix
		-- Made in Matrix Wrapper itself to reduce complexity
	5. Use SmartTimer API for benchmark.

	Design Assumptions/Considerations:
	1. The kind of filter described in the problem is a diffrential filter, meaning we lose some data as we fiter it , this data loss is seen at the edges of the matrix.
		-- The kernel(filter matrix) convolutes and replaces the underlying matrix with a single value , this means loss of information
		-- We have a choice to either fill in the missing values or reduce the size of our input depending on the application.
		-- I have chosen to forgo the lost information as the question doesn't specify anything regarding preserving information.
	2. The filter is a simple arithmetic operation ,because the problem mentions that filter is fixed , I have assumed the filter to be fixed values and sizes and accordingly hard-coded a few operations to save time.
	3. I thought of implementing memoization to save time , but the speed benefits seem trivial against the memory requirement.

*/

#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <string>

/*
Abridged Scoped Timer Library , created by me for MilindSTL , will use as Benchmark Instrumentation
https://github.com/milli9d/C-Practice/blob/master/MilindSTL/MilindSTL/Components/Timer.h
	This can work as one-off or stopwatch timer.
	Usage :
		1. Instantiate the Smart Timer where you want the timer to start , takes in string param to give name to timer , no default constructor
		2. Timer will automatically report time from instantiation to end of current scope
		3. You can also use stopTimer() to stop the timer at a particular line , timer will report this duration data at the end of scope.
*/
class SmartTimer {
private:

	std::chrono::system_clock::time_point start, end;
	std::chrono::duration<float> duration = std::chrono::milliseconds(0);
	const char* nameTimer;
	bool stop = false;

public:

	// Construct Timer Object and take start count
	SmartTimer(const char* str) {
		nameTimer = str;
		printf("Time Benchmark Started for %s \n", nameTimer);
		start = std::chrono::high_resolution_clock::now();
	}

	// Stop Timer and store duration
	void stopTimer() {
		end = std::chrono::high_resolution_clock::now();
		duration = (end - start);
		stop = true;
	}

	// Destructor call displays the end time automatically
	~SmartTimer() {
		if (!stop) {
			end = std::chrono::high_resolution_clock::now();
			duration = (end - start);
		}
		printf("==============================\n%s ended after %.02lf ms\n\n", nameTimer, (double)duration.count() * 1000.0f);
	}
};

/*
Matrix Wrapper Class
	Approach:
		1. I understand that this increases code complexity but having a easy to use wrapper eases up code manipulation
		2. Performance impact is negated or minimized throughout the wrapper.
		3. The wrapper can store size , number of rows and number of columns , I have also exposed mData to the user for easy access.
		4. The wrapper will increase constant memory complexity , but assuming we are not working on a very tight memory constraint , the increas due to padding and extra instructions will be negligible.
	Usage:
		1. Default constructor instantiation gives a blank Matrix wrapper with 0 sized data.
		2. You can then use helper functions to populate the matrix
		3. The Data vector resizes when rows or columns are changed , initialized to 0
		4. You can also instantiate using custom constructor which can create a custom sized ,randomly filled(optional), matrix.
*/
template<typename T>
class Matrix {
private:

	// Using 1-D vector to store matrix for fast accesses
	std::vector<T> mData;
	size_t size = 0, nRows = 0, nColumns = 0;

	// Generates random numbers in given range [0,range] ; Default 255(range of unsigned char)
	void fillRandom(int range = UINT8_MAX) {
		// Give Random Seed using current time
		srand((int)time(0));
		// One-Pass
		for (size_t i = 0; i < size; i++) {
			// Take absolute values to get only positive random values
			mData[i] = abs(rand() % range);
		}
	}

public:

	// Default Constructor
	Matrix() {
		this->nRows = 0;
		this->nColumns = 0;
		size = 0;
		mData.resize(size);
	}

	// Default Constructor , fills m * n matrix with random values
	Matrix(int nRows, int nColumns, bool fillRand = true) {
		if (nRows <= 0 || nColumns <= 0) {
			printf("Invalid Matrix Dimensions\n");
		}
		else {
			this->nRows = nRows;
			this->nColumns = nColumns;
			this->size = nRows * nColumns;
			mData.resize(size);
			if (fillRand) {
				fillRandom();
			}
		}
	}

	// Setters/Getters
	std::vector<T>* data() {
		return &mData;
	}

	const std::vector<T>* data() const {
		return &mData;
	}

	size_t getNRows() {
		return nRows;
	}
	size_t getNColumns() {
		return nColumns;
	}
	size_t getSize() {
		return size;
	}
	void setNRows(size_t nRows) {
		if (nRows <= 0) {
			printf("Invalid Matrix Dimensions\n");
		}
		else {
			this->nRows = nRows;
			this->size = this->nRows * this->nColumns;
			mData.resize(size);
		}
	}
	void setNColumns(size_t nColumns) {
		if (nColumns <= 0) {
			printf("Invalid Matrix Dimensions\n");
		}
		else {
			this->nColumns = nColumns;
			this->size = this->nRows * this->nColumns;
			mData.resize(size);
		}
	}

	// Return Element , Operator [] overload
	T& operator[](int idx) { return mData[idx]; }

	const T& operator[](int idx) const { return mData[idx]; }

	// Pretty Print Matrix (precision set for 16 bit integers)
	void prettyPrint() {
		printf("==================\n");
		for (size_t i = 0; i < nRows; i++)
		{
			printf("|");
			for (size_t j = 0; j < nColumns; j++) {
				printf(" %4d ", mData[(i * nColumns) + j]);
			}
			printf(" |\n");
		}
		printf("==================\n\n");
	}
};

/*
Solution Class
	Approach:
		1. To achieve maximum speed-up , assumed that filter does not change and did some hard-coded optimizations
		2. Used vector class for matrix storage because it manages resizes and insertions efficiently
		3. Convolutions take O(n*m) operations
	Usage:
	1. Instantiate the MatrixConvolution class using a valid matrix (atleast 3,3) as the argument.
	2. Use horizontalConvolution() and verticalConvolution() to calculate results
		-- Min Maxes are calculated after any convolution , default values are 0.
		-- Min-Max Functions are seperate functions which are called at the end of convolutions
	3. Use print functions to print min max and matrices.
*/
class MatrixConvolution {
private:

	Matrix<unsigned char>* M = nullptr;					// Input Matrice
	Matrix<int16_t> dX;
	Matrix<int16_t> dY;
	int16_t dX_min = 0, dX_max = 0, dY_min = 0, dY_max = 0;

	// Calculate Min-Maxes
	void dXminmax() {
		std::vector<int16_t>* temp = dX.data();

		int16_t min = INT16_MAX;
		int16_t max = INT16_MIN;

		for (int i : *temp) {
			if (i < min) { min = i; }
			if (i > max) { max = i; }
		}

		dX_min = min;
		dX_max = max;
	}

	// Calculate Min-Maxes
	void dYminmax() {
		std::vector<int16_t>* temp = dY.data();

		int16_t min = INT16_MAX;
		int16_t max = INT16_MIN;

		for (int i : *temp) {
			if (i < min) { min = i; }
			if (i > max) { max = i; }
		}

		dY_min = min;
		dY_max = max;
	}

public:

	// Default Constructor
	MatrixConvolution() {
		printf("Please supply input M matrix.\n");
	}

	// Default Deconstructor
	~MatrixConvolution() {
	}

	// Custom Constructor
	MatrixConvolution(Matrix<unsigned char>* M) {
		this->M = M;
		printf("Convolution Calculator Instantiated.\n");

		// Uncomment to print input
		//printf("Input Matrix:\n");
		//printM();
	}

	void horizontalConvolution() {
		// Boiler-Plate code
		int curr_col = 0;
		int thres_col = M->getNColumns() - 2;

		if (thres_col <= 0 || M->getSize() < 3) {
			printf("Invalid Matrix Size for Horizontal Convolution.\n");
			return;
		}

		int sizeNRowsOut = M->getNRows();

		// Output vector , resized to save time later
		std::vector<int16_t>* temp = dX.data();
		dX.setNRows(M->getNRows());
		dX.setNColumns(thres_col);
		temp->resize(M->getNRows() * thres_col);

		// Start benchmark timer
		SmartTimer timer("Horizontal Convolution");

		// Nested Loop to fetch elements , O(m*n)
		for (size_t i = 0; i < sizeNRowsOut; i++) {
			while (curr_col < thres_col) {
				int offset = (i * M->getNColumns()) + curr_col;

				// Because our filter is fixed , we can skip one calculation to save time [-1,0,1] , multiply by zero
				uint8_t a1 = ((*M)[offset]);
				uint8_t a2 = ((*M)[offset + 1]);
				uint8_t a3 = ((*M)[offset + 2]);

				int result = a3 - a1;

				//printf("a1 = %d | a2 = %d | a3 = %d | result = %d \n", a1, a2, a3, result);

				// Get current index in output array
				int tempIdx = curr_col + (i * dX.getNColumns());

				// Write to output array
				(*temp)[tempIdx] = result;

				curr_col++;
			}
			curr_col = 0;
		}
		// Stop Benchmark Timer here , display result when exit scope
		timer.stopTimer();
		dXminmax();
	}

	void verticalConvolution() {
		// Boiler-Plate code
		int curr_row = 0;
		int thres_rows = M->getNRows() - 2;

		if (thres_rows <= 0 || M->getSize() < 3) {
			printf("Invalid Matrix Size for Vertical Convolution.\n");
			return;
		}

		int outNColumsn = M->getNColumns();
		// Output vector , resized to save time later
		std::vector<int16_t>* temp = dY.data();
		dY.setNRows(M->getNRows() - 2);
		dY.setNColumns(M->getNColumns());

		//// Start benchmark timer
		SmartTimer timer("Vertical Convolution");

		// Nested Loop to fetch elements , O(m*n)
		for (int i = 0; i < outNColumsn; i++) {
			while (curr_row < thres_rows) {
				// Extract Values
				uint8_t a1 = (*M)[((curr_row + 0) * M->getNColumns()) + i];
				//uint8_t a2 = (*M)[((curr_row + 1) * M->getNColumns()) + i];
				uint8_t a3 = (*M)[((curr_row + 2) * M->getNColumns()) + i];

				int16_t result = a3 - a1;

				//printf("a1 = %d | a2 = %d | a3 = %d | result = %d \n", a1, a2, a3, result);

				// Get output index
				int tempOffset = (curr_row * M->getNColumns()) + i;

				// Write to output
				(*temp)[tempOffset] = result;

				curr_row++;
			}
			curr_row = 0;
		}
		// Stop Benchmark Timer here , display result when exit scope
		timer.stopTimer();
		dYminmax();
	}
	void printM() {
		M->prettyPrint();
	}

	void printdX() {
		dX.prettyPrint();
	}

	void printdY() {
		dY.prettyPrint();
	}
	void printMinMax() {
		printf("Min-Max Values:\n======================\n");
		printf("dXMin = %4d | dXMax = %4d\n\ndYMin = %4d | dYMin = %4d\n", dX_min, dX_max, dY_min, dY_max);
	}
};

int main(int argc, char* argv[]) {
	// Take matrix size from CLI , input format ./<program_name> <Rows> <Columns>
	if (argc != 3) {
		printf("Invalid arguments. Please enter <ROWS> <COLUMNS>.\n");
		return 0;
	}

	int rows = atoi(argv[1]);
	int cols = atoi(argv[2]);

	Matrix<unsigned char> M = Matrix<unsigned char>(rows, cols);
	MatrixConvolution test(&M);

	SmartTimer timer("Whole Convolution.");						//	This time includes all the boiler-plate time too.
	test.horizontalConvolution();
	test.verticalConvolution();
	timer.stopTimer();

	test.printdX();
	test.printdY();

	test.printMinMax();
	return 0;
}
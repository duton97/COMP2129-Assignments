#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#include "matrix.h"

#define CHUNK (g_width/g_nthreads) //This way, it separates each row into a thread. To have a thread for each index, change to g_elements/g_nthreads
#define CHUNK2 (g_elements/g_nthreads) //Split all elements
#define IDX(x, y) ((y) * g_width + (x))

typedef struct {
	size_t id;
	float* result;
	const float* a;
	const float* b;
	float scalar;
	int seed;
} worker_args;

typedef struct {
	size_t id;
	const float* matrix;
	int count;
	float value;
} worker_freq;

static int g_seed = 0;

static ssize_t g_width = 0;
static ssize_t g_height = 0;
static ssize_t g_elements = 0;

static ssize_t g_nthreads = 1;

////////////////////////////////
///     UTILITY FUNCTIONS    ///
////////////////////////////////

/**
 * Returns pseudorandom number determined by the seed.
 */
int fast_rand(void) {

	g_seed = (214013 * g_seed + 2531011);
	return (g_seed >> 16) & 0x7FFF;
}

/**
 * Sets the seed used when generating pseudorandom numbers.
 */
void set_seed(int seed) {

	g_seed = seed;
}

/**
 * Sets the number of threads available.
 */
void set_nthreads(ssize_t count) {

	g_nthreads = count;
}

/**
 * Sets the dimensions of the matrix.
 */
void set_dimensions(ssize_t order) {

	g_width = order;
	g_height = order;

	g_elements = g_width * g_height;
}

/**
 * Displays given matrix.
 */
void display(const float* matrix) {

	for (ssize_t y = 0; y < g_height; y++) {
		for (ssize_t x = 0; x < g_width; x++) {
			if (x > 0) printf(" ");
			printf("%.2f", matrix[y * g_width + x]);
		}

		printf("\n");
	}
}

/**
 * Displays given matrix row.
 */
void display_row(const float* matrix, ssize_t row) {

	for (ssize_t x = 0; x < g_width; x++) {
		if (x > 0) printf(" ");
		printf("%.2f", matrix[row * g_width + x]);
	}

	printf("\n");
}

/**
 * Displays given matrix column.
 */
void display_column(const float* matrix, ssize_t column) {

	for (ssize_t i = 0; i < g_height; i++) {
		printf("%.2f\n", matrix[i * g_width + column]);
	}
}

/**
 * Displays the value stored at the given element index.
 */
void display_element(const float* matrix, ssize_t row, ssize_t column) {

	printf("%.2f\n", matrix[row * g_width + column]);
}

////////////////////////////////
///   MATRIX INITALISATIONS  ///
////////////////////////////////

/**
 * Returns new matrix with all elements set to zero.
 */
float* new_matrix(void) {

	return calloc(g_elements, sizeof(float));
}

void* worker_identity(void* args) {
	worker_args* wargs = (worker_args*) args;
	const size_t start = wargs->id * CHUNK;
	const size_t end = wargs->id == g_nthreads - 1 ? g_width : (wargs->id + 1) * CHUNK;

	for (int i = start; i < end; i++) {
		wargs->result[i*g_width + i] = 1;
	}

	return NULL;
}

/**
 * Returns new identity matrix.
 */
float* identity_matrix(void) {

	float* result = new_matrix();

	worker_args args[g_nthreads]; //Create a struct for each thread
	pthread_t thread_ids[g_nthreads]; //Declare threads

	for (size_t i = 0; i < g_nthreads; i++) {
		args[i] = (worker_args) {
			.id = i,
			.result = result,
		};
	}

	//Launch threads
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_create(&thread_ids[i], NULL, worker_identity, &args[i]);
	}

	//Wait for threads to finish
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_join(thread_ids[i], NULL);
	}
	return result;
}

/**
 * Returns new matrix with elements generated at random using given seed.
 */
float* random_matrix(int seed) {

	float* matrix = new_matrix();

	set_seed(seed);

	for (ssize_t i = 0; i < g_elements; i++) {
		matrix[i] = fast_rand();
	}

	return matrix;
}

void* worker_uniform_matrix(void* args) {
	worker_args* wargs = (worker_args*) args;
	const size_t start = wargs->id * CHUNK2;
	const size_t end = wargs->id == g_nthreads - 1 ? g_elements : (wargs->id + 1) * CHUNK2;

	for (int i = start; i < end; i++) {
		wargs->result[i] = wargs->scalar;
	}

	return NULL;
}

/**
 * Returns new matrix with all elements set to given value.
 */
float* uniform_matrix(float value) {

	float* result = new_matrix();

	worker_args args[g_nthreads]; //Create a struct for each thread
	pthread_t thread_ids[g_nthreads]; //Declare threads

	for (size_t i = 0; i < g_nthreads; i++) {
		args[i] = (worker_args) {
			.id = i,
			.result = result,
			.scalar = value
		};
	}

	//Launch threads
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_create(&thread_ids[i], NULL, worker_uniform_matrix, &args[i]);
	}

	//Wait for threads to finish
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	return result;
}

/**
 * Returns new matrix with elements in sequence from given start and step
 */
float* sequence_matrix(float start, float step) {

	float* result = new_matrix();

	result[0] = start;
	for (int i = 1; i < g_elements; i++) {
		result[i] = result[i-1] + step;
	}

	return result;
}

////////////////////////////////
///     MATRIX OPERATIONS    ///
////////////////////////////////

/**
 * Returns new matrix with elements cloned from given matrix.
 */
float* cloned(const float* matrix) {

	float* result = new_matrix();

	for (ssize_t y = 0; y < g_height; y++) {
		for (ssize_t x = 0; x < g_width; x++) {
			result[y * g_width + x] = matrix[y * g_width + x];
		}
	}

	return result;
}

//Used in command sort
int compare(const void* a, const void* b) {
	const float *ia = (const float *)a; // casting pointer types
  	const float *ib = (const float *)b;
	return *ia - *ib;
}

/**
 * Returns new matrix with elements in ascending order.
 */
float* sorted(const float* matrix) {

	float* result = new_matrix();

	for (int i = 0; i < g_elements; i++) {
		result[i] = matrix[i];
	}

	qsort(result, g_elements, sizeof(float), compare);

	return result;
}

/**
 * Returns new matrix with elements rotated 90 degrees clockwise.
 */
float* rotated(const float* matrix) {

	float* result = new_matrix();

	int decrease = 1; //Used with g_width to modify the index in which it will be placed vertically
	int indexFM = g_width - decrease; //Index on the right column where elements will be stored, from right to left, top to bottom

	//Split array into a 2D array
	for (int i = 0; i < g_width; i++) {
		for (int j = 0; j < g_width; j++) {
			//Insert values from the matrix into the new matrix vertically, starting from right to left
			result[indexFM] = matrix[i*g_width+j];
			indexFM += g_width; //Jump to the next index below (vertical)
		}
		decrease++;
		indexFM = g_width - decrease; //Update index to the next column on the left
	}

	return result;
}

/**
 * Returns new matrix with elements ordered in reverse.
 */
float* reversed(const float* matrix) {

	float* result = new_matrix();

	int j = g_elements - 1;
	for (int i = 0; i < g_elements; i++) {
		result[i] = matrix[j];
		j--;
	}

	return result;
}


/**
 * Returns new transposed matrix.
 */
float* transposed(const float* matrix) {

	float* result = new_matrix();
	//Take columns, insert values as a rows

	int indexFM = 0;

	//Just iterate over each colum
	for (int i = 0; i < g_width; i++) {
		for (int j = 0; j < g_width; j++) {
			result[i*g_width+j] = matrix[indexFM];
			indexFM += g_width; //Jump to the index below it
		}
		indexFM = i + 1;
	}

	return result;
}

void* worker_scalar_add(void* args) {
	worker_args* wargs = (worker_args*) args;
	const size_t start = wargs->id * CHUNK2;
	const size_t end = wargs->id == g_nthreads - 1 ? g_elements : (wargs->id + 1) * CHUNK2;

	for (int i = start; i < end; i++) {
		wargs->result[i] = wargs->a[i] + wargs->scalar;
	}

	return NULL;
}

/**
 * Returns new matrix with scalar added to each element.
 */
float* scalar_add(const float* matrix, float scalar) {
	float* result = new_matrix();

	worker_args args[g_nthreads]; //Create a struct for each thread
	pthread_t thread_ids[g_nthreads]; //Declare threads

	for (size_t i = 0; i < g_nthreads; i++) {
		args[i] = (worker_args) {
			.a = matrix,
			.id = i,
			.result = result,
			.scalar = scalar
		};
	}

	//Launch threads
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_create(&thread_ids[i], NULL, worker_scalar_add, &args[i]);
	}

	//Wait for threads to finish
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	return result;
}

void* worker_scalar_mul(void* args) {
	worker_args* wargs = (worker_args*) args;
	const size_t start = wargs->id * CHUNK2;
	const size_t end = wargs->id == g_nthreads - 1 ? g_elements : (wargs->id + 1) * CHUNK2;

	for (int i = start; i < end; i++) {
		wargs->result[i] = wargs->a[i] * wargs->scalar;
	}

	return NULL;
}

/**
 * Returns new matrix with scalar multiplied to each element.
 */
float* scalar_mul(const float* matrix, float scalar) {

	float* result = new_matrix();

	worker_args args[g_nthreads]; //Create a struct for each thread
	pthread_t thread_ids[g_nthreads]; //Declare threads

	for (size_t i = 0; i < g_nthreads; i++) {
		args[i] = (worker_args) {
			.a = matrix,
			.id = i,
			.result = result,
			.scalar = scalar
		};
	}

	//Launch threads
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_create(&thread_ids[i], NULL, worker_scalar_mul, &args[i]);
	}

	//Wait for threads to finish
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	return result;
}

void* worker_add(void* args) {
	worker_args* wargs = (worker_args*) args;
	const size_t start = wargs->id * CHUNK2;
	const size_t end = wargs->id == g_nthreads - 1 ? g_elements : (wargs->id + 1) * CHUNK2;

	for (int i = start; i < end; i++) {
		wargs->result[i] = wargs->a[i] + wargs->b[i];
	}

	return NULL;
}

/**
 * Returns new matrix that is the result of
 * adding the two given matrices together.
 */
float* matrix_add(const float* matrix_a, const float* matrix_b) {

	float* result = new_matrix();

	worker_args args[g_nthreads]; //Create a struct for each thread
	pthread_t thread_ids[g_nthreads]; //Declare threads

	for (size_t i = 0; i < g_nthreads; i++) {
		args[i] = (worker_args) {
			.a = matrix_a,
			.b = matrix_b,
			.id = i,
			.result = result,
		};
	}

	//Launch threads
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_create(&thread_ids[i], NULL, worker_add, &args[i]);
	}

	//Wait for threads to finish
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	return result;
}

void* worker_multiply(void* args) {
	worker_args* wargs = (worker_args*) args;
	const size_t start = wargs->id * CHUNK2;
	const size_t end = wargs->id == g_nthreads - 1 ? g_elements : (wargs->id + 1) * CHUNK2;
	//printf("%zu %zu\n", start, end);

	for (size_t y = start/g_width; y < end/g_width; y++) {
		for (size_t k = 0; k < g_width; k++) {
			for (size_t x = 0; x < g_width; x++) {
				//printf("%zu\n", x);
				//printf("%f %f\n\n", wargs->a[IDX(k, y)], wargs->b[IDX(x, k)] );
				wargs->result[IDX(x, y)] += wargs->a[IDX(k, y)] * wargs->b[IDX(x, k)];
			}
		}
	}

	return NULL;
}

/**
 * Returns new matrix that is the result of
 * multiplying the two matrices together.
 */
float* matrix_mul(const float* matrix_a, const float* matrix_b) {

	float* result = new_matrix();

	worker_args args[g_nthreads]; //Create a struct for each thread
	pthread_t thread_ids[g_nthreads]; //Declare threads

	for (size_t i = 0; i < g_nthreads; i++) {
		args[i] = (worker_args) {
			.a = matrix_a,
			.b = matrix_b,
			.id = i,
			.result = result,
		};
	}

	//Launch threads
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_create(&thread_ids[i], NULL, worker_multiply, &args[i]);
	}

	//Wait for threads to finish
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	return result;
}

/**
 * Returns new matrix that is the result of
 * powering the given matrix to the exponent.
 */
float* matrix_pow(const float* matrix, int exponent) {

	float* result = new_matrix();
	float* temp;

	//If 0, return a identity matrix
	if (exponent == 0) {
		free(result);
		result = identity_matrix();

	} else if (exponent >= 1) {
		//if exponent equals 1, return same matrix, so store the same values of matrix into result
		//if (exponent == 1) {
			for (int i = 0; i < g_elements; i++) {
				result[i] = matrix[i];
			}
		//}

		//if exponent is equal or higher than 2, multiply matrices
		if (exponent >= 2){
			//Multiply the matrices according to the number of the exponent
			for (int i = 1; i < exponent; i++) {
				temp = matrix_mul(result, matrix); //Temporary matrix to point to the output

				//Store the output into result
				for (int i = 0; i < g_elements; i++) {
					result[i] = temp[i];
				}
				free(temp);
			}
		}
	}

	return result;
}

//Visualise the matrix as a 2D array, row and col from 0 to width-1
double get_value(const float* matrix, int row, int col) {
	//If statements serve to check if the element at given index is out of range (0 to width-1)

	//If the index is otuside on the upper side of the matrix, then increase it by 1, to reach the element below it
	if (row < 0) {
		row++;
	}
	//If the index is outside on the bottom side of the matrix, then decrease it by 1, to reach the element above it
	if (row >= g_width) {
		row--;
	}
	//If the index is outside of the left side of the matrix, then increase it by 1, to reach the element to its right
	if (col < 0) {
		col++;
	}
	//If the index is outside the right side of the matrix, then decrease it by 1, to reach the element to its left
	if (col >= g_width) {
		col--;
	}

	//The new index will be within the range of 0 to width-1
	return matrix[row*g_width + col];
}

void* worker_convo(void* args) {
	worker_args* wargs = (worker_args*) args;
	const size_t start = wargs->id * CHUNK2;
	const size_t end = wargs->id == g_nthreads - 1 ? g_elements : (wargs->id + 1) * CHUNK2;

	int kernelIndex;

	//Iterate over the matrix
	for (int row = start/g_width; row < end/g_width; row++) {
		for (int col = 0; col < g_width; col++) {
			kernelIndex = 0;

			//Iterate over the surrounding elements
			for (int i = row - 1; i <= row + 1; i++) {
				for (int j = col - 1; j <= col + 1; j++) {
					//Add new values
					wargs->result[row*g_width + col] += get_value(wargs->a, i, j) * wargs->b[kernelIndex];
					kernelIndex++;
				}
			}
		}
	}
	return NULL;
}

/**
 * Returns new matrix that is the result of
 * convolving given matrix with a 3x3 kernel matrix.
 */
float* matrix_conv(const float* matrix, const float* kernel) {

	float* result = new_matrix();

	worker_args args[g_nthreads]; //Create a struct for each thread
	pthread_t thread_ids[g_nthreads]; //Declare threads

	for (size_t i = 0; i < g_nthreads; i++) {
		args[i] = (worker_args) {
			.a = matrix,
			.b = kernel,
			.id = i,
			.result = result,
		};
	}

	//Launch threads
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_create(&thread_ids[i], NULL, worker_convo, &args[i]);
	}

	//Wait for threads to finish
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	return result;
}

////////////////////////////////
///       COMPUTATIONS       ///
////////////////////////////////

void* worker_get_sum(void* args) {
	worker_freq* wargs = (worker_freq*) args;
	const size_t start = wargs->id * CHUNK2;
	const size_t end = wargs->id == g_nthreads - 1 ? g_elements : (wargs->id + 1) * CHUNK2;

	for (int i = start; i < end; i++) {
		wargs->value += wargs->matrix[i];
	}

	return NULL;
}

/**
 * Returns the sum of all elements.
 */
float get_sum(const float* matrix) {
	worker_freq args[g_nthreads]; //Create a struct for each thread
	pthread_t thread_ids[g_nthreads]; //Declare threads

	for (size_t i = 0; i < g_nthreads; i++) {
		args[i] = (worker_freq) {
			.id = i,
			.matrix = matrix,
			.value = 0
		};
	}

	//Launch threads
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_create(&thread_ids[i], NULL, worker_get_sum, &args[i]);
	}

	//Wait for threads to finish
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_join(thread_ids[i], NULL);
	}


	double sum = 0;

	for (int i = 0; i < g_nthreads; i++) {
		sum += args[i].value;
	}

	return sum;
}

void* worker_trace(void* args) {
	worker_freq* wargs = (worker_freq*) args;
	const size_t start = wargs->id * CHUNK;
	const size_t end = wargs->id == g_nthreads - 1 ? g_width : (wargs->id + 1) * CHUNK;

	for (int i = start; i < end; i++) {
		wargs->value += wargs->matrix[i*g_width + i];
	}

	return NULL;
}

/**
 * Returns the trace of the matrix.
 */
float get_trace(const float* matrix) {

	worker_freq args[g_nthreads]; //Create a struct for each thread
	pthread_t thread_ids[g_nthreads]; //Declare threads

	for (size_t i = 0; i < g_nthreads; i++) {
		args[i] = (worker_freq) {
			.matrix = matrix,
			.id = i,
			.value = 0
		};
	}

	//Launch threads
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_create(&thread_ids[i], NULL, worker_trace, &args[i]);
	}

	//Wait for threads to finish
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	double trace = 0;

	for (int i = 0; i < g_nthreads; i++) {
		trace += args[i].value;
	}

	return trace;
}

void* worker_min(void* args) {
	worker_freq* wargs = (worker_freq*) args;
	const size_t start = wargs->id * CHUNK2;
	const size_t end = wargs->id == g_nthreads - 1 ? g_elements : (wargs->id + 1) * CHUNK2;

	wargs->value = wargs->matrix[start]; //Varimin to store the min value

	//Compare the first value to the other values in the array
	for (int i = start + 1; i < end; i++) {
		//If min is equal to the next value, store the next value in min
		if (wargs->value == wargs->matrix[i]) {
			wargs->value = wargs->matrix[i];
		}
		//If min is higher than the next value, store the next value in min
		else if (wargs->matrix[i] < wargs->value) {
			wargs->value = wargs->matrix[i];
		}
	}
	return NULL;
}

/**
 * Returns the smallest value in the matrix.
 */
float get_minimum(const float* matrix) {
	worker_freq args[g_nthreads]; //Create a struct for each thread
	pthread_t thread_ids[g_nthreads]; //Declare threads

	for (size_t i = 0; i < g_nthreads; i++) {
		args[i] = (worker_freq) {
			.matrix = matrix,
			.id = i,
		};
	}

	//Launch threads
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_create(&thread_ids[i], NULL, worker_min, &args[i]);
	}

	//Wait for threads to finish
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	float min = args[0].value; //Store first value in the matrix. Variable min to store the lowest value

	//Compare the first value to the other values in the array
	for (int i = 1; i < g_nthreads; i++) {
		//If min is equal to the next value, store the next value in min
		if (min == args[i].value) {
			min = args[i].value;
		}
		//If min is higher than the next value, store the next value in min
		else if (args[i].value < min) {
			min = args[i].value;
		}
	}

	return min;
}

void* worker_max(void* args) {

	worker_freq* wargs = (worker_freq*) args;
	const size_t start = wargs->id * CHUNK2;
	const size_t end = wargs->id == g_nthreads - 1 ? g_elements : (wargs->id + 1) * CHUNK2;

	wargs->value = wargs->matrix[start]; //Varimax to store the maximum value

	//Compare the first value to the other values in the array
	for (int i = start + 1; i < end; i++) {
		//If max is equal to the next value, store the next value in max
		if (wargs->value == wargs->matrix[i]) {
			wargs->value = wargs->matrix[i];
		}
		//If max is higher than the next vale, store the next value in max
		else if (wargs->matrix[i] > wargs->value) {
			wargs->value = wargs->matrix[i];
		}
	}

	return NULL;
}

/**
 * Returns the largest value in the matrix.
 */
float get_maximum(const float* matrix) {
	worker_freq args[g_nthreads]; //Create a struct for each thread
	pthread_t thread_ids[g_nthreads]; //Declare threads

	for (size_t i = 0; i < g_nthreads; i++) {
		args[i] = (worker_freq) {
			.matrix = matrix,
			.id = i,
		};
	}

	//Launch threads
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_create(&thread_ids[i], NULL, worker_max, &args[i]);
	}

	//Wait for threads to finish
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	float max = args[0].value;

	//Compare the first value to the other values in the array
	for (int i = 1; i < g_nthreads; i++) {
		//If max is equal to the next value, store the next value in max
		if (max == args[i].value) {
			max = args[i].value;
		}
		//If max is higher than the next vale, store the next value in max
		else if (args[i].value > max) {
			max = args[i].value;
		}
	}

	return max;
}


//Matrix is the matrix that we want to reduce, index is the index of the top row element we want to ignore and the elements below it, size is size of matrix
float* reduceMatrix(const float* matrix, int index, int size) {
	float* tempMatrix = (float *) malloc(sizeof(float)*(size*size));

	int count = size; //Index of the matrix passed
	int tempIndex = 0; //Index of the new matrix

	//Iterate over row, starting from the second row. Since the first row is not used to calculate the determinant
	for (int i = 1; i < size; i++) {
		//Iterate over the column
		for (int j = 0; j < size; j++) {
			//Check if the element is in the same column of the element at index which we want to ignore.
			//i is used to check the elements below it, index is the column we want to ignore, size to start at the second row
			if (count != size * i + index) {
				//Store the elements we want into the temporary Matrix
				tempMatrix[tempIndex] = matrix[count];
				//printf("%f\n", tempMatrix[tempIndex]);
				tempIndex++;
			}
			count++;
		}
	}

	return tempMatrix;
}

float determinant(const float* matrix, int size) {
	double det = 0;
	float* tempMatrix;

	//base case
	if (size == 2) {
		det = (matrix[0]*matrix[3]) - (matrix[1]*matrix[2]);
		return det;
	}
	//recursive call
	else {
		//Iterate over the elements in the first row, use that element inconjuction with the reduced matrix to calculate the determinant
		for (int i = 0; i < size; i++) {
			//Create matrix, pass the original matrix, i is the element we want to ignore, and size of matrix
			tempMatrix = reduceMatrix(matrix, i, size);

			//To calculate determinant, use the pattern + - + - etc. Even numbers are addition, odd numbers are substraction
			if (i % 2 == 0) {
				det += matrix[i] * determinant(tempMatrix, size-1);
				free(tempMatrix);
			}
			else {
				det -= matrix[i] * determinant(tempMatrix, size-1);
				free(tempMatrix);
			}
		}
	}

	return det;
}


/**
 * Returns the determinant of the matrix.
 */
float get_determinant(const float* matrix) {
	double det = determinant(matrix, g_width);

	return det;
}

void* worker_freq_method(void* args) {
	worker_freq* wargs = (worker_freq*) args;
	const size_t start = wargs->id * CHUNK2;
	const size_t end = wargs->id == g_nthreads - 1 ? g_elements : (wargs->id + 1) * CHUNK2;

	for (int i = start; i < end; i++) {
		if (wargs->matrix[i] == wargs->value) {
			wargs->count++;
		}
	}

	return NULL;
}

/**
 * Returns the frequency of the given value in the matrix.
 */
ssize_t get_frequency(const float* matrix, float value) { //Need to fix
	worker_freq args[g_nthreads]; //Create a struct for each thread
	pthread_t thread_ids[g_nthreads]; //Declare threads

	for (size_t i = 0; i < g_nthreads; i++) {
		args[i] = (worker_freq) {
			.matrix = matrix,
			.id = i,
			.value = value,
			.count = 0
		};
	}

	//Launch threads
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_create(&thread_ids[i], NULL, worker_freq_method, &args[i]);
	}

	//Wait for threads to finish
	for (size_t i = 0; i < g_nthreads; i++) {
		pthread_join(thread_ids[i], NULL);
	}

	int count = 0;
	// Calculate total count
	for (size_t i = 0; i < g_nthreads; i++) {
		count += args[i].count;
	}

	return count;
}

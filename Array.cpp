#include <iostream>

#include "Array.h"

using namespace std;

/// <summary>
/// Allocates a 2D array for int type and initializes all elements to zero.
/// </summary>
/// <param name="rows">Number of rows in the array</param>
/// <param name="cols">Number of columns in the array</param>
/// <returns>Pointer to the allocated 2D array (int) </returns>
int** allocate2DArray(int rows, int cols) {
    int** array = new int* [rows];
    if(array == NULL){
        cout << "Allocation failed!\n";
        exit(1);
    }
    for (int i = 0; i < rows; ++i) {
        array[i] = new int[cols];
    }

    // Return to zero
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = 0;
        }
    }
    return array;
}

/// <summary>
/// Frees the memory allocated for a 2D array for int type.
/// </summary>
/// <param name="arr">Pointer to the 2D array</param>
/// <param name="rows">Number of rows in the array</param>
void free2DArray(int** arr, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

double** allocate2DArray_d(int rows, int cols) {
    double** matrix = new double* [rows];
    if (matrix == NULL) {
        cout << "Allocation failed!\n";
        exit(1);
    }
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[cols];
    }

    // return to zero
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

void free2DArray_d(double** arr, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

float** allocate2DArray_f(int rows, int cols) {
    float** matrix = new float* [rows];
    if (matrix == NULL) {
        cout << "Allocation failed!\n";
        exit(1);
    }
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new float[cols];
    }

    // return to zero
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

void free2DArray_f(float** arr, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}
/*
void free2D_dcomplex(dcomplex** arr, int rows){
    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);
}
*/



double* linspace(double start, double over, int N){
    double *result = (double *)calloc(N, sizeof(double));
    double step = (over - start) / (N - 1);

    for(int i=0;i<N;i++){
        result[i] = start + i * step;
    }

    return result;
}


int** constant_2Darrayd(int height, int width, int val){
    int **result = allocate2DArray(height, width);
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            result[j][i] = val;
        }
    }

    return result;
}

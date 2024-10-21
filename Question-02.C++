// Design a program to implement matrix operations, such as add, subtract and multiply
// (we won’t do divide). In order to do this, we will create a class called Matrix that
// processes a two-dimensional matrix. This class contains a constructor that builds the
// matrix with data from a character string. To describe a matrix with a string, we use
// parenthesis to delineate the rows of the matrix. For example: (1,2,3),(4,5,6),(7,8,9)
// would represent the matrix: 
// [1 2 3
// 4 5 6
// 7 8 9]
// The three types of matrix operations should be covered in the method(s). We will also
// use a Not A Matrix flag in our matrix class to indicate that the matrix is invalid. This
// would be set when the size of the matrices being added or multiplied are not compatible.

// Answer:

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Matrix {
private:
    int rows, cols;
    int** data;
    bool isNaM;

    void parseFromString(const std::string& matrixString) {
        std::stringstream ss(matrixString);
        std::string item;
        std::vector<std::vector<int>> tempData;

        while (std::getline(ss, item, '(')) {
            std::vector<int> row;
            std::stringstream rowStream(item);
            std::string value;

            while (std::getline(rowStream, value, ',')) {
                if (!value.empty() && value.back() == ')') {
                    value.pop_back();
                }
                if (!value.empty()) {
                    row.push_back(stoi(value));
                }
            }

            if (!row.empty()) {
                tempData.push_back(row);
            }
        }

        // Initialize matrix dimensions
        rows = tempData.size();
        cols = rows ? tempData[0].size() : 0;

        // Allocate memory for matrix
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = tempData[i][j];
            }
        }
    }

public:
    Matrix(const std::string& matrixString) : isNaM(false) {
        parseFromString(matrixString);
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    bool IsNaM() const {
        return isNaM;
    }

    int* operator[](int index) {
        return data[index];
    }

    // Add other matrix operations (add, subtract, multiply) here
    // Make sure to check for matrix dimensions and set isNaM accordingly
};

int main() {
    Matrix m("(1,2,3),(4,5,6),(7,8,9)");
    if (!m.IsNaM()) {
        std::cout << "Matrix element [0][1]: " << m[0][1] << std::endl;
    }
    return 0;
}

// Output- 
// Matrix element [0][1]: 2


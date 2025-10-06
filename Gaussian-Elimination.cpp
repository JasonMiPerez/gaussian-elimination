// Jason M. Perez

// This program allows the user to input an n x m matrix of their chosen row and column size that represents a system of linear equations.
// The program will then solve the system of linear equations via Guassian Elimination by transforming the matrix into reduced row echelon
// form. The program then allows the user to see the solutions for the program, see the intermediary steps for solving the system
// of linear equations, and see the rank of the matrix.

#include <iostream>
#include <vector>
#include <math.h>
#include <float.h>
using namespace std;


// This function stores each step for the calculations done on the matrix in the "third-dimension" 
// (matrix[first-dimension][second-dimension][third-dimension]) of the tensor (three-dimensional array).
// NOTE: All calculations are done and temporarly stored in the first entry of the "thrid-dimension"
// (matrix[first-dimension][second-dimension][0]). All other steps are stored in all the other entires in the "third-dimension" of the
// tensor (When: third-dimension > 0).
void storeSteps(int equations, int variables, int& resize, vector<vector<vector<double>>>& matrix){

    // Checks to see if the matrix has changed from the previous operation done on it.
    bool matrixDifferent = false;
    for(int i = 0; i < equations; ++i){
        for(int j = 0; j < variables + 1; ++j){
            if(matrix[i][j][resize - 1] != matrix[i][j][0]){
                matrixDifferent = true;
            }
        }
    }

    // If the matrix has changed, increases the size of the "third-dimension" of the tensor by 1 and store the new matrix there.
    if((matrixDifferent == true)){
        ++resize;
        for(int i = 0; i < equations; ++i){
            for(int j = 0; j < variables + 1; ++j){
                matrix[i][j].resize(resize);
            }
        }
        for(int i = 0; i < equations; ++i){
            for(int j = 0; j < variables + 1; ++j){
                matrix[i][j][resize - 1] = matrix[i][j][0];
            }
        }
    }
}

// This function resets all the entires of the boolean vector "done" to false.
void resetBool(int equations, vector<bool>& done){
    for(int i = 0; i < equations; ++i){
        done[i] = false;
    }
}

// This function prints out one of the entires of the "third-dimension" of the tensor to the terminal. In other words, prints out a chosen
// step for the calculations of the matrix that was stored in an entry in the "third-dimension" of the tensor.
// NOTE: When the entry for the "third-dimension" is equal to zero (matrix[first-dimension][second-dimension][0]), prints out the version
// of the matrix that has had the most recent operation done on it.
void displayMatrix(int equations, int variables, int step, vector<vector<vector<double>>>& matrix){
    for(int i = 0; i < equations; ++i){
        for(int j = 0; j < variables + 1; ++j){
            cout << matrix[i][j][step] << " ";        
        }
        cout << endl;
    }
}

int main(){

    int equations, variables, checkint, step, action, rank = 0, countNonZeros = 0, zeroRemainder = 1, resize = 2;
    double swap, divisor, gcd, smallestEntry = DBL_MAX, rowswap = 0;
    bool noSolutions = false;

    // User chooses row and column size of matrix.
    cout << "Enter the number of equations for the system of equations: ";
    cin >> equations;
    cout << "Enter the number of variables for the system of equations: ";
    cin >> variables;
    cout << "-----------------------------------------------------------" << endl;
    cout << endl;
    cout << "Enter the values for the entries of the matrix: " << endl;
    cout << endl;

    // Note, "matrix" is initilized with 2 entries for the "third-dimension" since resize = 2.
    vector<vector<vector<double>>> matrix(equations, vector<vector<double>>(variables + 1, vector<double>(resize)));
    vector<bool> done(equations, false);

    // User inputs values for matrix.
    for(int i = 0; i < equations; ++i){
        for(int j = 0; j < variables + 1; ++j){
            cin >> matrix[i][j][0];
        }
    }

    // Stores the matrix the user inputed into the second entry of the "third-dimension" of the tensor "matrix".
    // (Stores it in matrix[first-dimension][second-dimension][1])
    for(int i = 0; i < equations; ++i){
        for(int j = 0; j < variables + 1; ++j){
            matrix[i][j][resize - 1] = matrix[i][j][0];
        }
    }

    // From this point forward, the function storeSteps will be used to store the steps for solving the system of linear equations in the
    // entries of the "third-dimension" of the tensor "matrix".

    // Entire for loop checks to see one by one if there is non-zero entries in the rows of the matrix, swaps those rows with the one on the 
    // top, multiplies the first row by the entries located where it found the non-zero entry in, multiplies the row it just swapped with 
    // by the entry located in the first row and the column where it found the non-zero entry in, subtracts the rows on the bottom with the
    // row on the top, and then divides each row by the greatest common divisor in that row.
    for(int i = 0; i < equations; ++i){
        for(int j = 0; j < variables; ++j){

            // Checks to see if entry is non-zero and if calculations have already been done for that row.
            if((matrix[i][j][0] != 0) && (done[i] != true)){

                // Swap row with non-zero entry with one on the top.
                for(int k = 0; k < variables + 1; ++k){
                    swap = matrix[i][k][0];
                    matrix[i][k][0] = matrix[0][k][0];
                    matrix[0][k][0] = swap;
                }
                storeSteps(equations, variables, resize, matrix);

                // Multiples and substracts rows appropriatly as stated before.
                for(int k = 1; k < equations; ++k){

                    double multiplier1 = matrix[0][j][0], multiplier2 = matrix[k][j][0];
                    
                    // Checks to see if entry in the column where the non-zero entry was found before the rows were swapped is zero.
                    if(multiplier2 != 0){

                        // Multiples the first row and the rows below it appropriatly as stated previously.
                        for(int r = 0; r < variables + 1; ++r){
                            matrix[0][r][0] = matrix[0][r][0] * multiplier2;
                            matrix[k][r][0] = matrix[k][r][0] * multiplier1;
                        }
                        storeSteps(equations, variables, resize, matrix);

                        // Subtracts the rows below the first row by the first row.
                        for(int r = 0; r < variables + 1; ++r){
                            matrix[k][r][0] = matrix[k][r][0] - matrix[0][r][0];
                        }
                        storeSteps(equations, variables, resize, matrix);

                        // Divides each row by it's greatest common divisor.
                        for(int a = 0; a < equations; ++a){
                            for(int b = 0; b < variables + 1; ++b){
                                // Finds smallest entry in row.
                                if((matrix[a][b][0] != 0) && (fabs(matrix[a][b][0]) < smallestEntry)){
                                    smallestEntry = fabs(matrix[a][b][0]);
                                }
                            }
                            // Set "gcd" equal to smallest entry in row.
                            gcd = smallestEntry;
                            // Check to see if each entry in the row has a remainder of 0 if they're divided by "gcd" and "gcd" does not
                            // equal 1. If not, decrements "gcd" by 1.
                            while((zeroRemainder != 0) && (gcd != 1)){
                                zeroRemainder = 0;
                                for(int b = 0; b < variables + 1; ++b){
                                    checkint = matrix[a][b][0]/gcd;
                                    if(checkint != matrix[a][b][0]/gcd){
                                        ++zeroRemainder;
                                    }
                                }
                                if(zeroRemainder != 0){
                                    --gcd;
                                }
                            }
                            // "gcd" is now the greatest common divisor in the row. Divide the row by "gcd".
                            for(int b = 0; b < variables + 1; ++b){
                                matrix[a][b][0] = matrix[a][b][0]/gcd;
                            }
                            // Reset values for "smallestEntry" and "zeroRemainder".
                            smallestEntry = DBL_MAX;
                            zeroRemainder = 1;
                            storeSteps(equations, variables, resize, matrix);

                        }

                    }

                }

                done[i] = true;

            }
        }
    }

    resetBool(equations, done);

    // Divides each row to produce leading ones.
    for(int i = 0; i < equations; ++i){
        for(int j = 0; j < variables; ++j){
            // Finds first non-zero entry in row, skips if statment if row as already been computed.
            if((matrix[i][j][0] != 0) && (done[i] == false)){
                divisor = matrix[i][j][0];
                // Divides entire row by first non-zero entry.
                for(int k = 0; k < variables + 1; ++k){
                    matrix[i][k][0] = matrix[i][k][0] / divisor;
                }
            done[i] = true;
            }
            storeSteps(equations, variables, resize, matrix);
        }
    }

    resetBool(equations, done);

    // Swaps rows until leading ones on the top are to the left of all leading ones below it.
    for(int i = 0; i < variables; ++i){
        for(int j = 0; j < equations; ++j){
            // Checks each column for first entry that is equal to 1 and skips column if already checked once before.
            if((matrix[j][i][0] == 1) && (done[j] == false)){
                // Swaps row such that all leading ones in the row above it are to the left of the leading one in that row, and all leading
                // ones below it are to the right of the leading one in that row.
                for(int k = 0; k < variables + 1; ++k){
                    swap = matrix[j][k][0];
                    matrix[j][k][0] = matrix[rowswap][k][0];
                    matrix[rowswap][k][0] = swap;
                }
                storeSteps(equations, variables, resize, matrix);
                rowswap++;
                done[j] = true;
            }
        }
    }

    cout << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << endl;
    cout << "This is the matrix in reduced row echelon form: " << endl;
    cout << endl;
    displayMatrix(equations, variables, 0, matrix);
    cout << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << endl;
    cout << "Press 0 if you want to see the solution(s)," << endl << "press 1 if you want to see the previous steps," << endl
    << "press 2 if you want to see the rank of the matrix," << endl << "press any other button to exit the program." << endl;
    cout << endl;
    cout << "-----------------------------------------------------------" << endl;
    cout << endl;

    // Lets user press 0 to see solutions for the system of linear equations, 1 to see intermediate steps of solving system of linear 
    // equations, and 2 to see rank of matrix. Lets user press any other button to exit out of program.
    while(cin >> action){

        cout << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << endl;

        // Shows solution of system of linear equations.
        if(action == 0){
            for(int i = 0; i < equations; ++i){
                for(int j = 0; j < variables + 1; ++j){
                    // Counts number of non-zero entries in row.
                    if (matrix[i][j][0] != 0){
                        countNonZeros += 1;
                    }
                }
                // If all coefficents are zero but the constant is non-zero in the row, prints out that there are no solutions to the system.
                if(countNonZeros == 1 && matrix[i][variables][0] != 0){
                    cout << "This system of equations has no solutions!" << endl;
                    cout << endl;
                    noSolutions = true;
                    break;
                }
                countNonZeros = 0;
            }
            // If there are no solutions break out of for loop.
            for(int i = 0; i < equations; ++i){
                if(noSolutions == true){
                    break;
                }
            // Counts number of non-zero entries in row again.
            for(int k = 0; k < variables + 1; ++k){
                if(matrix[i][k][0] != 0){
                    countNonZeros += 1;
                }
            }
            // Prints out solutions if they are unique or infinite.
            if(countNonZeros != 0){
                for(int j = 0; j < variables + 1; ++j){
                    if(matrix[i][j][0] == 0 && j != variables){
                        continue;
                    }else if(countNonZeros == 1){
                        cout << "= " << matrix[i][j][0];
                    }else if(countNonZeros == 2){
                        cout << matrix[i][j][0] << "x_" << j + 1 << " ";
                    }else{
                        cout << matrix[i][j][0] << "x_" << j + 1 << " + ";
                    }
                    --countNonZeros;
                }
            }
            cout << endl;
            countNonZeros = 0;
            }
        // Shows user previous steps to solving system of linear equations.
        }else if(action == 1){
            cout << "Enter the step you want to look at or large number to escape (entering non-numbers will exit the entire program): ";
            // User inputs what step they want to see. If they enter a step that doesn't exist they exit out of the loop so that they can
            // pick another action. Otherwise, they keep entering in steps.
            while(true){
                cin >> step;
                if(step >= resize || cin.fail()){
                    cout << endl;
                    break;
                }
                cout << endl;
                cout << "Step " << step << ")" << endl;
                cout << endl;
                // Prints out step.
                displayMatrix(equations, variables, step, matrix);
                cout << endl;
                cout << "Enter the step you want to look at or large number to escape (entering non-numbers will exit the entire program): ";
            }
        // Prints out the rank of the matrix.
        }else if(action == 2){
            for(int i = 0; i < equations; ++i){
                for(int j = 0; j < variables; ++j){
                    // Counts number of leading ones. If leading one found, breaks out of first loop.
                    if(matrix[i][j][0] == 1){
                        ++rank;
                        break;
                    }
                }
            }
            cout << "This is the rank of the matrix: " << rank << endl;
            cout << endl;
            // Reset rank to 0.
            rank = 0;
        }

        cout << "-----------------------------------------------------------" << endl;
        cout << endl;
        cout << "Press 0 if you want to see the solution(s)," << endl << "press 1 if you want to see the previous steps," << endl
        << "press 2 if you want to see the rank of the matrix," << endl << "press any other button to exit the program." << endl;
        cout << endl;
        cout << "-----------------------------------------------------------" << endl;
        cout << endl;

    }

    return 0;

}
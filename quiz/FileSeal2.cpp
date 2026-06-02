/*
 * File: elephant_seal_average.cpp
 * Author: Your Name
 * Date: June 2026
 *
 * Description:
 * This program reads elephant seal weights from a data file,
 * stores the values in an array, and calculates the average
 * weight of the elephant seals. The program demonstrates
 * encapsulation through the ElephantSealData class and uses
 * file input to process the dataset.
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
 * Class: ElephantSealData
 *
 * Purpose:
 * Stores elephant seal weights and provides functionality
 * to read data from a file and compute the average weight.
 */
class ElephantSealData {
private:
    static const int MAX_SIZE = 10000;
    int weights[MAX_SIZE];
    int count;

public:
    /*
     * Constructor
     *
     * Initializes the object with zero records.
     */
    ElephantSealData() {
        count = 0;
    }

    /*
     * Function: loadData
     *
     * Purpose:
     * Reads integer weights from a file and stores them
     * in the weights array.
     *
     * Input:
     *   filename - name of the input file
     *
     * Output:
     *   Populates the weights array and count.
     *
     * Returns:
     *   true if file was successfully opened,
     *   false otherwise.
     */
    bool loadData(const string& filename) {
        ifstream inputFile(filename);

        if (!inputFile) {
            return false;
        }

        int weight;

        while (inputFile >> weight && count < MAX_SIZE) {
            weights[count] = weight;
            count++;
        }

        inputFile.close();
        return true;
    }

    /*
     * Function: calculateAverage
     *
     * Purpose:
     * Computes the average elephant seal weight.
     *
     * Input:
     *   None
     *
     * Output:
     *   None
     *
     * Returns:
     *   Average weight as a double.
     */
    double calculateAverage() const {
        if (count == 0) {
            return 0.0;
        }

        long long sum = 0;

        for (int i = 0; i < count; i++) {
            sum += weights[i];
        }

        return static_cast<double>(sum) / count;
    }

    /*
     * Function: getCount
     *
     * Purpose:
     * Returns the number of weights stored.
     *
     * Input:
     *   None
     *
     * Output:
     *   None
     *
     * Returns:
     *   Number of elephant seal records.
     */
    int getCount() const {
        return count;
    }
};

/*
 * Function: main
 *
 * Purpose:
 * Creates an ElephantSealData object, loads data from
 * a file, computes the average weight, and displays
 * the results.
 *
 * Input:
 *   elephant_seal_data.txt
 *
 * Output:
 *   Number of records and average weight.
 *
 * Returns:
 *   0 on successful execution.
 */
int main() {
    ElephantSealData seals;

    if (!seals.loadData("elephant_seal_data.txt")) {
        cout << "Error: Unable to open file." << endl;
        return 1;
    }

    cout << "Number of elephant seals: "
         << seals.getCount() << endl;

    cout << "Average weight: "
         << seals.calculateAverage() << endl;

    return 0;
}
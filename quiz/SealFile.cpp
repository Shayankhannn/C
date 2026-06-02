#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream inputFile("elephant_seal_data.txt");

    if (!inputFile) {
        cout << "Error: Unable to open file." << endl;
        return 1;
    }

    int weight;
    long long sum = 0;
    int count = 0;

    while (inputFile >> weight) {
        sum += weight;
        count++;
    }

    inputFile.close();

    if (count == 0) {
        cout << "No data found in file." << endl;
        return 1;
    }

    double average = static_cast<double>(sum) / count;

    cout << "Number of elephant seals: " << count << endl;
    cout << "Average weight: " << average << endl;

    return 0;
}
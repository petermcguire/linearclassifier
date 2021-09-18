#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>
#include <math.h>
using namespace std;

double predict(double *row, uint8_t rowLen, double *coefs)
{
    double yhat = coefs[0];

    for (uint8_t i = 0; i < (rowLen - 1); i++)
    {
        yhat += coefs[i + 1] * row[i];
    }

    return 1.0 / (1.0 + exp(-yhat));
}

vector<vector<float> > minmax(vector<vector<float> > &data) {
    vector<vector<float> > _minmax;
    vector<float> col;
    vector<vector<float> >::iterator it;
    int i;

    for (i = 0; i < (data[0].size() - 1); i++) {
        for (it = data.begin(); it != data.end(); it++) {
            col.push_back((*it)[i]);
        }
        vector<float> entry;
        entry.push_back(*min_element(col.begin(), col.end()));
        entry.push_back(*max_element(col.begin(), col.end()));
        _minmax.push_back(entry);
        col.clear();
    }
    return _minmax;
}

void normalize(vector<vector<float> > &data, vector<vector<float> > &minmax) {
    for (vector<vector<float> >::iterator it = data.begin() ; it != data.end(); ++it) {
        for (int i = 0; i < (it->size()-1); i++) {
            (*it)[i] = ((*it)[i] - minmax[i][0]) / (minmax[i][1] - minmax[i][0]);
        }
    }
}

vector<vector<float> > openCSV(string fileName)
{
    ifstream csvFile;
    string l;
    string v;
    istringstream iss;
    vector<float> csvLine;
    vector<vector<float> > csv;

    csvFile.open(fileName, ios::in);
    if (csvFile.fail())
    {
        cerr << "Failed to open file " << fileName << ": " << strerror(errno) << endl;
        return csv;
    }

    while (!csvFile.eof())
    {
        getline(csvFile, l);
        iss.str(l);
        while (!iss.eof()) {
            getline(iss, v, ',');
            csvLine.push_back(stof(v));
        }
        csv.push_back(csvLine);
        csvLine.clear();
        iss.clear();
    }
    csvFile.close();

    return csv;
}

int main()
{
    vector<vector<float> > csv, _minmax;
    // double yhat;
    // uint8_t rowLen = 3;
    // double dataset[10][3] = {
    //     {2.7810836, 2.550537003, 0},
    //     {1.465489372, 2.362125076, 0},
    //     {3.396561688, 4.400293529, 0},
    //     {1.38807019, 1.850220317, 0},
    //     {3.06407232, 3.005305973, 0},
    //     {7.627531214, 2.759262235, 1},
    //     {5.332441248, 2.088626775, 1},
    //     {6.922596716, 1.77106367, 1},
    //     {8.675418651, -0.242068655, 1},
    //     {7.673756466, 3.508563011, 1}};
    // double coef[3] = {-0.406605464,
    //                   0.852573316,
    //                   -1.104746259};

    // for (uint8_t i = 0; i < 10; i++)
    // {
    //     yhat = predict(dataset[i], rowLen, coef);
    //     cout << "\nExpected=" << dataset[i][rowLen - 1] << ", Predicted=" << yhat << " [" << round(yhat) << "]\n";
    // }

    csv = openCSV("../test.csv");

    for (vector<vector<float> >::iterator it = csv.begin() ; it != csv.end(); ++it) {
        for (vector<float>::iterator _it = it->begin(); _it != it->end(); ++_it) {
            cout << *_it << " ";
        }
        cout << endl;
    }

    _minmax = minmax(csv);
    normalize(csv, _minmax);

    cout << endl;

    for (vector<vector<float> >::iterator it = _minmax.begin() ; it != _minmax.end(); ++it) {
        for (vector<float>::iterator _it = it->begin(); _it != it->end(); ++_it) {
            cout << *_it << " ";
        }
        cout << endl;
    }

    cout << endl;

    for (vector<vector<float> >::iterator it = csv.begin() ; it != csv.end(); ++it) {
        for (vector<float>::iterator _it = it->begin(); _it != it->end(); ++_it) {
            cout << *_it << " ";
        }
        cout << endl;
    }

    return 0;
}
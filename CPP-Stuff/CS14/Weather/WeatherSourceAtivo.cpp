/*header*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MONTHS_SIZE = 12;
const string MONTHS[MONTHS_SIZE] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

struct weatherData
{
    string month;
    float rain;
    float highTemp;
    float lowTemp;
    float avgTemp;
};

void InputValues(ifstream& fin, weatherData locationData[]);
void CalculationLoop(ostream& out, const string location, weatherData locationData[], double& totalRain, double& totalAvgTemp, 
                     int& locMost, int& locLeast);
void OutputStats(ostream& out, weatherData locationData[], const string location);

int main()
{
    ifstream fin;
    ofstream fout;
    string location;
    weatherData locationData[MONTHS_SIZE];

    fin.open("WeatherData.txt");
    if(!fin.is_open())
    {
        cout << "Error: Could not open WeatherData.txt";
        return 1;
    }

    fout.open("AtivoWeatherResults.txt");
    if(!fout.is_open())
    {
        cout << "Error: Could not open AtivoWeatherResults.txt";
        return 1;
    }

    while(!fin.eof())
    {
        getline(fin, location, '\r');
        InputValues(fin, locationData);

        if(location != "\n")
        {
            OutputStats(fout, locationData, location);
            OutputStats(cout, locationData, location);    
        }
    }

    fin.close();
    fout.close();

    return 0;
}

void InputValues(ifstream& fin, weatherData locationData[])
{
    for(int i = 0; i < MONTHS_SIZE; i++)
    {
        locationData[i].month = MONTHS[i];
        fin >> locationData[i].rain >> locationData[i].highTemp >> locationData[i].lowTemp >> locationData[i].avgTemp;
    }

    fin.ignore(1);
}

void CalculationLoop(ostream& out, const string location, weatherData locationData[], double& totalRain, double& totalAvgTemp, 
                     int& locMost, int& locLeast)
{
    out << fixed << setprecision(2) << right;
    out << location << " Statistics\n";
    out << "Month" << setw(7) << "Rain" << setw(10) << "Hi Temp" << setw(11) << "Low Temp" << setw(12) << "Avg Temp\n";

    for(int i = 0; i < MONTHS_SIZE; i++)
    {
        out << locationData[i].month << setw(9) << locationData[i].rain << setw(10) 
            << locationData[i].highTemp << setw(11) << locationData[i].lowTemp << setw(11) << locationData[i].avgTemp << "\n";

        totalRain += locationData[i].rain;
        totalAvgTemp += locationData[i].avgTemp;

        if(locationData[i].highTemp > locationData[locMost].highTemp) {locMost = i;}
        if(locationData[i].lowTemp < locationData[locLeast].lowTemp) {locLeast = i;}
    }
}

void OutputStats(ostream& out, weatherData locationData[], const string location)
{
    double totalRain = 0, totalAvgTemp = 0;
    int locMost = 0, locLeast = 0;
    CalculationLoop(out, location, locationData, totalRain, totalAvgTemp, locMost, locLeast);

    out << "\nTotal rainfall for year: " << totalRain << " inches";
    out << "\nAverage rainfall per month: " << totalRain / MONTHS_SIZE << " inches";
    out << "\nThe highest temperature of " << locationData[locMost].highTemp 
        << " degrees F occurred in " << MONTHS[locMost] << '.';
    out << "\nThe lowest temperature of " << locationData[locLeast].lowTemp 
        << " degrees F occured in " << MONTHS[locLeast] << '.';
    out << "\nThe average annual temperature for this locality is " << totalAvgTemp / MONTHS_SIZE << " degrees F.\n\n";
}
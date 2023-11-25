#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>
#include <fstream>
#include <map>

using namespace std;

void write_to_file(map<string, int> &data, string fileName)
{
    // Declare an output file stream object
    ofstream outfile;

    // Open the file "pomodoro.txt" for writing
    outfile.open(fileName);

    // Check if the file is successfully opened
    if (outfile.is_open())
    {
        // Use a for loop to write the property keys and values to the file
        for (auto p : data)
        {
            outfile << p.first << "=" << p.second << endl;
        }

        // Close the file
        outfile.close();
    }
    else
    {
        // Display an error message if the file cannot be opened
        cout << "Unable to open the file. Creating it" << endl;
    }
}

map<string, int> read_from_file(string fileName)
{
    // Open the file "pomodoro.txt" for reading, create if it does not exist
    fstream infile(fileName,  fstream::in | fstream::out | fstream::trunc);
    
    // infile.open(fileName);
    // Declare a map variable to store the property keys and values
    map<string, int> properties;
    // Check if the file is successfully opened
    if (infile.is_open())
    {

        // Declare a string variable to store each line
        string line;

        // Use a while loop to read the file line by line
        while (getline(infile, line))
        {
            // Split the line by the equal sign
            size_t pos = line.find('=');

            // Check if the equal sign is found
            if (pos != string::npos)
            {
                // Extract the property key and value
                string key = line.substr(0, pos);
                int value = stoi(line.substr(pos + 1));

                // Insert the key and value pair into the map
                properties.insert({key, value});
            }
        }
        // Close the file
        infile.close();
    }
    else
    {
        // Display an error message if the file cannot be opened
        cout << "Unable to open the file." << endl;
    }
    return properties;
}
int main()
{
    string fileName = "pomodoro.txt";
    map<string, int> properties = read_from_file(fileName);

    // Output the property keys and values to the console
    for (auto p : properties)
    {
        cout << p.first << " = " << p.second << endl;
    }

    // Update the property values
    properties["totalWorkDuration"] = 2500; // Change this to your desired value
    properties["totalBreakDuration"] = 550; // Change this to your desired value

    // Call the write to file function
    write_to_file(properties, fileName);

    return 0;
}
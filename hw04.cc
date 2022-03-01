/**
 *File: hw04.cc
 *Author: Mila Gmerek
 *Date: 2/26/2022
 *Brief: Program that takes zipcodes from a file and returns barcodes to a different file.
 *
 */

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

string getDigitCode(char digit); // required function that returns a barcode for a single digit

int getCheckDigitValue(int sum); // required function that returns the check digit

int charToInteger(char digit); // function that converts character to digit

char integerToChar(int digit); // function that converts integer to character

bool isValid(string zipcode); // required function that checks validity of zipcode

int main()
{
    string zipcode;
    string barcode = "";
    string barSegment;
    string zipChoice;
    char currentNumber;
    int sum(0);
    int checkDigit;
    char checkDigitChar;
    string filename; // input file
    ifstream inStream;
    ofstream outStream;
    string filename2; // output file

    cout << "Enter input file name: " << endl;
    cin >> filename;
    inStream.open(filename); // opens file to pull zipcodes from
    if (inStream.fail()) // incase file fails to open
    {
        cout << "Error: failed to open file. " << endl;
        exit(0);
    }

    while (inStream >> zipcode) // goes through loop as long as it reads zipcodes
    {
    
        isValid(zipcode); // checks for validity 

        barcode = "|"; // the long bar at begining
        checkDigit = 0;
        sum = 0;

        for (int i = 0; i < 5; i++) // for each character of the input
        {
            currentNumber = zipcode.at(i);
            barSegment = getDigitCode(currentNumber); // program returns bar segment for the current number
            barcode += " " + barSegment;              // new barcode each time
            sum += charToInteger(currentNumber);
        }

        checkDigit = getCheckDigitValue(sum);
        checkDigitChar = integerToChar(checkDigit);
        barcode += " " + getDigitCode(checkDigitChar);

        barcode += " |"; // long bar at end
        cout << "Enter output file name: " << endl;
        cin >> filename2; 
        outStream.open(filename2); // opens file to output barcodes in
        outStream << "Code: " << barcode << endl;
    }
    inStream.close();
    outStream.close();
    cout << "Done. Your barcodes are in " << filename2 << endl; // lets user know it was completed successfully 
    return 0;
}

string getDigitCode(char digit) // function that returns bar segment for a digit
{
    string barSegment;

    if (digit == '1')
    {
        barSegment = ":::||";
    }
    else if (digit == '2')
    {
        barSegment = "::|:|";
    }
    else if (digit == '3')
    {
        barSegment = "::||:";
    }
    else if (digit == '4')
    {
        barSegment = ":|::|";
    }
    else if (digit == '5')
    {
        barSegment = ":|:|:";
    }
    else if (digit == '6')
    {
        barSegment = ":||::";
    }
    else if (digit == '7')
    {
        barSegment = "|:::|";
    }
    else if (digit == '8')
    {
        barSegment = "|::|:";
    }
    else if (digit == '9')
    {
        barSegment = "|:|::";
    }
    else if (digit == '0')
    {
        barSegment = "||:::";
    }

    return barSegment; // returns bar segment
}

int getCheckDigitValue(int sum) // adds check digit so that the zipcode is divisible by 10
{
    int remainder = sum % 10;
    return (10 - remainder);
}

int charToInteger(char digit) // converts character to integer
{
    int number;

    if (digit == '1')
    {
        number = 1;
    }
    else if (digit == '2')
    {
        number = 2;
    }
    else if (digit == '3')
    {
        number = 3;
    }
    else if (digit == '4')
    {
        number = 4;
    }
    else if (digit == '5')
    {
        number = 5;
    }
    else if (digit == '6')
    {
        number = 6;
    }
    else if (digit == '7')
    {
        number = 7;
    }
    else if (digit == '8')
    {
        number = 8;
    }
    else if (digit == '9')
    {
        number = 9;
    }
    else if (digit == '0')
    {
        number = 10;
    }

    return number;
}

char integerToChar(int digit) // converts integer to character
{
    char number;

    if (digit == 1)
    {
        number = '1';
    }
    else if (digit == 2)
    {
        number = '2';
    }
    else if (digit == 3)
    {
        number = '3';
    }
    else if (digit == 4)
    {
        number = '4';
    }
    else if (digit == 5)
    {
        number = '5';
    }
    else if (digit == 6)
    {
        number = '6';
    }
    else if (digit == 7)
    {
        number = '7';
    }
    else if (digit == 8)
    {
        number = '8';
    }
    else if (digit == 9)
    {
        number = '9';
    }
    else if (digit == 0)
    {
        number = '0';
    }

    return number;
}

bool isValid(string zipcode) // checks that zipcode is 5 characters and all digits 
{
    ofstream outStream;
    int currentNumber;
    bool characterTest(1);
    for (unsigned int i = 0; i < zipcode.length(); i++) // checks each character of the input
    {
        currentNumber = zipcode.at(i);
        characterTest = isdigit(currentNumber);

        if (characterTest == 0) // if fails, loop will return invalid code error message
        {

            i = zipcode.length();
        }
    }
    while (zipcode.length() != 5 || characterTest == 0) // tests if there is an error, if so, error message is returned
    {

        if (zipcode.length() != 5)
        {

            outStream << "Error: zip code must be 5 digits" << endl;
        }
        else
        {
            outStream << "Error: Code is invalid" << endl;
        }
    }
    if (characterTest == 0)
    {
        return false;
    }
    return true;
}

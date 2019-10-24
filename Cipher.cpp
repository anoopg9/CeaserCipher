#include <stdio.h>
#include <vector>
#include <map>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

//implementing rot13 function
void rot13(string letters)
{
    for (int i = 0; i < letters.length(); i++)
    {
        //check to see if it is aplhabet
        if (isalpha(letters[i]))
        {
            //any aplhabet set that to offset
            int offset = 65;
            //check if it lowercase or not
            if (islower(letters[i]))
            {
                //if it lowercase then update offset
                offset = 97;
            }
            int cipheredLetter = (((int)letters[i] - offset + 13) % 26) + offset;
            //print out the ciphered letter
            cout << (char)cipheredLetter;
        }
        //if this is not alpha print and continue
        else
        {
            cout << letters[i];
            continue;
        }
    }
}

//MAIN TO RUN THE PROGRAM

int main(int argc, char *argv[])
{
    string message;
    if (argc == 1)
    {
        cout << "MISSING COMMAND" << endl;
        return -1;
    }
    //error checking
    if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-d") == 0)
    {

        // check if the argument is -r
        if (strcmp(argv[1], "-r") == 0)
        {
            if (argc == 3)
            {
                ifstream inFile;
                inFile.open(argv[2]);
                //checks if the file can be open
                if (inFile.fail())
                {
                    cerr << " FILE COULD NOT BE OPENED" << endl;
                    exit(0);
                }
                //if the file is open then read the file and store it on message
                //then run rot13 on message
                if (inFile.is_open())
                {
                    while (!inFile.eof() && getline(inFile, message))
                    {
                        rot13(message);
                        cout << endl;
                    }
                    inFile.close();
                }
            }
            //if there is no file then get standard input
            else
            {
                while (getline(cin, message))
                {
                    rot13(message);
                    cout << endl;
                }
            }
        }
        //check if the argument is -g
        // then generate dictionary
        else if (strcmp(argv[1], "-g") == 0)
        {
            int letter[26];
            for (int i = 0; i < 26; i++)
            {
                letter[i] = i;
            }
            srand(time(NULL));
            int poolsize = 26;
            for (int i = 0; i < 26; i++)
            {
                int val = rand() % poolsize;
                // char str = char(letter[val] + 'a');
                // char test = char('a' + i) if (str == test)
                // {
                //     val = rand() % poolsize;
                // }
                cout << char('a' + i) << char(letter[val] + 'a') << endl;
                letter[val] = letter[poolsize - 1];
                poolsize--;
            }
        }

        if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-d") == 0)
        {
            if (argc < 3)
            {
                cout << "NO DICTIONARY GIVEN" << endl;
                exit(0);
            }

            else
            {
                string input;
                ifstream inFile;
                inFile.open(argv[2]);
                if (inFile.fail())
                {
                    cout << argv[2] << " DICTIONARY COULD NOT BE OPENED" << endl;
                    exit(0);
                }

                //encryption
                map<char, char> myMap1;
                vector<char> key;
                vector<char> value;

                while (inFile >> input)
                {

                    if (input[0] == input[1])
                    {
                        cout << " MAPPING ERROR " << input[0] << endl;
                        exit(0);
                    }
                    if (input.size() != 2 || isalpha(input[0]) == false || isalpha(input[1]) == false)
                    {
                        cout << "FORMATTING ERROR " << input << endl;
                        exit(0);
                    }
                    //cout << input[0] << " " << input[1];
                    myMap1[input[0]] = input[1];
                    key.push_back(input[0]);
                    value.push_back(input[1]);
                }
                char alphaCheck;
                for (int i = 0; i < value.size(); i++)
                {
                    alphaCheck = value[i];
                    for (int j = 0; j < value.size(); j++)
                    {
                        if (i == j)
                        {
                            continue;
                        }

                        if (alphaCheck == value[j])
                        {
                            cout << "DUPLICATE CIPHERTEXT " << value[j] << endl;
                            exit(0);
                        }
                    }
                }
                // missing letter
                for(int i=0; i<key.size();i++){
                    char check= 'a';
                    if (!check ==key[i]){
                        cout<<" MISSING LETTER" <<key[i]<< endl;
                           exit(0);
                    }
                    check++;

                }

    


                //map2 for decipher
                map<char, char> myMap2;
                for (auto it = myMap1.begin(); it != myMap1.end(); it++)
                {
                    myMap2[it->second] = it->first;
                }

                // if File is given
                if (strcmp(argv[1], "-e") == 0 && argc == 4)
                {
                    string letter;
                    ifstream ifile;
                    ifile.open(argv[3]);
                    if (ifile.is_open() == false)
                    {
                        cout << argv[3] << " FILE COULD NOT BE OPENED" << endl;
                    }
                    else
                    {
                        while (!ifile.eof() && getline(ifile, letter))
                        {
                            // Run through the map and encrypt
                            string result1;
                            char word;
                            for (int i = 0; i < letter.length(); i++)
                            {
                                if (isalpha(letter[i]))
                                {
                                    if (isupper(letter[i]))
                                    {
                                        word = tolower(letter[i]);
                                        word = myMap1[word];
                                        result1 += toupper(word);
                                    }
                                    else
                                    {
                                        result1 += myMap1[(letter[i])];
                                    }
                                }
                                else
                                {
                                    result1 += letter[i];
                                }
                            }
                            cout << result1 << endl;
                        }
                        return 0;
                    }
                }
                if(strcmp(argv[1], "-e") == 0 && argc == 3)
                {
                    // get standard input
                    string letter;
                    while (getline(cin, letter))
                    {

                        string result1;
                        char word;
                        for (int i = 0; i < letter.length(); i++)
                        {
                            if (isalpha(letter[i]))
                            {
                                if (isupper(letter[i]))
                                {
                                    word = tolower(letter[i]);
                                    word = myMap1[word];
                                    result1 += toupper(word);
                                }
                                else
                                {
                                    result1 += myMap1[(letter[i])];
                                }
                            }
                            else
                            {
                                result1 += letter[i];
                            }
                        }

                        cout << result1 << endl;
                    }
                }
                if (strcmp(argv[1], "-d") == 0 && argc == 4)
                {
                    string letter;
                    ifstream ifile;
                    ifile.open(argv[3]);
                    if (ifile.is_open() == false)
                    {
                        cout << argv[3] << " FILE COULD NOT BE OPENED" << endl;
                    }
                    else
                    {
                        while (!ifile.eof() && getline(ifile, letter))
                        {
                            // Run through the map and encrypt
                            string result1;
                            char word;
                            for (int i = 0; i < letter.length(); i++)
                            {
                                if (isalpha(letter[i]))
                                {
                                    if (isupper(letter[i]))
                                    {
                                        word = tolower(letter[i]);
                                        word = myMap2[word];
                                        result1 += toupper(word);
                                    }
                                    else
                                    {
                                        result1 += myMap2[(letter[i])];
                                    }
                                }
                                else
                                {
                                    result1 += letter[i];
                                }
                            }
                            cout << result1 << endl;
                        }
                    }
                }
                if(strcmp(argv[1], "-d") == 0 && argc == 3)
                {
                    // get standard input
                    string letter;
                    while (getline(cin, letter))
                    {

                        string result1;
                        char word;
                        for (int i = 0; i < letter.length(); i++)
                        {
                            if (isalpha(letter[i]))
                            {
                                if (isupper(letter[i]))
                                {
                                    word = tolower(letter[i]);
                                    word = myMap2[word];
                                    result1 += toupper(word);
                                }
                                else
                                {
                                    result1 += myMap2[(letter[i])];
                                }
                            }
                            else
                            {
                                result1 += letter[i];
                            }
                        }

                        cout << result1 << endl;
                    }
                }
            }
        }
    }

    //if the argument is not any of those above then prints not a valid command
    else
    {
        cout << argv[1] << "NOT A VALID COMMAND" << endl;
        return -1;
    }

    return 0;
}

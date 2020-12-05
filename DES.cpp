#include <bits/stdc++.h>

using namespace std;

string asciiToBinary(char character)
{

    int i;
    int s[8];
    string binary = "";

    for (i = 0; i < 8; i++)
    {
        s[i] = character % 2;
        character = character / 2;
    }
    int a, b;
    for (b = 0, a = 7; b < 8; b++, a--)
    {
        //cout << s[a];
        if (s[a] == 1)
        {
            binary += "1";
        }
        else
        {
            binary += "0";
        }
    }
    return binary;
}

int main()
{
    string plainText;
    cout << "Enter plain text: ";
    cin >> plainText;


    string result = ""; 
    
    for (int i = 0; i < plainText.length(); i++)
    {
        result += asciiToBinary(plainText[i]);
    }
    
    
    cout << result;
}
#include <bits/stdc++.h>

using namespace std;

string asciiToBinary(char character)
{
    int s[8];
    string binary = "";

    for (int i = 0; i < 8; i++)
    {
        s[i] = character % 2;
        character = character / 2;
    }
    
    for (int b = 0, a = 7; b < 8; b++, a--)
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

string textToBinaryText(string text){

    string binaryText= "";
    for (int i = 0; i < text.length(); i++)
    {
        binaryText += asciiToBinary(text[i]);
    }

    return binaryText;

}

int main()
{
    string plainText = "PRITOMKD";
    string key = "LAMAOLOL";
   // cout << "Enter plain text: ";
   // cin >> plainText;


    string binaryText = textToBinaryText(plainText); 
    string binaryKey =  textToBinaryText(key); 
    
   
    

    
    cout << binaryText;
}
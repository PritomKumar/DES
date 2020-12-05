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

string hex2bin(string s) 
{ 
    // hexadecimal to binary conversion 
    unordered_map<char, string> mp; 
    mp['0'] = "0000"; 
    mp['1'] = "0001"; 
    mp['2'] = "0010"; 
    mp['3'] = "0011"; 
    mp['4'] = "0100"; 
    mp['5'] = "0101"; 
    mp['6'] = "0110"; 
    mp['7'] = "0111"; 
    mp['8'] = "1000"; 
    mp['9'] = "1001"; 
    mp['A'] = "1010"; 
    mp['B'] = "1011"; 
    mp['C'] = "1100"; 
    mp['D'] = "1101"; 
    mp['E'] = "1110"; 
    mp['F'] = "1111"; 
    string bin = ""; 
    for (int i = 0; i < s.size(); i++) { 
        bin += mp[s[i]]; 
    } 
    return bin; 
} 

string bin2hex(string s) 
{ 
    // binary to hexadecimal conversion 
    unordered_map<string, string> mp; 
    mp["0000"] = "0"; 
    mp["0001"] = "1"; 
    mp["0010"] = "2"; 
    mp["0011"] = "3"; 
    mp["0100"] = "4"; 
    mp["0101"] = "5"; 
    mp["0110"] = "6"; 
    mp["0111"] = "7"; 
    mp["1000"] = "8"; 
    mp["1001"] = "9"; 
    mp["1010"] = "A"; 
    mp["1011"] = "B"; 
    mp["1100"] = "C"; 
    mp["1101"] = "D"; 
    mp["1110"] = "E"; 
    mp["1111"] = "F"; 
    string hex = ""; 
    for (int i = 0; i < s.length(); i += 4) { 
        string ch = ""; 
        ch += s[i]; 
        ch += s[i + 1]; 
        ch += s[i + 2]; 
        ch += s[i + 3]; 
        hex += mp[ch]; 
    } 
    return hex; 
} 

string stepPC1(string binaryKey){

    int pc1[56] = { 57 ,  49 ,  41 ,  33 ,  25 ,  17 ,  9,
                     1 ,  58 ,  50 ,  42 ,  34 ,  26 ,  18,
                    10 ,   2 ,  59 ,  51 ,  43 ,  35 ,  27,
                    19 ,  11 ,   3 ,  60 ,  52 ,  44 ,  36,
                    63 ,  55 ,  47 ,  39 ,  31 ,  23 ,  15,
                     7 ,  62 ,  54 ,  46 ,  38 ,  30 ,  22,
                    14 ,  6  ,  61 ,  53 ,  45 ,  37 ,  29,
                    21 ,  13 ,   5 ,  28 ,  20 ,  12 ,  4};

    string keyAfterPC1 = "";
    
    for (int i = 0; i < 56; i++)
    {
        keyAfterPC1 += binaryKey[pc1[i]-1];
    }
    //cout << keyAfterPC1 << endl;
    return keyAfterPC1;
}

string createLeftC0(string keyAfterPC1){
    string leftC0 = "";
    for (int i = 0; i < 28; i++)
    {
        leftC0 += keyAfterPC1[i];
    }
    return leftC0;
}

string createRightD0(string keyAfterPC1){
    string rightD0 = "";
    for (int i = 28; i < 56; i++)
    {
        rightD0 += keyAfterPC1[i];
    }
    return rightD0;
}


string createKeys(string binaryKey){

    string keyAfterPC1 = stepPC1(binaryKey);
    string leftC0 = createLeftC0(keyAfterPC1);
    string rightD0 = createRightD0(keyAfterPC1);

    cout << keyAfterPC1 <<endl;
    cout << leftC0 <<endl;
    cout << rightD0 <<endl;

}

int main()
{
    string plainText = "PRITOMKD";
    string key = "LAMAOLOL";
   // cout << "Enter plain text: ";
   // cin >> plainText;


    string binaryText = textToBinaryText(plainText); 
    string binaryKey =  textToBinaryText(key); 
    
   // cout << binaryText << endl;
   // cout << binaryKey << endl;

    string testText = "0000000100100011010001010110011110001001101010111100110111101111";
    string testKey = "0001001100110100010101110111100110011011101111001101111111110001";
    createKeys(testKey);
}
#include <bits/stdc++.h>

using namespace std;

string subKeyList[16];

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

string textToBinaryText(string text)
{

    string binaryText = "";
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
    for (int i = 0; i < s.size(); i++)
    {
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
    for (int i = 0; i < s.length(); i += 4)
    {
        string ch = "";
        ch += s[i];
        ch += s[i + 1];
        ch += s[i + 2];
        ch += s[i + 3];
        hex += mp[ch];
    }
    return hex;
}

string stepPC1(string binaryKey)
{
    int pc1[56] = {57, 49, 41, 33, 25, 17, 9,
                   1, 58, 50, 42, 34, 26, 18,
                   10, 2, 59, 51, 43, 35, 27,
                   19, 11, 3, 60, 52, 44, 36,
                   63, 55, 47, 39, 31, 23, 15,
                   7, 62, 54, 46, 38, 30, 22,
                   14, 6, 61, 53, 45, 37, 29,
                   21, 13, 5, 28, 20, 12, 4};

    string keyAfterPC1 = "";

    for (int i = 0; i < 56; i++)
    {
        keyAfterPC1 += binaryKey[pc1[i] - 1];
    }
    //cout << keyAfterPC1 << endl;
    return keyAfterPC1;
}

string createLeftPart(string text)
{
    string leftPart = "";
    for (int i = 0; i < text.length()/2; i++)
    {
        leftPart += text[i];
    }
    return leftPart;
}

string createRightPart(string text)
{
    string rightPart = "";
    for (int i = text.length()/2; i < text.length(); i++)
    {
        rightPart += text[i];
    }
    return rightPart;
}

string shiftSubKey(string subKey , int shiftConstant){

    string shiftedSubKey = "";
   
    for (int i = shiftConstant; i < subKey.length(); i++)
    {
        shiftedSubKey += subKey[i];
    }
    for (int i = 0; i < shiftConstant; i++)
    {
        shiftedSubKey += subKey[i];
    }

    //cout << shiftedSubKey << endl;
    return shiftedSubKey;

}

string stepPC2(string shiftedKey)
{
    int pc2[48] = {  14,    17,   11,    24,     1,    5,
                      3,    28,   15,     6,    21,   10,
                     23,    19,   12,     4,    26,    8,
                     16,     7,   27,    20,    13,    2,
                     41,    52,   31,    37,    47,   55,
                     30,    40,   51,    45,    33,   48,
                     44,    49,   39,    56,    34,   53,
                     46,    42,   50,    36,    29,   32};

    string keyAfterPC2 = "";

    for (int i = 0; i < 48; i++)
    {
        keyAfterPC2 += shiftedKey[pc2[i] - 1];
    }
    //cout << keyAfterPC2 << endl;
    return keyAfterPC2;
}

string createKeys(string binaryKey)
{
    string keyAfterPC1 = stepPC1(binaryKey);
    string leftC0 = createLeftPart(keyAfterPC1);
    string rightD0 = createRightPart(keyAfterPC1);

    //cout << keyAfterPC1 << endl;
    //cout << leftC0 << endl;
   // cout << rightD0 << endl;

    int shiftConstants[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

    int round = 16;
    string shiftedLeftC[round];
    string shiftedRightD[round];

    shiftedLeftC[0] = shiftSubKey(leftC0 , shiftConstants[0]);
    shiftedRightD[0] = shiftSubKey(rightD0 , shiftConstants[0]);
    for (int i = 1; i < round; i++)
    {
        //cout<<endl;
        shiftedLeftC[i] = shiftSubKey(shiftedLeftC[i-1] , shiftConstants[i]);
        shiftedRightD[i] = shiftSubKey(shiftedRightD[i-1] , shiftConstants[i]);
       // cout<<endl;
    }
    
    for (int i = 0; i < round; i++)
    {
        subKeyList[i] = stepPC2(shiftedLeftC[i] + shiftedRightD[i]);
        //cout<<endl;
    }

}

string stepInitialPermutation(string text){
    int IP[64] = {
            58,    50,   42,    34,    26,   18,    10,    2,
            60,    52,   44,    36,    28,   20,    12,    4,
            62,    54,   46,    38,    30,   22,    14,    6,
            64,    56,   48,    40,    32,   24,    16,    8,
            57,    49,   41,    33,    25,   17,     9,    1,
            59,    51,   43,    35,    27,   19,    11,    3,
            61,    53,   45,    37,    29,   21,    13,    5,
            63,    55,   47,    39,    31,   23,    15,    7
    };
    string textAfterInitialPermutation = "";
    for (int i = 0; i < 64; i++)
    {
        textAfterInitialPermutation += text[IP[i] - 1];
    }
    return textAfterInitialPermutation;
}

int main()
{
    string plainText = "PRITOMKD";
    string key = "LAMAOLOL";
    // cout << "Enter plain text: ";
    // cin >> plainText;

    string binaryText = textToBinaryText(plainText);
    string binaryKey = textToBinaryText(key);

    // cout << binaryText << endl;
    // cout << binaryKey << endl;

    string testText = "0000000100100011010001010110011110001001101010111100110111101111";
    string testKey = "0001001100110100010101110111100110011011101111001101111111110001";
    createKeys(testKey);

    string textAfterInitialPermutation = stepInitialPermutation(testText);
    // cout << textAfterInitialPermutation << endl;
    string l0 = createLeftPart(textAfterInitialPermutation);
    string R0 = createRightPart(textAfterInitialPermutation);

}
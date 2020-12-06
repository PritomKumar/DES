#include <bits/stdc++.h>

using namespace std;

string subKeyList[16];
string leftPartList[17];
string rightPartList[17];

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
    map<char, string> mp;
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
    map<string, string> mp;
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
    for (int i = 0; i < text.length() / 2; i++)
    {
        leftPart += text[i];
    }
    return leftPart;
}

string createRightPart(string text)
{
    string rightPart = "";
    for (int i = text.length() / 2; i < text.length(); i++)
    {
        rightPart += text[i];
    }
    return rightPart;
}

string shiftSubKey(string subKey, int shiftConstant)
{

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
    int pc2[48] = {14, 17, 11, 24, 1, 5,
                   3, 28, 15, 6, 21, 10,
                   23, 19, 12, 4, 26, 8,
                   16, 7, 27, 20, 13, 2,
                   41, 52, 31, 37, 47, 55,
                   30, 40, 51, 45, 33, 48,
                   44, 49, 39, 56, 34, 53,
                   46, 42, 50, 36, 29, 32};

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

    int shiftConstants[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    int round = 16;
    string shiftedLeftC[round];
    string shiftedRightD[round];

    shiftedLeftC[0] = shiftSubKey(leftC0, shiftConstants[0]);
    shiftedRightD[0] = shiftSubKey(rightD0, shiftConstants[0]);
    for (int i = 1; i < round; i++)
    {
        //cout<<endl;
        shiftedLeftC[i] = shiftSubKey(shiftedLeftC[i - 1], shiftConstants[i]);
        shiftedRightD[i] = shiftSubKey(shiftedRightD[i - 1], shiftConstants[i]);
        //cout<<endl;
    }

    for (int i = 0; i < round; i++)
    {
        subKeyList[i] = stepPC2(shiftedLeftC[i] + shiftedRightD[i]);
        //cout<<endl;
    }
}

string stepInitialPermutation(string text)
{
    int IP[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7};
    string textAfterInitialPermutation = "";
    for (int i = 0; i < 64; i++)
    {
        textAfterInitialPermutation += text[IP[i] - 1];
    }
    return textAfterInitialPermutation;
}

string eBitExpansionStep(string rightPart)
{
    int EBit[48] = {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1};

    string rightPartAfterEBItExpansion = "";
    for (int i = 0; i < 48; i++)
    {
        rightPartAfterEBItExpansion += rightPart[EBit[i] - 1];
    }
    return rightPartAfterEBItExpansion;
}

string XORstep(string r0AfterEBItExpansion, string subKey)
{
    string r0AfterXOR = "";
    for (int i = 0; i < r0AfterEBItExpansion.length(); i++)
    {
        if (r0AfterEBItExpansion[i] == subKey[i])
        {
            r0AfterXOR += "0";
        }
        else
        {
            r0AfterXOR += "1";
        }
    }
    return r0AfterXOR;
}

string XORstepForLAndRAfterPBox(string rAfterPBox, string l)
{
    string rPlus = "";
    for (int i = 0; i < rAfterPBox.length(); i++)
    {
        if (rAfterPBox[i] == l[i])
        {
            rPlus += "0";
        }
        else
        {
            rPlus += "1";
        }
    }
    return rPlus;
}

int binaryToDecimal(int n)
{
    int factor = 1;
    int total = 0;

    while (n != 0)
    {
        total += (n%10) * factor;
        n /= 10;
        factor *= 2;
    }

    return total;
}

string decToBinary(int n)
{
    int binaryNum[4];
    int binaryNumReal[4];
    string binaryStr="0000";
    int i = 0;
    while (n > 0) {

        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    for (int j = 0,k=3; j <i; j++,k--) {
        binaryNumReal[k] =  binaryNum[j];
        if(binaryNum[j]==0){
            binaryStr[k] = '0';
        }
        else{
            binaryStr[k] = '1';
        }
    }

    return binaryStr;

}
int stringToInt(string str)
{
    stringstream converter(str);
    int num = 0;
    converter >> num;
    return num;
}

string intToString(int num)
{
    stringstream converter;
    converter << num;
    string str = converter.str();
    return str;
    //return to_string(num);
}

string sBoxStep(string r0AfterXOR)
{
    int sBox[8][4][16] = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                           0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                           4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                           15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
                          {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                           3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                           0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                           13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
                          {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                           13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                           13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                           1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
                          {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                           13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                           10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                           3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
                          {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                           14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                           4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                           11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
                          {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                           10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                           9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                           4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
                          {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                           13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                           1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                           6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
                          {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                           1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                           7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                           2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};


    int sBoxRound = 0;
    string subOfR0AfterXOR = "";
    string r0AfterSBox = "";
    //cout << "Before" <<endl;
    for (int i = 0; i < r0AfterXOR.length(); i++)
    {
        //string s(1,r0AfterXOR[i]);
        subOfR0AfterXOR += r0AfterXOR[i];

        if(subOfR0AfterXOR.length()%6==0){

            string rowStr = "" ;
            rowStr += subOfR0AfterXOR[0];
            rowStr += subOfR0AfterXOR[5];
            string colStr = "" ;
            colStr += subOfR0AfterXOR[1];
            colStr += subOfR0AfterXOR[2];
            colStr += subOfR0AfterXOR[3];
            colStr += subOfR0AfterXOR[4];

            //cout << rowStr << "  " << colStr <<endl;

            int row = binaryToDecimal(stringToInt(rowStr));
            int col = binaryToDecimal(stringToInt(colStr));

            //cout << row << "  " << col <<endl;
            int sBoxValue = sBox[sBoxRound][row][col];

            //cout << sBoxValue <<endl;

            string sBoxValueStr = decToBinary(sBoxValue);
            //cout << sBoxValueStr <<endl;

            r0AfterSBox += sBoxValueStr;
            subOfR0AfterXOR="";
            sBoxRound++;
        }
    }
    //cout << r0AfterSBox <<endl;
    //cout << "After" <<endl;

    return r0AfterSBox;
}

string pBoxStep(string r0AfterSBox)
{
    int PBox[32] = {
                         16,   7,  20,  21,
                         29,  12,  28,  17,
                          1,  15,  23,  26,
                          5,  18,  31,  10,
                          2,   8,  24,  14,
                         32,  27,   3,   9,
                         19,  13,  30,   6,
                         22,  11,   4,  25,
        };

    string r0AfterPBox = "";
    for (int i = 0; i < 32; i++)
    {
        r0AfterPBox += r0AfterSBox[PBox[i] - 1];
    }
    return r0AfterPBox;
}

string secondPhase(){

    for(int i=0; i< 16;i++){

        string r0AfterEBItExpansion = eBitExpansionStep(rightPartList[i]);
        string r0AfterXOR = XORstep(r0AfterEBItExpansion, subKeyList[i]);

        //cout << leftPartList[i] << endl;
        //cout << rightPartList[i] << endl;
        //cout << r0AfterEBItExpansion << endl;
        //cout << r0AfterXOR << endl;

        string r0AfterSBox = sBoxStep(r0AfterXOR);
        string r0AfterPBox = pBoxStep(r0AfterSBox);
        string r1 = XORstepForLAndRAfterPBox(r0AfterPBox , leftPartList[i]);
        rightPartList[i+1] = r1;
        leftPartList[i+1] = rightPartList[i];

       // cout << r0AfterSBox <<endl;
        //cout << r0AfterPBox <<endl;
        //cout << l0 << endl;
        //cout << r1 << endl;
    }

    for(int j=0;j<17;j++){
        cout << "Round " << j <<endl;;
        cout<<"Left Part   "<<endl;
        for(int i=0; i< 32;i++){
            cout << leftPartList[j][i];
            if((i+1)%8==0){
                cout<<endl;
            }
        }
        cout<<endl;
        cout<<"Right Part  "<<endl;
        for(int i=0; i< 32;i++){
            cout << rightPartList[j][i];
            if((i+1)%8==0){
                cout<<endl;
            }
        }
        cout<<endl;
    }

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
    string testText2 = "0100100001100101011011000110110001101111001000000101011101101111";
    string testKey2 = "0011010000101101101101011010100000011101110110111001000000000100";
    createKeys(testKey);

    string textAfterInitialPermutation = stepInitialPermutation(testText);
    // cout << textAfterInitialPermutation << endl;
    string l0 = createLeftPart(textAfterInitialPermutation);
    string r0 = createRightPart(textAfterInitialPermutation);
    leftPartList[0] = l0;
    rightPartList[0] = r0;

    secondPhase();

}

#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include "clsDate.h"

using namespace std;

class clsUtil
{

public:

    enum enCharacters {SmallLetter = 1, CapitalLetter = 2, Digit = 3, SpecialCharacter = 4, MixChars = 5};

    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int from, int to)
    {
        int number = rand() % (to - from + 1) + from;
        return number;
    }

    static char GetRandomCharacter(enCharacters CharType) {

        if(CharType == enCharacters::MixChars)
        {
            CharType = enCharacters(RandomNumber(1,3));
        }

        switch(CharType) {
            case enCharacters::SmallLetter:
                return RandomNumber(97,122);
            case enCharacters::CapitalLetter:
                return RandomNumber(65,90);
            case enCharacters::SpecialCharacter:
                return RandomNumber(33,47);
            case enCharacters::Digit:
                return RandomNumber(48,57);
        }
        return ' ';
}

    static string GenerateWord(enCharacters CharType, short Length) {

        string word;

        for(int i = 1; i <= Length; i++) {
            word = word + GetRandomCharacter(CharType);
        }
        return word;
    }

    static string GenerateKey(enCharacters CharType) {

        string key = "";

        for(int i = 0; i <= 3; i++) {
            key = key + GenerateWord(CharType, 4);
            if(!(i == 3))
                key = key + "-";
        }

        return key;
    }

    static void GenerateKeys(short numberOfKeys, enCharacters CharType) {

        for(int i = 1; i <= numberOfKeys; i++) {
            cout << "Key [" << i << "] : " << GenerateKey(CharType) << endl;
        }
    }

    static void Swap(int &a, int &b)
    {
        int temp;
        temp = a;
        a = b;
        b = temp;
    } 

    static void Swap(double &a, double &b)
    {
        double temp;
        temp = a;
        a = b;
        b = temp;
    } 

    static void Swap(string &a, string &b)
    {
        string temp;
        temp = a;
        a = b;
        b = temp;
    } 

    static void Swap(clsDate &Date1, clsDate &Date2)
    {
        clsDate::SwapDates(Date1,Date2);
    }

    static void ShuffleArray(int array[100], int length) {

        int temp[100];
        for(int i = 0; i < length; i++) {
            Swap(array[RandomNumber(0,length - 1)],array[RandomNumber(0,length - 1)]);
        }
    }

    static void ShuffleArray(string array[100], int length) {

        string temp[100];
        for(int i = 0; i < length; i++) {
            Swap(array[RandomNumber(0,length - 1)],array[RandomNumber(0,length - 1)]);
        }
    }

    static void FillArrayWithRandomNumbers(int array[100], int length, int from, int to) {

        for(int i = 0; i < length; i++) {
            array[i] = RandomNumber(from,to);
        }
    }

    static void FillArrayWithRandomWords(string array[100], int length, enCharacters CharType, int Size) {

        for(int i = 0; i < length; i++) {
            array[i] = GenerateWord(CharType, Size);
        }
    }

    static void FillArrayWithRandomKeys(string array[100], int length, enCharacters CharType) {

        for(int i = 0; i < length; i++) {
            array[i] = GenerateKey(CharType);
        }
    }

    static string Tabs(short NumberOfTaps)
    {
        string Tabs = "";
        for(int i = 0; i < NumberOfTaps; i++)
        {
            Tabs += "\t";
        }
        return Tabs;
    }

    static string EncryptionText(string original, short EncryptionKey) {

        for(int i = 0; i < original.size(); i++) {
            original[i] = char(original[i] + EncryptionKey);
    }

        return original;
    }

    static string DecryptionText(string decrypted, short EncryptionKey) {

        for(int i = 0; i < decrypted.size(); i++) {
            decrypted[i] = char(decrypted[i] - EncryptionKey);
    }

        return decrypted;
    }   

   static string NumberToText(int Number)
   {

       if (Number == 0)
       {
           return "";
       }

       if (Number >= 1 && Number <= 19)
       {
           string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
       "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
         "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

           return  arr[Number] + " ";

       }

       if (Number >= 20 && Number <= 99)
       {
           string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
           return  arr[Number / 10] + " " + NumberToText(Number % 10);
       }

       if (Number >= 100 && Number <= 199)
       {
           return  "One Hundred " + NumberToText(Number % 100);
       }

       if (Number >= 200 && Number <= 999)
       {
           return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
       }

       if (Number >= 1000 && Number <= 1999)
       {
           return  "One Thousand " + NumberToText(Number % 1000);
       }

       if (Number >= 2000 && Number <= 999999)
       {
           return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
       }

       if (Number >= 1000000 && Number <= 1999999)
       {
           return  "One Million " + NumberToText(Number % 1000000);
       }

       if (Number >= 2000000 && Number <= 999999999)
       {
           return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
       }

       if (Number >= 1000000000 && Number <= 1999999999)
       {
           return  "One Billion " + NumberToText(Number % 1000000000);
       }
       else
       {
           return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
       }
   }

};
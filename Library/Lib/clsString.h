#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsString
{

private:

    string _Value;

public:

    // default constructor
    clsString()
    {
        _Value = "";
    }

    // paramatrized constructor
    clsString(string Value)
    {
        _Value = Value;
    }

    void SetValue(string Value)
    {
        _Value = Value;
    }

    string GetValue()
    {
        return _Value;
    }

    static vector<string> SplitString(string S1, string Delim)
    {

        vector<string> vString;
        short pos = 0;
        string sWord;

        while ((pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos);
            vString.push_back(sWord);

            S1.erase(0, pos + Delim.length());
        }

        if (S1 != "")
        {
            vString.push_back(S1);
        }

        return vString;

    }

    static short CountWords(string message)
    {   
        string delim = " ";
        short pos = 0;
        string sWord;
        short Counter = 0;

        while((pos = message.find(delim)) != std::string::npos)
        {
            sWord = message.substr(0, pos);
            if(sWord != "")
            {
                Counter++;
            }

            message.erase(0, pos + delim.length());
        }

        if(message != "")
        {
            Counter++;
        }
        return Counter;
    }

    static string UpperFirstLetterOfEachWord(string message)
    {

        bool isFirstLetter = true;

        for(short i = 0; i < message.length(); i++)
        {

            if(message[i] != ' ' && isFirstLetter)
            {
                message[i] = toupper(message[i]);
            }

            isFirstLetter = (message[i] == ' ' ? true : false);
        }
        return message;
    }
    
    static string LowerFirstLetterOfEachWord(string message)
    {

        bool isFirstLetter = true;

        for(short i = 0; i < message.length(); i++)
        {

            if(message[i] != ' ' && isFirstLetter)
            {
                message[i] = tolower(message[i]);
            }

            isFirstLetter = (message[i] == ' ' ? true : false);
        }
        return message;
    }

    static string UpperAllLetters(string message)
    {
        for(short i = 0; i < message.length(); i++)
        {
            message[i] = toupper(message[i]);
        }
        return message;
    }   

    static string LowerAllLetters(string message)
    {
        for(short i = 0; i < message.length(); i++)
        {
            message[i] = tolower(message[i]);
        }
        return message;
    }

    static string InvertAllLettersCase(string message)
    {

        for(int i = 0; i < message.length(); i++)
        {
            message[i] = InvertLetterCase(message[i]);
        }
        return message;
    }

    static char InvertLetterCase(char Character)
    {
        return isupper(Character) ? tolower(Character) : toupper(Character); // short hand if
    }

    static bool IsVowel(char letter)
    {
        letter = tolower(letter);

        return ((letter == 'a') || (letter == 'e') || (letter == 'i') || (letter == 'o') || (letter == 'u'));
    }

    static short CountSpecificLetter(string message, char letter, bool MatchCase = true)
    {

        short Counter = 0;

        for(short i = 0; i < message.length(); i++)
        {
            if(MatchCase)
            {
                if(message[i] == letter)
                {
                    Counter++;
                }
            } else
            {
                if(tolower(message[i]) == tolower(letter))
                {
                    Counter++;
                }
            }
        }
        return Counter;
    }

    static short CountLetters(string message)
    {

        short Counter = 0;

        for(short i = 0; i < message.length(); i++)
        {
            if(isalpha(message[i]))
            {
                Counter++;
            }
        return Counter;
    }
}

    static short CountCapitalLetters(string message)
    {
        short Counter = 0;

        for(short i = 0; i < message.length(); i++)
        {
            if(isalpha(message[i]) && isupper(message[i]))
            {
                Counter++;
            }
        }
        return Counter;
    }

    static short CountSmallLetters(string message)
    {
        short Counter = 0;

        for(short i = 0; i < message.length(); i++)
        {
            if(isalpha(message[i]) && islower(message[i]))
            {
                Counter++;
            }
        }
        return Counter;
    }

    static short CountVowel(string message)
    {
        short Counter = 0;
        for(short i = 0; i < message.length(); i++)
        {
            if(IsVowel(message[i]))
            {
                Counter++;
            }
        }
        return Counter;
    }

    static string TrimLeft(string message)
    {

        for(short i = 0; i < message.length(); i++)
        {
            if(message[i] != ' ')
            {
                return message.substr(i,message.length() - i);
            }
        }
        return "";
    }

    static string TrimRight(string message)
    {

        for(short i = message.length() - 1; i >= 0; i--)
        {
            if(message[i] != ' ')
            {
                return message.substr(0,i + 1);
            }
        }
        return "";
    }

    static string Trim(string message)
    {
        return(TrimLeft(TrimRight(message)));
    }

    static string JoinString(vector<string> vMessage, string delim)
    {   

        string message = "";

        for(string &s : vMessage)
        {
            message = message + s + delim;
        }

        return message.substr(0,message.length() - delim.length());
    }

    static string ReverseWords(string S1)
    {

        vector <string> vString;
        string S2 = "";

        vString = SplitString(S1, " ");

        vector<string>::iterator iter = vString.end();

        while(iter != vString.begin())
        {
            --iter;

            S2 += *iter + " ";
        }

        S2 = S2.substr(0, S2.length() - 1);

        return S2;
    }

    static string ReplaceWord(string S1, string StringToReplace, string sReplaceTo, bool MatchCase = true)
    {
        vector <string> vString = SplitString(S1, " ");

        for(string &s : vString)
        {
            if(MatchCase)
            {
                if (s == StringToReplace)
                {
                    s = sReplaceTo;
                }
            } else 
            {
                if(LowerAllLetters(s) == LowerAllLetters(StringToReplace))
                {
                    s =sReplaceTo;
                }
            }
        }

        return JoinString(vString, " ");
    }

    static string RemovePunctuations(string S1)
    {

        string message = "";
        for(int i = 0; i < S1.length(); i++)
        {
            if(!ispunct(S1[i]))
            {
                message += S1[i];
            }
        }

        return message;
    }

    short CountWords()
    {
        return CountWords(_Value);
    }

    void UpperFirstLetterOfEachWord()
    {
        _Value = UpperFirstLetterOfEachWord(_Value);
    }

    void LowerFirstLetterOfEachWord()
    {
        _Value = LowerFirstLetterOfEachWord(_Value);
    }

    void UpperAllLetters()
    {
        _Value = UpperAllLetters(_Value);
    }

    void LowerAllLetters()
    {
        _Value = LowerAllLetters(_Value);
    }

    void InvertAllLettersCase()
    {
        _Value = InvertAllLettersCase(_Value);
    }

    short CountSpecificLetter(char letter, bool MatchCase = true)
    {
        return CountSpecificLetter(_Value,letter,MatchCase);
    }

    short CountLetters()
    {
        return CountLetters(_Value);
    }

    short CountCapitalLetters()
    {
        return CountCapitalLetters(_Value);
    }

    short CountSmallLetters()
    {
        return CountSmallLetters(_Value);
    }

    short CountVowel()
    {
        return CountVowel(_Value);
    }

    void TrimRight()
    {
        _Value = TrimRight(_Value);
    }

    void TrimLeft()
    {
        _Value = TrimLeft(_Value);
    }

    void Trim()
    {
        _Value = Trim(_Value);
    }

    void ReverseWords()
    {
        _Value = ReverseWords(_Value);
    }

    void ReplaceWord(string OldWord, string NewWord, bool MatchCase = true)
    {
        _Value = ReplaceWord(_Value,OldWord,NewWord,MatchCase);
    }

    void RemovePunctuations()
    {
        _Value = RemovePunctuations(_Value);
    }

    short Length()
    {
        return _Value.length();
    }

    static string Encryption(string original, short EncryptionKey) {

        for(int i = 0; i < original.size(); i++) {
            original[i] = char(original[i] + EncryptionKey);
    }

        return original;
    }

    static string Decryption(string decrypted, short EncryptionKey) {

        for(int i = 0; i < decrypted.size(); i++) {
            decrypted[i] = char(decrypted[i] - EncryptionKey);
    }

        return decrypted;
    }   
};

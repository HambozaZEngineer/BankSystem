#pragma once
#include <iostream>
#include <cstdlib>
using namespace std;

enum CharType
{
    CapitalChar,
    SmallChar,
    SpecialChar,
    DigitChar,
    MixChar
};

class ZUtil
{
public:
    static void Srand() { srand((unsigned)time(NULL)); }
    static int GetRandomNumber(int from, int to) { return rand() % (to - from + 1) + from; }
    static char GetRandomChar(CharType charType)
    {
        switch(charType)
        {
            case CapitalChar: return GetRandomNumber(65, 90);
            case SmallChar: return GetRandomNumber(97, 122);
            case SpecialChar: return GetRandomNumber(33, 42);
            case DigitChar: return GetRandomNumber(48, 57);
            case MixChar:
                int randomChar = GetRandomNumber(1, 3);
                switch(randomChar)
                {
                    case 1: return GetRandomChar(CapitalChar);
                    case 2: return GetRandomChar(SmallChar);
                    case 3: return GetRandomChar(DigitChar);
                }
        }

        return '\n';
    }
    static string GetRandomWord(CharType charType, int length)
    {
        string resultString = "";
        for(int i = 0; i < length; i++)
        {
            resultString += GetRandomChar(charType);
        }

        return resultString;
    }
    static string GenerateKey(CharType charType)
    {
        string resultString = "";
        for(int i = 0; i < 4; i++)
        {
            resultString += GetRandomWord(charType, 4);
            if(i != 3) resultString += '-';
        }

        return resultString;
    }
    static void GenerateKeys(CharType charType, int count)
    {
        for(int i = 0; i < count; i++)
        {
            cout << "Key[" << i + 1 << "]: " << GenerateKey(charType) << endl;
        }
    }
    static void Swap(int& x, int& y) { int temp = x; x = y; y = temp; }
    static void Swap(double& x, double& y) { double temp = x; x = y; y = temp; }
    static void Swap(string& x, string& y) { string temp = x; x = y; y = temp; }
    static void ShuffleArray(int arr[], int length)
    {
        for(int i = 0; i < length - 1; i++)
        {
            int rand = GetRandomNumber(0, length - 1);
            int temp = arr[i];
            arr[i] = arr[rand];
            arr[rand] = temp;
        }
    }
    static void ShuffleArray(string arr[], int length)
    {
        for(int i = 0; i < length - 1; i++)
        {
            int rand = GetRandomNumber(0, length - 1);
            string temp = arr[i];
            arr[i] = arr[rand];
            arr[rand] = temp;
        }
    }
    static void FillArrayWithRandomNumber(int arr[], int length, int from, int to)
    {
        for(int i = 0; i < length; i++)
        {
            arr[i] = GetRandomNumber(from, to);
        }
    }
    static void FillArrayWithRandomWords(string arr[], int length, CharType charType, int wordLength)
    {
        for(int i = 0; i < length; i++)
        {
            arr[i] = GetRandomWord(charType, wordLength);
        }
    }
    static void FillArrayWithRandomKeys(string arr[], int length, CharType charType)
    {
        for(int i = 0; i < length; i++)
        {
            arr[i] = GenerateKey(charType);
        }
    }
    static string Tabs(int number)
    {
        string resultString;
        
        for(int i = 0; i < number; i++)
        {
            resultString += "\t";
        }

        return resultString;
    }
    static string EncryptText(string text, int key)
    {
        string resultString = "";

        for(char c : text)
        {
            resultString += (c + key);
        }   

        return resultString;
    }
    static string DecryptText(string text, int key)
    {
        string resultString = "";

        for(char c : text)
        {
            resultString += (c - key);
        }   

        return resultString;
    }
};
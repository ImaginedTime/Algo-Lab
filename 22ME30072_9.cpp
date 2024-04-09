/*************************************************
    Uday om srivastava 22ME30072 Assignment 9
**************************************************/

/*
    The time complexity of the code is O((m+n)^2
    which is way below the specified time complexity of O(mn(m+n))
*/

#include <iostream>
#include <string>

using namespace std;

// O((m + n)) => length of s
// to find if a given string x is a substring of s
bool isSubstring(string x, string s)
{
    int sIndex = 0, xIndex = 0;

    if(x.length() > s.length())
        return false;

    while(sIndex < s.length())
    {
        if(s[sIndex] == x[xIndex])
        {
            xIndex++;
        }
        sIndex++;

        if(xIndex == x.length() - 1)
            break;
    }

    return xIndex == x.length() - 1;
}

// O(m + n) => length of s
// to find the number of all characters in x and y minus that of number of characters in s
int* findCharacters(string x, string y, string s)
{
    int sl = s.length(), xl = x.length(), yl = y.length();

    int* characters = (int*)(malloc(sizeof(int) * 128));

    for(int i = 0; i < 128; i++)
        characters[i] = 0;
    
    for(int i = 0; i < xl; i++)
        characters[x[i]]++;
    for(int i = 0; i < yl; i++)
        characters[y[i]]++;

    for(int i = 0; i < sl; i++)
        characters[s[i]]--;
    
    return characters;
}

// O(n + m) => from the findCharacters function
// to find whether the given s is interleaving of x and y
bool isInterleaving(string x, string y, string s)
{
    if(s.length() != x.length() + y.length())
        return false;

    int* characters = findCharacters(x, y, s);

    for(int i = 0; i < 128; i++)
        if(characters[i] != 0)
            return false;

    return isSubstring(x, s) && isSubstring(y, s);
}

// O((m + n)^2) which is less than the given O(mn(m + n))
// to try Interleaving with Hamming distance of 1
// the number of such anamoly characters can not be greater than 2
// one would be negative and the other would be positive in the respective character array
// For ex - abclfdgh for abcd and efgh
// the value of e in the characters array would be 1 and similarly for l would be -1

string tryInterleaving(string x, string y, string s)
{
    int sl = s.length(), xl = x.length(), yl = y.length();

    if(sl != xl + yl)
        return "";

    int* characters = findCharacters(x, y, s);

    int posAnamolies = 0, negAnamolies = 0;
    for(int i = 0; i < 128; i++)
    {
        if(characters[i] < -1 || characters[i] > 1)
            return "";

        if(characters[i] < 0)
            negAnamolies++;
        else if(characters[i] > 0)
            posAnamolies++;

        if(posAnamolies > 1 || negAnamolies > 1)
            return "";
    }

    char reqd, found;
    for(int i = 0; i < 128; i++)
    {
        if(characters[i] == -1)
            found = (char)(i);
        else if(characters[i] == 1)
            reqd = (char)(i);
    }

    // try to replace the required character in the given string and check if it results in the interleaving of x and y
    for(int i = 0; i < sl; i++)
    {
        if(s[i] == found)
        {
            string str = s.substr(0, i) + reqd + s.substr(i + 1, sl - i - 1);
            if(isInterleaving(x, y, str))
                return str;
        }
    }

    return "";
}

int main()
{
    string x, y, s;

    cout << "Input x: ";
    cin >> x;
    cout << "Input y: ";
    cin >> y;
    cout << "Input s: ";
    cin >> s;


    if(isInterleaving(x, y, s))
    {
        cout << s << " is an interleaving of " << x << " and " << y << endl;
        return 0;
    }

    string ans = tryInterleaving(x, y, s);

    if(ans != "")
        cout << ans << " is an interleaving of x and y that has Hamming distance 1 with s" << endl;
    else 
        cout << "No such Interleaving exists" << endl;
}
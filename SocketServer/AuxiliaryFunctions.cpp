#include "pch.h"
#include "AuxiliaryFunctions.h"

int AuxiliaryFunctions::FindMaxLengthVectorStr(const vector<string>& vectorStr)
{
    int maxLength = -1;
    for (int i = 0; i < vectorStr.size(); ++i)
    {
        if ((int)vectorStr[i].size() > maxLength)
        {
            maxLength = vectorStr[i].size();
        }
    }
    return maxLength;
}


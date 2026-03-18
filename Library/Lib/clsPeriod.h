#pragma once
#include <iostream>
#include <vector>
#include "clsDate.h"
using namespace std;


class clsPeriod
{

private:
    clsDate Start;
    clsDate End;

public:

    clsPeriod(clsDate Start, clsDate End)
    {
        this->Start = Start;
        this->End = End;
    }

    void setStart(clsDate Start)
    {
        this->Start = Start;
    }

    void setEnd(clsDate End)
    {
        this->End = End;
    }

    static bool isPeriodOverlap(clsPeriod Period1, clsPeriod Period2)
    {
        if  (
            clsDate::CompareDates(Period2.End, Period1.Start) == clsDate::enDateCompare::Before
            ||
            clsDate::CompareDates(Period2.Start,Period1.End) == clsDate::enDateCompare::After
            )
            return false;
        else
            return true;
    }

    bool isPeriodOverlap(clsPeriod Period2)
    {
        return isPeriodOverlap(*this, Period2);
    }

    static short PeriodLengthInDays(clsPeriod Period, bool IncludeEndDay = false)
    {
        return clsDate::DifferenceBetweenTwoDates(Period.Start,Period.End,IncludeEndDay);
    }

    short PeriodLengthInDays(bool IncludeEndDay = false)
    {
        return PeriodLengthInDays(*this,IncludeEndDay);
    }

    static bool isDateInPeriod(clsDate Date, clsPeriod Period)
    {
        return!(clsDate::CompareDates(Date,Period.Start) == clsDate::enDateCompare::Before
            ||
                clsDate::CompareDates(Date,Period.End) == clsDate::enDateCompare::After);
    }

    bool isDateInPeriod(clsDate Date)
    {
        return isDateInPeriod(Date,*this);
    }

    static short OverlapDaysCount(clsPeriod Period1, clsPeriod Period2)
    {
        if(isPeriodOverlap(Period1,Period2))
        {
            if(clsDate::CompareDates(Period2.End,Period1.End) == clsDate::enDateCompare::After)
                Period2.End = Period1.End;
            if(clsDate::CompareDates(Period2.Start,Period1.Start) == clsDate::enDateCompare::Before)
                Period2.Start = Period1.Start;
            return PeriodLengthInDays(Period2);
        }
        return 0;
    }

    short OverlapDaysCount(clsPeriod Period2)
    {
        return OverlapDaysCount(*this, Period2);
    }
};
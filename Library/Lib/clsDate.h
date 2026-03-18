#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsDate
{

private:


    short _Year = 1900;
    short _Month = 1;
    short _Day = 1;

public:

    enum enDateCompare { Before = -1, Equal = 0, After = 1};

    clsDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        _Year = now->tm_year + 1900;
        _Month = now->tm_mon + 1;
        _Day = now->tm_mday; 
    }

    clsDate(string Date)
    { 
        vector <string> vDate = SplitString(Date, "/");

        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
    }

    clsDate(int Day, int Month, int Year)
    {
        _Year = Year;
        _Month = Month;
        _Day = Day;
    }

    clsDate(int DayInYear, int Year)
    {   
        short Month;
    
        for(int i = 1; i <= 12; i++)
        {
            if(DayInYear < NumberOfDaysInMonth(Year,i)) 
            {
                Month = i;
                break;
            }
            DayInYear = DayInYear - NumberOfDaysInMonth(Year,i);
        }
        _Year = Year;
        _Month = Month;
        _Day = DayInYear;
    }

    static vector <string> SplitString(string message, string delim)
    {   
        vector <string> words;
        short pos = 0;
        string sWord;

        while((pos = message.find(delim)) != std::string::npos)
        {
            sWord = message.substr(0, pos);
            if(sWord != "")
            {
                words.push_back(sWord);
            }

            message.erase(0, pos + delim.length());
        }

        if(message != "")
        {
            words.push_back(message);
        }
        return words;
    }

    void setYear(int Year)
    {
        _Year = Year;
    }

    int Year()
    {
        return _Year;
    }

    void setMonth(int Month)
    {
        _Month = Month;
    }

    int Month()
    {
        return _Month;
    }

    void setDay(int Day)
    {
        _Day = Day;
    }

    int Day()
    {
        return _Day;
    }

    void Print()
    {
        cout << _Day << "/" << _Month << "/" << _Year << endl; 
    }

    static bool IsLeapYear(int year)
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    bool IsLeapYear()
    {
        return IsLeapYear(_Year);
    }

    static short NumberOfDaysInYear(short Year)
    {
        return IsLeapYear(Year)? 366 : 365;
    }

    short NumberOfDaysInYear()
    {
        return NumberOfDaysInYear(_Year);
    }

    static short NumberOfHoursInAYear(short Year)
    {
        return NumberOfDaysInYear(Year) * 24;
    }

    short NumberOfHoursInAYear()
    {
        return NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(short Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear()
    {
        return NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(short Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear()
    {
        return NumberOfSecondsInAYear(_Year);
    }

    static short NumberOfDaysInMonth(short Year, short Month)
    {
        // Validation
        if(Month < 1 || Month > 12)
            return 0;

        int NumberOfDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

        return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
    }

    short NumberOfDaysInMonth()
    {
        return NumberOfDaysInMonth(_Year, _Month);
    }

    static short NumberOfHoursInAMonth(short Year, short Month)
    {
        return NumberOfDaysInMonth(Year,Month) * 24;
    }

    short NumberOfHoursInAMonth()
    {
        return NumberOfHoursInAMonth(_Year,_Month);
    }

    static int NumberOfMinutesInAMonth(short Year, short Month)
    {
        return NumberOfHoursInAMonth(Year, Month) * 60;
    }

    int NumberOfMinutesInAMonth()
    {
        return NumberOfMinutesInAMonth(_Year, _Month);
    }

    static int NumberOfSecondsInAMonth(short Year, short Month)
    {
        return NumberOfMinutesInAMonth(Year, Month) * 60;
    }

    int NumberOfSecondsInAMonth()
    {
        return NumberOfSecondsInAMonth(_Year, _Month);
    }

    static short DayOfWeekOrder(short Year, short Month, short Day)
    {
        short a = ( 14 - Month ) / 12;
        short y = Year - a;
        short m = Month + ( 12 * a ) - 2;

        return ( Day + y + ( y / 4) - ( y / 100) + ( y / 400) + ((31 * m) / 12)) % 7;
    }

    static short DayOfWeekOrder(clsDate Date)
    {
        short a = ( 14 - Date.Month() ) / 12;
        short y = Date.Year() - a;
        short m = Date.Month() + ( 12 * a ) - 2;

        return ( Date.Day() + y + ( y / 4) - ( y / 100) + ( y / 400) + ((31 * m) / 12)) % 7;
    }

    short DayOfWeekOrder()
    {
        return DayOfWeekOrder(_Year, _Month, _Day);
    }

    static string DayShortName(short DayOrder)
    {
        string NameOfDays[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

        return NameOfDays[DayOrder];
    }

    string DayShortName()
    {
        return DayShortName(DayOfWeekOrder());
    }

    static string MonthShortName(short Month)
    {

        string MonthNames[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

        return MonthNames[Month - 1];
    }

    string MonthShortName()
    {
        return MonthShortName(_Month);
    }

    static void PrintMonthCalender(short Year, short Month)
    {

        int NumberOfDays;

        int current = DayOfWeekOrder(Year,Month,1);

        NumberOfDays = NumberOfDaysInMonth(Year,Month);

        printf("\n ______________%s______________\n\n",
        MonthShortName(Month).c_str());

        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        int i = 0;
        for(i = 0; i < current; i++)
            printf("     ");

        for(int j = 1; j <= NumberOfDays; j++)
        {
            printf("%5d", j);

            if(++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }

        printf("\n ______________________________\n");

    }

    void PrintMonthCalender()
    {
        PrintMonthCalender(_Year,_Month);
    }

    static void PrintYearCalendar(short Year)
    {

        cout << string(40,'-') << endl;
        cout << "\t Calender - " << Year << endl;
        cout << string(40,'-') << endl;

        for(int i = 1; i <= 12; i++)
        {
            PrintMonthCalender(Year, i);
        }
    }

    void PrintYearCalendar()
    {
        PrintYearCalendar(_Year);
    }

    static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
    {

        for(int i = 1; i < Month; i++)
            Day += NumberOfDaysInMonth(Year,i);

        return Day;
    }

    short NumberOfDaysFromTheBeginingOfTheYear()
    {
        return NumberOfDaysFromTheBeginingOfTheYear(_Day,_Month,_Year);
    }

    static void AddDays(short Days, clsDate &Date)
    {

        short RemainingDays = Days + NumberOfDaysFromTheBeginingOfTheYear(Date.Day(),Date.Month(),Date.Year());
        short MonthDays = 0;

        Date.setMonth(1);

        while(true)
        {
            MonthDays = NumberOfDaysInMonth(Date.Year(),Date.Month());

            if(RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date.setMonth(Date.Month() + 1);

                if(Date.Month() > 12)
                {
                    Date.setMonth(1);
                    Date.setYear(Date.Year() + 1);
                }
            }
            else
            {
                Date.setDay(RemainingDays);
                break;
            }
        }
    }

    void AddDays(short Days)
    {
        AddDays(Days,*this);
    }

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1.Year() < Date2.Year()) ? true : ((Date1.Year() == Date2.Year()) ? (Date1.Month() < Date2.Month() ? true : (Date1.Month() == Date2.Month() ? Date1.Day() < Date2.Day() : false)) : false);
    }

    bool IsDate1BeforeDate2(clsDate Date2)
    {
        return IsDate1BeforeDate2(*this,Date2);
    }

    static bool IsDate1EqualsToDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1.Year() == Date2.Year()) ? ((Date1.Month() == Date2.Month()) ? ((Date1.Day() == Date2.Day()) ? true :false ) :false ) :false;
    }    

    bool IsDate1EqualsToDate2(clsDate Date2)
    {
        return IsDate1EqualsToDate2(*this, Date2);
    }

    static bool isLastDayInMonth(clsDate Date)
    {
        return NumberOfDaysInMonth(Date.Year(),Date.Month()) == Date.Day();
    }

    bool isLastDayInMonth()
    {
        return isLastDayInMonth(*this);
    }

    static bool isLastMonthInYear(clsDate Date)
    {
        return Date.Month() == 12;
    }

    bool isLastMonthInYear()
    {
        return isLastMonthInYear(*this);
    }

    static void IncreaseDateByOneDay(clsDate &Date)
    {

        if(isLastDayInMonth(Date) && isLastMonthInYear(Date))
        {
            Date.setYear(Date.Year() + 1);
            Date.setMonth(1);
            Date.setDay(1);
        } else if(isLastDayInMonth(Date))
        {
            Date.setDay(1);
            Date.setMonth(Date.Month() + 1);
        } else {
            Date.setDay(Date.Day() + 1);
        }
        
    }

    void IncreaseDateByOneDay()
    {
        IncreaseDateByOneDay(*this);
    }

    static void SwapDates(clsDate &Date1, clsDate &Date2)
    {
        clsDate Temp;
        Temp.setDay(Date1.Day());
        Temp.setMonth(Date1.Month());
        Temp.setYear(Date1.Year());

        Date1.setDay(Date2.Day());
        Date1.setMonth(Date2.Month());
        Date1.setYear(Date2.Year());

        Date2.setDay(Temp.Day());
        Date2.setMonth(Temp.Month());
        Date2.setYear(Temp.Year());
    }

    void SwapDates(clsDate &Date2)
    {
        SwapDates(*this,Date2);
    }

    static int DifferenceBetweenTwoDates(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Difference = 0;
        short SwapFlagValue = 1;

        if(!IsDate1BeforeDate2(Date1,Date2))
        {
            //Swap Dates
            SwapDates(Date1,Date2);
            SwapFlagValue = -1;
        }

        while (IsDate1BeforeDate2(Date1,Date2))
        {
            Difference++;
            IncreaseDateByOneDay(Date1);
        }

        return IncludeEndDay? ++Difference * SwapFlagValue : Difference * SwapFlagValue;
    }

    int DifferenceBetweenTwoDates(clsDate Date2, bool IncludeEndDay = false)
    {
        return DifferenceBetweenTwoDates(*this, Date2, IncludeEndDay);
    }

    static void IncreaseDateByXDays(clsDate &Date, short Days)
    {

        for(short i = 1; i <= Days; i++)
        {
            IncreaseDateByOneDay(Date);
        }
    }

    void IncreaseDateByXDays(short Days)
    {
        IncreaseDateByXDays(*this,Days);
    }

    static void IncreaseDateByOneWeek(clsDate &Date)
    {
        IncreaseDateByXDays(Date,7);
    }

    void IncreaseDateByOneWeek()
    {
        IncreaseDateByOneWeek(*this);
    }

    static void IncreaseDateByXWeeks(clsDate &Date, short Weeks)
    {

        for(int i = 1; i <= Weeks; i++)
        {
            IncreaseDateByOneWeek(Date);
        }
    }

    void IncreaseDateByXWeeks(short Weeks)
    {
        IncreaseDateByXWeeks(*this,Weeks);
    }

    static void IncreaseDateByOneMonth(clsDate &Date)
    {

        if(Date.Month() == 12)
        {
            Date.setMonth(1);
            Date.setYear(Date.Year() + 1);
        } 
        else
        {
            Date.setMonth(Date.Month() + 1);
        }

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }
    }

    void IncreaseDateByOneMonth()
    {
        IncreaseDateByOneMonth(*this);
    }

    static void IncreaseDateByXMonth(clsDate &Date, short Months)
    {
        for(int i = 1; i <= Months; i++)
        {
            IncreaseDateByOneMonth(Date);
        }
    }

    void IncreaseDateByXMonth(short Months)
    {
        IncreaseDateByXMonth(*this,Months);
    }

    static void IncreaseDateByOneYear(clsDate &Date)
    {
        
        Date.setYear(Date.Year() + 1);

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }
        
    }

    void IncreaseDateByOneYear()
    {
        IncreaseDateByOneYear(*this);
    }

    static void IncreaseDateByXYears(clsDate &Date, short Year)
    {

        Date.setYear(Date.Year() + Year);

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }
    }

    void IncreaseDateByXYears(short Years)
    {
        IncreaseDateByXYears(*this, Years);
    }

    static void IncreaseDateByOneDecade(clsDate &Date)
    {
        Date.setYear(Date.Year() + 10);

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }
    }

    void IncreaseDateByOneDecade()
    {
        IncreaseDateByOneDecade(*this);
    }

    static void IncreaseDateByXDecades(clsDate &Date, short Decades)
    {
        Date.setYear(Date.Year() + (Decades * 10));

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }
    }

    void IncreaseDateByXDecades(short Decades)
    {
        IncreaseDateByXDecades(*this, Decades);
    }

    static void IncreaseDateByOneCentury(clsDate &Date)
    {
        Date.setYear(Date.Year() + 100);

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }
    }

    void IncreaseDateByOneCentury()
    {
        IncreaseDateByOneCentury(*this);
    }

    static void IncreaseDateByOneMillennium(clsDate &Date)
    {
        Date.setYear(Date.Year() + 1000);

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }
    }

    void IncreaseDateByOneMillennium()
    {
        IncreaseDateByOneMillennium(*this);
    }

    static bool isFirstDayInMonth(clsDate Date)
    {
        return Date.Day() == 1;
    }

    bool isFirstDayInMonth()
    {
        return isFirstDayInMonth(*this);
    }

    static bool isFirstMonthInYear(clsDate Date)
    {
        return Date.Month() == 1;
    }

    bool isFirstMonthInYear()
    {
        return isFirstMonthInYear(*this);
    }

    static void DecreaseDateByOneDay(clsDate &Date)
    {

        if(isFirstDayInMonth(Date) && isFirstMonthInYear(Date))
        {
            Date.setYear(Date.Year() - 1);
            Date.setMonth(12);
            Date.setDay(31);
        } 
        else if(isFirstDayInMonth(Date))
        {
            Date.setMonth(Date.Month() - 1);
            Date.setDay(NumberOfDaysInMonth(Date.Year(),Date.Month()));
        } 
        else 
        {
            Date.setDay(Date.Day() - 1);
        }
    }

    void DecreaseDateByOneDay()
    {
        DecreaseDateByOneDay(*this);
    }

    static void DecreaseDateByXDays(clsDate &Date, short Days)
    {

        for(short i = 1; i <= Days; i++)
        {
            DecreaseDateByOneDay(Date);
        }
    }

    void DecreaseDateByXDays(short Days)
    {
        DecreaseDateByXDays(*this, Days);
    }

    static void DecreaseDateByOneWeek(clsDate &Date)
    {
        DecreaseDateByXDays(Date,7);
    }

    void DecreaseDateByOneWeek()
    {
        DecreaseDateByOneWeek(*this);
    }    

    static void DecreaseDateByXWeeks(clsDate &Date, short Weeks)
    {

        for(int i = 1; i <= Weeks; i++)
        {
            DecreaseDateByOneWeek(Date);
        }
    }

    void DecreaseDateByXWeeks(short Weeks)
    {
        DecreaseDateByXWeeks(*this, Weeks);
    }

    static void DecreaseDateByOneMonth(clsDate &Date)
    {

        if(Date.Month() == 1)
        {
            Date.setMonth(12);
            Date.setYear(Date.Year() - 1);
        } 
        else
            Date.setMonth(Date.Month() - 1);

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
            Date.setDay(NumberOfDaysInCurrentMonth);
    }

    void DecreaseDateByOneMonth()
    {
        DecreaseDateByOneMonth(*this);
    }

    static void DecreaseDateByXMonth(clsDate &Date, short Months)
    {
        for(int i = 1; i <= Months; i++)
        {
            DecreaseDateByOneMonth(Date);
        }
    }

    void DecreaseDateByXMonth(short Months)
    {
        DecreaseDateByXMonth(*this, Months);
    }

    static void DecreaseDateByOneYear(clsDate &Date)
    {
        
        Date.setYear(Date.Year() - 1);

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }   
    }

    void DecreaseDateByOneYear()
    {
        DecreaseDateByOneYear(*this);
    }

    static void DecreaseDateByXYears(clsDate &Date, short Year)
    {

        Date.setYear(Date.Year() - Year);

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }
    }

    void DecreaseDateByXYears(short Year)
    {
        DecreaseDateByXYears(*this, Year);
    }

    static void DecreaseDateByOneDecade(clsDate &Date)
    {
        Date.setYear(Date.Year() - 10);

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }
    }

    void DecreaseDateByOneDecade()
    {
        DecreaseDateByOneDecade(*this);
    }

    static void DecreaseDateByXDecades(clsDate &Date, short Decades)
    {
        Date.setYear(Date.Year() - (Decades * 10));

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }
    }

    void DecreaseDateByXDecades(short Decades)
    {
        DecreaseDateByXDecades(*this, Decades);
    }

    static void DecreaseDateByOneCentury(clsDate &Date)
    {
        Date.setYear(Date.Year() - 100);

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }
    }

    void DecreaseDateByOneCentury()
    {
        DecreaseDateByOneCentury(*this);
    }

    void DecreaseDateByOneMillennium(clsDate &Date)
    {
        Date.setYear(Date.Year() - 1000);

        short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year(),Date.Month());
        if(Date.Day() > NumberOfDaysInCurrentMonth)
        {
            Date.setDay(NumberOfDaysInCurrentMonth);
        }
    }

    void DecreaseDateByOneMillennium()
    {
        DecreaseDateByOneMillennium(*this);
    }

    static bool isEndOfWeek(clsDate Date)
    {
        return DayOfWeekOrder(Date) == 6;
    }

    bool isEndOfWeek()
    {
        return isEndOfWeek(*this);
    }

    static bool isWeekEnd(clsDate Date)
    {
        short DayOrder = DayOfWeekOrder(Date);

        return DayOrder == 5 || DayOrder == 6;
    }

    bool isWeekEnd()
    {
        return isWeekEnd(*this);
    }

    static bool isBusinessDay(clsDate Date)
    {
        return !isWeekEnd(Date);
    }

    bool isBusinessDay()
    {
        return isBusinessDay(*this);
    }

    static short DaysUntilTheEndOfWeek(clsDate Date)
    {
        return 6 - DayOfWeekOrder(Date);
    }

    short DaysUntilTheEndOfWeek()
    {
        return DaysUntilTheEndOfWeek(*this);
    }

    static short DaysUntilTheEndOfMonth(clsDate Date)
    {
        return (NumberOfDaysInMonth(Date.Year(),Date.Month()) - Date.Day() ) + 1;
    }

    short DaysUntilTheEndOfMonth()
    {
        return DaysUntilTheEndOfMonth(*this);
    }

    static short DaysUntilTheEndOfYear(clsDate Date)
    {
        return (NumberOfDaysInYear(Date.Year()) - NumberOfDaysFromTheBeginingOfTheYear(Date.Day(),Date.Month(),Date.Year())) + 1;
    }

    short DaysUntilTheEndOfYear()
    {
        return DaysUntilTheEndOfYear(*this);
    }

    static short CalculateVacationDays(clsDate Date1, clsDate Date2)
    {
        short DaysCount = 0;

        while (IsDate1BeforeDate2(Date1,Date2))
        {
            if(isBusinessDay(Date1))
                DaysCount++;
            
            IncreaseDateByOneDay(Date1);
        }

        return DaysCount;
    }

    short CalculateVacationDays(clsDate Date2)
    {
        return CalculateVacationDays(*this, Date2);
    }

    static void CalculateVacationReturnDate(clsDate &DateFrom, short VacationDays)
    {

        short WeekEndCounter = 0;

        //in case the data  is weekend keep adding one day util you reach business day
        //we get rid of all weekends before the first business day
        while (isWeekEnd(DateFrom))
        {
            IncreaseDateByOneDay(DateFrom);
        }

        //here we increase the vacation dates to add all weekends to it.
        
        for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
        {

            if (isWeekEnd(DateFrom))
                WeekEndCounter++;

            IncreaseDateByOneDay(DateFrom);
        }
        
        //in case the return date is week end keep adding one day util you reach business day
        while (isWeekEnd(DateFrom))
        {
            IncreaseDateByOneDay(DateFrom);
        }
    }

    void CalculateVacationReturnDate(short VacationDays)
    {
        CalculateVacationReturnDate(*this, VacationDays);
    }

    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1,Date2) && !IsDate1EqualsToDate2(Date1,Date2));
    }

    bool IsDate1AfterDate2(clsDate Date2)
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    static bool isValidDate(clsDate Date)
    {
        return (Date.Month() >= 1 && Date.Month() <= 12)? ((NumberOfDaysInMonth(Date.Year(),Date.Month()) >= Date.Day() && Date.Day() >= 1)? true : false) : false;
    }

    bool isValidDate()
    {
        return isValidDate(*this);
    }

    static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
    {
        return IsDate1EqualsToDate2(Date1,Date2)? enDateCompare::Equal : IsDate1BeforeDate2(Date1,Date2)? enDateCompare::Before : enDateCompare::After;
    }

    static string DateToString(clsDate Date)
    {
        return to_string(Date.Day()) + "/" + to_string(Date.Month()) + "/" + to_string(Date.Year());
    }
    
    string DateToString()
    {
        return DateToString(*this);
    }

    static string GetSystemDateTimeString()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day, Month, Year, Hour, Minute, Second;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday; 
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;

        return ( to_string(Day) + "/" + to_string(Month) + "/"
            + to_string(Year) + " - "
             + to_string(Hour) + ":"
              + to_string(Minute) + ":" + to_string(Second));
    }

};

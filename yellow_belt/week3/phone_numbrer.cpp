#include <string>
#include<iostream>
#include "phone_number.h"

using namespace std;


    /* Принимает строку в формате +XXX-YYY-ZZZZZZ
       Часть от '+' до первого '-' - это код страны.
       Часть между первым и вторым символами '-' - код города
       Всё, что идёт после второго символа '-' - местный номер.
       Код страны, код города и местный номер не должны быть пустыми.
       Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

       Примеры:
       * +7-495-111-22-33
       * +7-495-1112233
       * +323-22-460002
       * +1-2-coursera-cpp
       * 1-2-333 - некорректный номер - не начинается на '+'
       * +7-1233 - некорректный номер - есть только код страны и города
    */
    PhoneNumber::PhoneNumber(const string &international_number)
    {
        string str = international_number;
        if(str[0] != '+')
            throw invalid_argument("Error1");
        bool flag1 = false, flag2  = false, flag3 = false;
        int pos = 0, bpos = 0;
        for(int i = 1; i < str.size();i++)
        {

            if(str[i] == '-')
            {
                pos = i;
                bpos = pos+1;
                flag1 = true;
                break;
            }

        }
        if(flag1 == false)
            throw invalid_argument("Error2");
        country_code_ = str.substr(1,pos-1);

        for(int i = bpos; i < str.size() ;i++)
        {

            if(str[i] == '-')
            {
                pos = i;
                flag2 = true;
                break;
            }
        }
        if(flag2 == false)
            throw invalid_argument("Error3");
        city_code_ = str.substr(bpos,pos-bpos);

        bpos = pos+1;
        for(int i = pos+1; i < str.size() ;i++)
        {

            //cout << str[i] << endl;
            if(i == str.size()-2 || str[i] == '\n')
            {
                flag3 = true;
                pos = i;
                break;
            }
        }

        if(flag3 == false)
            throw invalid_argument("Error4");

            
        local_number_ = str.substr(bpos,pos-bpos+2);

    }

    string PhoneNumber::GetCountryCode() const
    {
        return country_code_;
    }
   string PhoneNumber::GetCityCode() const
    {
        return city_code_;
    }
   string PhoneNumber::GetLocalNumber() const
    {
        return local_number_;
    }
   string PhoneNumber::GetInternationalNumber() const
    {
        return "+"+country_code_+"-"+city_code_+"-"+local_number_;
    }

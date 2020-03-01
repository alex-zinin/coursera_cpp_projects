//#include<iostream>
//#include "new_booking_providers.h"

namespace RAII
{

    template<typename Provider>
    class Booking
    {
    public:
        Booking(): counter(Provider::Counter), provider(nullptr) {
           Provider::counter++;
        }
        Booking(Provider* pr,  int c): provider(pr), counter(c){
            Provider::counter++;
        }
        ~Booking()
        {
            if(Provider::counter <= 1)
                Provider::counter = 0;
            else
                Provider::counter--;
            counter = 0;
        }
    private:
        Provider* provider;
        int counter;
    };
}
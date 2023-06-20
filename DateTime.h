#include<iostream>
#include<string>
#include<ctime>
using namespace std;
class DateTime{
    public:
        int day, month, year, hour, minute, second;
        DateTime(){ SetDateTime(); }
        auto GetTime() const {
            return (to_string(hour) + ":" + to_string(minute) + ":" + to_string(second));
        }
        auto GetDate() const {
            return (to_string(day)+"-"+to_string(month)+"-"+to_string(year));
        }
        auto SetCurrentTime() {
            time_t currentTime = time(nullptr);
            tm* localTime = localtime(&currentTime);
            hour = localTime->tm_hour;
            minute = localTime->tm_min;
            second = localTime->tm_sec;
        }
        auto SetCurrentDate() {
            time_t currentTime = time(nullptr);
            tm* localTime = localtime(&currentTime);
            day = localTime->tm_mday;
            month = localTime->tm_mon;
            year = localTime->tm_year;
        }
        auto SetDateTime()->void{
            SetCurrentDate();
            SetCurrentTime();
        }
	auto GetHour() const { return hour; }
        friend ostream& operator<<(ostream& os, const DateTime& time) {
            os<<time.day<<"-"<<time.month<<"-"<<time.year<<" "<<time.hour<<":"<<time.minute<<":"<<time.second;
            return os;
        }
};

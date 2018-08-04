#include "Time.hpp"

Time::Time() {
	ms = std::chrono::steady_clock::now();
	elapsed = std::chrono::milliseconds(0);
}
Time::Time(const Time& t) {
	ms = t.ms;
	elapsed = t.elapsed;
}
Time::~Time() {
}
Time& Time::operator=(const Time& t) {
	ms = t.ms;
	elapsed = t.elapsed;
	return *this;
}
ofstream& operator << (ofstream& out, Time &T) {
	out << (long)(T.getElapsed()*1000) << '\n'; //tak newline, lebih sering sebagai elemen
	out << std::chrono::duration_cast<std::chrono::milliseconds>(T.elapsed).count();
	return out;
}
ifstream& operator >> (ifstream& in, Time &T) {
	long timeelapsed;
	in >> timeelapsed;
	T.ms = std::chrono::steady_clock::now() - std::chrono::milliseconds((long)timeelapsed);
	in >> timeelapsed;
	T.elapsed = std::chrono::milliseconds((long)timeelapsed);
	return in;
}
double Time::getElapsed() const {
	return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - ms).count())/1000.0;
}
void Time::resetTime() {
	ms = std::chrono::steady_clock::now();
}
void Time::markTime() {
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - ms);
}
void Time::continueTime() {
	ms = std::chrono::steady_clock::now() - elapsed;
}
string Time::toString() const {
	int dur = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - ms).count());
	string str = to_string(dur/60000) + ":";
	dur %= 60000;
	if (dur < 10000)
		str += "0";
	str += to_string(dur/1000) + ".";
	dur %= 1000;
	if (dur < 100) {
		str += "0";
		if (dur < 10)
			str += "0";
	}
	str += to_string(dur%1000);
	return str;
}
void Time::setTime(long ms) {
	this->ms = std::chrono::steady_clock::now() - std::chrono::milliseconds((long)ms);
}

std::string getNowTime() {
	std::time_t currtime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	return std::ctime(&currtime);
}

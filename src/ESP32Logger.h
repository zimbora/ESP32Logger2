/*
 Name:		ESP32Logger.h
 Created:	4/20/2021 11:19:33 PM
 Author:	Martin
 Editor:	http://www.visualmicro.com
*/

#ifndef _ESP32Logger_h
#define _ESP32Logger_h

#include "Arduino.h"

enum class ESP32LogLevel {
	Error,
	Info,
	Debug
};

enum class ESP32Timestamp {
	TimestampNone,
	TimestampSinceStart,
	TimestampLocaltime
};

class ESP32Logger {
public:
	void init(Print* output, ESP32Timestamp useTimestamp = ESP32Timestamp::TimestampSinceStart);
	void start();
	void stop();
	void setLogLevel(ESP32LogLevel logLevel);
	void log(ESP32LogLevel logLevel, const char* message, ...);

private:
	ESP32LogLevel _logLevel = ESP32LogLevel::Info;
	Print* _output = nullptr;
	ESP32Timestamp _useTimestamp = ESP32Timestamp::TimestampSinceStart;
	bool _isActive = false;

	void print(const char* logLine);
	void printEoL();
};

#endif // #ifndef _ESP32Logger_h

#ifdef ESP32DEBUGGING

#ifndef _ESP32Logger_2
#define _ESP32Logger_2
ESP32Logger Log;
#endif // #ifndef _ESP32Logger_2

// For "##__VA_ARGS__" see https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
#define DBGINI(output, ...) Log.init(output, ##__VA_ARGS__);
#define DBGSTA Log.start();
#define DBGSTP Log.stop();
#define DBGLEV(loglevel) Log.setLogLevel(ESP32LogLevel::loglevel);
#define DBGCOD(debugexpression) debugexpression
#define DBGLOG(loglevel, logmsg, ...) { String logstr = String(__func__) + ": " + String(logmsg); Log.log(ESP32LogLevel::loglevel, logstr.c_str(), ##__VA_ARGS__); }
#define DBGCHK(loglevel, cond, logmsg, ...) if(!(cond)) DBGLOG(loglevel, logmsg, ##__VA_ARGS__)

#else // #ifdef ESP32DEBUGGING

// No debugging, i.e. empty definitions.
#define DBGINI(output, ...) ;
#define DBGSTA ;
#define DBGSTP ;
#define DBGLEV(loglevel) ;
#define DBGCOD(debugexpression) ;
#define DBGLOG(loglevel, logmsg, ...) ;
#define DBGCHK(loglevel, cond, logmsg, ...) ;

#endif // #ifdef ESP32DEBUGGING



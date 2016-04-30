#include "Logger.h"

using namespace MCTSG;

Logger::Logger()
{
	_fptrLog = NULL;
}

Logger::Logger(const std::string &path)
{
	// initiate the logger
	init(path);
}

Logger::~Logger()
{
	// close the log
	if(_fptrLog)
		fclose(_fptrLog);
}

// initiate the log if hasn't been
void Logger::init(const std::string &path)
{
	// if the log hasn't been initiated
	if(!_fptrLog)
	{
		_logPath = path;
		_fptrLog = fopen(path.c_str(), "a");

		// failed to open
		if(!_fptrLog)
		{
			BWAPI::Broodwar << "ERROR: Can't initiate the logger." << std::endl;
		}
	}
	else
	{
		// error message
		log("Logger has already been initiated!");
	}
		
}

// log a string with timestamp and newline
void Logger::log(const std::string &str) const
{
	// if not initiated
	if(!_fptrLog)
		return;

	// timestamp
	timestamp();

	// log
	std::string strOut = str + "\n";
	fprintf(_fptrLog, strOut.c_str());
}

// log a state
void Logger::log(const State &state) const
{
	// if not initiated
	if(!_fptrLog)
		return;

	// timestamp
	timestamp();
	fprintf(_fptrLog, "\n");
	fprintf(_fptrLog, "\t<State>\n");
	fprintf(_fptrLog, "\n");
	
	// time frame
	fprintf(_fptrLog, "\tTime Frame = %d\n", state.getTimeFrame());
	fprintf(_fptrLog, "\n");

	// ally units
	fprintf(_fptrLog, "\tAlly Units (%d):\n", state.getAllyUnitsNum()); // title
	Unitset allyUnits = state.getAllyUnits();
	logUnits(allyUnits);

	// enemy units
	fprintf(_fptrLog, "\tEnemy Units (%d):\n", state.getEnemyUnitsNum()); // title
	Unitset enemyUnits = state.getEnemyUnits();
	logUnits(enemyUnits);
}

// log an integer
void Logger::log(const long long num) const
{
	timestamp();
	fprintf(_fptrLog, "%lld\n", num);
}

void Logger::log(const double num) const
{
	timestamp();
	fprintf(_fptrLog, "%lf\n", num);
}

// support function of log state
void Logger::logUnits(const Unitset &units) const
{
	for(Unitset::const_iterator itr = units.begin(); itr != units.end(); itr++)
	{
		Unit unit = itr->second;
		fprintf(_fptrLog, "\t\t%2d %-20s (%4d,%4d) %4d %4d %5d %5d\n",
			unit->getID(),
			unit->getType().toString().c_str(),
			unit->getPosition().x, unit->getPosition().y,
			unit->getHitPoints(),
			unit->getShields(),
			unit->getNextCanAttackFrame(),
			unit->getNextCanMoveFrame());
	}
	fprintf(_fptrLog, "\n");
}

// prefix for every log message
void Logger::timestamp() const
{
	time_t now = time(0); // get current time
	tm *timeStruct = localtime(&now); // convert to local time struct

	// print out the timestamp prefix
	fprintf(_fptrLog, "[%04d/%02d/%02d %02d:%02d:%02d] ",
			timeStruct->tm_year + 1900,
			timeStruct->tm_mon + 1,
			timeStruct->tm_mday,
			timeStruct->tm_hour,
			timeStruct->tm_min,
			timeStruct->tm_sec);
}
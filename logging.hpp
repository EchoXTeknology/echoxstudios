////////////////////////////////////////////////////////////
//
// File: logging.hpp
// Copyright (C) 2018-2020 EchoXTeknology (lead@echoxteknology-dev.org)
// Copyright (C) 2018-2020 EchoXStudios (echoxstudios@echoxteknology-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////



#ifndef ECHOXSTUDIOS_LOGGING_HPP
#define ECHOXSTUDIOS_LOGGING_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "stdafx.hpp"



////////////////////////////////////////////////////////////
// Declare/Define Class: [Logging]
////////////////////////////////////////////////////////////
class LoggingProgram
{
public:
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// \brief std::string file logging system, includes time stamp...
	//
	// \param @fileDir: List file directory. No file name, and/or file extension, required...
	// \param @logStr:  Log String (Message) that will be written to file...
	// \param @sevLev:  Integer for Severity Level 0 to (n)	[0: HIGHEST, (n): LOWEST]
	// \param @flags:   For debugging reasons, writes output to a console (if given value of true)
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////
	inline void sErrorLogging(std::string fileDir, std::string logStr, const unsigned int sevLev, bool flags)
	{
		TimeStamp timeStamp;

		std::string fileLoc = fileDir + "/log_" + timeStamp.sTimeStamp(1) + ".tmp";
		std::string curTime = timeStamp.sTimeStamp(2);

		std::ofstream logStr_s(fileLoc.c_str(), std::ios_base::out | std::ios_base::app);

		switch (flags)
		{
		case true:
			std::cout << "[ " << curTime << " ]\t" << logStr << "\t" << "[" << SeverityLevel[sevLev] << "]" << std::endl;

			logStr_s << "[ " << curTime << " ]\t" << logStr << "\t" << "[" << SeverityLevel[sevLev] << "]" << std::endl;
			logStr_s.close();
			break;
		case false:
			logStr_s << "[ " << curTime << " ]\t" << logStr << "\t" << "[" << SeverityLevel[sevLev] << "]" << std::endl;
			logStr_s.close();
			break;
		}
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////
	// \brief const char* file logging system, includes time stamp...
	//
	// \param @fileDir: List file directory. No file name, and/or file extension, required...
	// \param @logStr:  Log String (Message) that will be written to file...
	// \param @sevLev:  Integer for Severity Level 0 to (n)	[0: HIGHEST, (n): LOWEST]
	// \param @flags:   For debugging reasons, writes output to a console (if given value of true)
	//
	// @BROKEN: DO NOT USE! IS NOT YET CREATED/INITIALIZED!
	/////////////////////////////////////////////////////////////////////////////////////////////////
	inline void cErrorLogging(const char* fileDir, const char* logStr, const unsigned int sevLev, bool flags)
	{

	}


private:
	const char* SeverityLevel[16] =
	{
		/* [ Log Severity ] [ Reference #] */
			"   FATAL   ",	// 0
			"   ERROR   ",	// 1
			"  WARNING  ",	// 2
			"   DEBUG   ",	// 3
			"           ",	// 4
			"           ",	// 5
			"           ",	// 6
							// RESERVED FOR EXTRA LABELS
	};



	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Structure: TimeStamp
	//
	// \ref sTimeStamp(..)
	/////////////////////////////////////////////////////////////////////////////////////////////////
	struct TimeStamp
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////
		// \brief std::string time stamping function
		//
		// \param @stampVal: initial time stamping value, determines which time stamp to return...
		/////////////////////////////////////////////////////////////////////////////////////////////////
		inline std::string sTimeStamp(const int stampVal)
		{
			time_t curTime = time(0);
			struct tm tstruct;
			char buf[80];
			tstruct = *localtime(&curTime);

			switch (stampVal)
			{
			case 0:
				strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
				break;
			case 1:
				strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
				break;
			case 2:
				strftime(buf, sizeof(buf), "%X", &tstruct);
				break;
			default:
				strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
				break;
			}

			return std::string(buf);
		}
	};

};

#endif // ! ECHOXSTUDIOS_LOGGING_HPP

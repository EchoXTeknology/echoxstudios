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

/*
List of common, "comment," references:
@INDEV
@TODO

@fileDir
@logStr
@sevLev
@flags

@stampVal
*/



////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "stdafx.hpp"



////////////////////////////////////////////////////////////
// Pre-defined User definitions
////////////////////////////////////////////////////////////
typename unsigned int size_t;					// For those that are using standalone compiling...
								// If not remove, or comment...


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
	inline void sErrorLogging(std::string fileDir, std::string logStr, const size_t sevLev, bool flags)
	{
		TimeStamp timeStamp;

		std::string fileLoc = fileDir + "/log_" + timeStamp.sTimeStamp(1) + ".tmp";
		std::string curTime = timeStamp.sTimeStamp(2);

		std::ofstream logStr_s(fileLoc.c_str(), std::ios_base::out | std::ios_base::app);

		switch (flags)
		{
		case true:		// Logging is displayed on compiler console window & saved to [fileDir]/FILE
			std::cout << "[ " << curTime << " ]\t" << logStr << "\t" << "[" << SeverityLevel[sevLev] << "]" << std::endl;

			logStr_s << "[ " << curTime << " ]\t" << logStr << "\t" << "[" << SeverityLevel[sevLev] << "]" << std::endl;
			logStr_s.close();
			break;
		case false:		// Logging is not displayed to compiler console window, as it is saved to [fileDir]/FILE instead
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
	// @INDEV: DO NOT USE! IS NOT YET CREATED/INITIALIZED!
	/////////////////////////////////////////////////////////////////////////////////////////////////
	inline void cErrorLogging(const char* fileDir, const char* logStr, const size_t sevLev, bool flags)
	{
		// @TODO: Create const char* logging system? For cross-platform compatability or standalone projects?
	}


private:
	const char* SeverityLevel[16] =
	{
		/* [ Log Severity ] [ Reference #] */
			"   FATAL   ",	// 0
			"   ERROR   ",	// 1
			"  WARNING  ",	// 2
			"   DEBUG   ",	// 3
			"           ",	// 4		   RESERVED FOR EXTRA LABEL
			"           ",	// 5		   RESERVED FOR EXTRA LABEL
			"           ",	// 6		   RESERVED FOR EXTRA LABEL
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
		inline std::string sTimeStamp(const size_t stampVal)
		{
			time_t curTime = time(0);
			struct tm tstruct;
			char buf[80];
			tstruct = *localtime(&curTime);

			switch (stampVal)
			{
			case 0:	// Returns YYYY-MM-DD HH:MM:SS
				strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
				return std::string(buf);
			case 1: // Returns YYYY-MM-DD
				strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
				return std::string(buf);
			case 2: // Returns HH:MM:SS
				strftime(buf, sizeof(buf), "%X", &tstruct);
				return std::string(buf);
			default: // Defaults to Switch Case: (0)
				strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
				return std::string(buf);
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////
			// Return std::string(buf), if not done already...
			/////////////////////////////////////////////////////////////////////////////////////////////////
			return std::string(buf);
		}
	};

};

#endif // !ECHOXSTUDIOS_LOGGING_HPP

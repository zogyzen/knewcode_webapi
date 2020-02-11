#pragma once

#include "common/knewcode_version.h"
#include "util/auto_release.h"
#include "util/backtrace_symbols.h"
#include "util/proc_meminfo.h"

#include <string>
#include <fstream>

#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time.hpp>
#include <boost/process.hpp>

namespace KC
{
	// 临时写日志
	class CTempLog
	{
	public:
            static void Write(std::string sInfo, std::string sPos)
	    {
                std::string sLogDir = boost::filesystem::initial_path<boost::filesystem::path>().string() + "/" + c_KnewcodeVersion;
                if (!boost::filesystem::exists(sLogDir)) boost::filesystem::create_directories(sLogDir);
                std::string sLogFile = sLogDir + "/" + boost::lexical_cast<std::string>(boost::this_process::get_id()) + "-" + boost::lexical_cast<std::string>(std::this_thread::get_id()) + ".log";
                std::ofstream flog(sLogFile, std::ios::out | std::ios::app);
                CAutoRelease _auto(boost::bind(&std::ofstream::close, &flog));
                flog << "[" << boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()) << "] " << sInfo << std::endl << sPos << std::endl
                     << (" - >>> " + CProcMemInfo::Get() + " <<<") << std::endl << CBacktraceSymbols::Get() << std::endl;
	    }
	};
}

#pragma once

#include <stdexcept>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/process.hpp>

namespace KC
{
        // 基础异常
	class TException : public std::runtime_error
	{
	public:
                TException(int id, std::string place, std::string msg) : std::runtime_error(msg), m_id(id), m_place(place) {}
		virtual ~TException() throw () {}

                virtual const char* what() const { return std::runtime_error::what(); }

                virtual std::string error_info(void) const
		{
                    return std::string() + std::runtime_error::what()
                    + " [" + boost::lexical_cast<std::string>(boost::this_process::get_id()) + ":" + boost::lexical_cast<std::string>(boost::this_thread::get_id())
                    + "][" + m_place + "][" + boost::lexical_cast<std::string>(m_id) + "][" + m_ExceptType + "]"
                    + m_backtrace;
        }
		virtual int error_id(void) const { return m_id; }
                virtual std::string error_place(void) const { return m_place; }

    public:
        std::string& CurrPosInfo(void) { return m_CurrPosInfo; }
        std::string& ExceptType(void) { return m_ExceptType; }
        std::string& OtherInfo(void) { return m_OtherInfo; }
        std::string& BackTrace(void) { return m_backtrace; }

	protected:
		const int m_id = 0;
                const std::string m_place = "";
                std::string m_CurrPosInfo = "", m_ExceptType = typeid(*this).name(), m_OtherInfo = "", m_backtrace = "";
	};
}

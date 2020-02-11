#pragma once

#include <string>
#include <sstream>
#include <thread>

#include <boost/date_time.hpp>
#include <boost/algorithm/string.hpp>

namespace KC
{
	// ��������
	struct CUtilFunc
	{
		// ��ʽ��·���ַ���
                static std::string FormatPath(std::string sPath)
		{
            boost::algorithm::trim_right_if(sPath, boost::algorithm::is_any_of("\\"));
            boost::algorithm::trim_right_if(sPath, boost::algorithm::is_any_of("/"));
            return sPath;
		}

		// �ַ���ȫСд
                static std::string StrToLower(std::string str)
		{
            boost::algorithm::trim(str);
		    boost::algorithm::to_lower(str);
            return str;
		}

		// ��ȫת���ַ���
                static std::string PCharSafeToStr(const char* p)
		{
		    return nullptr == p ? "" : p;
		}

                static std::string TimeToStr(boost::posix_time::ptime pt, std::string fmt)
		{
            boost::posix_time::time_input_facet input_facet(fmt);
            std::stringstream ss;
            ss.imbue(std::locale(ss.getloc(), &input_facet));
            ss << pt;
            return ss.str();
		}

                static boost::posix_time::ptime StrToTime(std::string dt, std::string fmt)
		{
            boost::posix_time::time_input_facet input_facet(fmt);
            std::stringstream ss;
            ss.imbue(std::locale(ss.getloc(), &input_facet));
            ss << dt;
            boost::posix_time::ptime pResult;
            ss >> pResult;
            return pResult;
		}

		// ��׼ʱ���ʽת��ΪGMT��ʽʱ��
                static std::string ISO2GMT(std::string dt)
		{
		    boost::posix_time::ptime pt = boost::posix_time::time_from_string(dt);
		    return CUtilFunc::TimeToStr(pt, "%a, %d %b %Y %H:%M:%S %z");
		}

		// GMTʱ���ʽת��Ϊ��׼��ʽʱ��
                static std::string GMT2ISO(std::string dt)
		{
		    boost::posix_time::ptime pt = CUtilFunc::StrToTime(dt, "%a, %d %b %Y %H:%M:%S %z");
		    return CUtilFunc::TimeToStr(pt, "%Y-%m-%d %H:%M:%S");
		}

                // ��ǰ�߳�ID
                static int CurrThreadID(void)
                {
                    std::ostringstream oss;
                    oss << std::this_thread::get_id();
                    std::string stid = oss.str();
                    return std::stoi(stid);
                }
        };
}

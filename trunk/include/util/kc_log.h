#pragma once

#include <iostream>
#include <string>

//#undef _WIN32_WINNT
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/process.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/common.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/record_ordering.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/detail/format.hpp>
#include <boost/log/detail/process_id.hpp>
#include <boost/log/detail/thread_id.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;

using boost::shared_ptr;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)
BOOST_LOG_ATTRIBUTE_KEYWORD(log_severity, "Severity", logging::trivial::severity_level)

typedef sinks::text_file_backend backend_t;
typedef sinks::asynchronous_sink<
    backend_t,
    sinks::unbounded_ordering_queue<logging::attribute_value_ordering<unsigned int, std::less<unsigned int>>>
> sink_t;
typedef boost::shared_ptr<sink_t> sink_tptr;

namespace KC
{
    class MyLog
    {
    public:
      // 在使用之前必须先调用此函数
      void Init(std::string dir, unsigned id, boost::log::trivial::severity_level lv)
      {
                if (!boost::filesystem::exists(dir))
                        boost::filesystem::create_directories(dir);
                // string exePath = boost::filesystem::initial_path<boost::filesystem::path>().leaf().string();
                //sink_tptr sink(new sink_t(boost::make_shared<backend_t>(), keywords::order = logging::make_attr_ordering("RecordID", std::less<unsigned int>())));
                //m_sink.reset(new sink_t(boost::make_shared<backend_t>(), keywords::order = logging::make_attr_ordering("RecordID", std::less<unsigned int>())));
                auto odAttr = logging::make_attr_ordering("RecordID", std::less<unsigned int>());
                //auto sinkBack = boost::make_shared<backend_t>();
                auto sinkBack = new backend_t;
                auto sinkPtr = new sink_t(sinkBack, keywords::order = odAttr);
                m_sink.reset(sinkPtr);
                m_sink->locked_backend()->set_rotation_size(1024 * 1024 * 8);
                m_sink->locked_backend()->set_file_name_pattern(dir + "/" + (boost::format("%d_%d") % id % boost::this_process::get_id()).str() + ".log");
                //m_sink->locked_backend()->set_file_collector(sinks::file::make_collector(
                //    keywords::target = dir + "/back/" + boost::lexical_cast<std::string>(::_getpid())        //备份文件夹名
                //    //, keywords::max_size = 50 * 1024 * 1024           // 文件夹所占最大空间
                //    //, keywords::min_free_space = 100 * 1024 * 1024    // 磁盘最小预留空间
                //));
                m_sink->locked_backend()->auto_flush(true);
                //m_sink->locked_backend()->scan_for_files();

                m_sink->set_filter(log_severity >= lv);
                //m_sink->imbue(std::locale("zh_CN.UTF-8"));   // 本地化
                m_sink->set_formatter
                (
                        expr::stream
                        << "[#" << expr::attr<unsigned int>("RecordID")
                        << " &" << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
                        << " @" << expr::attr<logging::aux::process::id>("ProcessID")
                        << ":" << expr::attr<logging::aux::thread::id>("ThreadID")
                        << " *" << logging::trivial::severity
                        << "] " << expr::smessage << std::endl
                );

                logging::add_common_attributes();

                // Add it to the core
                logging::core::get()->add_sink(m_sink);

                // Add some attributes too
                logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
                logging::core::get()->add_global_attribute("RecordID", attrs::counter<unsigned int>(1));
	  }

	  // 结束后调用此函数
          void Free(void)
	  {
			  m_sink->stop();
			  m_sink.reset();

              logging::core::get()->flush();
              logging::core::get()->remove_all_sinks();

			  //logging::core::get()->remove_sink(m_sink);
			  //m_sink->stop();
			  //m_sink->flush();
			  //m_sink.reset();
	  }

          // 写日志
          void WriteLog(std::string sMsg, boost::log::trivial::severity_level level = boost::log::trivial::info)
          {
              BOOST_LOG_SEV(s_slg, level) << sMsg;
          }

          // 提交
          void Flush(void)
          {
              try
              {
                  logging::core::get()->flush();
              }
              catch (...) {}
          }

    public:
          boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> s_slg;
          sink_tptr m_sink;
    };
}

#define MY_BOOST_LOG_SEV(logger, lvl) BOOST_LOG_SEV((logger.s_slg), lvl)
#define MY_BOOST_LOG_SEV_DEBUG(logger) MY_BOOST_LOG_SEV(logger, boost::log::trivial::debug)
#define MY_BOOST_LOG_SEV_LOG(logger) MY_BOOST_LOG_SEV(logger, boost::log::trivial::info)
#define MY_BOOST_LOG_SEV_ERR(logger) MY_BOOST_LOG_SEV(logger, boost::log::trivial::error)

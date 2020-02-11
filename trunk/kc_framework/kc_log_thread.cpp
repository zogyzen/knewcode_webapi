#include "std.h"
#include "kc_log_thread.h"

//---------------------------------------------------------------------------
// CLogThread类
CLogThread::CLogThread(IBundleContext& bc) : m_context(bc), m_mtx(m_context.LockWork())
{
}
CLogThread::~CLogThread(void)
{
    BreakRun();
}

void CLogThread::WriteLog(TLogInfo& log)
{
    log::trivial::severity_level lv = log::trivial::info;
    switch (log.m_level)
    {
    case TLogInfo::lglvTrace:
        lv = log::trivial::trace;
        break;
    case TLogInfo::lglvDebug:
        lv = log::trivial::debug;
        break;
    case TLogInfo::lglvInfo:
        lv = log::trivial::info;
        break;
    case TLogInfo::lglvWarning:
        lv = log::trivial::warning;
        break;
    case TLogInfo::lglvError:
        lv = log::trivial::error;
        break;
    case TLogInfo::lglvFatal:
        lv = log::trivial::fatal;
        break;
    }
    MY_BOOST_LOG_SEV(m_log, lv) << "  \t"
            << log.m_ProcessID << ":" << log.m_threadID << " [" << CProcMemInfo::Get() << "] \t@" << log.m_place << endl
            << log.m_info << endl
            << log.m_other << " \t&\t " << log.m_excpType << " \t&\t " << log.m_excpID << endl
            << log.m_bundleName << " \t&\t " << log.m_serviceName << " \t&\t " << log.m_serviceGUID << " \t&\t " << log.m_refID << endl
            ;
}

bool CLogThread::WriteLogList(void)
{
    vector<TLogInfo> logList;
    {
        CKcLock lck(m_mtx);
        if (!m_logList.empty()) m_logList.swap(logList);
    }
    bool bResult = logList.empty();
    if (!bResult)
        for (TLogInfo& log: logList)
            this->WriteLog(log);
    return bResult;
}

void CLogThread::RunThd(void)
{
    while (!m_end)
        if (this->WriteLogList())
            boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
}

void CLogThread::BreakRun(void)
{
    if (nullptr != m_thrd && m_thrd->joinable())
    {
        //pthread_cancel(m_thrd->native_handle());
        m_thrd->interrupt();
        //m_thrd->join();
        m_thrd->timed_join(1000);
    }
    if (nullptr != m_thrd)
    {
        delete m_thrd;
        m_thrd = nullptr;
        this->WriteLogList();
    }
}

void CLogThread::Start(void)
{
    // 日志等级
    string sLv = m_context.GetCfgInfo("Config.Parameters.logging", "Level", "info");
    if ("trace" == sLv) m_logLevel = log::trivial::trace;
    else if ("debug" == sLv) m_logLevel = log::trivial::debug;
    else if ("info" == sLv) m_logLevel = log::trivial::info;
    else if ("warning" == sLv) m_logLevel = log::trivial::warning;
    else if ("error" == sLv) m_logLevel = log::trivial::error;
    // 日志目录
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
    string strDateDir = (format("%d") % (today.year() * 10000 + today.month() * 100 + today.day())).str();
    string sLogDir = string(m_context.getPath()) + "/" + c_LogDirectoryName + strDateDir;
    // 初始化日志
    m_log.Init(sLogDir.c_str(), today.week_number(), m_logLevel);
    // 启动线程
    if (string(m_context.GetCfgInfo("Config.Parameters.log_use_thread", "value", "0")) == "1")
        m_thrd = new boost::thread(&CLogThread::RunThd, this);
}

void CLogThread::Stop(void)
{
    m_end = true;
    BreakRun();
    m_log.Free();
}

void CLogThread::AppendLog(TLogInfo& log)
{
    if (nullptr != m_thrd)
    {
        CKcLock lck(m_mtx);
        m_logList.push_back(log);
    }
    else this->WriteLog(log);
}

log::trivial::severity_level CLogThread::GetCfgLogLevel(void) const
{
    return m_logLevel;
}

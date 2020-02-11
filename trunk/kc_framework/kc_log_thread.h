#pragma once

namespace KC
{
    class CLogThread
    {
    public:
        CLogThread(IBundleContext&);
        ~CLogThread(void);

        void Start(void);
        void Stop(void);

        void AppendLog(TLogInfo&);
        log::trivial::severity_level GetCfgLogLevel(void) const;

    private:
        void WriteLog(TLogInfo&);
        bool WriteLogList(void);
        void RunThd(void);
        void BreakRun(void);

    private:
        IBundleContext& m_context;
        vector<TLogInfo> m_logList;
        CKcMutex m_mtx;
        bool m_end = false;
        boost::thread* m_thrd = nullptr;
        // 日志
        log::trivial::severity_level m_logLevel = log::trivial::info;
        MyLog m_log;
    };
}

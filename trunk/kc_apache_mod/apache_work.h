#pragma once

namespace KC
{
    class CAPACHEWork
    {
    public:
        CAPACHEWork(string, string);
        ~CAPACHEWork();

        // 初始化
        void Init(void);
        // 处理请求
        void Work(request_rec& r);

    private:
        // 初始化锁
        boost::mutex m_mtxInit;
        // 框架路径、模块、主页目录
        string m_FxPath, m_FxDll, m_PgPath;
        // 主框架
        BundleContextHelper m_contHelp;
        // 主插件上下文
        IBundleContext &m_BundleContextIF;
        // 主应用引用
        IServiceReference* m_WebMainRef = nullptr;
    };
}

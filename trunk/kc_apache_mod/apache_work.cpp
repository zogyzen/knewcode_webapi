#include "std.h"
#include "apache_work.h"
#include "request_respond.h"

////////////////////////////////////////////////////////////////////////////////
// CAPACHEWork类
KC::CAPACHEWork::CAPACHEWork(string fxPath, string pgPath)
    : m_FxPath(fxPath), m_FxDll(m_FxPath + "/" + c_frameworkDllName), m_PgPath(pgPath)
    , m_contHelp(m_FxPath.c_str()), m_BundleContextIF(m_contHelp.getContext())
{
}

KC::CAPACHEWork::~CAPACHEWork()
{
    m_BundleContextIF.freeServiceReference(m_WebMainRef);
}

// 初始化
void KC::CAPACHEWork::Init(void)
{
    // 初始化锁
    m_mtxInit.lock();
    CAutoRelease _auto(boost::bind(&boost::mutex::unlock, &this->m_mtxInit));
    // 获取主处理应用
    if (nullptr == m_WebMainRef)
        m_WebMainRef = m_BundleContextIF.takeServiceReference(c_KCWebApiWorkSrvGUID);
}

// 处理请求
void KC::CAPACHEWork::Work(request_rec& r)
{
    try
    {
        // 设置返回类型
        r.content_type = "text/html";
        //apr_table_set(r.headers_out, "Set-Cookie", "KC_ID=101; path=/");
        // 初始化主模块接口
        if (nullptr == m_WebMainRef) this->Init();
        IKCWebApiWork& wbwk = dynamic_cast<IServiceReferenceEx*>(m_WebMainRef)->getServiceSafe<IKCWebApiWork>();
        // 执行页面请求
        CWebRequestRespond re(*this, r, m_PgPath);
        wbwk.RenderPage(re);
    }
    catch(TException& ex)
    {
        string sPTID = lexical_cast<string>(boost::this_process::get_id()) + ":" + lexical_cast<string>(boost::this_thread::get_id());
        ap_rputs(("Internal server error. (Apache " + sPTID + ")<br>" + ex.error_info()).c_str(), &r);
    }
    catch(std::exception& ex)
    {
        string sPTID = lexical_cast<string>(boost::this_process::get_id()) + ":" + lexical_cast<string>(boost::this_thread::get_id());
        ap_rputs(("Internal server error. (Apache " + sPTID + ")<br>" + ex.what()).c_str(), &r);
    }
    catch(const char* ex)
    {
        string sPTID = lexical_cast<string>(boost::this_process::get_id()) + ":" + lexical_cast<string>(boost::this_thread::get_id());
        ap_rputs(("Internal server error. (Apache " + sPTID + ")<br>" + ex).c_str(), &r);
    }
    catch(...)
    {
        string sPTID = lexical_cast<string>(boost::this_process::get_id()) + ":" + lexical_cast<string>(boost::this_thread::get_id());
        ap_rputs(("Internal server error. (Apache " + sPTID + ")<br>Not load page.").c_str(), &r);
    }
}

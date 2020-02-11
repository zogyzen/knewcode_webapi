#include "std.h"
#include "kc_webapi_work.h"
#include "request_respond.h"

////////////////////////////////////////////////////////////////////////////////
// CKCWebWork类
CKCWebWork::CKCWebWork(const IBundle& bundle)
    : m_context(bundle.getContext()), m_bundle(bundle)
{
}

CKCWebWork::~CKCWebWork()
{
}

// 得到服务特征码
const char* CKCWebWork::getGUID(void) const
{
    return c_KCWebApiWorkSrvGUID;
}

// 对应的模块
const IBundle& CKCWebWork::getBundle(void) const
{
    return m_bundle;
}

// 处理请求
void CKCWebWork::RenderPage(IWebRequestRespond& re)
{
    // 创建页面数据
    CKCRequestRespond reKc(re, *this);
    // 提交应答
    CAutoRelease _auto(boost::bind(&CKCRequestRespond::CommitResponseBody, &reKc));
    try
    {
        // 处理页面
        //this->RenderPageTry(reKc);
    }
    catch(TException& ex)
    {
        ex.OtherInfo() = re.GetLocalFilename();
        TLogInfo log(ex);
        log.m_place = __FUNCTION__;
        this->WriteLog(log);
        string sPos = "\r\n" + lexical_cast<string>(getpid()) + ":" + lexical_cast<string>(boost::this_thread::get_id()) + "\r\n";
        reKc.OutputHTML((ex.CurrPosInfo() + ex.what() + sPos).c_str());
    }
    catch(std::exception& e)
    {
        TException ex(0, __FUNCTION__, e.what());
        ex.OtherInfo() = re.GetLocalFilename();
        ex.ExceptType() = typeid(e).name();
        this->WriteLog(TLogInfo(ex));
        string sPos = "\r\n" + lexical_cast<string>(getpid()) + ":" + lexical_cast<string>(boost::this_thread::get_id()) + "\r\n";
        reKc.OutputHTML((ex.what() + sPos).c_str());
    }
	catch(const char* e)
	{
        TException ex(0, __FUNCTION__, e);
        ex.OtherInfo() = re.GetLocalFilename();
        ex.ExceptType() = "const char*";
        this->WriteLog(TLogInfo(ex));
        string sPos = "\r\n" + lexical_cast<string>(getpid()) + ":" + lexical_cast<string>(boost::this_thread::get_id()) + "\r\n";
        reKc.OutputHTML((ex.what() + sPos).c_str());
	}
	catch(int e)
	{
        TException ex(0, __FUNCTION__, lexical_cast<string>(e).c_str());
        ex.OtherInfo() = re.GetLocalFilename();
        ex.ExceptType() = "int";
        this->WriteLog(TLogInfo(ex));
        string sPos = "\r\n" + lexical_cast<string>(getpid()) + ":" + lexical_cast<string>(boost::this_thread::get_id()) + "\r\n";
        reKc.OutputHTML((ex.what() + sPos).c_str());
	}
    catch(...)
    {
        this->WriteLogError(this->getHint("Unknown_exception"), __FUNCTION__, re.GetLocalFilename());
        string sPos = "\r\n" + lexical_cast<string>(getpid()) + ":" + lexical_cast<string>(boost::this_thread::get_id()) + "\r\n";
        reKc.OutputHTML((re.GetLocalFilename() + sPos).c_str());
    }
}

// 固定响应类型字符串
const char* CKCWebWork::FixContentTypeString(const char* ct)
{
    for (auto it = m_ResponseContentTypes.begin(); it != m_ResponseContentTypes.end(); ++it)
        if (*it == ct) return it->c_str();
    m_ResponseContentTypes.push_back(string(ct));
    return m_ResponseContentTypes.rbegin()->c_str();
}

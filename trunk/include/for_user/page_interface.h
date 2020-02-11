#pragma once

#include "for_user/common_define.h"

namespace KC
{
    // ���������Ӧ��ӿ�
    class IBaseRequestRespond
    {
    public:
        ////////////////////////////���󲿷�///////////////////////////
        // �õ���������ȫ����Ϣ
        virtual const char* CALL_TYPE GetAllInfo(const char* = "\n") = 0;
        // �õ����������ļ���
        virtual const char* CALL_TYPE GetLocalFilename(void) = 0;
        // �õ������ļ���
        virtual const char* CALL_TYPE GetUriFilename(void) = 0;
        // Э��
        virtual const char* CALL_TYPE GetProtocol(void) = 0;
        // ������
        virtual const char* CALL_TYPE GetHostName(void) = 0;
        // �˿�
        virtual int CALL_TYPE GetPort(void) = 0;
        // �ͻ�����Ϣ
        virtual const char* CALL_TYPE GetUserAgent(void) = 0;
        // �ͻ���IP
        virtual const char* CALL_TYPE GetClientIP(void) = 0;
        // ���յ���Ϣ
        virtual const char* CALL_TYPE GetAccept(const char* = "") = 0;
        // GET�Ĳ���
        virtual const char* CALL_TYPE GetGetArgStr(void) = 0;
        // Post�Ĳ���
        virtual const char* CALL_TYPE GetPostArgType(void) = 0;
        virtual int CALL_TYPE GetPostArgLength(void) = 0;
        virtual int CALL_TYPE GetPostArgBuffer(char*, int) = 0;
        // �õ���վ����������Ŀ¼
        virtual const char* CALL_TYPE GetLocalRootPath(void) = 0;
        // �����Ƶõ�����ͷ
        virtual const char* CALL_TYPE GetRequestHeader(const char*) = 0;
        // �õ�Cookie
        virtual const char* CALL_TYPE GetCookieStr(void) = 0;

        ////////////////////////////Ӧ�𲿷�///////////////////////////
        // ��Ӧ�ı�����
        virtual bool CALL_TYPE SetResponseContentType(const char*) = 0;
        virtual const char* CALL_TYPE GetResponseContentType(void) = 0;
        // �����ҳ���ݣ�����Ϊ�������
        virtual bool CALL_TYPE AddResponseBody(const char*, int = 0) = 0;
        // �����������Ӧͷ
        virtual void CALL_TYPE AddResponseHeader(const char*, const char*) = 0;

    protected:
        virtual CALL_TYPE ~IBaseRequestRespond() = default;
    };

    // ͨ�������Ӧ��ӿ�
    class IActionData;
    class IKCRequestRespond : public IBaseRequestRespond
    {
    public:
        // ��������е�����
        struct IReStepData
        {
            virtual CALL_TYPE ~IReStepData() = default;
            // �õ�����
            virtual const char* CALL_TYPE GetName(void) = 0;
        };

    public:
        // �źŴ���ʵ���ӿ�
        virtual ISignoCatch& CALL_TYPE SignoCatch(void) = 0;
        // ��
        virtual IKcLockWork& CALL_TYPE LockWork(void) = 0;
        // ��ʱʱ��
        virtual int CALL_TYPE GetTimeOutSeconds(void) const = 0;
        // ִ���е�ҳ�����ݽӿ�
        virtual IActionData* CALL_TYPE GetActionData(void) = 0;
        virtual void CALL_TYPE SetActionData(IActionData* = nullptr) = 0;

        ////////////////////////////���󲿷�///////////////////////////
        // �õ���ǰҳ����������Ŀ¼
        virtual const char* CALL_TYPE GetLocalPagePath(void) = 0;

        ////////////////////////////Ӧ�𲿷�///////////////////////////
        // ���Cookie����������Ϊ�����ơ�ֵ����Ч�ڡ�Url·�������򡿡���Ч�ڸ�ʽ���磬2014-10-01 13:00:05
        virtual bool CALL_TYPE AddCookie(const char*, const char*, const char* = "", const char* = "/", const char* = "") = 0;
        // �����ҳ���ݣ�����Ϊ�������
        virtual bool CALL_TYPE OutputData(const char*, const char*, int = 0) = 0;
        virtual bool CALL_TYPE OutputHTML(const char*) = 0;

        ////////////////////////��������е�����///////////////////////
        // �ж�ĳ���������Ƿ����
        virtual bool CALL_TYPE ExistsReStepData(const char*) = 0;
        // �õ�ĳ��������
        virtual IReStepData& CALL_TYPE GetReStepData(const char*) = 0;
        // ���ĳ�������ݣ���ӹ������ݽӿ�ָ�룬���ɱ����߸���ɾ����
        virtual bool CALL_TYPE AddReStepData(const char*, IReStepData*&) = 0;

    protected:
        virtual CALL_TYPE ~IKCRequestRespond() = default;
    };

    // ִ���е�ҳ�����ݽӿ�
    class IActionData
    {
    public:
        // �õ�ҳ�������Ӧ��
        virtual IKCRequestRespond& CALL_TYPE GetRequestRespond(void) = 0;
        // �õ�����
        virtual IActionData* CALL_TYPE GetActOwn(void) = 0;
        virtual IActionData& CALL_TYPE GetActRoot(void) = 0;
        virtual IActionData& CALL_TYPE GetActNow(void) = 0;
        // д��־
        virtual bool CALL_TYPE WriteLogTrace(const char*, const char*, const char* = "") const = 0;
        virtual bool CALL_TYPE WriteLogDebug(const char*, const char*, const char* = "") const = 0;
        virtual bool CALL_TYPE WriteLogInfo(const char*, const char*, const char* = "") const = 0;
        virtual bool CALL_TYPE WriteLogError(const char*, const char*, const char* = "") const = 0;
        // ������ִ���ַ����ű�
        virtual bool CALL_TYPE ParseActionScript(const char*, const char*) = 0;
        // �������ͷż����ݻ�ӿ�
        virtual IKcWebDataVal& CALL_TYPE CreateDataVal(void) = 0;
        virtual bool CALL_TYPE ReleaseDataVal(IKcWebDataVal&) = 0;
        virtual IKcWebInfVal& CALL_TYPE CreateInfVal(void) = 0;
        virtual bool CALL_TYPE ReleaseInfVal(IKcWebInfVal&) = 0;
        // ��ʶ�����ڲ������Ƿ����
        virtual bool CALL_TYPE ExistsVar(const char*) const = 0;
        virtual bool CALL_TYPE ExistsInnerVar(const char*, const char*) const = 0;
        // �ӿڱ���
        virtual IKcWebInfVal& CALL_TYPE GetInterfaceVar(const char*) = 0;
        virtual bool CALL_TYPE SetInterfaceVar(const char*, IKcWebInfVal&) = 0;
        // �����ͱ���ֵ
        virtual IKcWebDataVal& CALL_TYPE GetVarValue(const char*) = 0;
        virtual bool CALL_TYPE SetVarValue(const char*, IKcWebDataVal&) = 0;
        // �ڲ�����ֵ
        virtual IKcWebInfVal& CALL_TYPE GetInnerVarInf(const char*, const char*) = 0;
        virtual IKcWebDataVal& CALL_TYPE GetInnerVarVal(const char*, const char*) = 0;
        virtual bool CALL_TYPE SetInnerVar(const char*, const char*, IKcWebInfVal&) = 0;
        virtual bool CALL_TYPE SetInnerVar(const char*, const char*, IKcWebDataVal&) = 0;
        // ��������
        virtual void CALL_TYPE GC(void) = 0;
        // ��ȡ���ػ���ʾ��Ϣ
        virtual const char* CALL_TYPE getHint(const char* key) const = 0;
        // ��һ���ַ����쳣
        virtual void CALL_TYPE ThrowString(const char* ex) const = 0;

    protected:
        virtual CALL_TYPE ~IActionData() = default;
    };
}

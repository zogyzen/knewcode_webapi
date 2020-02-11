#pragma once

namespace KC
{
    // �����Ӧ��
    class CKCRequestRespond : public IKCRequestRespondData
    {
    public:
        // �źŴ���ʵ���ӿ�
        virtual ISignoCatch& CALL_TYPE SignoCatch(void);
        // ��
        virtual IKcLockWork& CALL_TYPE LockWork(void);
        // ��ʱʱ��
        virtual int CALL_TYPE GetTimeOutSeconds(void) const;
        // ִ���е�ҳ�����ݽӿ�
        virtual IActionData* CALL_TYPE GetActionData(void);
        virtual void CALL_TYPE SetActionData(IActionData* = nullptr);

        ////////////////////////////���󲿷�///////////////////////////
        // �õ���������ȫ����Ϣ
        virtual const char* CALL_TYPE GetAllInfo(const char* = "\n");
        // �õ����������ļ���
        virtual const char* CALL_TYPE GetLocalFilename(void);
        // �õ������ļ���
        virtual const char* CALL_TYPE GetUriFilename(void);
        // Э��
        virtual const char* CALL_TYPE GetProtocol(void);
        // ������
        virtual const char* CALL_TYPE GetHostName(void);
        // �˿�
        virtual int CALL_TYPE GetPort(void);
        // �ͻ�����Ϣ
        virtual const char* CALL_TYPE GetUserAgent(void);
        // �ͻ���IP
        virtual const char* CALL_TYPE GetClientIP(void);
        // ���յ���Ϣ
        virtual const char* CALL_TYPE GetAccept(const char* = "");
        // GET�Ĳ���
        virtual const char* CALL_TYPE GetGetArgStr(void);
        // Post�Ĳ���
        virtual const char* CALL_TYPE GetPostArgType(void);
        virtual int CALL_TYPE GetPostArgLength(void);
        virtual int CALL_TYPE GetPostArgBuffer(char*, int);
        // �õ���վ����������Ŀ¼
        virtual const char* CALL_TYPE GetLocalRootPath(void);
        // �õ���ǰҳ����������Ŀ¼
        virtual const char* CALL_TYPE GetLocalPagePath(void);
        // �����Ƶõ�����ͷ
        virtual const char* CALL_TYPE GetRequestHeader(const char*);
        // �õ�Cookie
        virtual const char* CALL_TYPE GetCookieStr(void);

        ////////////////////////////Ӧ�𲿷�///////////////////////////
        // ��Ӧ�ı�����
        virtual bool CALL_TYPE SetResponseContentType(const char*);
        virtual const char* CALL_TYPE GetResponseContentType(void);
        // �����ҳ����
        virtual bool CALL_TYPE AddResponseBody(const char*, int = 0);
        // �����������Ӧͷ
        virtual void CALL_TYPE AddResponseHeader(const char*, const char*);
        // ���Cookie
        virtual bool CALL_TYPE AddCookie(const char*, const char*, const char* = "", const char* = "/", const char* = "");
        // �����ҳ����
        virtual bool CALL_TYPE OutputData(const char*, const char*, int = 0);
        virtual bool CALL_TYPE OutputHTML(const char*);

        ////////////////////////��������е�����///////////////////////
        // �ж�ĳ���������Ƿ����
        virtual bool CALL_TYPE ExistsReStepData(const char*);
        // �õ�ĳ��������
        virtual IReStepData& CALL_TYPE GetReStepData(const char*);
        // ���ĳ��������
        virtual bool CALL_TYPE AddReStepData(const char*, IReStepData*&);

    public:
        CKCRequestRespond(IWebRequestRespond&, IKCWebApiWork&);
        virtual CALL_TYPE ~CKCRequestRespond();
        // ����ӿ�
        IKCWebApiWork& GetWork(void);
        // �ͷ�
        void Release(void);
        // �ύ
        void CommitResponseBody(void);

    private:
        IWebRequestRespond& m_re;
        IKCWebApiWork& m_webWork;
        IActionData* m_ActionData = nullptr;
        string m_LocalPagePath;     // ҳ���ļ���������·��
        string m_Protocol;          // Э��
        // ��Ӧ������
        std::map<string, string> m_ResponseBodys;
        // ��������е�����
        typedef boost::shared_ptr<IReStepData> TReStepDataPtr;
        typedef map<string, TReStepDataPtr> TReStepDataPtrList;
        TReStepDataPtrList m_ReStepDataPtrList;
    };
}

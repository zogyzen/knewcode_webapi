#pragma once

namespace KC
{
    class CAPACHEWork
    {
    public:
        CAPACHEWork(string, string);
        ~CAPACHEWork();

        // ��ʼ��
        void Init(void);
        // ��������
        void Work(request_rec& r);

    private:
        // ��ʼ����
        boost::mutex m_mtxInit;
        // ���·����ģ�顢��ҳĿ¼
        string m_FxPath, m_FxDll, m_PgPath;
        // �����
        BundleContextHelper m_contHelp;
        // �����������
        IBundleContext &m_BundleContextIF;
        // ��Ӧ������
        IServiceReference* m_WebMainRef = nullptr;
    };
}

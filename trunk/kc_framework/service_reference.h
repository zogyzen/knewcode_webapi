#pragma once

namespace KC
{
    class CBundleContext;
    class CServiceReference : public IServiceReferenceEx
    {
    public:
        CServiceReference(string symbolic, long ID, IService* srv, CBundleContext& ct);
        virtual CALL_TYPE ~CServiceReference();

        // �õ����ñ��
        long CALL_TYPE getID(void) const override;
        // �õ�����������
        const char* CALL_TYPE getGUID(void) const override;
        // �õ���������������
        const char* CALL_TYPE getName(void) const override;
        // �����Ƿ���ʧЧ��ģ��ж�ء�����ע���ȣ�
        bool CALL_TYPE disable(void) const override;
        // ��ȡ����ӿ�
        IService& CALL_TYPE getService(void) const override;
        // ��ȡģ��ӿ�
        const IBundle& CALL_TYPE getBundle(void) const override;
        // д��־
        bool CALL_TYPE WriteLog(TLogInfo) const override;
    public:
        // ���÷���
        void setService(IService* srv);

    private:
        // Ψһ������
        string m_symbolic;
        // ����
        mutable string m_name;
        // ���
        const long m_ID;
        // ����ӿ�
        IService* m_service = nullptr;
        // ���
        CBundleContext& m_Context;
    };
}

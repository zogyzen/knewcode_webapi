#pragma once

namespace KC
{
	class CActivator : public IBundleActivator
	{
	public:
		CActivator(const IBundle&);
		virtual CALL_TYPE ~CActivator() = default;

		// ����ģ�飨ע�����ȣ�
		virtual bool CALL_TYPE start(void);
		// ֹͣģ�飨ע������ȣ�
		virtual bool CALL_TYPE stop(void);

    private:
        // ���������
        IBundleContext& m_context;
        const IBundle& m_bundle;

        // �����
        IKCWebApiWork *m_srv = nullptr;
        IServiceRegistration *m_sreg = nullptr;
	};
}

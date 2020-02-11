#include "std.h"
#include "activator.h"

#include "kc_webapi_work.h"

////////////////////////////////////////////////////////////////////////////////
// ȫ�ֱ���
IKCWebApiWork *g_WebWork = nullptr;

////////////////////////////////////////////////////////////////////////////////
// TActivator��
KC::CActivator::CActivator(const IBundle& bundle)
        : m_context(bundle.getContext()), m_bundle(bundle)
{
}

// ����ģ�飨ע�����ȣ�
bool KC::CActivator::start(void)
{
	if (nullptr == m_srv)
		m_srv = new CKCWebWork(m_bundle);
	if (nullptr == m_sreg)
		m_sreg = m_context.registerService(*m_srv);
    g_WebWork = m_srv;
	return true;
}

// ֹͣģ�飨ע������ȣ�
bool KC::CActivator::stop(void)
{
    g_WebWork = nullptr;
	m_context.unregisterService(m_sreg);
	m_sreg = nullptr;
	delete dynamic_cast<CKCWebWork*>(m_srv);
	m_srv = nullptr;
	return true;
}

KC_SET_ACTIVATOR(KC::CActivator)

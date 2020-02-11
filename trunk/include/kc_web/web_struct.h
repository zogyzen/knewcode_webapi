#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <typeinfo>

#include <boost/any.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/smart_ptr.hpp>

#include "for_user/page_interface.h"
#include "framework/service_i.h"
#include "kc_web/web_exception.h"
#include "util/kc_tuple.h"

namespace KC
{
    ////////////////////////////////////ͨ������///////////////////////////////////
    // apache��isapi�����Ӧ��ӿ�
    class IWebRequestRespond : public IBaseRequestRespond
    {
    public:
        ////////////////////////////���󲿷�///////////////////////////

        ////////////////////////////Ӧ�𲿷�///////////////////////////

    protected:
        virtual CALL_TYPE ~IWebRequestRespond() = default;
    };
	
    // �����е������Ӧ��ӿ�
    class IKCRequestRespondData : public IKCRequestRespond
    {
    protected:
        virtual CALL_TYPE ~IKCRequestRespondData() = default;
    };

}

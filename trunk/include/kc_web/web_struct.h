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
    ////////////////////////////////////通用类型///////////////////////////////////
    // apache或isapi请求和应答接口
    class IWebRequestRespond : public IBaseRequestRespond
    {
    public:
        ////////////////////////////请求部分///////////////////////////

        ////////////////////////////应答部分///////////////////////////

    protected:
        virtual CALL_TYPE ~IWebRequestRespond() = default;
    };
	
    // 过程中的请求和应答接口
    class IKCRequestRespondData : public IKCRequestRespond
    {
    protected:
        virtual CALL_TYPE ~IKCRequestRespondData() = default;
    };

}

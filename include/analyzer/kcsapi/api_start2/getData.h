#ifndef API_START_TWO_GET_DATA_HXX_
#define API_START_TWO_GET_DATA_HXX_

#include <kcsapi.h>

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace KCSAPI {
namespace api_start2 {
    class GetData : KCSAPI::API {
        public:
            GetData(std::string name);
            ~GetData();

        private:
            std::string APIName;
            json data;
    }
}
}

#endif // API_START_TWO_GET_DATA_HXX_

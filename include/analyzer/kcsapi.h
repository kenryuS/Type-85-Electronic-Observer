#ifndef KCSAPI_HXX_
#define KCSAPI_HXX_

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace KCSAPI {
    class API {
        public:
            API(std::string name);
            ~API();

            virtual void onRequest(std::string json_string);

            std::string getAPIName(void) { return APIName; };

        private:
            std::string APIName;
            json data;
    }
}

#endif // KCSAPI_HXX_

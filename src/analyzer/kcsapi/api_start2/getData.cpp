#include "kcsapi/api_start2/getData.h"

using namespace KCSAPI::api_start2;

GetData::GetData(std::string name, std::string &json_data) {
    APIName = name;
    data = json::parse(json_data);
}

GetData::~GetData() {}

std::string GetData::process() {
    return "Init";
}

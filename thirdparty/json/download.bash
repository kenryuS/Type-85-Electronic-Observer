#!/usr/bin/env bash

TAG="v3.12.0"

wget --output-document json.hpp "https://github.com/nlohmann/json/raw/refs/tags/$TAG/single_include/nlohmann/json.hpp"

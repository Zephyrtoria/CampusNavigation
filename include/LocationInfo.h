//
// Created by Lenovo on 2024/12/10.
//

#ifndef CAMPUSNAVIGATION_LOCATIONINFO_H
#define CAMPUSNAVIGATION_LOCATIONINFO_H

#include <string>
#include <iostream>

namespace Graph {
    struct LocationInfo {
        std::string name;         // 地点名称
        int visitTime;       // 建议参观用时（单位：分钟）
        std::string type;   // 地点类型
        LocationInfo() = default;
        LocationInfo(const std::string& name_, const int visitTime_, const std::string& type_)
            : name(name_), visitTime(visitTime_), type(type_) {}
    };
} // Graph

#endif //CAMPUSNAVIGATION_LOCATIONINFO_H
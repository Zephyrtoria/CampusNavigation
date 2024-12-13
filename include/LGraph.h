//
// Created by Zephyrtoria on 2024/12/10.
//

#ifndef LGRAPH_LGRAPH_H
#define LGRAPH_LGRAPH_H

#include <map>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include "LocationInfo.h"


namespace Graph {
    typedef size_t Vertex;    /* 顶点ID类型，这里使用size_t类型 */
    typedef int GElemSet;  /* 边权类型，这里使用int类型 */
    typedef LocationInfo VertInfo; /* 顶点信息类型，这里使用LocationInfo */
    constexpr int NIL = -1;         /* 顶点不存在时的返回值 */
    constexpr int INF = 0x3f3f3f3f;

    struct EdgeNode {
        Vertex from, dest;     /* 边的另一端点编号 */
        GElemSet weight; /* 权重 */
        EdgeNode(): from(INF), dest(INF), weight(INF) {}

        EdgeNode(Vertex from, Vertex dest, GElemSet weight)
            : from(from), dest(dest), weight(weight) {}

        friend bool operator ==(EdgeNode a, EdgeNode b) {   // 为两个结构体参数，结构体调用一定要写上friend
            return a.from == b.from && a.dest == b.dest || a.from == b.dest && a.dest == b.from;
        }
    };

    inline bool compare(const EdgeNode& a, const EdgeNode& b) {
        if (a.from == b.from) {
            return a.dest < b.dest;
        }
        return a.from < b.from;
    }

    struct HeadNode {
        std::list<EdgeNode> adj; /* 邻接表，使用STL的链表list实现 */
        VertInfo data;           /* 存储顶点信息 */
        HeadNode() = default;

        explicit HeadNode(const VertInfo& data_)
            : data(data_), adj(std::list<EdgeNode>()) {}
    };

    class LGraph {
    private:
        int vertexNumber;   // 顶点数，删除顶点时减少
        int edgesNumber;   // 边数，删除边时减少
        bool directed; // true为有向图，false为无向图
        std::vector<HeadNode> graphList; // 邻接表
        std::map<std::string, Vertex> nameToId; // 地点名和地点ID映射，ID从0开始
        std::map<Vertex, std::string> idToName;

    public:
        explicit LGraph(bool directed = false);

        const int& getVertexNumber() const { return vertexNumber; } // 获取顶点数
        const int& getEdgesNumber() const { return edgesNumber; } // 获取边数
        const std::vector<HeadNode>& getGraphList() const { return graphList; } // 获取邻接表
        const std::map<std::string, Vertex>& getNameToIdMap() const { return nameToId; } //获取映射表

        bool vertexIsExist(const std::string& name) const; // 查询节点是否存在，存在返回true
        void insertVertex(const LocationInfo& vertexInfo); // 插入点
        void deleteVertex(const LocationInfo& vertexInfo); // 删除点，同时删除相邻边
        void updateVertex(const LocationInfo& oldVertexInfo, LocationInfo& newVertexInfo); //修改点信息
        VertInfo getVertex(const std::string& name) const; // 通过地点名 查询点
        VertInfo getVertex(Vertex vertexId) const; // 通过点ID查询点

        bool edgeIsExist(const std::string& fromVertexName,
                         const std::string& destVertexName) const; // 查询边是否存在，存在返回true
        void insertEdge(Vertex fromVertex, Vertex destVertex, GElemSet weight);
        void insertEdge(const std::string& fromVertexName, const std::string& destVertexName, GElemSet weight);// 插入边
        void deleteEdge(const std::string& fromVertexName, const std::string& destVertexName); // 删除边
        void deleteEdge(Vertex fromVertexName, Vertex destVertexName); // 删除边
        void updateEdge(const std::string& fromVertexName, const std::string& destVertexName,
                        GElemSet newWeight); // 修改边
        GElemSet getEdgeWeight(const std::string& fromVertexName, const std::string& destVertexName) const; // 查询边
        std::vector<EdgeNode> getSortedEdges(
            std::function<bool(const EdgeNode& a, const EdgeNode& b)> cmp = compare
        ) const; // 返回边权按值排序的结果(从小到大)
        std::string getNameById(Vertex vertex) const;
        Vertex getIdByName(const std::string& name) const;

    };
}
#endif  // LGRAPH_LGRAPH_H

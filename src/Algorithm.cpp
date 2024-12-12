//
// Created by Lenovo on 2024/12/10.
//
#include "../include/Algorithm.h"
#include <queue>
#include <string.h>

namespace Graph {
    namespace Algorithm {
        const int INF = 0x3f3f3f3f;

        std::list<Vertex> GetCircuit(LGraph& graph, Vertex start) {
            //TODO:从给定点出发获得一条回路
            return {};
        }

        std::list<Vertex> EulerCircle(const LGraph& graph) {
            //TODO:获取欧拉回路,你可以使用GetCircuit函数
            std::cerr << "EulerCircle 还没实现" << std::endl;
            return {};
        }

        bool HaveEulerCircle(const LGraph& graph) {
            //TODO:判断是否有欧拉回路

            // 判断是否连通
            if (!isConnected(graph)) {
                return false;
            }
            // 判断每个顶点的度是否为偶数
            auto& head_nodes = graph.getGraphList();
            for (auto& each : head_nodes) {
                if (each.adj.size() % 2 != 0) {
                    return false;
                }
            }
            return true;
        }

        void BFSv(const LGraph& graph, Vertex v, std::vector<bool>& visited) {
            //TODO:广度优先搜索整个图
            std::vector<Vertex> result;
            std::queue<HeadNode> q;
            auto& nodes = graph.getGraphList();
            auto& map = graph.getNameToIdMap();
            q.push(nodes.at(v));
            while (!q.empty()) {
                auto& cur = q.front();
                q.pop();
                Vertex thiss = map.at(cur.data.name);
                visited[thiss] = true;
                result.push_back(thiss);
                for (auto& each : cur.adj) {
                    Vertex other = (thiss == each.from) ? each.dest : each.from;
                    if (!visited[other]) {
                        q.push(nodes.at(other));
                    }
                }
            }
        }

        bool isConnected(const LGraph& graph) {
            //TODO:判断图是否联通
            DSU dsu(graph.getVertexNumber());
            auto& allNodes = graph.getGraphList();
            auto& nameToId = graph.getNameToIdMap();
            for (const auto& ve : allNodes) {
                Vertex from = nameToId.at(ve.data.name);
                for (const auto& edge : ve.adj) {
                    Vertex dest = edge.from == from ? dest : from;
                    dsu.unite(from, dest);
                }
            }
            return dsu.isSingle();
        }

        int GetShortestPath(const LGraph& graph, const std::string& sourceName, const std::string& destName) {
            // TODO:获取两点之间的最短路径
            // 使用Dijkstra算法
            if (!isConnected(graph)) {
                return NIL;
            }
            int result = 0;
            auto& allNodes = graph.getGraphList();
            bool visited[graph.getVertexNumber()];
            return 0;
        }


        int TopologicalShortestPath(const LGraph& graph, std::vector<std::string> path) {
            //TODO:获取拓扑受限的最短路径，拓扑序由path给出
            std::cerr << "TopologicalShortestPath 还没实现" << std::endl;
            return -1;
        }

        std::vector<EdgeNode> MinimumSpanningTree(const LGraph& graph) {
            // TODO:计算最小生成树，并返回树上的边
            // 使用Prim算法
            std::vector<EdgeNode> result;
            int size = graph.getVertexNumber();
            int cost = 0;
            bool visited[size];
            std::vector<EdgeNode> minDist;
            for (int i = 0; i < size; i++) {
                minDist.push_back({INF, INF, INF});
            }

            auto& allNodes = graph.getGraphList();
            for (int i = 0; i < size; i++) {
                Vertex nextVertex = -1;
                for (Vertex j = 0; j < size; j++) {
                    if (!visited[j] && (nextVertex == -1 || minDist[nextVertex].weight > minDist[j].weight)) {
                        nextVertex = j;
                    }
                }
                // 必然连通，不做连通性判断了
                if (i != 0) {
                    cost += minDist[nextVertex].weight;
                }
                // 添加结果
                result.push_back(minDist[nextVertex]);
                for (Vertex j = 0; j < size; j++) {
                    GElemSet t = graph.getEdgeWeight(allNodes[nextVertex].data.name, allNodes[j].data.name);
                    if (t < minDist[j].weight) {
                        minDist[j].weight = t;
                        minDist[j].from = nextVertex;
                        minDist[j].dest = j;
                    }
                }
                visited[nextVertex] = true;
            }
            return result;
        }
    }
}

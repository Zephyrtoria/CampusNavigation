//
// Created by Zephyrtoria on 2024/12/10.
//
#include "../include/Algorithm.h"
#include <queue>
#include <stack>
#include <cstring>
#include <random>

#include "../include/GraphException.h"

namespace Graph {
    namespace Algorithm {
        std::list<Vertex> getCircuit(LGraph& graph, Vertex start) {
            //TODO:从给定点出发获得一条回路
            int size = graph.getVertexNumber();
            bool visited[size];
            std::list<Vertex> result;
            std::stack<Vertex> curPath;
            auto& allNodes = graph.getGraphList();

            curPath.push(start);
            while (!curPath.empty()) {
                Vertex u = curPath.top();
                if (!allNodes[u].adj.empty()) {
                    auto& edge = allNodes[u].adj.front();
                    Vertex other = edge.from == u ? edge.dest : edge.from;
                    curPath.push(other);
                    graph.deleteEdge(u, other);
                } else {
                    result.push_back(u);
                    curPath.pop();
                }
            }
            return result;
        }

        std::list<Vertex> eulerCircle(LGraph& graph) {
            //TODO:获取欧拉回路,你可以使用GetCircuit函数
            std::list<Vertex> result;
            if (!haveEulerCircle(graph)) {
                return result;
            }
            return getCircuit(graph, 0);
        }

        bool haveEulerCircle(const LGraph& graph) {
            //TODO:判断是否有欧拉回路
            // 没有奇度节点
            auto& allNodes = graph.getGraphList();
            for (auto& each : allNodes) {
                if (each.adj.size() % 2 != 0) {
                    return false;
                }
            }
            // 判断是否连通
            if (!isConnected(graph)) {
                return false;
            }
            return true;
        }

        void BFSv(const LGraph& graph, Vertex start, std::vector<bool>& visited) {
            //TODO:广度优先搜索整个图
            std::queue<Vertex> q;
            auto& allNodes = graph.getGraphList();
            auto& map = graph.getNameToIdMap();
            q.push(start);
            while (!q.empty()) {
                auto& curId = q.front();
                q.pop();
                auto& curNode = allNodes[curId];
                visited[curId] = true;
                for (auto& each : curNode.adj) {
                    Vertex other = (curId == each.from) ? each.dest : each.from;
                    if (!visited[other]) {
                        q.push(other);
                    }
                }
            }
        }

        bool isConnected(const LGraph& graph) {
            //TODO:判断图是否联通
            int size = graph.getVertexNumber();
            DSU dsu(size);
            auto& allNodes = graph.getGraphList();
            auto& nameToId = graph.getNameToIdMap();
            for (Vertex i = 0; i < size; i++) {
                for (const auto& edge : allNodes[i].adj) {
                    Vertex dest = edge.from == i ? edge.dest : edge.from;
                    dsu.unite(i, dest);
                }
            }
            return dsu.isSingle();
        }

        void makeGraphConnected(LGraph& graph) {
            int size = graph.getVertexNumber();
            DSU dsu(size);
            auto& allNodes = graph.getGraphList();
            auto& nameToId = graph.getNameToIdMap();
            for (Vertex i = 0; i < size; i++) {
                for (const auto& edge : allNodes[i].adj) {
                    Vertex dest = edge.from == i ? edge.dest : edge.from;
                    dsu.unite(i, dest);
                }
            }
            std::random_device rd;  // 真随机数生成器
            std::mt19937 gen(rd()); // Mersenne Twister 引擎
            std::uniform_int_distribution<> dis(0, 500);  // 生成 0 到 500 之间的整数
            std::uniform_int_distribution<> vex(0, size - 1);  // 生成 0 到 size - 1 之间的整数
            while (!dsu.isSingle()) {
                Vertex i = vex(gen);
                for (Vertex j = 0; j < size; j++) {
                    if (!dsu.same(i, j)) {
                        std::cout << "地点" << graph.getVertexName(i) << "与" << graph.getVertexName(j) <<
                            "之间不连通，请输入边的权重（输入0则会添加随机权重） ";
                        GElemSet in;
                        std::cin >> in;
                        if (in == 0) {
                            in = dis(gen);
                        }
                        graph.insertEdge(i, j, in);
                        dsu.unite(i, j);
                        break;
                    }
                }
            }
        }

        int getShortestPath(const LGraph& graph, const std::string& sourceName, const std::string& destName) {
            // TODO:获取两点之间的最短路径
            // 判断点是否存在
            if (!graph.vertexIsExist(sourceName) || !graph.vertexIsExist(destName)) {
                throw GraphException("");
            }
            // 同一个点
            if (sourceName == destName) {
                return 0;
            }
            // Dijkstra
            const int size = graph.getVertexNumber();
            bool visited[size];
            auto& allNodes = graph.getGraphList();
            auto& nameToId = graph.getNameToIdMap();

            Vertex start = nameToId.at(sourceName), end = nameToId.at(destName);
            GElemSet minDist[size];
            std::memset(minDist, 0x3f, sizeof(minDist));
            minDist[start] = 0;

            for (int i = 0; i < size; i++) {
                Vertex nextVertex = -1;
                for (Vertex j = 0; j < size; j++) {
                    if (!visited[j] && (nextVertex == -1 || minDist[nextVertex] > minDist[j])) {
                        nextVertex = j;
                    }
                }

                if (nextVertex == end) {
                    return minDist[end];
                }

                // 更新距离
                for (Vertex j = 0; j < size; j++) {
                    GElemSet t = graph.getEdgeWeight(allNodes[nextVertex].data.name, allNodes[j].data.name);
                    minDist[j] = std::min(minDist[j], minDist[nextVertex] + t);
                }
                visited[nextVertex] = true;
            }
            // 已经判断是否能走到
            if (minDist[end] == INF) {
                throw GraphException("");
            }
            return minDist[end];
        }


        int topologicalShortestPath(const LGraph& graph, std::vector<std::string> path) {
            //TODO:获取拓扑受限的最短路径，拓扑序由path给出
            int cost = 0;
            int size = path.size();
            for (int i = 0; i < size - 1; i++) {
                cost += getShortestPath(graph, path.at(i), path.at(i + 1));
            }
            return cost;
        }

        std::vector<EdgeNode> minimumSpanningTree(const LGraph& graph) {
            // TODO:计算最小生成树，并返回树上的边
            // 使用Prim算法
            std::vector<EdgeNode> result;
            int size = graph.getVertexNumber();
            int cost = 0;
            bool visited[size];
            std::vector<EdgeNode> minDist(size);

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
                    result.push_back(minDist[nextVertex]);
                }
                // 添加结果
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

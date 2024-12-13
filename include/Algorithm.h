//
// Created by Zephyrtoria on 2024/12/10.
//

#ifndef CAMPUSNAVIGATION_ALGORITHM_H
#define CAMPUSNAVIGATION_ALGORITHM_H

#include "LGraph.h"

namespace Graph {
    namespace Algorithm {
        class DSU {
        private:
            std::vector<Vertex> parent;

        public:
            // 并查集构造函数
            explicit DSU(Vertex n) {
                // TODO: 请完成并查集的构造函数
                for (Vertex i = 0; i < n; i++) {
                    parent.push_back(i);
                }
            }

            // 查找根节点并路径压缩
            Vertex find(Vertex x) {
                // TODO: 查找元素的根节点，并完成路径压缩
                if (x != parent[x]) {
                    parent[x] = find(parent[x]);
                }
                return parent[x];
            }

            // 合并两个集合
            void unite(Vertex x, Vertex y) {
                // TODO: 合并集合
                Vertex px = find(x), py = find(y);
                parent[px] = py;
            }

            // 检查两个节点是否属于同一集合
            bool same(Vertex x, Vertex y) {
                // TODO: 检查两个节点是否属于同一个集合
                return (find(x) == find(y));
            }

            bool isSingle() {
                Vertex record = parent[0];
                for (Vertex i : parent) {
                    if (!same(record, i)) {
                        return false;
                    }
                }
                return true;
            }
        };

        std::list<Vertex> eulerCircle(LGraph& graph); //计算欧拉回路
        bool haveEulerCircle(const LGraph& graph); //判断是否存在欧拉回路
        bool isConnected(const LGraph& graph); //判断图是否联通
        void makeGraphConnected(LGraph& graph); // 添加边
        int getShortestPath(const LGraph& graph, const std::string& sourceName,
                            const std::string& destName); //计算单源最短路径
        int topologicalShortestPath(const LGraph& graph, std::vector<std::string> path); //计算拓扑受限的最短路径
        std::vector<EdgeNode> minimumSpanningTree(const LGraph& graph); //计算最小生成树
        std::vector<Vertex> planningRoute(const LGraph& graph, std::string& fromVertexName, std::string& destVertexName, int time);
    }
}
#endif //CAMPUSNAVIGATION_ALGORITHM_H

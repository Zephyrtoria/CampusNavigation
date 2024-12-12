//
// Created by Lenovo on 2024/12/10.
//

#ifndef CAMPUSNAVIGATION_ALGORITHM_H
#define CAMPUSNAVIGATION_ALGORITHM_H

#include "LGraph.h"

namespace Graph {
    namespace Algorithm {
        class DSU {
        private:
            std::vector<int> parent;

        public:
            // 并查集构造函数
            explicit DSU(int n) {
                // TODO: 请完成并查集的构造函数
                for (int i = 0; i < n; i++) {
                    parent.push_back(i);
                }
            }

            // 查找根节点并路径压缩
            int find(int x) {
                // TODO: 查找元素的根节点，并完成路径压缩
                if (x != parent[x]) {
                    parent[x] = find(parent[x]);
                }
                return x;
            }

            // 合并两个集合
            void unite(int x, int y) {
                // TODO: 合并集合
                int px = find(x), py = find(y);
                parent[px] = py;
            }

            // 检查两个节点是否属于同一集合
            bool same(int x, int y) {
                // TODO: 检查两个节点是否属于同一个集合
                return (find(x) == find(y));
            }

            bool isSingle() {
                int record = parent[0];
                for (int i : parent) {
                    if (i != record) {
                        return false;
                    }
                }
                return true;
            }
        };

        std::list<Vertex> EulerCircle(const LGraph& graph); //计算欧拉回路
        bool HaveEulerCircle(const LGraph& graph); //判断是否存在欧拉回路
        bool isConnected(const LGraph& graph); //判断图是否联通
        int GetShortestPath(const LGraph& graph, const std::string& sourceName,
                            const std::string& destName); //计算单源最短路径
        int TopologicalShortestPath(const LGraph& graph, std::vector<std::string> path); //计算拓扑受限的最短路径
        std::vector<EdgeNode> MinimumSpanningTree(const LGraph& graph); //计算最小生成树
    }
}
#endif //CAMPUSNAVIGATION_ALGORITHM_H

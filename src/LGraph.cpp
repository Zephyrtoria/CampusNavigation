//
// Created by Zephyrtoria on 2024/12/10.
//

#include "../include/LGraph.h"
#include <algorithm>
#include <utility>

#include "../include/GraphException.h"

namespace Graph {
    LGraph::LGraph(bool directed)
        : vertexNumber(0), edgesNumber(0), directed(directed), graphList(std::vector<HeadNode>()) {}

    bool LGraph::vertexIsExist(const std::string& name) const {
        //TODO:判断是否存在name名称的节点
        return nameToId.find(name) != nameToId.end();
    }


    void LGraph::insertVertex(const LocationInfo& vertexInfo) {
        //TODO:插入节点，节点信息由LocationInfo类给出
        if (vertexIsExist(vertexInfo.name)) {
            throw GraphException("");
        }
        HeadNode ins{vertexInfo};
        graphList.push_back(ins);
        nameToId[vertexInfo.name] = vertexNumber;
        idToName[vertexNumber] = vertexInfo.name;
        vertexNumber++;
    }

    void LGraph::deleteVertex(const LocationInfo& vertexInfo) {
        //TODO:删除节点，节点信息由LocationInfo类给出
        if (!vertexIsExist(vertexInfo.name)) {
            throw GraphException("");
        }

        // 删除与该点相连的所有边
        Vertex deleteId = getIdByName(vertexInfo.name);
        HeadNode& deleteHead = graphList.at(deleteId);
        std::list<EdgeNode>& deleteList = deleteHead.adj;
        for (auto& each : deleteList) {
            deleteEdge(each.from, each.dest);
        }
        // 将删除的节点和最后一个节点进行位置交换
        vertexNumber--;
        graphList[deleteId] = graphList[vertexNumber];
        graphList.pop_back();

        nameToId[idToName[vertexNumber]] = deleteId;
        idToName[deleteId] = idToName[vertexNumber];
        nameToId.erase(vertexInfo.name);
        idToName.erase(vertexNumber);
    }

    void LGraph::updateVertex(const LocationInfo& oldVertexInfo, LocationInfo& newVertexInfo) {
        //TODO:更新节点，新/旧节点的信息由LocationInfo类给出
        if (!vertexIsExist(oldVertexInfo.name) || vertexIsExist(newVertexInfo.name)) {
            throw GraphException("");
        }

        Vertex updateId = getIdByName(oldVertexInfo.name);
        nameToId.at(newVertexInfo.name) = updateId;
        idToName.at(updateId) = newVertexInfo.name;
        nameToId.erase(oldVertexInfo.name);

        graphList[updateId].data = newVertexInfo;
    }

    VertInfo LGraph::getVertex(const std::string& name) const {
        //TODO:获取节点，由节点名查询节点信息
        if (!vertexIsExist(name)) {
            throw GraphException("");
        }
        return graphList[getIdByName(name)].data;
    }

    VertInfo LGraph::getVertex(const Vertex searchId) const {
        //TODO:获取节点，由节点的ID查询
        if (!vertexIsExist(idToName.at(searchId))) {
            throw GraphException("");
        }
        return graphList[searchId].data;
    }

    bool LGraph::edgeIsExist(const std::string& fromVertexName, const std::string& destVertexName) const {
        //TODO:判断是否存在x-y的边
        if (!vertexIsExist(fromVertexName) || !vertexIsExist(destVertexName)) {
            std::cout << "端点不存在或者已经被删除" << std::endl;
            return false;
        }
        Vertex fromId = getIdByName(fromVertexName);
        Vertex destId = getIdByName(destVertexName);
        EdgeNode temp{fromId, destId, NIL};
        for (auto& edge : graphList.at(fromId).adj) {
            if (edge == temp) {
                return true;
            }
        }
        return false;
    }

    void LGraph::insertEdge(Vertex fromVertex, Vertex destVertex, GElemSet weight) {
        insertEdge(idToName.at(fromVertex), idToName.at(destVertex), weight);
    }

    void LGraph::insertEdge(const std::string& fromVertexName, const std::string& destVertexName, GElemSet weight) {
        //TODO:插入边
        if (!vertexIsExist(fromVertexName) || !vertexIsExist(destVertexName)) {
            throw GraphException("");
        }
        if (edgeIsExist(fromVertexName, destVertexName)) {
            return;
        }
        Vertex fromId = getIdByName(fromVertexName), destId = getIdByName(destVertexName);
        edgesNumber++;
        EdgeNode a{fromId, destId, weight};
        graphList[fromId].adj.push_back(a);
        graphList[destId].adj.push_back(a);
    }

    void LGraph::deleteEdge(const std::string& fromVertexName, const std::string& destVertexName) {
        //TODO:删除边，由两个节点名确定一条边
        if (!vertexIsExist(fromVertexName) || !vertexIsExist(destVertexName) || !edgeIsExist(
            fromVertexName, destVertexName)) {
            throw GraphException("");
        }

        Vertex fromId = getIdByName(fromVertexName), destId = getIdByName(destVertexName);

        EdgeNode temp{fromId, destId, NIL};
        for (auto& edge : graphList[fromId].adj) {
            if (edge == temp) {
                graphList[fromId].adj.remove(edge);
                break;
            }
        }
        for (auto& edge : graphList[destId].adj) {
            if (edge == temp) {
                graphList[destId].adj.remove(edge);
                break;
            }
        }
        edgesNumber--;
    }

    void LGraph::deleteEdge(Vertex fromVertexName, Vertex destVertexName) {
        //TODO:删除边，由两个节点ID确定一条边
        deleteEdge(getNameById(fromVertexName), getNameById(destVertexName));
    }


    void LGraph::updateEdge(const std::string& fromVertexName, const std::string& destVertexName, GElemSet newWeight) {
        //TODO:更新边，由两个节点名确定一条边
        if (!vertexIsExist(fromVertexName) || !vertexIsExist(destVertexName) || !edgeIsExist(
            fromVertexName, destVertexName)) {
            throw GraphException("");
        }
        Vertex fromId = getIdByName(fromVertexName), destId = getIdByName(destVertexName);
        EdgeNode temp{fromId, destId, NIL};
        for (auto& edge : graphList[fromId].adj) {
            if (edge == temp) {
                edge.weight = newWeight;
                break;
            }
        }
        for (auto& edge : graphList[destId].adj) {
            if (edge == temp) {
                edge.weight = newWeight;
                break;
            }
        }
    }

    GElemSet LGraph::getEdgeWeight(const std::string& fromVertexName, const std::string& destVertexName) const {
        //TODO:获取边的信息
        if (!vertexIsExist(fromVertexName) || !vertexIsExist(destVertexName)) {
            throw GraphException("");
        }
        Vertex fromId = getIdByName(fromVertexName), destId = getIdByName(destVertexName);
        EdgeNode temp{fromId, destId, NIL};
        for (auto& edge : graphList[fromId].adj) {
            if (edge == temp) {
                return edge.weight;
            }
        }
        return INF;
    }

    std::vector<EdgeNode> LGraph::getSortedEdges(std::function<bool(const EdgeNode& a, const EdgeNode& b)> cmp) const {
        //TODO:获取按边权和给定规则排序的所有边
        std::vector<EdgeNode> result;
        for (const auto& head : graphList) {
            for (const auto& edge : head.adj) {
                result.push_back(edge);
            }
        }
        std::sort(result.begin(), result.end(), std::move(cmp));
        result.erase(std::unique(result.begin(), result.end()), result.end());
        return result;
    }

    std::string LGraph::getNameById(Vertex vertex) const {
        return idToName.at(vertex);
    }

    Vertex LGraph::getIdByName(const std::string& name) const {
        return nameToId.at(name);
    }

}

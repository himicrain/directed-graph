
#ifndef _GRAPH_
#define _GRAPH_
#include<algorithm>
#include<vector>
#include <memory>
#include <iostream>

using namespace std;
namespace gdwg{

    //节点类
    template<typename N,typename E> class Node{
        private:
            
        public:

            N name;
            int outDegree;
            int inDegree;
            vector<shared_ptr<tuple<N,N,E>> > edges;

            Node(const N& node);

            void setName(const N& name);
            N getName();

            void addEdge(const N& dst,const E& w);

            void deleteEdge(const N& dst,const E& w);

            int isExistEdge(const N& dst, const E& w);

    };

    //图本身
    template<typename N, typename E> class Graph{
        public:
        mutable  Node<N,E>* head;
        mutable int counter ;

        public:
            Graph();

            Graph(const Graph &graph);
            Graph(Graph&& graph);
            Graph& operator=( Graph& graph);
            Graph& operator=( Graph&& graph);

            mutable vector<shared_ptr<Node<N,E>> > nodes;
            bool addNode(const N& val);
            bool addEdge(const N& src, const N& dst, const E& w);
            bool replace(const N& oldData, const N& newData);
            void mergeReplace(const N& oldData, const N& newData);
  
            void deleteAndModifyNode(const N& oldData, const N& newData) noexcept;
            void deleteNode(const N&) noexcept; 
            void deleteEdge(const N& src, const N& dst, const E& w)noexcept;
            void clear()noexcept;
            bool isNode(const N& val) const;
            bool isConnected(const N& src, const N& dst) const; 
            void printNodes()const;
            void printEdges(const N& val) const;

            void begin() const;
            bool end() const;
            void next() const;
            const N& value() const;

            bool isExistNode(N& node);

    };



    #include "Graph.cpp"


};

#endif



template<typename N, typename E> Node<N,E>::Node(const N& node){
    this->name = node;
    this->inDegree = 0;
    this->outDegree = 0;

}


template<typename N, typename E>void Node<N,E>::setName(const N& name){
            this->name = name;
}
template<typename N, typename E>N Node<N,E>::getName(){
        return this->name;
}

template<typename N, typename E>void Node<N,E>::addEdge(const N& dst,const E& w){

        edges.push_back(make_shared<tuple<N,N,E> >(this->name,dst,w));
}

template<typename N, typename E>void Node<N,E>::deleteEdge(const N& dst,const E& w){
    int index = isExistEdge(dst,w);
    
    if(index==-1){
        return ;
    }

    edges.erase(edges.begin() + index);  
}

template<typename N, typename E>int Node<N,E>::isExistEdge(const N& dst,const E& w){
    int index=-1;
    for(unsigned int i=0;i<edges.size();i++){
        if(get<1>(*(edges.at(i)).get())==dst && get<2>(*(edges.at(i)).get()) == w){
            index = i;
            break;
        }
    }
    return index;
}


template<typename N,typename E> Graph<N,E>::Graph(){
    this->counter = 0;
}

template<typename N,typename E> Graph<N,E>::Graph( Graph<N,E>&& graph){
    
    for(unsigned int i=0;i<graph.nodes.size();i++){
        auto t = graph.nodes.at(i).get();
        this->nodes.push_back(make_shared<Node<N,E>>(t->name));
        for(unsigned int j=0;j<t->edges.size();j++){
                auto e = t->edges.at(j).get();
                this->nodes.at(i).get()->addEdge(get<1>(*e),get<2>(*e));
        }
    }
    graph.clear();
     //cout << " && " << endl;

}

template<typename N,typename E> Graph<N,E>& Graph<N,E>::operator=( Graph<N,E>&& graph){
    
    this->nodes.clear();
    

    for(unsigned int i=0;i<graph.nodes.size();i++){
        auto t = graph.nodes.at(i).get();
        this->nodes.push_back(make_shared<Node<N,E>>(t->name));
        for(unsigned int j=0;j<t->edges.size();j++){
                auto e = t->edges.at(j).get();
                this->nodes.at(i).get()->addEdge(get<1>(*e),get<2>(*e));
        }
    }

    //cout << " && = " << endl;

    graph.clear();

    return *this;

}


template<typename N,typename E> Graph<N,E>::Graph(const Graph<N,E>& graph){

    for(unsigned int i=0;i<graph.nodes.size();i++){
        auto t = graph.nodes.at(i).get();
        //cout <<" ----- " << t->name << endl;
        this->nodes.push_back(make_shared<Node<N,E>>(t->name));
        for(unsigned int j=0;j<t->edges.size();j++){
                auto e = t->edges.at(j).get();
                this->nodes.at(i).get()->addEdge(get<1>(*e),get<2>(*e));
        }
    }
    //cout << " & " << graph.nodes.size() << endl;

}
template<typename N,typename E> Graph<N,E>&   Graph<N,E>::operator=( Graph<N,E>& graph){
    
    if(this != &graph){
        
            this->nodes.clear();
            for(unsigned int i=0;i<graph.nodes.size();i++){
                auto t = graph.nodes.at(i).get();
                
                this->nodes.push_back(make_shared<Node<N,E>>(t->name));

                for(unsigned int j=0;j<t->edges.size();j++){
                    auto e = t->edges.at(j).get();
                    this->nodes.at(i).get()->addEdge(get<1>(*e),get<2>(*e));
                }
            }
        
    }
 //cout << " &= " << endl;
    return *this;

}


template<typename N,typename E> bool Graph<N,E>::addNode(const N& val){

    bool exist = isNode(val);

    if(exist == true){
        return false;
    }

    this->nodes.push_back(make_shared<Node<N,E> >(val));

    return true;



}
template<typename N,typename E> bool Graph<N,E>::addEdge(const N& src, const N& dst, const E& w){
    int index = 0;


    if(isNode(src) == false || isNode(dst) == false){
        throw runtime_error("No such node");
    }


    for(unsigned int i=0;i<this->nodes.size();i++){
        if(this->nodes.at(i)->name == src){
            index = i;
            break;
        }
    }

    int exist =  this->nodes.at(index)->isExistEdge(dst,w);

    if(exist != -1){
        return false;
    }

    this->nodes.at(index)->addEdge(dst,w);

    return true;
}

template<typename N,typename E> bool Graph<N,E>::replace(const N& oldData, const N& newData){

    if(isNode(oldData) == false){
        throw runtime_error("No such node");
    }

    if(isNode(newData) == true){
        return false;
    }
   
    int index = -1;
    for(unsigned int i=0;i<this->nodes.size();i++){
        if(this->nodes.at(i)->name == oldData){
            index = i;
        }
    }

    this->nodes.at(index)->setName(newData);
    return true;

}


template<typename N,typename E> void Graph<N,E>::mergeReplace(const N& oldData, const N& newData){

    if(isNode(oldData)==false || isNode(newData) == false){
        throw runtime_error("no such node");
    }

    int index = -1;
    for(unsigned int i=0;i<this->nodes.size();i++){
        if(this->nodes.at(i)->name == oldData){
            index = i;
        }
    }

    for(auto t:this->nodes.at(index).get()->edges){

        this->addEdge(newData,get<1>(*t.get()),get<2>(*t.get()));

    }

    this->deleteAndModifyNode(oldData,newData);



}

//删除节点，同时把所有与之相关的其他点有向路径的dst端设置为newData，
template<typename N,typename E> void Graph<N,E>::deleteAndModifyNode(const N& oldData, const N& newData) noexcept{

    bool exist = isNode(oldData);

    if(exist == false){
        return ;
    }

    int index = -1;
    for(unsigned int i=0;i<this->nodes.size();i++){
        if(this->nodes.at(i)->name == oldData){
            index = i;
        }
    }


    this->nodes.erase(this->nodes.begin()+index);

    for(auto t: this->nodes){

        typename vector<shared_ptr<tuple<N,N,E>> >::iterator it;

        for(unsigned int i=0;i<t.get()->edges.size();i++){
            if(get<1>(*(t.get()->edges.at(i).get())) == oldData){
                t.get()->edges.at(i) = make_shared<tuple<N,N,E> >(get<0>(*(t.get()->edges.at(i).get())),newData,get<2>(*(t.get()->edges.at(i).get())))  ;
            }
        }

    }

}



template<typename N,typename E> void Graph<N,E>::deleteNode(const N& src) noexcept{

    bool exist = isNode(src);

    if(exist == false){
        return ;
    }

    int index = -1;
    for(unsigned int i=0;i<this->nodes.size();i++){
        if(this->nodes.at(i)->name == src){
            index = i;
        }
    }


    this->nodes.erase(this->nodes.begin()+index);


    for(auto t: this->nodes){

        typename vector<shared_ptr<tuple<N,N,E>> >::iterator it;

        for(it=t.get()->edges.begin();it!=t.get()->edges.end();){
            if(get<1>(*(*it).get()) == src){

                it = t.get()->edges.erase(it); 
            }else{
                ++ it;
            }
        }

    }
}


template<typename N,typename E> void Graph<N,E>::deleteEdge(const N& src, const N& dst, const E& w)noexcept{
    
    bool exist = isNode(src);
    if(exist == false){
        return;
    }
    
    int index = -1;
    for(unsigned int i=0;i<this->nodes.size();i++){
        if(this->nodes.at(i)->name == src){
            index = i;
        }
    }
    
    this->nodes.at(index)->deleteEdge(dst,w);
  
}
template<typename N,typename E> void Graph<N,E>::clear()noexcept{

    this->nodes.clear();

}


template<typename N,typename E> bool Graph<N,E>::isNode(const N& val) const{

    for(auto t:this->nodes){
        if(t.get()->name == val){
            return true; 
        }
    }

    return false;


}


template<typename N,typename E> bool Graph<N,E>::isConnected(const N& src, const N& dst) const{

    int index = 0;

    if(isNode(src) == false || isNode(dst) == false){
        throw runtime_error("No such node");
    }

    for(unsigned int i=0;i<this->nodes.size();i++){
        if(this->nodes.at(i)->name == src){
            index = i;
            break;
        }
    }

    for(auto t : this->nodes.at(index)->edges){
        if(get<1>(*t.get()) == dst){
            return true;
        }
    }

    return false;

}


template<typename N,typename E> bool comp1(const shared_ptr<Node<N,E>>& c1, const shared_ptr<Node<N,E>>& c2){

    if(c1.get()->edges.size() == c2.get()->edges.size()){
       return c1.get()->name < c2.get()->name;
    }

    //cout << c1.get()->edges.size()<< "   " << c2.get()->edges.size() << endl;
    
    return c1.get()->edges.size() < c2.get()->edges.size();
}

template<typename N,typename E> void Graph<N,E>::printNodes()const{

    sort(this->nodes.begin(),this->nodes.end(),comp1<N,E>);

    for(auto& t: this->nodes){
        cout <<  t.get()->name << endl;
    }

}

template<typename N,typename E> bool comp(const shared_ptr<tuple<N,N,E>>& c1, const shared_ptr<tuple<N,N,E>>& c2){
    

    if( get<2>(*(c1.get())) == get<2>(*(c2.get())) ){
        return get<1>(*(c1.get())) < get<1>(*(c2.get()));
    }

    
    return get<2>(*(c1.get())) < get<2>(*(c2.get()));
}


template<typename N,typename E> void Graph<N,E>::printEdges(const N& val) const{
    int index = 0;


    if(isNode(val) == false){
        throw runtime_error("No such node");
    }


    for(unsigned  int i=0;i<this->nodes.size();i++){
        if(this->nodes.at(i)->name == val){
            index = i;
            break;
        }
    }

    cout << "Edges attached to Node " << this->nodes.at(index)->name << endl;

    sort(this->nodes.at(index)->edges.begin(),this->nodes.at(index)->edges.end(),comp<N,E>);

    for(auto t: this->nodes.at(index)->edges){
        cout << get<1>(*t.get()) << " " << get<2>(*t.get()) << endl;
    }


    if(this->nodes.at(index)->edges.size() == 0){
        cout << "(null)" << endl;
    }


}

template<typename N,typename E> void Graph<N,E>::begin()const {

    shared_ptr<Node<N,E>> temp = this->nodes.at(0);
    this->head  = temp.get();

}
template<typename N,typename E> bool Graph<N,E>::end() const{
    if (counter == this->nodes.size()){
        counter = 0;
        return true;
    }
    return false;

}
template<typename N,typename E> void Graph<N,E>::next() const{
    counter ++ ;

    if(counter >= this->nodes.size()){
        return;
    }

    this->head = this->nodes.at(this->counter).get();
    
}
template<typename N,typename E> const N& Graph<N,E>::value() const{
    return this->head->name;

}

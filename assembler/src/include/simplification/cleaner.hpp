#pragma once

#include "omni/basic_vertex_conditions.hpp"
#include "graph_processing_algorithm.hpp"

namespace omnigraph {

template<class Graph>
class Cleaner : public PersistentProcessingAlgorithm<Graph,
        typename Graph::VertexId,
        ParallelInterestingElementFinder < Graph, typename Graph::VertexId>> {
    typedef typename Graph::EdgeId EdgeId;
    typedef typename Graph::VertexId VertexId;
    typedef PersistentProcessingAlgorithm <Graph,
    VertexId, ParallelInterestingElementFinder<Graph, VertexId>> base;
    typedef IsolatedVertexCondition<Graph> ConditionT;

    Graph &g_;
    ConditionT isolated_condition_;

public:
    Cleaner(Graph &g, size_t chunk_cnt = 1) :
            base(g,
                 ParallelInterestingElementFinder<Graph, VertexId>(g,
                                                                   ConditionT(g), chunk_cnt),
                    /*canonical only*/true),
            g_(g), isolated_condition_(g) {
    }

protected:

    bool Process(VertexId v) {
        if (isolated_condition_.Check(v)) {
            g_.DeleteVertex(v);
            return true;
        } else {
            return false;
        }
    }
};

}
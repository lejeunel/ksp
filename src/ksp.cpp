#include "include/ksp.h"
#include "include/path.h"
#include <memory>
#include <vector>
#include "include/easylogging++.h"
#include <iostream>

KSP::KSP(std::unique_ptr<DirectedGraph> a_graph, int a_source, int a_sink){
   graph = std::move(a_graph);
   source = graph->get_node(a_source);
   sink = graph->get_node(a_sink);
}

std::expected<std::vector<Path>, std::string> KSP::run(int k){
    if(validate_source_sink() == false){
        return std::unexpected{
            "source and/or sink are not valid nodes."};
    }

    if(graph->has_cycle()){
        return std::unexpected{"found cycle"};
    }

    auto path = Path();
    path.append(source);
    path.append(sink);
    std::vector<Path> result = {path};

    return result;
}


bool KSP::validate_source(){
    if ((source->get_leaving_edges().size() > 0) &&
        (source->get_incoming_edges().size() == 0)){
            return true;
        }
    return false;
}

bool KSP::validate_sink(){
    if ((sink->get_incoming_edges().size() > 0) &&
        (sink->get_leaving_edges().size() == 0)){
            return true;
        }
    return false;
}

bool KSP::validate_source_sink(){
    return validate_source() & validate_sink();

}

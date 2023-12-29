#include "include/ksp.h"
#include "include/path.h"
#include <memory>
#include <vector>
using namespace std;


KSP::KSP(unique_ptr<Graph> a_graph, int a_source, int a_sink){
   this->graph = move(a_graph);
   this->source = a_source;
   this->sink = a_sink;
}

vector<Path> KSP::run(int k){
    auto path = Path();
    path.append(std::make_shared<Node>(0));
    path.append(std::make_shared<Node>(1));
    vector<Path> result = {path};

    return result;

}

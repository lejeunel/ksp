#include "include/ksp.h"
#include "include/path.h"
#include <memory>
#include <vector>
using namespace std;


KSP::KSP(unique_ptr<Graph> a_graph, int a_source, int a_sink){
   graph = move(a_graph);
   source = std::make_shared<Node>(a_source);
   sink = std::make_shared<Node>(a_sink);
}

vector<Path> KSP::run(int k){
    auto path = Path();
    path.append(source);
    path.append(sink);
    vector<Path> result = {path};

    return result;

}

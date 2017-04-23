
#include <vector>
#include <future>
#include <algorithm>
#include <numeric>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

namespace py = pybind11;

// In this case, f is a python function passed into this class
double parallel_eval(const std::function<double(double)> &f, double x, int N)
{
    /* Release the GIL */
    py::gil_scoped_release release;
    {
        std::vector<std::future<double> > futures;
        std::vector<double > v;
        for (auto i = 0; i < N; ++i){
            futures.push_back(std::async(std::launch::async, [f,x](){
                /* Acquire GIL before calling Python code */
                py::gil_scoped_acquire acquire;
                // f is a python function
                return f(x);
            } ));
        }
        // Get all the values
        for(auto &f : futures){
            v.push_back(f.get());
        }
        // Sum them all up - a stupid example, but its just for proof of concept
        return std::accumulate(v.begin(), v.end(), 0.0);
    }
}

void init_dummy(py::module &m){
    // Note that is function is not defined to modify the GIL
    m.def("parallel_eval", &parallel_eval);
}

PYBIND11_PLUGIN(dummy) {
    py::module m("dummy", "dummy module");
    init_dummy(m);
    return m.ptr();
}

#include <pybind11/pybind11.h>

#include <G4VUserTaskQueue.hh>

#include "typecast.hh"

namespace py = pybind11;

// TODO
void export_G4VUserTaskQueue(py::module &m)
{
   py::class_<G4VUserTaskQueue, std::unique_ptr<G4VUserTaskQueue>>(m, "G4VUserTaskQueue");
}
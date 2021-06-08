#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VUserTaskQueue.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

// TODO
void export_G4VUserTaskQueue(py::module &m)
{
   py::class_<G4VUserTaskQueue>(m, "G4VUserTaskQueue");
}
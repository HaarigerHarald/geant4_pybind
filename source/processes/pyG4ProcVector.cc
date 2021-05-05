#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <G4VProcess.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ProcVector(py::module &m)
{
   py::bind_vector<G4ProcVector>(m, "G4ProcVector");
}

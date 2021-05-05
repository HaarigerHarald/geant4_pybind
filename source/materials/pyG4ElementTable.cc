#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <G4Element.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ElementTable(py::module &m)
{
   py::bind_vector<G4ElementTable>(m, "G4ElementTable");

   m.attr("G4ElementVector") = m.attr("G4ElementTable");
}

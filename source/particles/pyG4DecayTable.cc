#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include <G4DecayTable.hh>

#include "holder.hh"
#include "typecast.hh"

namespace py = pybind11;

void export_G4DecayTable(py::module &m)
{
   py::class_<G4DecayTable, owntrans_ptr<G4DecayTable>>(m, "G4DecayTable", "decay table")
      .def(py::init<>())

      .def(py::self == py::self)
      .def(py::self != py::self)

      .def("Insert", &G4DecayTable::Insert)
      .def("entries", &G4DecayTable::entries)
      .def("SelectADecayChannel", &G4DecayTable::SelectADecayChannel, py::arg("parentMass") = -1.,
           py::return_value_policy::reference_internal)

      .def("GetDecayChannel", &G4DecayTable::SelectADecayChannel, py::arg("index"),
           py::return_value_policy::reference_internal)

      .def("__getitem__", &G4DecayTable::operator[], py::is_operator())
      .def("DumpInfo", &G4DecayTable::DumpInfo);
}

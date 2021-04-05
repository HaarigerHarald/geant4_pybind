#include <pybind11/pybind11.h>

#include <G4Navigator.hh>

#include "typecast.hh"

namespace py = pybind11;

void export_G4Navigator(py::module &m)
{
   py::class_<G4Navigator, std::unique_ptr<G4Navigator>>(m, "G4Navigator", "navigator")
      .def(py::init<>())

      .def("GetWorldVolume", &G4Navigator::GetWorldVolume, py::return_value_policy::reference)
      .def("GetVerboseLevel", &G4Navigator::GetVerboseLevel)
      .def("SetVerboseLevel", &G4Navigator::SetVerboseLevel)
      .def("IsActive", &G4Navigator::IsActive)
      .def("PrintState", &G4Navigator::PrintState);
}

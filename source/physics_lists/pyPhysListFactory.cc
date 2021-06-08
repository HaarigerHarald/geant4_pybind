#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PhysListFactory.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_PhysListFactory(py::module &m)
{
   py::class_<G4PhysListFactory>(m, "G4PhysListFactory", "phys list factory")
      .def(py::init<>())
      .def("GetReferencePhysList", &G4PhysListFactory::GetReferencePhysList,
           py::return_value_policy::reference_internal)

      .def("ReferencePhysList", &G4PhysListFactory::ReferencePhysList, py::return_value_policy::reference_internal)
      .def("IsReferencePhysList", &G4PhysListFactory::IsReferencePhysList)
      .def("AvailablePhysLists", &G4PhysListFactory::AvailablePhysLists, py::return_value_policy::reference)
      .def("AvailablePhysListsEM", &G4PhysListFactory::AvailablePhysListsEM, py::return_value_policy::reference);
}

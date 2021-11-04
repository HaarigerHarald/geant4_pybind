#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4NavigationHistoryPool.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4LogicalVolume.hh>
#include <G4VPVParameterisation.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4NavigationHistoryPool(py::module &m)
{
   py::class_<G4NavigationHistoryPool, py::nodelete>(m, "G4NavigationHistoryPool")

      .def("__copy__", [](const G4NavigationHistoryPool &self) { return G4NavigationHistoryPool(self); })
      .def("__deepcopy__", [](const G4NavigationHistoryPool &self, py::dict) { return G4NavigationHistoryPool(self); })
      .def_static("GetInstance", &G4NavigationHistoryPool::GetInstance, py::return_value_policy::reference)
      .def("GetNewLevels", &G4NavigationHistoryPool::GetNewLevels, py::return_value_policy::reference)
      .def("GetLevels", &G4NavigationHistoryPool::GetLevels, py::return_value_policy::reference)
      .def("DeRegister", &G4NavigationHistoryPool::DeRegister, py::arg("pLevels"))
      .def("Clean", &G4NavigationHistoryPool::Clean)
      .def("Print", &G4NavigationHistoryPool::Print);
}

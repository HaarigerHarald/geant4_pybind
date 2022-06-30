#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UCNMaterialPropertiesTable.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UCNMaterialPropertiesTable(py::module &m)
{
   py::class_<G4UCNMaterialPropertiesTable, G4MaterialPropertiesTable>(m, "G4UCNMaterialPropertiesTable")

      .def("__copy__", [](const G4UCNMaterialPropertiesTable &self) { return new G4UCNMaterialPropertiesTable(self); })
      .def("__deepcopy__",
           [](const G4UCNMaterialPropertiesTable &self, py::dict) { return new G4UCNMaterialPropertiesTable(self); })

      .def(py::init<>())
      .def("ComputeMicroRoughnessTables", &G4UCNMaterialPropertiesTable::ComputeMicroRoughnessTables)
      .def("ConditionsValid", &G4UCNMaterialPropertiesTable::ConditionsValid, py::arg("E"), py::arg("VFermi"),
           py::arg("theta_i"))

      .def("GetCorrLen", &G4UCNMaterialPropertiesTable::GetCorrLen)
      .def("GetMRIntProbability", &G4UCNMaterialPropertiesTable::GetMRIntProbability)
      .def("GetMRIntTransProbability", &G4UCNMaterialPropertiesTable::GetMRIntTransProbability)
      .def("GetMRMaxProbability", &G4UCNMaterialPropertiesTable::GetMRMaxProbability)
      .def("GetMRMaxTransProbability", &G4UCNMaterialPropertiesTable::GetMRMaxTransProbability)
      .def("GetMRProbability", &G4UCNMaterialPropertiesTable::GetMRProbability)
      .def("GetMRTransProbability", &G4UCNMaterialPropertiesTable::GetMRTransProbability)
      .def("GetMicroRoughnessTable", &G4UCNMaterialPropertiesTable::GetMicroRoughnessTable,
           py::return_value_policy::reference)

      .def("GetMicroRoughnessTransTable", &G4UCNMaterialPropertiesTable::GetMicroRoughnessTransTable,
           py::return_value_policy::reference)

      .def("GetRMS", &G4UCNMaterialPropertiesTable::GetRMS)
      .def("InitMicroRoughnessTables", &G4UCNMaterialPropertiesTable::InitMicroRoughnessTables)
      .def("LoadMicroRoughnessTables",
           [](G4UCNMaterialPropertiesTable &self, G4double *arg0, G4double *arg1, G4double *arg2, G4double *arg3) {
              self.LoadMicroRoughnessTables(arg0, arg1, arg2, arg3);
              return std::tuple(arg0, arg1, arg2, arg3);
           })

      .def("SetMRMaxProbability", &G4UCNMaterialPropertiesTable::SetMRMaxProbability)
      .def("SetMRMaxTransProbability", &G4UCNMaterialPropertiesTable::SetMRMaxTransProbability)
      .def("SetMicroRoughnessParameters", &G4UCNMaterialPropertiesTable::SetMicroRoughnessParameters)
      .def("TransConditionsValid", &G4UCNMaterialPropertiesTable::TransConditionsValid, py::arg("E"), py::arg("VFermi"),
           py::arg("theta_i"))

      ;
}

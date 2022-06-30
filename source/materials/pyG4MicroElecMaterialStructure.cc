#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MicroElecMaterialStructure.hh>
#include <G4DensityEffectData.hh>
#include <G4DensityEffectCalculator.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4MicroElecMaterialStructure(py::module &m)
{
   py::class_<G4MicroElecMaterialStructure>(m, "G4MicroElecMaterialStructure")

      .def("__copy__", [](const G4MicroElecMaterialStructure &self) { return new G4MicroElecMaterialStructure(self); })
      .def("__deepcopy__",
           [](const G4MicroElecMaterialStructure &self, py::dict) { return new G4MicroElecMaterialStructure(self); })

      .def(py::init<const G4String &>(), py::arg("matName") = "")
      .def("ConvertUnit", &G4MicroElecMaterialStructure::ConvertUnit, py::arg("unitName"))
      .def("Energy", &G4MicroElecMaterialStructure::Energy, py::arg("level"))
      .def("GetEADL_Enumerator", &G4MicroElecMaterialStructure::GetEADL_Enumerator, py::arg("shell"))
      .def("GetElasticModelHighLimit", &G4MicroElecMaterialStructure::GetElasticModelHighLimit)
      .def("GetElasticModelLowLimit", &G4MicroElecMaterialStructure::GetElasticModelLowLimit)
      .def("GetEnergyGap", &G4MicroElecMaterialStructure::GetEnergyGap)
      .def("GetInelasticModelHighLimit", &G4MicroElecMaterialStructure::GetInelasticModelHighLimit, py::arg("pdg"))
      .def("GetInelasticModelLowLimit", &G4MicroElecMaterialStructure::GetInelasticModelLowLimit, py::arg("pdg"))
      .def("GetInitialEnergy", &G4MicroElecMaterialStructure::GetInitialEnergy)
      .def("GetLimitEnergy", &G4MicroElecMaterialStructure::GetLimitEnergy, py::arg("level"))
      .def("GetMaterialName", &G4MicroElecMaterialStructure::GetMaterialName)
      .def("GetWorkFunction", &G4MicroElecMaterialStructure::GetWorkFunction)
      .def("GetZ", &G4MicroElecMaterialStructure::GetZ, py::arg("Shell"))
      .def("IsShellWeaklyBound", &G4MicroElecMaterialStructure::IsShellWeaklyBound, py::arg("level"))
      .def("NumberOfLevels", &G4MicroElecMaterialStructure::NumberOfLevels)
      .def("ReadMaterialFile", &G4MicroElecMaterialStructure::ReadMaterialFile);
}

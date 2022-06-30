#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SandiaTable.hh>
#include <G4Material.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SandiaTable(py::module &m)
{
   py::class_<G4SandiaTable>(m, "G4SandiaTable")

      .def(py::init<const G4Material *>())
      .def(py::init<G4int>(), py::arg("matIndex"))
      .def(py::init<>())
      .def("GetLowerI1", &G4SandiaTable::GetLowerI1)
      .def("GetMatNbOfIntervals", &G4SandiaTable::GetMatNbOfIntervals)
      .def("GetMaxInterval", &G4SandiaTable::GetMaxInterval)
      .def("GetPhotoAbsorpCof", &G4SandiaTable::GetPhotoAbsorpCof, py::arg("i"), py::arg("j"))
      .def("GetSandiaCofForMaterial",
           py::overload_cast<G4int, G4int>(&G4SandiaTable::GetSandiaCofForMaterial, py::const_))

      .def("GetSandiaCofForMaterial", py::overload_cast<G4double>(&G4SandiaTable::GetSandiaCofForMaterial, py::const_),
           py::arg("energy"), py::return_value_policy::reference)

      .def("GetSandiaCofPerAtom", &G4SandiaTable::GetSandiaCofPerAtom, py::arg("Z"), py::arg("energy"),
           py::arg("coeff"))

      .def("GetSandiaCofWater", &G4SandiaTable::GetSandiaCofWater, py::arg("energy"), py::arg("coeff"))
      .def("GetSandiaMatTable", &G4SandiaTable::GetSandiaMatTable)
      .def("GetSandiaMatTablePAI", &G4SandiaTable::GetSandiaMatTablePAI)
      .def("GetWaterCofForMaterial", &G4SandiaTable::GetWaterCofForMaterial)
      .def("GetWaterEnergyLimit", &G4SandiaTable::GetWaterEnergyLimit)
      .def_static("GetZtoA", &G4SandiaTable::GetZtoA, py::arg("Z"))
      .def("Initialize", &G4SandiaTable::Initialize)
      .def(
         "SandiaIntervals",
         [](G4SandiaTable &self, G4int *Z, G4int el) { return std::make_tuple(self.SandiaIntervals(Z, el), Z); },
         py::arg("Z"), py::arg("el"))

      .def(
         "SandiaMixing",
         [](G4SandiaTable &self, G4int *Z, const G4double *fractionW, G4int el, G4int mi) {
            return std::make_tuple(self.SandiaMixing(Z, fractionW, el, mi), Z);
         },
         py::arg("Z"), py::arg("fractionW"), py::arg("el"), py::arg("mi"))

      .def("SetLowerI1", &G4SandiaTable::SetLowerI1, py::arg("flag"))
      .def("SetVerbose", &G4SandiaTable::SetVerbose, py::arg("ver"));
}

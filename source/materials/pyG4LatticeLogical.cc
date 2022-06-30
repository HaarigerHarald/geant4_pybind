#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4LatticeLogical.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4LatticeLogical : public G4LatticeLogical, public py::trampoline_self_life_support {
public:
   using G4LatticeLogical::G4LatticeLogical;

   G4double MapKtoV(G4int arg0, const G4ThreeVector &arg1) const override
   {
      PYBIND11_OVERRIDE(G4double, G4LatticeLogical, MapKtoV, arg0, arg1);
   }

   G4ThreeVector MapKtoVDir(G4int arg0, const G4ThreeVector &arg1) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4LatticeLogical, MapKtoVDir, arg0, arg1);
   }
};

void export_G4LatticeLogical(py::module &m)
{
   py::class_<G4LatticeLogical, PyG4LatticeLogical>(m, "G4LatticeLogical")

      .def("__copy__", [](const PyG4LatticeLogical &self) { return new PyG4LatticeLogical(self); })
      .def("__deepcopy__", [](const PyG4LatticeLogical &self, py::dict) { return new PyG4LatticeLogical(self); })
      .def("__copy__", [](const G4LatticeLogical &self) { return new G4LatticeLogical(self); })
      .def("__deepcopy__", [](const G4LatticeLogical &self, py::dict) { return new G4LatticeLogical(self); })
      .def(py::init<>())
      .def("Dump", &G4LatticeLogical::Dump, py::arg("os"))
      .def("DumpMap", &G4LatticeLogical::DumpMap, py::arg("os"), py::arg("pol"), py::arg("name"))
      .def("Dump_NMap", &G4LatticeLogical::Dump_NMap, py::arg("os"), py::arg("pol"), py::arg("name"))
      .def("GetAnhDecConstant", &G4LatticeLogical::GetAnhDecConstant)
      .def("GetBeta", &G4LatticeLogical::GetBeta)
      .def("GetFTDOS", &G4LatticeLogical::GetFTDOS)
      .def("GetGamma", &G4LatticeLogical::GetGamma)
      .def("GetLDOS", &G4LatticeLogical::GetLDOS)
      .def("GetLambda", &G4LatticeLogical::GetLambda)
      .def("GetMu", &G4LatticeLogical::GetMu)
      .def("GetSTDOS", &G4LatticeLogical::GetSTDOS)
      .def("GetScatteringConstant", &G4LatticeLogical::GetScatteringConstant)
      .def("LoadMap", &G4LatticeLogical::LoadMap)
      .def("Load_NMap", &G4LatticeLogical::Load_NMap)
      .def("MapKtoV", &G4LatticeLogical::MapKtoV)
      .def("MapKtoVDir", &G4LatticeLogical::MapKtoVDir)
      .def("SetAnhDecConstant", &G4LatticeLogical::SetAnhDecConstant, py::arg("a"))
      .def("SetDynamicalConstants", &G4LatticeLogical::SetDynamicalConstants, py::arg("Beta"), py::arg("Gamma"),
           py::arg("Lambda"), py::arg("Mu"))

      .def("SetFTDOS", &G4LatticeLogical::SetFTDOS, py::arg("FTDOS"))
      .def("SetLDOS", &G4LatticeLogical::SetLDOS, py::arg("LDOS"))
      .def("SetSTDOS", &G4LatticeLogical::SetSTDOS, py::arg("STDOS"))
      .def("SetScatteringConstant", &G4LatticeLogical::SetScatteringConstant, py::arg("b"))
      .def("SetVerboseLevel", &G4LatticeLogical::SetVerboseLevel, py::arg("vb"))
      .def(
         "__str__",
         [](const G4LatticeLogical &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}

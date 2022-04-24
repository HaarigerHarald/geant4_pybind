#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VPrimaryGenerator.hh>
#include <G4Event.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VPrimaryGenerator : public G4VPrimaryGenerator, public py::trampoline_self_life_support {
public:
   using G4VPrimaryGenerator::G4VPrimaryGenerator;

   void GeneratePrimaryVertex(G4Event *evt) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VPrimaryGenerator, GeneratePrimaryVertex, evt);
   }
};

void export_G4VPrimaryGenerator(py::module &m)
{
   py::class_<G4VPrimaryGenerator, PyG4VPrimaryGenerator>(m, "G4VPrimaryGenerator")

      .def("__copy__", [](const PyG4VPrimaryGenerator &self) { return new PyG4VPrimaryGenerator(self); })
      .def("__deepcopy__", [](const PyG4VPrimaryGenerator &self, py::dict) { return new PyG4VPrimaryGenerator(self); })
      .def(py::init<>())
      .def_static("CheckVertexInsideWorld", &G4VPrimaryGenerator::CheckVertexInsideWorld, py::arg("pos"))
      .def("GeneratePrimaryVertex", &G4VPrimaryGenerator::GeneratePrimaryVertex, py::arg("evt"))
      .def("GetParticlePosition", &G4VPrimaryGenerator::GetParticlePosition)
      .def("GetParticleTime", &G4VPrimaryGenerator::GetParticleTime)
      .def("SetParticlePosition", &G4VPrimaryGenerator::SetParticlePosition, py::arg("aPosition"))
      .def("SetParticleTime", &G4VPrimaryGenerator::SetParticleTime, py::arg("aTime"));
}

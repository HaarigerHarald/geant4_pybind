#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GenericBiasingPhysics.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4GenericBiasingPhysics : public G4GenericBiasingPhysics, public py::trampoline_self_life_support {
public:
   using G4GenericBiasingPhysics::G4GenericBiasingPhysics;

   void ConstructParticle() override { PYBIND11_OVERRIDE(void, G4GenericBiasingPhysics, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE(void, G4GenericBiasingPhysics, ConstructProcess, ); }
};

void export_G4GenericBiasingPhysics(py::module &m)
{
   py::class_<G4GenericBiasingPhysics, PyG4GenericBiasingPhysics, G4VPhysicsConstructor>(m, "G4GenericBiasingPhysics")

      .def(py::init<const G4String &>(), py::arg("name") = "BiasingP")

      .def("ConstructParticle", &G4GenericBiasingPhysics::ConstructParticle)
      .def("ConstructProcess", &G4GenericBiasingPhysics::ConstructProcess)

      .def("PhysicsBias", py::overload_cast<const G4String &>(&G4GenericBiasingPhysics::PhysicsBias),
           py::arg("particleName"))

      .def("PhysicsBias",
           py::overload_cast<const G4String &, const std::vector<G4String> &>(&G4GenericBiasingPhysics::PhysicsBias),
           py::arg("particleName"), py::arg("processToBiasNames"))

      .def("NonPhysicsBias", &G4GenericBiasingPhysics::NonPhysicsBias, py::arg("particleName"))
      .def("Bias", py::overload_cast<const G4String &>(&G4GenericBiasingPhysics::Bias), py::arg("particleName"))
      .def("Bias", py::overload_cast<const G4String &, const std::vector<G4String> &>(&G4GenericBiasingPhysics::Bias),
           py::arg("particleName"), py::arg("processToBiasNames"))

      .def("PhysicsBiasAddPDGRange", &G4GenericBiasingPhysics::PhysicsBiasAddPDGRange, py::arg("PDGlow"),
           py::arg("PDGhigh"), py::arg("includeAntiParticle") = true)

      .def("NonPhysicsBiasAddPDGRange", &G4GenericBiasingPhysics::NonPhysicsBiasAddPDGRange, py::arg("PDGlow"),
           py::arg("PDGhigh"), py::arg("includeAntiParticle") = true)

      .def("BiasAddPDGRange", &G4GenericBiasingPhysics::BiasAddPDGRange, py::arg("PDGlow"), py::arg("PDGhigh"),
           py::arg("includeAntiParticle") = true)

      .def("PhysicsBiasAllCharged", &G4GenericBiasingPhysics::PhysicsBiasAllCharged,
           py::arg("includeShortLived") = false)

      .def("NonPhysicsBiasAllCharged", &G4GenericBiasingPhysics::NonPhysicsBiasAllCharged,
           py::arg("includeShortLived") = false)

      .def("BiasAllCharged", &G4GenericBiasingPhysics::BiasAllCharged, py::arg("includeShortLived") = false)

      .def("PhysicsBiasAllNeutral", &G4GenericBiasingPhysics::PhysicsBiasAllNeutral,
           py::arg("includeShortLived") = false)

      .def("NonPhysicsBiasAllNeutral", &G4GenericBiasingPhysics::NonPhysicsBiasAllNeutral,
           py::arg("includeShortLived") = false)

      .def("BiasAllNeutral", &G4GenericBiasingPhysics::BiasAllNeutral, py::arg("includeShortLived") = false)

      .def("AddParallelGeometry",
           py::overload_cast<const G4String &, const G4String &>(&G4GenericBiasingPhysics::AddParallelGeometry),
           py::arg("particleName"), py::arg("parallelGeometryName"))

      .def("AddParallelGeometry",
           py::overload_cast<const G4String &, const std::vector<G4String> &>(
              &G4GenericBiasingPhysics::AddParallelGeometry),
           py::arg("particleName"), py::arg("parallelGeometryNames"))

      .def("AddParallelGeometry",
           py::overload_cast<G4int, G4int, const G4String &, G4bool>(&G4GenericBiasingPhysics::AddParallelGeometry),
           py::arg("PDGlow"), py::arg("PDGhigh"), py::arg("parallelGeometryName"),
           py::arg("includeAntiParticle") = true)

      .def("AddParallelGeometry",
           py::overload_cast<G4int, G4int, const std::vector<G4String> &, G4bool>(
              &G4GenericBiasingPhysics::AddParallelGeometry),
           py::arg("PDGlow"), py::arg("PDGhigh"), py::arg("parallelGeometryNames"),
           py::arg("includeAntiParticle") = true)

      .def("AddParallelGeometryAllCharged",
           py::overload_cast<const G4String &, G4bool>(&G4GenericBiasingPhysics::AddParallelGeometryAllCharged),
           py::arg("parallelGeometryName"), py::arg("includeShortLived") = false)

      .def("AddParallelGeometryAllCharged",
           py::overload_cast<const std::vector<G4String> &, G4bool>(
              &G4GenericBiasingPhysics::AddParallelGeometryAllCharged),
           py::arg("parallelGeometryNames"), py::arg("includeShortLived") = false)

      .def("AddParallelGeometryAllNeutral",
           py::overload_cast<const G4String &, G4bool>(&G4GenericBiasingPhysics::AddParallelGeometryAllNeutral),
           py::arg("parallelGeometryName"), py::arg("includeShortLived") = false)

      .def("AddParallelGeometryAllNeutral",
           py::overload_cast<const std::vector<G4String> &, G4bool>(
              &G4GenericBiasingPhysics::AddParallelGeometryAllNeutral),
           py::arg("parallelGeometryNames"), py::arg("includeShortLived") = false)

      .def("BeVerbose", &G4GenericBiasingPhysics::BeVerbose);
}

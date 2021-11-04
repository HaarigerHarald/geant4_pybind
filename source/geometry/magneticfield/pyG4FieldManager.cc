#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4FieldManager.hh>
#include <G4Field.hh>
#include <G4MagneticField.hh>
#include <G4ChordFinder.hh>
#include <G4Track.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4FieldManager : public G4FieldManager, public py::trampoline_self_life_support {
public:
   using G4FieldManager::G4FieldManager;

   void ConfigureForTrack(const G4Track *arg0) override
   {
      PYBIND11_OVERRIDE(void, G4FieldManager, ConfigureForTrack, arg0);
   }

   G4FieldManager *Clone() const override { PYBIND11_OVERRIDE(G4FieldManager *, G4FieldManager, Clone, ); }
};

void export_G4FieldManager(py::module &m)
{
   py::class_<G4FieldManager, PyG4FieldManager>(m, "G4FieldManager")

      .def(py::init<G4Field *, G4ChordFinder *, G4bool>(), py::arg("detectorField") = static_cast<G4Field *>(nullptr),
           py::arg("pChordFinder") = static_cast<G4ChordFinder *>(nullptr), py::arg("b") = true)

      .def(py::init<G4MagneticField *>(), py::arg("detectorMagneticField"))
      .def("SetDetectorField", &G4FieldManager::SetDetectorField, py::arg("detectorField"), py::arg("failMode") = 0)
      .def("ProposeDetectorField", &G4FieldManager::ProposeDetectorField, py::arg("detectorField"))
      .def("ChangeDetectorField", &G4FieldManager::ChangeDetectorField, py::arg("detectorField"))
      .def("GetDetectorField", &G4FieldManager::GetDetectorField, py::return_value_policy::reference)
      .def("DoesFieldExist", &G4FieldManager::DoesFieldExist)
      .def("CreateChordFinder", &G4FieldManager::CreateChordFinder, py::arg("detectorMagField"))
      .def("SetChordFinder", &G4FieldManager::SetChordFinder, py::arg("aChordFinder"))
      .def("GetChordFinder", py::overload_cast<>(&G4FieldManager::GetChordFinder), py::return_value_policy::reference)
      .def("GetChordFinder", py::overload_cast<>(&G4FieldManager::GetChordFinder, py::const_),
           py::return_value_policy::reference)

      .def("ConfigureForTrack", &G4FieldManager::ConfigureForTrack)
      .def("GetDeltaIntersection", &G4FieldManager::GetDeltaIntersection)
      .def("GetDeltaOneStep", &G4FieldManager::GetDeltaOneStep)
      .def("SetAccuraciesWithDeltaOneStep", &G4FieldManager::SetAccuraciesWithDeltaOneStep, py::arg("valDeltaOneStep"))
      .def("SetDeltaOneStep", &G4FieldManager::SetDeltaOneStep, py::arg("valueD1step"))
      .def("SetDeltaIntersection", &G4FieldManager::SetDeltaIntersection, py::arg("valueDintersection"))
      .def("GetMinimumEpsilonStep", &G4FieldManager::GetMinimumEpsilonStep)
      .def("SetMinimumEpsilonStep", &G4FieldManager::SetMinimumEpsilonStep, py::arg("newEpsMin"))
      .def("GetMaximumEpsilonStep", &G4FieldManager::GetMaximumEpsilonStep)
      .def("SetMaximumEpsilonStep", &G4FieldManager::SetMaximumEpsilonStep, py::arg("newEpsMax"))
      .def("DoesFieldChangeEnergy", &G4FieldManager::DoesFieldChangeEnergy)
      .def("SetFieldChangesEnergy", &G4FieldManager::SetFieldChangesEnergy, py::arg("value"))
      .def("Clone", &G4FieldManager::Clone, py::return_value_policy::reference);
}

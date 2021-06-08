#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Track.hh>
#include <G4TrackingManager.hh>
#include <G4UserTrackingAction.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4UserTrackingAction : public G4UserTrackingAction, public py::trampoline_self_life_support {

public:
   using G4UserTrackingAction::G4UserTrackingAction;

   void SetTrackingManagerPointer(G4TrackingManager *pValue) override
   {
      PYBIND11_OVERRIDE(void, G4UserTrackingAction, SetTrackingManagerPointer, pValue);
   }

   void PreUserTrackingAction(const G4Track *atrack) override
   {
      PYBIND11_OVERRIDE(void, G4UserTrackingAction, PreUserTrackingAction, atrack);
   }

   void PostUserTrackingAction(const G4Track *atrack) override
   {
      PYBIND11_OVERRIDE(void, G4UserTrackingAction, PostUserTrackingAction, atrack);
   }
};

void export_G4UserTrackingAction(py::module &m)
{
   py::class_<G4UserTrackingAction, PyG4UserTrackingAction>(m, "G4UserTrackingAction", "tracking action class")

      .def(py::init<>())

      .def("SetTrackingManagerPointer", &G4UserTrackingAction::SetTrackingManagerPointer)
      .def("PreUserTrackingAction", &G4UserTrackingAction::PreUserTrackingAction)
      .def("PostUserTrackingAction", &G4UserTrackingAction::PostUserTrackingAction);
}

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SteppingVerbose.hh>
#include <G4SteppingManager.hh>
#include <G4Navigator.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VSensitiveDetector.hh>
#include <G4ProcessVector.hh>
#include <G4SteppingManager.hh>
#include <G4Track.hh>
#include <G4UserSteppingAction.hh>
#include <G4StepPoint.hh>
#include <G4VParticleChange.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4SteppingVerbose : public G4SteppingVerbose, public py::trampoline_self_life_support {
public:
   using G4SteppingVerbose::G4SteppingVerbose;

   void NewStep() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, NewStep, ); }

   void AtRestDoItInvoked() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, AtRestDoItInvoked, ); }

   void AlongStepDoItAllDone() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, AlongStepDoItAllDone, ); }

   void PostStepDoItAllDone() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, PostStepDoItAllDone, ); }

   void AlongStepDoItOneByOne() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, AlongStepDoItOneByOne, ); }

   void PostStepDoItOneByOne() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, PostStepDoItOneByOne, ); }

   void StepInfo() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, StepInfo, ); }

   void TrackingStarted() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, TrackingStarted, ); }

   void DPSLStarted() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, DPSLStarted, ); }

   void DPSLUserLimit() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, DPSLUserLimit, ); }

   void DPSLPostStep() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, DPSLPostStep, ); }

   void DPSLAlongStep() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, DPSLAlongStep, ); }

   void VerboseTrack() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, VerboseTrack, ); }

   void VerboseParticleChange() override { PYBIND11_OVERRIDE(void, G4SteppingVerbose, VerboseParticleChange, ); }
};

void export_G4SteppingVerbose(py::module &m)
{
   py::class_<G4SteppingVerbose, PyG4SteppingVerbose, G4VSteppingVerbose>(m, "G4SteppingVerbose")

      .def(py::init<>())
      .def("NewStep", &G4SteppingVerbose::NewStep)
      .def("AtRestDoItInvoked", &G4SteppingVerbose::AtRestDoItInvoked)
      .def("AlongStepDoItAllDone", &G4SteppingVerbose::AlongStepDoItAllDone)
      .def("PostStepDoItAllDone", &G4SteppingVerbose::PostStepDoItAllDone)
      .def("AlongStepDoItOneByOne", &G4SteppingVerbose::AlongStepDoItOneByOne)
      .def("PostStepDoItOneByOne", &G4SteppingVerbose::PostStepDoItOneByOne)
      .def("StepInfo", &G4SteppingVerbose::StepInfo)
      .def("TrackingStarted", &G4SteppingVerbose::TrackingStarted)
      .def("DPSLStarted", &G4SteppingVerbose::DPSLStarted)
      .def("DPSLUserLimit", &G4SteppingVerbose::DPSLUserLimit)
      .def("DPSLPostStep", &G4SteppingVerbose::DPSLPostStep)
      .def("DPSLAlongStep", &G4SteppingVerbose::DPSLAlongStep)
      .def("VerboseTrack", &G4SteppingVerbose::VerboseTrack)
      .def("VerboseParticleChange", &G4SteppingVerbose::VerboseParticleChange)
      .def("ShowStep", &G4SteppingVerbose::ShowStep);
}

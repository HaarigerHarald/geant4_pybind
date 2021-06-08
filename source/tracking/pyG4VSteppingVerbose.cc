#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VSteppingVerbose.hh>
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

class PublicG4VSteppingVerbose : public G4VSteppingVerbose {
public:
   using G4VSteppingVerbose::fManager;
   using G4VSteppingVerbose::fUserSteppingAction;

   using G4VSteppingVerbose::CorrectedStep;
   using G4VSteppingVerbose::FirstStep;
   using G4VSteppingVerbose::fStepStatus;
   using G4VSteppingVerbose::GeometricalStep;
   using G4VSteppingVerbose::PhysicalStep;
   using G4VSteppingVerbose::PreStepPointIsGeom;

   using G4VSteppingVerbose::Mass;
   using G4VSteppingVerbose::TempInitVelocity;
   using G4VSteppingVerbose::TempVelocity;

   using G4VSteppingVerbose::sumEnergyChange;

   using G4VSteppingVerbose::fParticleChange;
   using G4VSteppingVerbose::fPostStepPoint;
   using G4VSteppingVerbose::fPreStepPoint;
   using G4VSteppingVerbose::fSecondary;
   using G4VSteppingVerbose::fStep;
   using G4VSteppingVerbose::fTrack;

   using G4VSteppingVerbose::fCurrentProcess;
   using G4VSteppingVerbose::fCurrentVolume;
   using G4VSteppingVerbose::fSensitive;

   using G4VSteppingVerbose::fAlongStepDoItVector;
   using G4VSteppingVerbose::fAtRestDoItVector;
   using G4VSteppingVerbose::fPostStepDoItVector;

   using G4VSteppingVerbose::fAlongStepGetPhysIntVector;
   using G4VSteppingVerbose::fAtRestGetPhysIntVector;
   using G4VSteppingVerbose::fPostStepGetPhysIntVector;

   using G4VSteppingVerbose::MAXofAlongStepLoops;
   using G4VSteppingVerbose::MAXofAtRestLoops;
   using G4VSteppingVerbose::MAXofPostStepLoops;

   using G4VSteppingVerbose::currentMinimumStep;
   using G4VSteppingVerbose::numberOfInteractionLengthLeft;

   using G4VSteppingVerbose::fAlongStepDoItProcTriggered;
   using G4VSteppingVerbose::fAtRestDoItProcTriggered;
   using G4VSteppingVerbose::fPostStepDoItProcTriggered;

   using G4VSteppingVerbose::fN2ndariesAlongStepDoIt;
   using G4VSteppingVerbose::fN2ndariesAtRestDoIt;
   using G4VSteppingVerbose::fN2ndariesPostStepDoIt;

   using G4VSteppingVerbose::fNavigator;

   using G4VSteppingVerbose::verboseLevel;

   using G4VSteppingVerbose::fSelectedAlongStepDoItVector;
   using G4VSteppingVerbose::fSelectedAtRestDoItVector;
   using G4VSteppingVerbose::fSelectedPostStepDoItVector;

   using G4VSteppingVerbose::fPreviousStepSize;

   using G4VSteppingVerbose::fTouchableHandle;

   using G4VSteppingVerbose::StepControlFlag;

   using G4VSteppingVerbose::fCondition;
   using G4VSteppingVerbose::fGPILSelection;
   using G4VSteppingVerbose::physIntLength;
};

class PyG4VSteppingVerbose : public G4VSteppingVerbose, public py::trampoline_self_life_support {
public:
   using G4VSteppingVerbose::G4VSteppingVerbose;

   void NewStep() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, NewStep, ); }

   void AtRestDoItInvoked() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, AtRestDoItInvoked, ); }

   void AlongStepDoItAllDone() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, AlongStepDoItAllDone, ); }

   void PostStepDoItAllDone() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, PostStepDoItAllDone, ); }

   void AlongStepDoItOneByOne() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, AlongStepDoItOneByOne, ); }

   void PostStepDoItOneByOne() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, PostStepDoItOneByOne, ); }

   void StepInfo() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, StepInfo, ); }

   void TrackingStarted() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, TrackingStarted, ); }

   void DPSLStarted() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, DPSLStarted, ); }

   void DPSLUserLimit() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, DPSLUserLimit, ); }

   void DPSLPostStep() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, DPSLPostStep, ); }

   void DPSLAlongStep() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, DPSLAlongStep, ); }

   void VerboseTrack() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, VerboseTrack, ); }

   void VerboseParticleChange() override { PYBIND11_OVERRIDE(void, G4VSteppingVerbose, VerboseParticleChange, ); }
};

void export_G4VSteppingVerbose(py::module &m)
{
   py::class_<G4VSteppingVerbose, PyG4VSteppingVerbose>(m, "G4VSteppingVerbose")

      .def_static("SetInstance",
                  [](py::disown_ptr<G4VSteppingVerbose> instance) { G4VSteppingVerbose::SetInstance(instance); })

      .def_static("GetInstance", &G4VSteppingVerbose::GetInstance, py::return_value_policy::reference)
      .def_static("GetSilent", &G4VSteppingVerbose::GetSilent)
      .def_static("SetSilent", &G4VSteppingVerbose::SetSilent)
      .def_static("SetSilentStepInfo", &G4VSteppingVerbose::SetSilentStepInfo)

      .def("NewStep", &G4VSteppingVerbose::NewStep)
      .def("CopyState", &G4VSteppingVerbose::CopyState)
      .def("SetManager", &G4VSteppingVerbose::SetManager)
      .def("AtRestDoItInvoked", &G4VSteppingVerbose::AtRestDoItInvoked)
      .def("AlongStepDoItAllDone", &G4VSteppingVerbose::AlongStepDoItAllDone)
      .def("PostStepDoItAllDone", &G4VSteppingVerbose::PostStepDoItAllDone)
      .def("AlongStepDoItOneByOne", &G4VSteppingVerbose::AlongStepDoItOneByOne)
      .def("StepInfo", &G4VSteppingVerbose::StepInfo)
      .def("TrackingStarted", &G4VSteppingVerbose::TrackingStarted)
      .def("DPSLStarted", &G4VSteppingVerbose::DPSLStarted)
      .def("DPSLUserLimit", &G4VSteppingVerbose::DPSLUserLimit)
      .def("DPSLPostStep", &G4VSteppingVerbose::DPSLPostStep)
      .def("DPSLAlongStep", &G4VSteppingVerbose::DPSLAlongStep)
      .def("VerboseTrack", &G4VSteppingVerbose::VerboseTrack)
      .def("VerboseParticleChange", &G4VSteppingVerbose::VerboseParticleChange)

      .def_readwrite("fManager", &PublicG4VSteppingVerbose::fManager)
      .def_readwrite("fUserSteppingAction", &PublicG4VSteppingVerbose::fUserSteppingAction)

      .def_readwrite("PhysicalStep", &PublicG4VSteppingVerbose::PhysicalStep)
      .def_readwrite("GeometricalStep", &PublicG4VSteppingVerbose::GeometricalStep)
      .def_readwrite("CorrectedStep", &PublicG4VSteppingVerbose::CorrectedStep)
      .def_readwrite("PreStepPointIsGeom", &PublicG4VSteppingVerbose::PreStepPointIsGeom)
      .def_readwrite("FirstStep", &PublicG4VSteppingVerbose::FirstStep)
      .def_readwrite("fStepStatus", &PublicG4VSteppingVerbose::fStepStatus)

      .def_readwrite("TempInitVelocity", &PublicG4VSteppingVerbose::TempInitVelocity)
      .def_readwrite("TempVelocity", &PublicG4VSteppingVerbose::TempVelocity)
      .def_readwrite("Mass", &PublicG4VSteppingVerbose::Mass)

      .def_readwrite("sumEnergyChange", &PublicG4VSteppingVerbose::sumEnergyChange)

      .def_readwrite("fParticleChange", &PublicG4VSteppingVerbose::fParticleChange)
      .def_readwrite("fTrack", &PublicG4VSteppingVerbose::fTrack)
      .def_readwrite("fSecondary", &PublicG4VSteppingVerbose::fSecondary)
      .def_readwrite("fStep", &PublicG4VSteppingVerbose::fStep)
      .def_readwrite("fPreStepPoint", &PublicG4VSteppingVerbose::fPreStepPoint)
      .def_readwrite("fPostStepPoint", &PublicG4VSteppingVerbose::fPostStepPoint)

      .def_readwrite("fCurrentVolume", &PublicG4VSteppingVerbose::fCurrentVolume)
      .def_readwrite("fSensitive", &PublicG4VSteppingVerbose::fSensitive)
      .def_readwrite("fCurrentProcess", &PublicG4VSteppingVerbose::fCurrentProcess)

      .def_readwrite("fAtRestDoItVector", &PublicG4VSteppingVerbose::fAtRestDoItVector)
      .def_readwrite("fAlongStepDoItVector", &PublicG4VSteppingVerbose::fAlongStepDoItVector)
      .def_readwrite("fPostStepDoItVector", &PublicG4VSteppingVerbose::fPostStepDoItVector)

      .def_readwrite("fAtRestGetPhysIntVector", &PublicG4VSteppingVerbose::fAtRestGetPhysIntVector)
      .def_readwrite("fAlongStepGetPhysIntVector", &PublicG4VSteppingVerbose::fAlongStepGetPhysIntVector)
      .def_readwrite("fPostStepGetPhysIntVector", &PublicG4VSteppingVerbose::fPostStepGetPhysIntVector)

      .def_readwrite("MAXofAtRestLoops", &PublicG4VSteppingVerbose::MAXofAtRestLoops)
      .def_readwrite("MAXofAlongStepLoops", &PublicG4VSteppingVerbose::MAXofAlongStepLoops)
      .def_readwrite("MAXofPostStepLoops", &PublicG4VSteppingVerbose::MAXofPostStepLoops)

      .def_readwrite("currentMinimumStep", &PublicG4VSteppingVerbose::currentMinimumStep)
      .def_readwrite("numberOfInteractionLengthLeft", &PublicG4VSteppingVerbose::numberOfInteractionLengthLeft)

      .def_readwrite("fAtRestDoItProcTriggered", &PublicG4VSteppingVerbose::fAtRestDoItProcTriggered)
      .def_readwrite("fAlongStepDoItProcTriggered", &PublicG4VSteppingVerbose::fAlongStepDoItProcTriggered)
      .def_readwrite("fPostStepDoItProcTriggered", &PublicG4VSteppingVerbose::fPostStepDoItProcTriggered)

      .def_readwrite("fN2ndariesAtRestDoIt", &PublicG4VSteppingVerbose::fN2ndariesAtRestDoIt)
      .def_readwrite("fN2ndariesAlongStepDoIt", &PublicG4VSteppingVerbose::fN2ndariesAlongStepDoIt)
      .def_readwrite("fN2ndariesPostStepDoIt", &PublicG4VSteppingVerbose::fN2ndariesPostStepDoIt)

      .def_readwrite("fNavigator", &PublicG4VSteppingVerbose::fNavigator)

      .def_readwrite("verboseLevel", &PublicG4VSteppingVerbose::verboseLevel)

      .def_readwrite("fSelectedAtRestDoItVector", &PublicG4VSteppingVerbose::fSelectedAtRestDoItVector)
      .def_readwrite("fSelectedAlongStepDoItVector", &PublicG4VSteppingVerbose::fSelectedAlongStepDoItVector)
      .def_readwrite("fSelectedPostStepDoItVector", &PublicG4VSteppingVerbose::fSelectedPostStepDoItVector)

      .def_readwrite("fPreviousStepSize", &PublicG4VSteppingVerbose::fPreviousStepSize)
      .def_readwrite("fTouchableHandle", &PublicG4VSteppingVerbose::fTouchableHandle)

      .def_readwrite("StepControlFlag", &PublicG4VSteppingVerbose::StepControlFlag)

      .def_readwrite("physIntLength", &PublicG4VSteppingVerbose::physIntLength)
      .def_readwrite("fCondition", &PublicG4VSteppingVerbose::fCondition)
      .def_readwrite("fGPILSelection", &PublicG4VSteppingVerbose::fGPILSelection);
}

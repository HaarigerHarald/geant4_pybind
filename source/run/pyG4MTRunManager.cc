#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MTRunManager.hh>
#include <G4VUserDetectorConstruction.hh>
#include <G4VModularPhysicsList.hh>
#include <G4VUserPhysicsList.hh>
#include <G4UserWorkerInitialization.hh>
#include <G4UserWorkerThreadInitialization.hh>
#include <G4VUserActionInitialization.hh>
#include <G4UserRunAction.hh>
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4UserEventAction.hh>
#include <G4Timer.hh>
#include <G4RunMessenger.hh>
#include <G4DCtable.hh>
#include <G4Run.hh>
#include <G4Allocator.hh>
#include <G4VUserPrimaryParticleInformation.hh>
#include <G4VUserPrimaryVertexInformation.hh>
#include <G4VHit.hh>
#include <G4VDigi.hh>
#include <G4VTrajectoryPoint.hh>
#include <G4AttDef.hh>
#include <G4AttValue.hh>
#include <G4GeomSplitter.hh>
#include <G4ProductionCuts.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VisAttributes.hh>
#include <G4DecayTable.hh>
#include <G4ParticlePropertyTable.hh>
#include <G4DecayProducts.hh>
#include <G4ReferenceCountedHandle.hh>
#include <G4DensityEffectData.hh>
#include <G4DensityEffectCalculator.hh>
#include <G4VAuxiliaryTrackInformation.hh>
#include <G4Polyline.hh>
#include <G4StackingMessenger.hh>
#include <G4ParticleMessenger.hh>
#include <G4IonTable.hh>
#include <G4EvManMessenger.hh>
#include <G4VoxelLimits.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4VoxelSafety.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Trd.hh>
#include <G4Trap.hh>
#include <G4Cons.hh>
#include <G4Sphere.hh>
#include <G4Orb.hh>
#include <G4Ellipsoid.hh>
#include <G4Torus.hh>
#include <G4Para.hh>
#include <G4Polycone.hh>
#include <G4Polyhedra.hh>
#include <G4Hype.hh>
#include <G4ProcessTable.hh>
#include <G4ProcessManagerMessenger.hh>
#include <G4ProcessAttribute.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithABool.hh>
#include <G4SDManager.hh>
#include <G4StateManager.hh>
#include <G4ExceptionHandler.hh>
#include <G4RunManagerFactory.hh>
#include <G4MTRunManagerKernel.hh>
#include <G4ScoringManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4MTRunManager(py::module &m)
{
   py::class_<G4MTRunManager, G4RunManager, py::nodelete> mG4MTRunManager(m, "G4MTRunManager");

   py::enum_<G4MTRunManager::WorkerActionRequest>(mG4MTRunManager, "WorkerActionRequest")
      .value("UNDEFINED", G4MTRunManager::WorkerActionRequest::UNDEFINED)
      .value("NEXTITERATION", G4MTRunManager::WorkerActionRequest::NEXTITERATION)
      .value("PROCESSUI", G4MTRunManager::WorkerActionRequest::PROCESSUI)
      .value("ENDWORKER", G4MTRunManager::WorkerActionRequest::ENDWORKER);

   mG4MTRunManager.def(py::init<>())
      .def("AbortEvent", &G4MTRunManager::AbortEvent)
      .def("AbortRun", &G4MTRunManager::AbortRun, py::arg("softAbort") = false)
      .def("ConstructScoringWorlds", &G4MTRunManager::ConstructScoringWorlds)
      .def("GetCommandStack", &G4MTRunManager::GetCommandStack)
      .def("GetEventModulo", &G4MTRunManager::GetEventModulo)
      .def_static("GetMTMasterRunManagerKernel", &G4MTRunManager::GetMTMasterRunManagerKernel,
                  py::return_value_policy::reference)

      .def_static("GetMasterRunManager", &G4MTRunManager::GetMasterRunManager, py::return_value_policy::reference)
      .def_static("GetMasterRunManagerKernel", &G4MTRunManager::GetMasterRunManagerKernel,
                  py::return_value_policy::reference)

      .def_static("GetMasterScoringManager", &G4MTRunManager::GetMasterScoringManager,
                  py::return_value_policy::reference)

      .def_static("GetMasterThreadId", &G4MTRunManager::GetMasterThreadId)
      .def_static("GetMasterWorlds", &G4MTRunManager::GetMasterWorlds)
      .def("GetNumberActiveThreads", &G4MTRunManager::GetNumberActiveThreads)
      .def("GetNumberOfThreads", &G4MTRunManager::GetNumberOfThreads)
      .def("GetPinAffinity", &G4MTRunManager::GetPinAffinity)
      .def("Initialize", &G4MTRunManager::Initialize)
      .def("InitializeEventLoop", &G4MTRunManager::InitializeEventLoop, py::arg("n_event"),
           py::arg("macroFile") = static_cast<const char *>(0), py::arg("n_select") = -1)

      .def("InitializeThreadPool", &G4MTRunManager::InitializeThreadPool)
      .def("MergeRun", &G4MTRunManager::MergeRun, py::arg("localRun"))
      .def("MergeScores", &G4MTRunManager::MergeScores, py::arg("localScoringManager"))
      .def("ProcessOneEvent", &G4MTRunManager::ProcessOneEvent, py::arg("i_event"))
      .def("RequestWorkersProcessCommandsStack", &G4MTRunManager::RequestWorkersProcessCommandsStack)
      .def("RunTermination", &G4MTRunManager::RunTermination)
      .def_static("SeedOncePerCommunication", &G4MTRunManager::SeedOncePerCommunication)
      .def("SetEventModulo", &G4MTRunManager::SetEventModulo, py::arg("i") = 1)
      .def("SetNumberOfThreads", &G4MTRunManager::SetNumberOfThreads, py::arg("n"))
      .def("SetPinAffinity", &G4MTRunManager::SetPinAffinity, py::arg("n") = 1)
      .def_static("SetSeedOncePerCommunication", &G4MTRunManager::SetSeedOncePerCommunication, py::arg("val"))
      .def(
         "SetUpAnEvent",
         [](G4MTRunManager &self, G4Event *arg0, long int &s1, long int &s2, long int &s3, G4bool reseedRequired) {
            return std::make_tuple(self.SetUpAnEvent(arg0, s1, s2, s3, reseedRequired), s1, s2, s3);
         },
         py::arg("arg0"), py::arg("s1"), py::arg("s2"), py::arg("s3"), py::arg("reseedRequired") = true)

      .def("SetUpNEvents", &G4MTRunManager::SetUpNEvents, py::arg("arg0"), py::arg("seedsQueue"),
           py::arg("reseedRequired") = true)

      .def("SetUserAction", py::overload_cast<G4UserRunAction *>(&G4MTRunManager::SetUserAction), py::arg("userAction"))
      .def("SetUserAction", py::overload_cast<G4VUserPrimaryGeneratorAction *>(&G4MTRunManager::SetUserAction),
           py::arg("userAction"))

      .def("SetUserAction", py::overload_cast<G4UserEventAction *>(&G4MTRunManager::SetUserAction),
           py::arg("userAction"))

      .def("SetUserAction", py::overload_cast<G4UserStackingAction *>(&G4MTRunManager::SetUserAction),
           py::arg("userAction"))

      .def("SetUserAction", py::overload_cast<G4UserTrackingAction *>(&G4MTRunManager::SetUserAction),
           py::arg("userAction"))

      .def("SetUserAction", py::overload_cast<G4UserSteppingAction *>(&G4MTRunManager::SetUserAction),
           py::arg("userAction"))

      .def("SetUserInitialization",
           [](G4MTRunManager &self, py::disown_ptr<G4VUserDetectorConstruction> detector) {
              self.SetUserInitialization(detector);
           })

      // I've not 100% understood this, but upcasting to (G4VUserPhysicsList *) does not properly work
      .def("SetUserInitialization",
           [](G4MTRunManager &self, py::disown_ptr<G4VModularPhysicsList> list) { self.SetUserInitialization(list); })

      .def("SetUserInitialization",
           [](G4MTRunManager &self, py::disown_ptr<G4VUserPhysicsList> list) { self.SetUserInitialization(list); })

      .def("SetUserInitialization",
           [](G4MTRunManager &self, py::disown_ptr<G4VUserActionInitialization> actionInit) {
              self.SetUserInitialization(actionInit);
           })

      .def("SetUserInitialization",
           py::overload_cast<G4UserWorkerInitialization *>(&G4MTRunManager::SetUserInitialization), py::arg("userInit"))

      .def("SetUserInitialization",
           py::overload_cast<G4UserWorkerThreadInitialization *>(&G4MTRunManager::SetUserInitialization),
           py::arg("userInit"))

      .def("TerminateOneEvent", &G4MTRunManager::TerminateOneEvent)
      .def("ThisWorkerEndEventLoop", &G4MTRunManager::ThisWorkerEndEventLoop)
      .def("ThisWorkerProcessCommandsStackDone", &G4MTRunManager::ThisWorkerProcessCommandsStackDone)
      .def("ThisWorkerReady", &G4MTRunManager::ThisWorkerReady)
      .def("ThisWorkerWaitForNextAction", &G4MTRunManager::ThisWorkerWaitForNextAction)
      .def_static("addWorld", &G4MTRunManager::addWorld, py::arg("counter"), py::arg("w"))
      .def("getMasterRandomEngine", &G4MTRunManager::getMasterRandomEngine, py::return_value_policy::reference);
}

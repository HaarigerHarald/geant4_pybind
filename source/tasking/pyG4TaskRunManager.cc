#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TaskRunManager.hh>
#include <G4VUserDetectorConstruction.hh>
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
#include <G4TaskRunManagerKernel.hh>
#include <G4UserTaskInitialization.hh>
#include <G4UserTaskThreadInitialization.hh>
#include <G4WorkerTaskRunManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TaskRunManager(py::module &m)
{
   py::class_<G4TaskRunManager, G4MTRunManager, py::nodelete>(m, "G4TaskRunManager", py::multiple_inheritance())

      .def(py::init<G4bool>(), py::arg("useTBB") = G4GetEnv("G4USE_TBB", false))
      .def(py::init<G4VUserTaskQueue *, G4bool, G4int>(), py::arg("taskQueue"),
           py::arg("useTBB") = G4GetEnv("G4USE_TBB", false), py::arg("evtGrainsize") = 0)

      .def("AbortEvent", &G4TaskRunManager::AbortEvent)
      .def("AbortRun", &G4TaskRunManager::AbortRun, py::arg("softAbort") = false)
      .def("ConstructScoringWorlds", &G4TaskRunManager::ConstructScoringWorlds)
      .def("GetGrainsize", &G4TaskRunManager::GetGrainsize)
      .def_static("GetMTMasterRunManagerKernel", &G4TaskRunManager::GetMTMasterRunManagerKernel,
                  py::return_value_policy::reference)

      .def_static("GetMasterRunManager", &G4TaskRunManager::GetMasterRunManager, py::return_value_policy::reference)
      .def_static("GetMasterThreadId", &G4TaskRunManager::GetMasterThreadId)
      .def("GetNumberActiveThreads", &G4TaskRunManager::GetNumberActiveThreads)
      .def("GetNumberOfEventsPerTask", &G4TaskRunManager::GetNumberOfEventsPerTask)
      .def("GetNumberOfTasks", &G4TaskRunManager::GetNumberOfTasks)
      .def("GetNumberOfThreads", &G4TaskRunManager::GetNumberOfThreads)
      .def("Initialize", py::overload_cast<>(&G4TaskRunManager::Initialize))
      .def("Initialize", py::overload_cast<uint64_t>(&G4TaskRunManager::Initialize), py::arg("nthreads"))
      .def("InitializeEventLoop", &G4TaskRunManager::InitializeEventLoop, py::arg("n_event"),
           py::arg("macroFile") = static_cast<const char *>(nullptr), py::arg("n_select") = -1)

      .def("InitializeThreadPool", &G4TaskRunManager::InitializeThreadPool)
      .def("MergeRun", &G4TaskRunManager::MergeRun, py::arg("localRun"))
      .def("MergeScores", &G4TaskRunManager::MergeScores, py::arg("localScoringManager"))
      .def("ProcessOneEvent", &G4TaskRunManager::ProcessOneEvent, py::arg("i_event"))
      .def("RequestWorkersProcessCommandsStack", &G4TaskRunManager::RequestWorkersProcessCommandsStack)
      .def("RunTermination", &G4TaskRunManager::RunTermination)
      .def("SetGrainsize", &G4TaskRunManager::SetGrainsize, py::arg("n"))
      .def("SetInitializeSeedsCallback", &G4TaskRunManager::SetInitializeSeedsCallback, py::arg("f"))
      .def("SetNumberOfThreads", &G4TaskRunManager::SetNumberOfThreads, py::arg("n"))
      .def(
         "SetUpAnEvent",
         [](G4TaskRunManager &self, G4Event *arg0, G4long &s1, G4long &s2, G4long &s3, G4bool reseedRequired) {
            return std::make_tuple(self.SetUpAnEvent(arg0, s1, s2, s3, reseedRequired), s1, s2, s3);
         },
         py::arg("arg0"), py::arg("s1"), py::arg("s2"), py::arg("s3"), py::arg("reseedRequired") = true)

      .def("SetUpNEvents", &G4TaskRunManager::SetUpNEvents, py::arg("arg0"), py::arg("seedsQueue"),
           py::arg("reseedRequired") = true)

      .def("TerminateOneEvent", &G4TaskRunManager::TerminateOneEvent)
      .def("ThisWorkerEndEventLoop", &G4TaskRunManager::ThisWorkerEndEventLoop)
      .def("ThisWorkerProcessCommandsStackDone", &G4TaskRunManager::ThisWorkerProcessCommandsStackDone)
      .def("ThisWorkerReady", &G4TaskRunManager::ThisWorkerReady)
      .def("ThisWorkerWaitForNextAction", &G4TaskRunManager::ThisWorkerWaitForNextAction)
      .def("ThreadPoolIsInitialized", &G4TaskRunManager::ThreadPoolIsInitialized)
      .def("WaitForEndEventLoopWorkers", &G4TaskRunManager::WaitForEndEventLoopWorkers)
      .def("WaitForReadyWorkers", &G4TaskRunManager::WaitForReadyWorkers);
}

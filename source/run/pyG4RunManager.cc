#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RunManager.hh>
#include <G4VUserDetectorConstruction.hh>
#include <G4VUserPhysicsList.hh>
#include <G4UserRunAction.hh>
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4UserEventAction.hh>
#include <G4UserStackingAction.hh>
#include <G4UserTrackingAction.hh>
#include <G4UserSteppingAction.hh>
#include <G4Region.hh>
#include <G4Run.hh>
#include <G4Event.hh>
#include <G4VUserActionInitialization.hh>
#include <G4VModularPhysicsList.hh>
#include <G4UImanager.hh>
#include <G4DCtable.hh>

#include "holder.hh"
#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4RunManager(py::module &m)
{
   py::class_<G4RunManager, std::unique_ptr<G4RunManager, py::nodelete>>(m, "G4RunManager", "run manager class")
      .def(py::init<>())

      .def_static("GetRunManager", &G4RunManager::GetRunManager, "Get an instance of G4RunManager",
                  py::return_value_policy::reference)

      .def("SetVerboseLevel", &G4RunManager::SetVerboseLevel)
      .def("GetVerboseLevel", &G4RunManager::GetVerboseLevel)
      .def("SetPrintProgress", &G4RunManager::SetPrintProgress)
      .def("GetPrintProgress", &G4RunManager::GetPrintProgress)

      .def("Initialize", &G4RunManager::Initialize)
      .def(
         "BeamOn",
         [](G4RunManager &self, G4int n_event, const char *macroFile = 0, G4int n_select = -1) {
            py::gil_scoped_release gil;
            self.BeamOn(n_event, macroFile, n_select);
         },
         py::arg("n_event"), py::arg("macroFile") = static_cast<const char *>(nullptr), py::arg("n_select") = -1,
         "Starts event loop.")

      .def("SetUserInitialization",
           [](G4RunManager &self, G4VUserDetectorConstruction *detector) {
              self.SetUserInitialization(detector);
              TRAMPOLINE_REF_INCREASE(G4VUserDetectorConstruction, detector);
              owntrans_ptr<G4VUserDetectorConstruction>::remove(detector);
           })

      // I've not 100% understood this, but upcasting to (G4VUserPhysicsList *) does not properly work
      .def("SetUserInitialization",
           [](G4RunManager &self, G4VModularPhysicsList *list) {
              self.SetUserInitialization(list);
              TRAMPOLINE_REF_INCREASE(G4VModularPhysicsList, list);
              owntrans_ptr<G4VModularPhysicsList>::remove(list);
           })

      .def("SetUserInitialization",
           [](G4RunManager &self, G4VUserPhysicsList *list) {
              self.SetUserInitialization(list);
              TRAMPOLINE_REF_INCREASE(G4VUserPhysicsList, list);
              owntrans_ptr<G4VUserPhysicsList>::remove(list);
           })

      .def("SetUserInitialization",
           [](G4RunManager &self, G4VUserActionInitialization *actionInit) {
              self.SetUserInitialization(actionInit);
              TRAMPOLINE_REF_INCREASE(G4VUserActionInitialization, actionInit);
              owntrans_ptr<G4VUserActionInitialization>::remove(actionInit);
           })

      // TODO
      // .def("SetUserInitialization",
      //       py::overload_cast<G4UserWorkerInitialization *>(&G4RunManager::SetUserInitialization),
      //       py::keep_alive<1, 2>())

      // .def("SetUserInitialization",
      //       py::overload_cast<G4UserWorkerThreadInitialization *>(&G4RunManager::SetUserInitialization),
      //       py::keep_alive<1, 2>())

      .def("SetUserAction",
           [](G4RunManager &self, G4UserRunAction *action) {
              self.SetUserAction(action);
              TRAMPOLINE_REF_INCREASE(G4UserRunAction, action);
              owntrans_ptr<G4UserRunAction>::remove(action);
           })

      .def("SetUserAction",
           [](G4RunManager &self, G4VUserPrimaryGeneratorAction *genAction) {
              self.SetUserAction(genAction);
              TRAMPOLINE_REF_INCREASE(G4VUserPrimaryGeneratorAction, genAction);
              owntrans_ptr<G4VUserPrimaryGeneratorAction>::remove(genAction);
           })

      .def("SetUserAction",
           [](G4RunManager &self, G4UserEventAction *eventAction) {
              self.SetUserAction(eventAction);
              TRAMPOLINE_REF_INCREASE(G4UserEventAction, eventAction);
              owntrans_ptr<G4UserEventAction>::remove(eventAction);
           })

      .def("SetUserAction",
           [](G4RunManager &self, G4UserStackingAction *stackingAction) {
              self.SetUserAction(stackingAction);
              TRAMPOLINE_REF_INCREASE(G4UserStackingAction, stackingAction);
              owntrans_ptr<G4UserStackingAction>::remove(stackingAction);
           })

      .def("SetUserAction",
           [](G4RunManager &self, G4UserTrackingAction *trackingAction) {
              self.SetUserAction(trackingAction);
              TRAMPOLINE_REF_INCREASE(G4UserTrackingAction, trackingAction);
              owntrans_ptr<G4UserTrackingAction>::remove(trackingAction);
           })

      .def("SetUserAction",
           [](G4RunManager &self, G4UserSteppingAction *steppingAction) {
              self.SetUserAction(steppingAction);
              TRAMPOLINE_REF_INCREASE(G4UserSteppingAction, steppingAction);
              owntrans_ptr<G4UserSteppingAction>::remove(steppingAction);
           })

      .def("GetUserDetectorConstruction", &G4RunManager::GetUserDetectorConstruction,
           py::return_value_policy::reference_internal)

      .def("GetUserPhysicsList", &G4RunManager::GetUserPhysicsList, py::return_value_policy::reference_internal)
      .def("GetUserPrimaryGeneratorAction", &G4RunManager::GetUserPrimaryGeneratorAction,
           py::return_value_policy::reference_internal)

      .def("GetUserRunAction", &G4RunManager::GetUserRunAction, py::return_value_policy::reference_internal)
      .def("GetUserEventAction", &G4RunManager::GetUserEventAction, py::return_value_policy::reference_internal)
      .def("GetUserStackingAction", &G4RunManager::GetUserStackingAction, py::return_value_policy::reference_internal)
      .def("GetUserTrackingAction", &G4RunManager::GetUserTrackingAction, py::return_value_policy::reference_internal)
      .def("GetUserSteppingAction", &G4RunManager::GetUserSteppingAction, py::return_value_policy::reference_internal)

      .def("AbortRun", &G4RunManager::AbortRun, py::arg("softAbort") = false, "Abort run (event loop).")
      .def("AbortEvent", &G4RunManager::AbortEvent)
      .def("DefineWorldVolume", &G4RunManager::DefineWorldVolume, py::arg("worldVol"),
           py::arg("topologyIsChanged") = true)

      .def("DumpRegion", py::overload_cast<const G4String &>(&G4RunManager::DumpRegion, py::const_))
      .def("DumpRegion", py::overload_cast<G4Region *>(&G4RunManager::DumpRegion, py::const_),
           py::arg("region") = static_cast<G4Region *>(nullptr))

      .def("rndmSaveThisRun", &G4RunManager::rndmSaveThisRun)
      .def("rndmSaveThisEvent", &G4RunManager::rndmSaveThisEvent)
      .def("RestoreRandomNumberStatus", &G4RunManager::RestoreRandomNumberStatus)
      .def("SetRandomNumberStore", &G4RunManager::SetRandomNumberStore)
      .def("GetRandomNumberStore", &G4RunManager::GetRandomNumberStore)
      .def("SetRandomNumberStoreDir", &G4RunManager::SetRandomNumberStoreDir)
      .def("GeometryHasBeenModified", &G4RunManager::GeometryHasBeenModified, py::arg("prop") = true)
      .def("PhysicsHasBeenModified", &G4RunManager::PhysicsHasBeenModified)
      .def("SetGeometryToBeOptimized", &G4RunManager::SetGeometryToBeOptimized)
      .def("GetGeometryToBeOptimized", &G4RunManager::GetGeometryToBeOptimized)
      .def("SetNumberOfEventsToBeStored", &G4RunManager::SetNumberOfEventsToBeStored)
      .def("GetCurrentRun", &G4RunManager::GetCurrentRun, py::return_value_policy::reference)
      .def("GetNonConstCurrentRun", &G4RunManager::GetNonConstCurrentRun, py::return_value_policy::reference)
      .def("GetCurrentEvent", &G4RunManager::GetCurrentEvent, py::return_value_policy::reference)
      .def("GetPreviousEvent", &G4RunManager::GetPreviousEvent, py::return_value_policy::reference)
      .def("GetNumberOfParallelWorld", &G4RunManager::GetNumberOfParallelWorld)
      .def("SetNumberOfEventsToBeProcessed", &G4RunManager::SetNumberOfEventsToBeProcessed)
      .def("GetNumberOfEventsToBeProcessed", &G4RunManager::GetNumberOfEventsToBeProcessed)
      .def("GetNumberOfSelectEvents", &G4RunManager::GetNumberOfSelectEvents)
      .def("GetSelectMacro", &G4RunManager::GetSelectMacro)
      .def("SetDCtable", &G4RunManager::SetDCtable)
      .def("GetRunManagerType", &G4RunManager::GetRunManagerType)
      .def("SetRunIDCounter", &G4RunManager::SetRunIDCounter)
      .def("GetVersionString", &G4RunManager::GetVersionString, py::return_value_policy::reference)
      .def("GetRandomNumberStoreDir", &G4RunManager::GetRandomNumberStoreDir,
           py::return_value_policy::reference_internal);

   m.add_object("_cleanup", py::capsule([]() {
                   G4UImanager *UImgr = G4UImanager::GetUIpointer();
                   UImgr->SetCoutDestination(0);
                   delete G4RunManager::GetRunManager();
                }));
}

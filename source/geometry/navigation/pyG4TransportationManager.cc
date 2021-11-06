#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TransportationManager.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4ProductionCuts.hh>
#include <G4Material.hh>
#include <G4VUserRegionInformation.hh>
#include <G4MaterialCutsCouple.hh>
#include <G4UserLimits.hh>
#include <G4FieldManager.hh>
#include <G4FastSimulationManager.hh>
#include <G4UserSteppingAction.hh>
#include <G4VSensitiveDetector.hh>
#include <G4VisAttributes.hh>
#include <G4Allocator.hh>
#include <G4ReferenceCountedHandle.hh>
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
#include <G4PathFinder.hh>
#include <G4PropagatorInField.hh>
#include <G4GeometryMessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TransportationManager(py::module &m)
{
   py::class_<G4TransportationManager, py::nodelete>(m, "G4TransportationManager")

      .def_static("GetTransportationManager", &G4TransportationManager::GetTransportationManager,
                  py::return_value_policy::reference)

      .def_static("GetInstanceIfExist", &G4TransportationManager::GetInstanceIfExist,
                  py::return_value_policy::reference)

      .def("GetPropagatorInField", &G4TransportationManager::GetPropagatorInField, py::return_value_policy::reference)
      .def("SetPropagatorInField", &G4TransportationManager::SetPropagatorInField, py::arg("newFieldPropagator"))
      .def("GetFieldManager", &G4TransportationManager::GetFieldManager, py::return_value_policy::reference)
      .def("SetFieldManager", &G4TransportationManager::SetFieldManager, py::arg("newFieldManager"))
      .def("GetNavigatorForTracking", &G4TransportationManager::GetNavigatorForTracking,
           py::return_value_policy::reference)

      .def("SetNavigatorForTracking", &G4TransportationManager::SetNavigatorForTracking, py::arg("newNavigator"))
      .def("SetWorldForTracking", &G4TransportationManager::SetWorldForTracking, py::arg("theWorld"))
      .def("GetNoActiveNavigators", &G4TransportationManager::GetNoActiveNavigators)
      .def(
         "GetActiveNavigatorsIterator",
         [](G4TransportationManager &self) {
            auto begin = self.GetActiveNavigatorsIterator();
            auto end   = begin + self.GetNoActiveNavigators();

            return py::make_iterator(begin, end);
         },
         py::keep_alive<0, 1>())

      .def("GetNoWorlds", &G4TransportationManager::GetNoWorlds)
      .def(
         "GetWorldsIterator",
         [](G4TransportationManager &self) {
            auto begin = self.GetWorldsIterator();
            auto end   = begin + self.GetNoWorlds();

            return py::make_iterator(begin, end);
         },
         py::keep_alive<0, 1>())

      .def("GetSafetyHelper", &G4TransportationManager::GetSafetyHelper, py::return_value_policy::reference)
      .def("GetParallelWorld", &G4TransportationManager::GetParallelWorld, py::arg("worldName"),
           py::return_value_policy::reference)

      .def("IsWorldExisting", &G4TransportationManager::IsWorldExisting, py::arg("worldName"),
           py::return_value_policy::reference)

      .def("GetNavigator", py::overload_cast<const G4String &>(&G4TransportationManager::GetNavigator),
           py::arg("worldName"), py::return_value_policy::reference)

      .def("GetNavigator", py::overload_cast<G4VPhysicalVolume *>(&G4TransportationManager::GetNavigator),
           py::arg("aWorld"), py::return_value_policy::reference)

      .def("RegisterWorld", &G4TransportationManager::RegisterWorld, py::arg("aWorld"))
      .def("DeRegisterNavigator", &G4TransportationManager::DeRegisterNavigator, py::arg("aNavigator"))
      .def("ActivateNavigator", &G4TransportationManager::ActivateNavigator, py::arg("aNavigator"))
      .def("DeActivateNavigator", &G4TransportationManager::DeActivateNavigator, py::arg("aNavigator"))
      .def("InactivateAll", &G4TransportationManager::InactivateAll)
      .def_static("GetFirstTrackingNavigator", &G4TransportationManager::GetFirstTrackingNavigator,
                  py::return_value_policy::reference)

      .def_static("SetFirstTrackingNavigator", &G4TransportationManager::SetFirstTrackingNavigator, py::arg("nav"))
      .def("ClearParallelWorlds", &G4TransportationManager::ClearParallelWorlds);
}

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <G4Event.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Event(py::module &m)
{
   py::class_<G4Event>(m, "G4Event")

      .def(py::init<>())
      .def(py::init<G4int>(), py::arg("evID"))
      .def("AddPrimaryVertex", &G4Event::AddPrimaryVertex, py::arg("aPrimaryVertex"))
      .def("Draw", &G4Event::Draw)
      .def("GetDCofThisEvent", &G4Event::GetDCofThisEvent, py::return_value_policy::reference_internal)
      .def("GetEventID", &G4Event::GetEventID)
      .def("GetHCofThisEvent", &G4Event::GetHCofThisEvent, py::return_value_policy::reference_internal)
      .def("GetNumberOfGrips", &G4Event::GetNumberOfGrips)
      .def("GetNumberOfPrimaryVertex", &G4Event::GetNumberOfPrimaryVertex)
      .def("GetPrimaryVertex", &G4Event::GetPrimaryVertex, py::arg("i") = 0,
           py::return_value_policy::reference_internal)

      .def("GetRandomNumberStatus", &G4Event::GetRandomNumberStatus)
      .def("GetRandomNumberStatusForProcessing", &G4Event::GetRandomNumberStatusForProcessing)
      .def("GetTrajectoryContainer", &G4Event::GetTrajectoryContainer, py::return_value_policy::reference_internal)
      .def("GetUserInformation", &G4Event::GetUserInformation, py::return_value_policy::reference_internal)
      .def("IsAborted", &G4Event::IsAborted)
      .def("KeepForPostProcessing", &G4Event::KeepForPostProcessing)
      .def("KeepTheEvent", &G4Event::KeepTheEvent, py::arg("vl") = true)
      .def("PostProcessingFinished", &G4Event::PostProcessingFinished)
      .def("Print", &G4Event::Print)
      .def(
         "SetDCofThisEvent", [](G4Event &self, py::disown_ptr<G4DCofThisEvent> value) { self.SetDCofThisEvent(value); },
         py::arg("value"))

      .def("SetEventAborted", &G4Event::SetEventAborted)
      .def("SetEventID", &G4Event::SetEventID, py::arg("i"))
      .def(
         "SetHCofThisEvent", [](G4Event &self, py::disown_ptr<G4HCofThisEvent> value) { self.SetHCofThisEvent(value); },
         py::arg("value"))

      .def("SetRandomNumberStatus", &G4Event::SetRandomNumberStatus, py::arg("st"))
      .def("SetRandomNumberStatusForProcessing", &G4Event::SetRandomNumberStatusForProcessing, py::arg("st"))
      .def(
         "SetTrajectoryContainer",
         [](G4Event &self, py::disown_ptr<G4TrajectoryContainer> value) { self.SetTrajectoryContainer(value); },
         py::arg("value"))

      .def(
         "SetUserInformation",
         [](G4Event &self, py::disown_ptr<G4VUserEventInformation> anInfo) { self.SetUserInformation(anInfo); },
         py::arg("anInfo"))

      .def("ToBeKept", &G4Event::ToBeKept)
      .def(py::self != py::self)
      .def(py::self == py::self);
}

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Event.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Event(py::module &m)
{
   py::class_<G4Event>(m, "G4Event", "event class")
      .def(py::init<>())
      .def(py::init<G4int>())

      .def("Print", &G4Event::Print)
      .def("Draw", &G4Event::Draw)

      .def("SetEventID", &G4Event::SetEventID)
      .def("SetHCofThisEvent", &G4Event::SetHCofThisEvent)
      .def("SetDCofThisEvent", &G4Event::SetDCofThisEvent)
      .def("SetTrajectoryContainer", &G4Event::SetTrajectoryContainer)
      .def("SetEventAborted", &G4Event::SetEventAborted)
      .def("SetRandomNumberStatus", &G4Event::SetRandomNumberStatus)
      .def("SetRandomNumberStatusForProcessing", &G4Event::SetRandomNumberStatusForProcessing)
      .def("KeepTheEvent", &G4Event::KeepTheEvent, py::arg("vl") = true)

      .def("ToBeKept", &G4Event::ToBeKept)
      .def("KeepForPostProcessing", &G4Event::KeepForPostProcessing)
      .def("PostProcessingFinished", &G4Event::PostProcessingFinished)
      .def("GetNumberOfGrips", &G4Event::GetNumberOfGrips)
      .def("GetEventID", &G4Event::GetEventID)
      .def("AddPrimaryVertex", &G4Event::AddPrimaryVertex)
      .def("GetNumberOfPrimaryVertex", &G4Event::GetNumberOfPrimaryVertex)
      .def("GetPrimaryVertex", &G4Event::GetPrimaryVertex, py::arg("i") = 0,
           py::return_value_policy::reference_internal)

      .def("GetHCofThisEvent", &G4Event::GetHCofThisEvent, py::return_value_policy::reference_internal)
      .def("GetDCofThisEvent", &G4Event::GetDCofThisEvent, py::return_value_policy::reference_internal)
      .def("GetTrajectoryContainer", &G4Event::GetTrajectoryContainer, py::return_value_policy::reference_internal)

      .def("IsAborted", &G4Event::IsAborted)

      .def("SetUserInformation", &G4Event::SetUserInformation, py::keep_alive<1, 2>())
      .def("GetUserInformation", &G4Event::GetUserInformation, py::return_value_policy::reference_internal)
      .def("GetRandomNumberStatus", &G4Event::GetRandomNumberStatus)
      .def("GetRandomNumberStatusForProcessing", &G4Event::GetRandomNumberStatusForProcessing);
}

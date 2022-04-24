#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <G4TrackStack.hh>
#include <G4VTrajectory.hh>
#include <G4Track.hh>
#include <G4SmartTrackStack.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TrackStack(py::module &m)
{
   py::bind_vector<G4TrackStack>(m, "G4TrackStack")

      .def("__copy__", [](const G4TrackStack &self) { return new G4TrackStack(self); })
      .def("__deepcopy__", [](const G4TrackStack &self, py::dict) { return new G4TrackStack(self); })
      .def(py::init<>())
      .def(py::init<size_t>(), py::arg("n"))
      .def("GetMaxNTrack", &G4TrackStack::GetMaxNTrack)
      .def("GetNStick", &G4TrackStack::GetNStick)
      .def("GetNTrack", &G4TrackStack::GetNTrack)
      .def("GetSafetyValue1", &G4TrackStack::GetSafetyValue1)
      .def("GetSafetyValue2", &G4TrackStack::GetSafetyValue2)
      .def("PopFromStack", &G4TrackStack::PopFromStack)
      .def("PushToStack", &G4TrackStack::PushToStack, py::arg("aStackedTrack"))
      .def("SetSafetyValue2", &G4TrackStack::SetSafetyValue2, py::arg("x"))
      .def("TransferTo", py::overload_cast<G4TrackStack *>(&G4TrackStack::TransferTo), py::arg("aStack"))
      .def("TransferTo", py::overload_cast<G4SmartTrackStack *>(&G4TrackStack::TransferTo), py::arg("aStack"))
      .def("clearAndDestroy", &G4TrackStack::clearAndDestroy)
      .def("getTotalEnergy", &G4TrackStack::getTotalEnergy);
}

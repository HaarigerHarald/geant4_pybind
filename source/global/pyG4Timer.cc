#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Timer.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Timer(py::module &m)
{
   py::class_<G4Timer>(m, "G4Timer", "Timer")
      .def(py::init<>())

      .def("Start", &G4Timer::Start)
      .def("Stop", &G4Timer::Stop)
      .def("IsValid", &G4Timer::IsValid)
      .def("GetRealElapsed", &G4Timer::GetRealElapsed)
      .def("GetSystemElapsed", &G4Timer::GetSystemElapsed)
      .def("GetUserElapsed", &G4Timer::GetUserElapsed);
}

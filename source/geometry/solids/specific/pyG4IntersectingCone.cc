#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4IntersectingCone.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4IntersectingCone(py::module &m)
{
   py::class_<G4IntersectingCone>(m, "G4IntersectingCone")

      .def(py::init<const G4double *, const G4double *>(), py::arg("r"), py::arg("z"))
      .def("__copy__", [](const G4IntersectingCone &self) { return G4IntersectingCone(self); })
      .def("__deepcopy__", [](const G4IntersectingCone &self, py::dict) { return G4IntersectingCone(self); })

      .def("LineHitsCone", &G4IntersectingCone::LineHitsCone, py::arg("p"), py::arg("v"), py::arg("s1"), py::arg("s2"))

      .def("HitOn", &G4IntersectingCone::HitOn, py::arg("r"), py::arg("z"))
      .def("RLo", &G4IntersectingCone::RLo)
      .def("RHi", &G4IntersectingCone::RHi)
      .def("ZLo", &G4IntersectingCone::ZLo)
      .def("ZHi", &G4IntersectingCone::ZHi);
}

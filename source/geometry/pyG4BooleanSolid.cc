#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4BooleanSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4BooleanSolid(py::module &m)
{
   py::class_<G4BooleanSolid, G4VSolid, std::unique_ptr<G4BooleanSolid, py::nodelete>>(m, "G4BooleanSolid",
                                                                                       "boolean solid class")

      .def("GetCubVolStatistics", &G4BooleanSolid::GetCubVolStatistics)
      .def("GetCubVolEpsilon", &G4BooleanSolid::GetCubVolEpsilon)
      .def("SetCubVolStatistics", &G4BooleanSolid::SetCubVolStatistics)
      .def("SetCubVolEpsilon", &G4BooleanSolid::SetCubVolEpsilon)
      .def("GetAreaStatistics", &G4BooleanSolid::GetAreaStatistics)
      .def("GetAreaAccuracy", &G4BooleanSolid::GetAreaAccuracy)
      .def("SetAreaStatistics", &G4BooleanSolid::SetAreaStatistics)
      .def("SetAreaAccuracy", &G4BooleanSolid::SetAreaAccuracy)
      .def("GetPointOnSurface", &G4BooleanSolid::GetPointOnSurface);
}

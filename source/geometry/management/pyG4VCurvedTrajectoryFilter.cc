#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VCurvedTrajectoryFilter.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VCurvedTrajectoryFilter : public G4VCurvedTrajectoryFilter, public py::trampoline_self_life_support {
public:
   using G4VCurvedTrajectoryFilter::G4VCurvedTrajectoryFilter;

   void TakeIntermediatePoint(G4ThreeVector newPoint) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VCurvedTrajectoryFilter, TakeIntermediatePoint, newPoint);
   }
};

void export_G4VCurvedTrajectoryFilter(py::module &m)
{
   py::class_<G4VCurvedTrajectoryFilter, PyG4VCurvedTrajectoryFilter>(m, "G4VCurvedTrajectoryFilter")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VCurvedTrajectoryFilter &self) { return PyG4VCurvedTrajectoryFilter(self); })
      .def("__deepcopy__",
           [](const PyG4VCurvedTrajectoryFilter &self, py::dict) { return PyG4VCurvedTrajectoryFilter(self); })

      .def("CreateNewTrajectorySegment", &G4VCurvedTrajectoryFilter::CreateNewTrajectorySegment)
      .def("TakeIntermediatePoint", &G4VCurvedTrajectoryFilter::TakeIntermediatePoint, py::arg("newPoint"))
      .def("GimmeThePointsAndForgetThem", &G4VCurvedTrajectoryFilter::GimmeThePointsAndForgetThem,
           py::return_value_policy::reference);
}

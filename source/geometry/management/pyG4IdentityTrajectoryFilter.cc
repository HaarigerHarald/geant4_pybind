#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4IdentityTrajectoryFilter.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4IdentityTrajectoryFilter : public G4IdentityTrajectoryFilter, public py::trampoline_self_life_support {
public:
   using G4IdentityTrajectoryFilter::G4IdentityTrajectoryFilter;

   void TakeIntermediatePoint(G4ThreeVector newPoint) override
   {
      PYBIND11_OVERRIDE(void, G4IdentityTrajectoryFilter, TakeIntermediatePoint, newPoint);
   }
};

void export_G4IdentityTrajectoryFilter(py::module &m)
{
   py::class_<G4IdentityTrajectoryFilter, PyG4IdentityTrajectoryFilter, G4VCurvedTrajectoryFilter>(
      m, "G4IdentityTrajectoryFilter")

      .def(py::init<>())
      .def("TakeIntermediatePoint", &G4IdentityTrajectoryFilter::TakeIntermediatePoint, py::arg("newPoint"));
}

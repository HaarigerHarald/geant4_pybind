#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ChordFinder.hh>
#include <G4VFSALIntegrationStepper.hh>
#include <G4MagneticField.hh>
#include <G4CachedMagneticField.hh>
#include <G4HelixHeum.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ChordFinder(py::module &m)
{
   py::class_<G4ChordFinder>(m, "G4ChordFinder")

      .def(py::init<G4VIntegrationDriver *>(), py::arg("pIntegrationDriver"))
      .def(py::init<G4MagneticField *, G4double, G4MagIntegratorStepper *, G4int>(), py::arg("itsMagField"),
           py::arg("stepMinimum") = 0.01, py::arg("pItsStepper") = static_cast<G4MagIntegratorStepper *>(nullptr),
           py::arg("stepperDriverChoice") = 2)

      .def("AdvanceChordLimited", &G4ChordFinder::AdvanceChordLimited, py::arg("yCurrent"), py::arg("stepInitial"),
           py::arg("epsStep_Relative"), py::arg("latestSafetyOrigin"), py::arg("lasestSafetyRadius"))

      .def("ApproxCurvePointS", &G4ChordFinder::ApproxCurvePointS, py::arg("curveAPointVelocity"),
           py::arg("curveBPointVelocity"), py::arg("ApproxCurveV"), py::arg("currentEPoint"), py::arg("currentFPoint"),
           py::arg("PointG"), py::arg("first"), py::arg("epsStep"))

      .def("ApproxCurvePointV", &G4ChordFinder::ApproxCurvePointV, py::arg("curveAPointVelocity"),
           py::arg("curveBPointVelocity"), py::arg("currentEPoint"), py::arg("epsStep"))

      .def("InvParabolic", &G4ChordFinder::InvParabolic, py::arg("xa"), py::arg("ya"), py::arg("xb"), py::arg("yb"),
           py::arg("xc"), py::arg("yc"))

      .def("GetDeltaChord", &G4ChordFinder::GetDeltaChord)
      .def("SetDeltaChord", &G4ChordFinder::SetDeltaChord, py::arg("newval"))
      .def("SetIntegrationDriver", &G4ChordFinder::SetIntegrationDriver, py::arg("IntegrationDriver"))
      .def("GetIntegrationDriver", &G4ChordFinder::GetIntegrationDriver, py::return_value_policy::reference)
      .def("ResetStepEstimate", &G4ChordFinder::ResetStepEstimate)
      .def("SetVerbose", &G4ChordFinder::SetVerbose, py::arg("newvalue") = 1)
      .def("OnComputeStep", &G4ChordFinder::OnComputeStep)
      .def(
         "__str__",
         [](const G4ChordFinder &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}

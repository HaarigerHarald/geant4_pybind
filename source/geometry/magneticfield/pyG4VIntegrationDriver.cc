#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VIntegrationDriver.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VIntegrationDriver : public G4VIntegrationDriver, public py::trampoline_self_life_support {
public:
   using G4VIntegrationDriver::G4VIntegrationDriver;

   G4double AdvanceChordLimited(G4FieldTrack &track, G4double hstep, G4double eps, G4double chordDistance) override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VIntegrationDriver, AdvanceChordLimited, track, hstep, eps, chordDistance);
   }

   G4bool AccurateAdvance(G4FieldTrack &track, G4double hstep, G4double eps, G4double hinitial) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VIntegrationDriver, AccurateAdvance, track, hstep, eps, hinitial);
   }

   void SetEquationOfMotion(G4EquationOfMotion *equation) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VIntegrationDriver, SetEquationOfMotion, equation);
   }

   G4EquationOfMotion *GetEquationOfMotion() override
   {
      PYBIND11_OVERRIDE_PURE(G4EquationOfMotion *, G4VIntegrationDriver, GetEquationOfMotion, );
   }

   void SetVerboseLevel(G4int level) override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VIntegrationDriver, SetVerboseLevel, level);
   }

   G4int GetVerboseLevel() const override { PYBIND11_OVERRIDE_PURE(G4int, G4VIntegrationDriver, GetVerboseLevel, ); }

   void OnComputeStep() override { PYBIND11_OVERRIDE_PURE(void, G4VIntegrationDriver, OnComputeStep, ); }

   void OnStartTracking() override { PYBIND11_OVERRIDE_PURE(void, G4VIntegrationDriver, OnStartTracking, ); }

   void GetDerivatives(const G4FieldTrack &track, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VIntegrationDriver, GetDerivatives, track, dydx);
   }

   void GetDerivatives(const G4FieldTrack &track, G4double *dydx, G4double *field) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VIntegrationDriver, GetDerivatives, track, dydx, field);
   }

   const G4MagIntegratorStepper *GetStepper() const override
   {
      PYBIND11_OVERRIDE_PURE(const G4MagIntegratorStepper *, G4VIntegrationDriver, GetStepper, );
   }

   G4MagIntegratorStepper *GetStepper() override
   {
      PYBIND11_OVERRIDE_PURE(G4MagIntegratorStepper *, G4VIntegrationDriver, GetStepper, );
   }

   G4double ComputeNewStepSize(G4double errMaxNorm, G4double hstepCurrent) override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VIntegrationDriver, ComputeNewStepSize, errMaxNorm, hstepCurrent);
   }

   G4bool DoesReIntegrate() const override { PYBIND11_OVERRIDE_PURE(G4bool, G4VIntegrationDriver, DoesReIntegrate, ); }

   void StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VIntegrationDriver, StreamInfo, os);
   }

   void RenewStepperAndAdjust(G4MagIntegratorStepper *pItsStepper) override
   {
      PYBIND11_OVERRIDE(void, G4VIntegrationDriver, RenewStepperAndAdjust, pItsStepper);
   }

   G4bool QuickAdvance(G4FieldTrack &arg0, const G4double *arg1, G4double arg2, G4double &arg3, G4double &arg4) override
   {
      PYBIND11_OVERRIDE(G4bool, G4VIntegrationDriver, QuickAdvance, arg0, arg1, arg2, arg3, arg4);
   }
};

void export_G4VIntegrationDriver(py::module &m)
{
   py::class_<G4VIntegrationDriver, PyG4VIntegrationDriver>(m, "G4VIntegrationDriver")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VIntegrationDriver &self) { return PyG4VIntegrationDriver(self); })
      .def("__deepcopy__", [](const PyG4VIntegrationDriver &self, py::dict) { return PyG4VIntegrationDriver(self); })
      .def("AdvanceChordLimited", &G4VIntegrationDriver::AdvanceChordLimited, py::arg("track"), py::arg("hstep"),
           py::arg("eps"), py::arg("chordDistance"))

      .def("AccurateAdvance", &G4VIntegrationDriver::AccurateAdvance, py::arg("track"), py::arg("hstep"),
           py::arg("eps"), py::arg("hinitial") = 0)

      .def("SetEquationOfMotion", &G4VIntegrationDriver::SetEquationOfMotion, py::arg("equation"))
      .def("GetEquationOfMotion", &G4VIntegrationDriver::GetEquationOfMotion, py::return_value_policy::reference)
      .def("RenewStepperAndAdjust", &G4VIntegrationDriver::RenewStepperAndAdjust, py::arg("pItsStepper"))
      .def("SetVerboseLevel", &G4VIntegrationDriver::SetVerboseLevel, py::arg("level"))
      .def("GetVerboseLevel", &G4VIntegrationDriver::GetVerboseLevel)
      .def("OnComputeStep", &G4VIntegrationDriver::OnComputeStep)
      .def("OnStartTracking", &G4VIntegrationDriver::OnStartTracking)
      .def("QuickAdvance", &G4VIntegrationDriver::QuickAdvance)
      .def("GetDerivatives",
           py::overload_cast<const G4FieldTrack &, G4double *>(&G4VIntegrationDriver::GetDerivatives, py::const_),
           py::arg("track"), py::arg("dydx"))

      .def("GetDerivatives",
           py::overload_cast<const G4FieldTrack &, G4double *, G4double *>(&G4VIntegrationDriver::GetDerivatives,
                                                                           py::const_),
           py::arg("track"), py::arg("dydx"), py::arg("field"))

      .def("GetStepper", py::overload_cast<>(&G4VIntegrationDriver::GetStepper, py::const_),
           py::return_value_policy::reference)

      .def("GetStepper", py::overload_cast<>(&G4VIntegrationDriver::GetStepper), py::return_value_policy::reference)
      .def("ComputeNewStepSize", &G4VIntegrationDriver::ComputeNewStepSize, py::arg("errMaxNorm"),
           py::arg("hstepCurrent"))

      .def("DoesReIntegrate", &G4VIntegrationDriver::DoesReIntegrate)
      .def("StreamInfo", &G4VIntegrationDriver::StreamInfo, py::arg("os"))
      .def(
         "__str__",
         [](const G4VIntegrationDriver &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4BFieldIntegrationDriver.hh>
#include <G4MagneticField.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4BFieldIntegrationDriver : public G4BFieldIntegrationDriver, public py::trampoline_self_life_support {
public:
   using G4BFieldIntegrationDriver::G4BFieldIntegrationDriver;

   G4double AdvanceChordLimited(G4FieldTrack &track, G4double hstep, G4double eps, G4double chordDistance) override
   {
      PYBIND11_OVERRIDE(G4double, G4BFieldIntegrationDriver, AdvanceChordLimited, track, hstep, eps, chordDistance);
   }

   G4bool AccurateAdvance(G4FieldTrack &track, G4double hstep, G4double eps, G4double hinitial) override
   {
      PYBIND11_OVERRIDE(G4bool, G4BFieldIntegrationDriver, AccurateAdvance, track, hstep, eps, hinitial);
   }

   G4bool DoesReIntegrate() const override { PYBIND11_OVERRIDE(G4bool, G4BFieldIntegrationDriver, DoesReIntegrate, ); }

   void GetDerivatives(const G4FieldTrack &track, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE(void, G4BFieldIntegrationDriver, GetDerivatives, track, dydx);
   }

   void GetDerivatives(const G4FieldTrack &track, G4double *dydx, G4double *field) const override
   {
      PYBIND11_OVERRIDE(void, G4BFieldIntegrationDriver, GetDerivatives, track, dydx, field);
   }

   void SetEquationOfMotion(G4EquationOfMotion *equation) override
   {
      PYBIND11_OVERRIDE(void, G4BFieldIntegrationDriver, SetEquationOfMotion, equation);
   }

   G4EquationOfMotion *GetEquationOfMotion() override
   {
      PYBIND11_OVERRIDE(G4EquationOfMotion *, G4BFieldIntegrationDriver, GetEquationOfMotion, );
   }

   const G4MagIntegratorStepper *GetStepper() const override
   {
      PYBIND11_OVERRIDE(const G4MagIntegratorStepper *, G4BFieldIntegrationDriver, GetStepper, );
   }

   G4MagIntegratorStepper *GetStepper() override
   {
      PYBIND11_OVERRIDE(G4MagIntegratorStepper *, G4BFieldIntegrationDriver, GetStepper, );
   }

   G4double ComputeNewStepSize(G4double errMaxNorm, G4double hstepCurrent) override
   {
      PYBIND11_OVERRIDE(G4double, G4BFieldIntegrationDriver, ComputeNewStepSize, errMaxNorm, hstepCurrent);
   }

   void SetVerboseLevel(G4int level) override
   {
      PYBIND11_OVERRIDE(void, G4BFieldIntegrationDriver, SetVerboseLevel, level);
   }

   G4int GetVerboseLevel() const override { PYBIND11_OVERRIDE(G4int, G4BFieldIntegrationDriver, GetVerboseLevel, ); }

   void OnComputeStep() override { PYBIND11_OVERRIDE(void, G4BFieldIntegrationDriver, OnComputeStep, ); }

   void OnStartTracking() override { PYBIND11_OVERRIDE(void, G4BFieldIntegrationDriver, OnStartTracking, ); }

   void StreamInfo(std::ostream &os) const override
   {
      PYBIND11_OVERRIDE(void, G4BFieldIntegrationDriver, StreamInfo, os);
   }

   void RenewStepperAndAdjust(G4MagIntegratorStepper *pItsStepper) override
   {
      PYBIND11_OVERRIDE(void, G4BFieldIntegrationDriver, RenewStepperAndAdjust, pItsStepper);
   }

   G4bool QuickAdvance(G4FieldTrack &arg0, const G4double *arg1, G4double arg2, G4double &arg3, G4double &arg4) override
   {
      PYBIND11_OVERRIDE(G4bool, G4BFieldIntegrationDriver, QuickAdvance, arg0, arg1, arg2, arg3, arg4);
   }
};

void export_G4BFieldIntegrationDriver(py::module &m)
{
   py::class_<G4BFieldIntegrationDriver, PyG4BFieldIntegrationDriver, G4VIntegrationDriver>(m,
                                                                                            "G4BFieldIntegrationDriver")

      .def(py::init<std::unique_ptr<G4VIntegrationDriver>, std::unique_ptr<G4VIntegrationDriver>>(),
           py::arg("smallStepDriver"), py::arg("largeStepDriver"))

      .def("AdvanceChordLimited", &G4BFieldIntegrationDriver::AdvanceChordLimited, py::arg("track"), py::arg("hstep"),
           py::arg("eps"), py::arg("chordDistance"))

      .def("AccurateAdvance", &G4BFieldIntegrationDriver::AccurateAdvance, py::arg("track"), py::arg("hstep"),
           py::arg("eps"), py::arg("hinitial") = 0)

      .def("DoesReIntegrate", &G4BFieldIntegrationDriver::DoesReIntegrate)
      .def("GetDerivatives",
           py::overload_cast<const G4FieldTrack &, G4double *>(&G4BFieldIntegrationDriver::GetDerivatives, py::const_),
           py::arg("track"), py::arg("dydx"))

      .def("GetDerivatives",
           py::overload_cast<const G4FieldTrack &, G4double *, G4double *>(&G4BFieldIntegrationDriver::GetDerivatives,
                                                                           py::const_),
           py::arg("track"), py::arg("dydx"), py::arg("field"))

      .def("SetEquationOfMotion", &G4BFieldIntegrationDriver::SetEquationOfMotion, py::arg("equation"))
      .def("GetEquationOfMotion", &G4BFieldIntegrationDriver::GetEquationOfMotion, py::return_value_policy::reference)
      .def("GetStepper", py::overload_cast<>(&G4BFieldIntegrationDriver::GetStepper, py::const_),
           py::return_value_policy::reference)

      .def("GetStepper", py::overload_cast<>(&G4BFieldIntegrationDriver::GetStepper),
           py::return_value_policy::reference)

      .def("ComputeNewStepSize", &G4BFieldIntegrationDriver::ComputeNewStepSize, py::arg("errMaxNorm"),
           py::arg("hstepCurrent"))

      .def("SetVerboseLevel", &G4BFieldIntegrationDriver::SetVerboseLevel, py::arg("level"))
      .def("GetVerboseLevel", &G4BFieldIntegrationDriver::GetVerboseLevel)
      .def("OnComputeStep", &G4BFieldIntegrationDriver::OnComputeStep)
      .def("OnStartTracking", &G4BFieldIntegrationDriver::OnStartTracking)
      .def("StreamInfo", &G4BFieldIntegrationDriver::StreamInfo, py::arg("os"))
      .def("PrintStatistics", &G4BFieldIntegrationDriver::PrintStatistics);
}

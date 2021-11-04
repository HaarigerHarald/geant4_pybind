#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4OldMagIntDriver.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4OldMagIntDriver : public G4OldMagIntDriver, public py::trampoline_self_life_support {
public:
   using G4OldMagIntDriver::G4OldMagIntDriver;

   G4double AdvanceChordLimited(G4FieldTrack &track, G4double stepMax, G4double epsStep,
                                G4double chordDistance) override
   {
      PYBIND11_OVERRIDE(G4double, G4OldMagIntDriver, AdvanceChordLimited, track, stepMax, epsStep, chordDistance);
   }

   void OnStartTracking() override { PYBIND11_OVERRIDE(void, G4OldMagIntDriver, OnStartTracking, ); }

   void OnComputeStep() override { PYBIND11_OVERRIDE(void, G4OldMagIntDriver, OnComputeStep, ); }

   G4bool DoesReIntegrate() const override { PYBIND11_OVERRIDE(G4bool, G4OldMagIntDriver, DoesReIntegrate, ); }

   G4bool AccurateAdvance(G4FieldTrack &y_current, G4double hstep, G4double eps, G4double hinitial) override
   {
      PYBIND11_OVERRIDE(G4bool, G4OldMagIntDriver, AccurateAdvance, y_current, hstep, eps, hinitial);
   }

   G4bool QuickAdvance(G4FieldTrack &y_val, const G4double *dydx, G4double hstep, G4double &dchord_step,
                       G4double &dyerr) override
   {
      PYBIND11_OVERRIDE(G4bool, G4OldMagIntDriver, QuickAdvance, y_val, dydx, hstep, dchord_step, dyerr);
   }

   void GetDerivatives(const G4FieldTrack &y_curr, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE(void, G4OldMagIntDriver, GetDerivatives, y_curr, dydx);
   }

   void GetDerivatives(const G4FieldTrack &track, G4double *dydx, G4double *field) const override
   {
      PYBIND11_OVERRIDE(void, G4OldMagIntDriver, GetDerivatives, track, dydx, field);
   }

   G4EquationOfMotion *GetEquationOfMotion() override
   {
      PYBIND11_OVERRIDE(G4EquationOfMotion *, G4OldMagIntDriver, GetEquationOfMotion, );
   }

   void SetEquationOfMotion(G4EquationOfMotion *equation) override
   {
      PYBIND11_OVERRIDE(void, G4OldMagIntDriver, SetEquationOfMotion, equation);
   }

   void RenewStepperAndAdjust(G4MagIntegratorStepper *pItsStepper) override
   {
      PYBIND11_OVERRIDE(void, G4OldMagIntDriver, RenewStepperAndAdjust, pItsStepper);
   }

   const G4MagIntegratorStepper *GetStepper() const override
   {
      PYBIND11_OVERRIDE(const G4MagIntegratorStepper *, G4OldMagIntDriver, GetStepper, );
   }

   G4MagIntegratorStepper *GetStepper() override
   {
      PYBIND11_OVERRIDE(G4MagIntegratorStepper *, G4OldMagIntDriver, GetStepper, );
   }

   G4double ComputeNewStepSize(G4double errMaxNorm, G4double hstepCurrent) override
   {
      PYBIND11_OVERRIDE(G4double, G4OldMagIntDriver, ComputeNewStepSize, errMaxNorm, hstepCurrent);
   }

   void StreamInfo(std::ostream &os) const override { PYBIND11_OVERRIDE(void, G4OldMagIntDriver, StreamInfo, os); }

   void SetVerboseLevel(G4int newLevel) override
   {
      PYBIND11_OVERRIDE(void, G4OldMagIntDriver, SetVerboseLevel, newLevel);
   }

   G4int GetVerboseLevel() const override { PYBIND11_OVERRIDE(G4int, G4OldMagIntDriver, GetVerboseLevel, ); }
};

void export_G4OldMagIntDriver(py::module &m)
{
   py::class_<G4OldMagIntDriver, PyG4OldMagIntDriver, G4VIntegrationDriver>(m, "G4OldMagIntDriver")

      .def(py::init<G4double, G4MagIntegratorStepper *, G4int, G4int>(), py::arg("hminimum"), py::arg("pItsStepper"),
           py::arg("numberOfComponents") = 6, py::arg("statisticsVerbosity") = 0)

      .def("AdvanceChordLimited", &G4OldMagIntDriver::AdvanceChordLimited, py::arg("track"), py::arg("stepMax"),
           py::arg("epsStep"), py::arg("chordDistance"))

      .def("OnStartTracking", &G4OldMagIntDriver::OnStartTracking)
      .def("OnComputeStep", &G4OldMagIntDriver::OnComputeStep)
      .def("DoesReIntegrate", &G4OldMagIntDriver::DoesReIntegrate)
      .def("AccurateAdvance", &G4OldMagIntDriver::AccurateAdvance, py::arg("y_current"), py::arg("hstep"),
           py::arg("eps"), py::arg("hinitial") = 0.)

      .def("QuickAdvance",
           py::overload_cast<G4FieldTrack &, const G4double *, G4double, G4double &, G4double &>(
              &G4OldMagIntDriver::QuickAdvance),
           py::arg("y_val"), py::arg("dydx"), py::arg("hstep"), py::arg("dchord_step"), py::arg("dyerr"))

      .def("QuickAdvance",
           py::overload_cast<G4FieldTrack &, const G4double *, G4double, G4double &, G4double &, G4double &>(
              &G4OldMagIntDriver::QuickAdvance),
           py::arg("y_posvel"), py::arg("dydx"), py::arg("hstep"), py::arg("dchord_step"), py::arg("dyerr_pos_sq"),
           py::arg("dyerr_mom_rel_sq"))

      .def("GetHmin", &G4OldMagIntDriver::GetHmin)
      .def("Hmin", &G4OldMagIntDriver::Hmin)
      .def("GetSafety", &G4OldMagIntDriver::GetSafety)
      .def("GetPshrnk", &G4OldMagIntDriver::GetPshrnk)
      .def("GetPgrow", &G4OldMagIntDriver::GetPgrow)
      .def("GetErrcon", &G4OldMagIntDriver::GetErrcon)
      .def("GetDerivatives",
           py::overload_cast<const G4FieldTrack &, G4double *>(&G4OldMagIntDriver::GetDerivatives, py::const_),
           py::arg("y_curr"), py::arg("dydx"))

      .def("GetDerivatives",
           py::overload_cast<const G4FieldTrack &, G4double *, G4double *>(&G4OldMagIntDriver::GetDerivatives,
                                                                           py::const_),
           py::arg("track"), py::arg("dydx"), py::arg("field"))

      .def("GetEquationOfMotion", &G4OldMagIntDriver::GetEquationOfMotion, py::return_value_policy::reference)
      .def("SetEquationOfMotion", &G4OldMagIntDriver::SetEquationOfMotion, py::arg("equation"))
      .def("RenewStepperAndAdjust", &G4OldMagIntDriver::RenewStepperAndAdjust, py::arg("pItsStepper"))
      .def("ReSetParameters", &G4OldMagIntDriver::ReSetParameters, py::arg("new_safety") = 0.9)
      .def("SetSafety", &G4OldMagIntDriver::SetSafety, py::arg("valS"))
      //.def("SetPshrnk", &G4OldMagIntDriver::SetPshrnk, py::arg("valPs"))
      .def("SetPgrow", &G4OldMagIntDriver::SetPgrow, py::arg("valPg"))
      .def("SetErrcon", &G4OldMagIntDriver::SetErrcon, py::arg("valEc"))
      .def("ComputeAndSetErrcon", &G4OldMagIntDriver::ComputeAndSetErrcon)
      .def("GetStepper", py::overload_cast<>(&G4OldMagIntDriver::GetStepper, py::const_),
           py::return_value_policy::reference)

      .def("GetStepper", py::overload_cast<>(&G4OldMagIntDriver::GetStepper), py::return_value_policy::reference)
      .def("OneGoodStep", &G4OldMagIntDriver::OneGoodStep, py::arg("ystart"), py::arg("dydx"), py::arg("x"),
           py::arg("htry"), py::arg("eps"), py::arg("hdid"), py::arg("hnext"))

      .def("ComputeNewStepSize", &G4OldMagIntDriver::ComputeNewStepSize, py::arg("errMaxNorm"), py::arg("hstepCurrent"))
      .def("StreamInfo", &G4OldMagIntDriver::StreamInfo, py::arg("os"))
      .def("ComputeNewStepSize_WithinLimits", &G4OldMagIntDriver::ComputeNewStepSize_WithinLimits,
           py::arg("errMaxNorm"), py::arg("hstepCurrent"))

      .def("GetMaxNoSteps", &G4OldMagIntDriver::GetMaxNoSteps)
      .def("SetMaxNoSteps", &G4OldMagIntDriver::SetMaxNoSteps, py::arg("val"))
      .def("SetHmin", &G4OldMagIntDriver::SetHmin, py::arg("newval"))
      .def("SetVerboseLevel", &G4OldMagIntDriver::SetVerboseLevel, py::arg("newLevel"))
      .def("GetVerboseLevel", &G4OldMagIntDriver::GetVerboseLevel)
      .def("GetSmallestFraction", &G4OldMagIntDriver::GetSmallestFraction)
      .def("SetSmallestFraction", &G4OldMagIntDriver::SetSmallestFraction, py::arg("val"));
}

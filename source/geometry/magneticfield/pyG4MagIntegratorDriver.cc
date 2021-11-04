#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4MagIntegratorDriver.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4MagInt_Driver : public G4MagInt_Driver, public py::trampoline_self_life_support {
public:
   using G4MagInt_Driver::G4MagInt_Driver;

   G4double AdvanceChordLimited(G4FieldTrack &track, G4double stepMax, G4double epsStep,
                                G4double chordDistance) override
   {
      PYBIND11_OVERRIDE(G4double, G4MagInt_Driver, AdvanceChordLimited, track, stepMax, epsStep, chordDistance);
   }

   void OnStartTracking() override { PYBIND11_OVERRIDE(void, G4MagInt_Driver, OnStartTracking, ); }

   void OnComputeStep() override { PYBIND11_OVERRIDE(void, G4MagInt_Driver, OnComputeStep, ); }

   G4bool DoesReIntegrate() const override { PYBIND11_OVERRIDE(G4bool, G4MagInt_Driver, DoesReIntegrate, ); }

   G4bool AccurateAdvance(G4FieldTrack &y_current, G4double hstep, G4double eps, G4double hinitial) override
   {
      PYBIND11_OVERRIDE(G4bool, G4MagInt_Driver, AccurateAdvance, y_current, hstep, eps, hinitial);
   }

   G4bool QuickAdvance(G4FieldTrack &y_val, const G4double *dydx, G4double hstep, G4double &dchord_step,
                       G4double &dyerr) override
   {
      PYBIND11_OVERRIDE(G4bool, G4MagInt_Driver, QuickAdvance, y_val, dydx, hstep, dchord_step, dyerr);
   }

   void StreamInfo(std::ostream &os) const override { PYBIND11_OVERRIDE(void, G4MagInt_Driver, StreamInfo, os); }

   void GetDerivatives(const G4FieldTrack &y_curr, G4double *dydx) const override
   {
      PYBIND11_OVERRIDE(void, G4MagInt_Driver, GetDerivatives, y_curr, dydx);
   }

   void GetDerivatives(const G4FieldTrack &track, G4double *dydx, G4double *field) const override
   {
      PYBIND11_OVERRIDE(void, G4MagInt_Driver, GetDerivatives, track, dydx, field);
   }

   G4EquationOfMotion *GetEquationOfMotion() override
   {
      PYBIND11_OVERRIDE(G4EquationOfMotion *, G4MagInt_Driver, GetEquationOfMotion, );
   }

   void SetEquationOfMotion(G4EquationOfMotion *equation) override
   {
      PYBIND11_OVERRIDE(void, G4MagInt_Driver, SetEquationOfMotion, equation);
   }

   void RenewStepperAndAdjust(G4MagIntegratorStepper *pItsStepper) override
   {
      PYBIND11_OVERRIDE(void, G4MagInt_Driver, RenewStepperAndAdjust, pItsStepper);
   }

   const G4MagIntegratorStepper *GetStepper() const override
   {
      PYBIND11_OVERRIDE(const G4MagIntegratorStepper *, G4MagInt_Driver, GetStepper, );
   }

   G4MagIntegratorStepper *GetStepper() override
   {
      PYBIND11_OVERRIDE(G4MagIntegratorStepper *, G4MagInt_Driver, GetStepper, );
   }

   G4double ComputeNewStepSize(G4double errMaxNorm, G4double hstepCurrent) override
   {
      PYBIND11_OVERRIDE(G4double, G4MagInt_Driver, ComputeNewStepSize, errMaxNorm, hstepCurrent);
   }

   void SetVerboseLevel(G4int newLevel) override
   {
      PYBIND11_OVERRIDE(void, G4MagInt_Driver, SetVerboseLevel, newLevel);
   }

   G4int GetVerboseLevel() const override { PYBIND11_OVERRIDE(G4int, G4MagInt_Driver, GetVerboseLevel, ); }
};

void export_G4MagIntegratorDriver(py::module &m)
{
   py::class_<G4MagInt_Driver, PyG4MagInt_Driver, G4VIntegrationDriver>(m, "G4MagInt_Driver")

      .def(py::init<G4double, G4MagIntegratorStepper *, G4int, G4int>(), py::arg("hminimum"), py::arg("pItsStepper"),
           py::arg("numberOfComponents") = 6, py::arg("statisticsVerbosity") = 0)

      .def("AdvanceChordLimited", &G4MagInt_Driver::AdvanceChordLimited, py::arg("track"), py::arg("stepMax"),
           py::arg("epsStep"), py::arg("chordDistance"))

      .def("OnStartTracking", &G4MagInt_Driver::OnStartTracking)
      .def("OnComputeStep", &G4MagInt_Driver::OnComputeStep)
      .def("DoesReIntegrate", &G4MagInt_Driver::DoesReIntegrate)
      .def("AccurateAdvance", &G4MagInt_Driver::AccurateAdvance, py::arg("y_current"), py::arg("hstep"), py::arg("eps"),
           py::arg("hinitial") = 0.)

      .def("QuickAdvance",
           py::overload_cast<G4FieldTrack &, const G4double *, G4double, G4double &, G4double &>(
              &G4MagInt_Driver::QuickAdvance),
           py::arg("y_val"), py::arg("dydx"), py::arg("hstep"), py::arg("dchord_step"), py::arg("dyerr"))

      .def("StreamInfo", &G4MagInt_Driver::StreamInfo, py::arg("os"))
      .def("QuickAdvance",
           py::overload_cast<G4FieldTrack &, const G4double *, G4double, G4double &, G4double &, G4double &>(
              &G4MagInt_Driver::QuickAdvance),
           py::arg("y_posvel"), py::arg("dydx"), py::arg("hstep"), py::arg("dchord_step"), py::arg("dyerr_pos_sq"),
           py::arg("dyerr_mom_rel_sq"))

      .def("GetHmin", &G4MagInt_Driver::GetHmin)
      .def("Hmin", &G4MagInt_Driver::Hmin)
      .def("GetSafety", &G4MagInt_Driver::GetSafety)
      .def("GetPshrnk", &G4MagInt_Driver::GetPshrnk)
      .def("GetPgrow", &G4MagInt_Driver::GetPgrow)
      .def("GetErrcon", &G4MagInt_Driver::GetErrcon)
      .def("GetDerivatives",
           py::overload_cast<const G4FieldTrack &, G4double *>(&G4MagInt_Driver::GetDerivatives, py::const_),
           py::arg("y_curr"), py::arg("dydx"))

      .def(
         "GetDerivatives",
         py::overload_cast<const G4FieldTrack &, G4double *, G4double *>(&G4MagInt_Driver::GetDerivatives, py::const_),
         py::arg("track"), py::arg("dydx"), py::arg("field"))

      .def("GetEquationOfMotion", &G4MagInt_Driver::GetEquationOfMotion, py::return_value_policy::reference)
      .def("SetEquationOfMotion", &G4MagInt_Driver::SetEquationOfMotion, py::arg("equation"))
      .def("RenewStepperAndAdjust", &G4MagInt_Driver::RenewStepperAndAdjust, py::arg("pItsStepper"))
      .def("ReSetParameters", &G4MagInt_Driver::ReSetParameters, py::arg("new_safety") = 0.9)
      .def("SetSafety", &G4MagInt_Driver::SetSafety, py::arg("valS"))
      //.def("SetPshrnk", &G4MagInt_Driver::SetPshrnk, py::arg("valPs"))
      .def("SetPgrow", &G4MagInt_Driver::SetPgrow, py::arg("valPg"))
      .def("SetErrcon", &G4MagInt_Driver::SetErrcon, py::arg("valEc"))
      .def("ComputeAndSetErrcon", &G4MagInt_Driver::ComputeAndSetErrcon)
      .def("GetStepper", py::overload_cast<>(&G4MagInt_Driver::GetStepper, py::const_),
           py::return_value_policy::reference)

      .def("GetStepper", py::overload_cast<>(&G4MagInt_Driver::GetStepper), py::return_value_policy::reference)
      .def("OneGoodStep", &G4MagInt_Driver::OneGoodStep, py::arg("ystart"), py::arg("dydx"), py::arg("x"),
           py::arg("htry"), py::arg("eps"), py::arg("hdid"), py::arg("hnext"))

      .def("ComputeNewStepSize", &G4MagInt_Driver::ComputeNewStepSize, py::arg("errMaxNorm"), py::arg("hstepCurrent"))

      .def("ComputeNewStepSize_WithoutReductionLimit", &G4MagInt_Driver::ComputeNewStepSize_WithoutReductionLimit,
           py::arg("errMaxNorm"), py::arg("hstepCurrent"))

      .def("ComputeNewStepSize_WithinLimits", &G4MagInt_Driver::ComputeNewStepSize_WithinLimits, py::arg("errMaxNorm"),
           py::arg("hstepCurrent"))

      .def("GetMaxNoSteps", &G4MagInt_Driver::GetMaxNoSteps)
      .def("SetMaxNoSteps", &G4MagInt_Driver::SetMaxNoSteps, py::arg("val"))
      .def("SetHmin", &G4MagInt_Driver::SetHmin, py::arg("newval"))
      .def("SetVerboseLevel", &G4MagInt_Driver::SetVerboseLevel, py::arg("newLevel"))
      .def("GetVerboseLevel", &G4MagInt_Driver::GetVerboseLevel)
      .def("GetSmallestFraction", &G4MagInt_Driver::GetSmallestFraction)
      .def("SetSmallestFraction", &G4MagInt_Driver::SetSmallestFraction, py::arg("val"));
}

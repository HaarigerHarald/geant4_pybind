#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VDivisionParameterisation.hh>
#include <G4Material.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VTouchable.hh>
#include <G4VSolid.hh>
#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4Trd.hh>
#include <G4Trap.hh>
#include <G4Cons.hh>
#include <G4Sphere.hh>
#include <G4Orb.hh>
#include <G4Ellipsoid.hh>
#include <G4Torus.hh>
#include <G4Para.hh>
#include <G4Polycone.hh>
#include <G4Polyhedra.hh>
#include <G4Hype.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VDivisionParameterisation : public G4VDivisionParameterisation, public py::trampoline_self_life_support {
public:
   using G4VDivisionParameterisation::G4VDivisionParameterisation;

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VDivisionParameterisation, ComputeTransformation, copyNo, physVol);
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VDivisionParameterisation, GetMaxParameter, );
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VDivisionParameterisation, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4VDivisionParameterisation, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4VDivisionParameterisation, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4VDivisionParameterisation, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4VDivisionParameterisation, GetMaterialScanner, );
   }

   void ComputeDimensions(G4Box &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Tubs &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trd &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trap &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Cons &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Sphere &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Orb &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Ellipsoid &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Torus &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Para &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polycone &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polyhedra &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Hype &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VDivisionParameterisation, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VDivisionParameterisation::ComputeDimensions(arg0, arg1, arg2);
   }
};

void export_G4VDivisionParameterisation(py::module &m)
{
   py::enum_<DivisionType>(m, "DivisionType")
      .value("DivNDIVandWIDTH", DivNDIVandWIDTH)
      .value("DivNDIV", DivNDIV)
      .value("DivWIDTH", DivWIDTH)
      .export_values();

   py::class_<G4VDivisionParameterisation, PyG4VDivisionParameterisation, G4VPVParameterisation>(
      m, "G4VDivisionParameterisation")

      .def("__copy__", [](const PyG4VDivisionParameterisation &self) { return PyG4VDivisionParameterisation(self); })

      .def("__deepcopy__",
           [](const PyG4VDivisionParameterisation &self, py::dict) { return PyG4VDivisionParameterisation(self); })

      .def(py::init<EAxis, G4int, G4double, G4double, DivisionType, G4VSolid *>(), py::arg("axis"), py::arg("nDiv"),
           py::arg("width"), py::arg("offset"), py::arg("divType"),
           py::arg("motherSolid") = static_cast<G4VSolid *>(nullptr))

      .def("ComputeSolid", &G4VDivisionParameterisation::ComputeSolid, py::return_value_policy::reference)

      .def("ComputeTransformation", &G4VDivisionParameterisation::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("GetAxis", &G4VDivisionParameterisation::GetAxis)
      .def("GetHalfGap", &G4VDivisionParameterisation::GetHalfGap)
      .def("GetMotherSolid", &G4VDivisionParameterisation::GetMotherSolid, py::return_value_policy::reference)

      .def("GetNoDiv", &G4VDivisionParameterisation::GetNoDiv)
      .def("GetOffset", &G4VDivisionParameterisation::GetOffset)
      .def("GetType", &G4VDivisionParameterisation::GetType)
      .def("GetWidth", &G4VDivisionParameterisation::GetWidth)
      .def("SetHalfGap", &G4VDivisionParameterisation::SetHalfGap, py::arg("hg"))
      .def("SetType", &G4VDivisionParameterisation::SetType, py::arg("type"))
      .def("VolumeFirstCopyNo", &G4VDivisionParameterisation::VolumeFirstCopyNo);
}

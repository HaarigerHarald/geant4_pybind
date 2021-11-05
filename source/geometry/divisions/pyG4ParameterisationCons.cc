#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParameterisationCons.hh>
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

class PyG4VParameterisationCons : public G4VParameterisationCons, public py::trampoline_self_life_support {
public:
   using G4VParameterisationCons::G4VParameterisationCons;

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VParameterisationCons, ComputeTransformation, copyNo, physVol);
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VParameterisationCons, GetMaxParameter, );
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VParameterisationCons, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4VParameterisationCons, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4VParameterisationCons, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4VParameterisationCons, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4VParameterisationCons, GetMaterialScanner, );
   }

   void ComputeDimensions(G4Box &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Tubs &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trd &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trap &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Cons &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Sphere &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Orb &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Ellipsoid &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Torus &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Para &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polycone &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polyhedra &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Hype &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationCons, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationCons::ComputeDimensions(arg0, arg1, arg2);
   }
};

class PyG4ParameterisationConsRho : public G4ParameterisationConsRho, public py::trampoline_self_life_support {
public:
   using G4ParameterisationConsRho::G4ParameterisationConsRho;

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationConsRho, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationConsRho, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Cons &tubs, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationConsRho, "ComputeDimensions", std::addressof(tubs), copyNo,
                             physVol);
      G4ParameterisationConsRho::ComputeDimensions(tubs, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationConsRho, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationConsRho, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationConsRho, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationConsRho, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationConsRho, GetMaterialScanner, );
   }
};

class PyG4ParameterisationConsPhi : public G4ParameterisationConsPhi, public py::trampoline_self_life_support {
public:
   using G4ParameterisationConsPhi::G4ParameterisationConsPhi;

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationConsPhi, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationConsPhi, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Cons &tubs, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationConsPhi, "ComputeDimensions", std::addressof(tubs), copyNo,
                             physVol);
      G4ParameterisationConsPhi::ComputeDimensions(tubs, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationConsPhi, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationConsPhi, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationConsPhi, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationConsPhi, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationConsPhi, GetMaterialScanner, );
   }
};

class PyG4ParameterisationConsZ : public G4ParameterisationConsZ, public py::trampoline_self_life_support {
public:
   using G4ParameterisationConsZ::G4ParameterisationConsZ;

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationConsZ, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationConsZ, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Cons &tubs, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationConsZ, "ComputeDimensions", std::addressof(tubs), copyNo, physVol);
      G4ParameterisationConsZ::ComputeDimensions(tubs, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationConsZ, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationConsZ, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationConsZ, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationConsZ, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationConsZ, GetMaterialScanner, );
   }
};

void export_G4ParameterisationCons(py::module &m)
{
   py::class_<G4VParameterisationCons, PyG4VParameterisationCons, G4VDivisionParameterisation>(
      m, "G4VParameterisationCons")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4VParameterisationCons &self) { return PyG4VParameterisationCons(self); })

      .def("__deepcopy__",
           [](const PyG4VParameterisationCons &self, py::dict) { return PyG4VParameterisationCons(self); });

   py::class_<G4ParameterisationConsRho, PyG4ParameterisationConsRho, G4VParameterisationCons>(
      m, "G4ParameterisationConsRho")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationConsRho &self) { return PyG4ParameterisationConsRho(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationConsRho &self, py::dict) { return PyG4ParameterisationConsRho(self); })

      .def("GetMaxParameter", &G4ParameterisationConsRho::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationConsRho::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Cons &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationConsRho::ComputeDimensions, py::const_),
           py::arg("tubs"), py::arg("copyNo"), py::arg("physVol"));

   py::class_<G4ParameterisationConsPhi, PyG4ParameterisationConsPhi, G4VParameterisationCons>(
      m, "G4ParameterisationConsPhi")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationConsPhi &self) { return PyG4ParameterisationConsPhi(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationConsPhi &self, py::dict) { return PyG4ParameterisationConsPhi(self); })

      .def("GetMaxParameter", &G4ParameterisationConsPhi::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationConsPhi::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Cons &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationConsPhi::ComputeDimensions, py::const_),
           py::arg("tubs"), py::arg("copyNo"), py::arg("physVol"));

   py::class_<G4ParameterisationConsZ, PyG4ParameterisationConsZ, G4VParameterisationCons>(m, "G4ParameterisationConsZ")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationConsZ &self) { return PyG4ParameterisationConsZ(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationConsZ &self, py::dict) { return PyG4ParameterisationConsZ(self); })

      .def("GetMaxParameter", &G4ParameterisationConsZ::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationConsZ::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Cons &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationConsZ::ComputeDimensions, py::const_),
           py::arg("tubs"), py::arg("copyNo"), py::arg("physVol"));
}

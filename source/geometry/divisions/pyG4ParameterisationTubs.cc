#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParameterisationTubs.hh>
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

class PyG4VParameterisationTubs : public G4VParameterisationTubs, public py::trampoline_self_life_support {
public:
   using G4VParameterisationTubs::G4VParameterisationTubs;

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VParameterisationTubs, ComputeTransformation, copyNo, physVol);
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VParameterisationTubs, GetMaxParameter, );
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VParameterisationTubs, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4VParameterisationTubs, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4VParameterisationTubs, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4VParameterisationTubs, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4VParameterisationTubs, GetMaterialScanner, );
   }

   void ComputeDimensions(G4Box &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Tubs &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trd &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trap &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Cons &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Sphere &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Orb &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Ellipsoid &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Torus &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Para &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polycone &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polyhedra &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Hype &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTubs, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTubs::ComputeDimensions(arg0, arg1, arg2);
   }
};

class PyG4ParameterisationTubsRho : public G4ParameterisationTubsRho, public py::trampoline_self_life_support {
public:
   using G4ParameterisationTubsRho::G4ParameterisationTubsRho;

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationTubsRho, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationTubsRho, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Tubs &tubs, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationTubsRho, "ComputeDimensions", std::addressof(tubs), copyNo,
                             physVol);
      G4ParameterisationTubsRho::ComputeDimensions(tubs, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationTubsRho, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationTubsRho, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationTubsRho, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationTubsRho, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationTubsRho, GetMaterialScanner, );
   }
};

class PyG4ParameterisationTubsPhi : public G4ParameterisationTubsPhi, public py::trampoline_self_life_support {
public:
   using G4ParameterisationTubsPhi::G4ParameterisationTubsPhi;

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationTubsPhi, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationTubsPhi, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Tubs &tubs, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationTubsPhi, "ComputeDimensions", std::addressof(tubs), copyNo,
                             physVol);
      G4ParameterisationTubsPhi::ComputeDimensions(tubs, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationTubsPhi, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationTubsPhi, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationTubsPhi, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationTubsPhi, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationTubsPhi, GetMaterialScanner, );
   }
};

class PyG4ParameterisationTubsZ : public G4ParameterisationTubsZ, public py::trampoline_self_life_support {
public:
   using G4ParameterisationTubsZ::G4ParameterisationTubsZ;

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationTubsZ, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationTubsZ, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Tubs &tubs, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationTubsZ, "ComputeDimensions", std::addressof(tubs), copyNo, physVol);
      G4ParameterisationTubsZ::ComputeDimensions(tubs, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationTubsZ, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationTubsZ, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationTubsZ, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationTubsZ, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationTubsZ, GetMaterialScanner, );
   }
};

void export_G4ParameterisationTubs(py::module &m)
{
   py::class_<G4VParameterisationTubs, PyG4VParameterisationTubs, G4VDivisionParameterisation>(
      m, "G4VParameterisationTubs")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4VParameterisationTubs &self) { return PyG4VParameterisationTubs(self); })

      .def("__deepcopy__",
           [](const PyG4VParameterisationTubs &self, py::dict) { return PyG4VParameterisationTubs(self); });

   py::class_<G4ParameterisationTubsRho, PyG4ParameterisationTubsRho, G4VParameterisationTubs>(
      m, "G4ParameterisationTubsRho")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationTubsRho &self) { return PyG4ParameterisationTubsRho(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationTubsRho &self, py::dict) { return PyG4ParameterisationTubsRho(self); })

      .def("GetMaxParameter", &G4ParameterisationTubsRho::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationTubsRho::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Tubs &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationTubsRho::ComputeDimensions, py::const_),
           py::arg("tubs"), py::arg("copyNo"), py::arg("physVol"));

   py::class_<G4ParameterisationTubsPhi, PyG4ParameterisationTubsPhi, G4VParameterisationTubs>(
      m, "G4ParameterisationTubsPhi")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationTubsPhi &self) { return PyG4ParameterisationTubsPhi(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationTubsPhi &self, py::dict) { return PyG4ParameterisationTubsPhi(self); })

      .def("GetMaxParameter", &G4ParameterisationTubsPhi::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationTubsPhi::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Tubs &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationTubsPhi::ComputeDimensions, py::const_),
           py::arg("tubs"), py::arg("copyNo"), py::arg("physVol"));

   py::class_<G4ParameterisationTubsZ, PyG4ParameterisationTubsZ, G4VParameterisationTubs>(m, "G4ParameterisationTubsZ")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationTubsZ &self) { return PyG4ParameterisationTubsZ(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationTubsZ &self, py::dict) { return PyG4ParameterisationTubsZ(self); })

      .def("GetMaxParameter", &G4ParameterisationTubsZ::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationTubsZ::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Tubs &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationTubsZ::ComputeDimensions, py::const_),
           py::arg("tubs"), py::arg("copyNo"), py::arg("physVol"));
}

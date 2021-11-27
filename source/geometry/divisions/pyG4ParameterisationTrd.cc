#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParameterisationTrd.hh>
#include <G4Material.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VTouchable.hh>
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
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VParameterisationTrd : public G4VParameterisationTrd, public py::trampoline_self_life_support {
public:
   using G4VParameterisationTrd::G4VParameterisationTrd;

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VParameterisationTrd, ComputeTransformation, copyNo, physVol);
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VParameterisationTrd, GetMaxParameter, );
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VParameterisationTrd, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4VParameterisationTrd, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4VParameterisationTrd, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4VParameterisationTrd, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4VParameterisationTrd, GetMaterialScanner, );
   }

   void ComputeDimensions(G4Box &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Tubs &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trd &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trap &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Cons &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Sphere &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Orb &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Ellipsoid &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Torus &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Para &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polycone &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polyhedra &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Hype &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationTrd, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationTrd::ComputeDimensions(arg0, arg1, arg2);
   }
};

class PyG4ParameterisationTrdX : public G4ParameterisationTrdX, public py::trampoline_self_life_support {
public:
   using G4ParameterisationTrdX::G4ParameterisationTrdX;

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationTrdX, CheckParametersValidity, );
   }

   G4double GetMaxParameter() const override { PYBIND11_OVERRIDE(G4double, G4ParameterisationTrdX, GetMaxParameter, ); }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationTrdX, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Trd &trd, const G4int copyNo, const G4VPhysicalVolume *pv) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationTrdX, "ComputeDimensions", std::addressof(trd), copyNo, pv);
      G4ParameterisationTrdX::ComputeDimensions(trd, copyNo, pv);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationTrdX, ComputeSolid, arg0, arg1);
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationTrdX, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationTrdX, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationTrdX, GetMaterialScanner, );
   }
};

class PyG4ParameterisationTrdY : public G4ParameterisationTrdY, public py::trampoline_self_life_support {
public:
   using G4ParameterisationTrdY::G4ParameterisationTrdY;

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationTrdY, CheckParametersValidity, );
   }

   G4double GetMaxParameter() const override { PYBIND11_OVERRIDE(G4double, G4ParameterisationTrdY, GetMaxParameter, ); }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationTrdY, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Trd &trd, const G4int copyNo, const G4VPhysicalVolume *pv) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationTrdY, "ComputeDimensions", std::addressof(trd), copyNo, pv);
      G4ParameterisationTrdY::ComputeDimensions(trd, copyNo, pv);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationTrdY, ComputeSolid, arg0, arg1);
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationTrdY, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationTrdY, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationTrdY, GetMaterialScanner, );
   }
};

class PyG4ParameterisationTrdZ : public G4ParameterisationTrdZ, public py::trampoline_self_life_support {
public:
   using G4ParameterisationTrdZ::G4ParameterisationTrdZ;

   G4double GetMaxParameter() const override { PYBIND11_OVERRIDE(G4double, G4ParameterisationTrdZ, GetMaxParameter, ); }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationTrdZ, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Trd &trd, const G4int copyNo, const G4VPhysicalVolume *pv) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationTrdZ, "ComputeDimensions", std::addressof(trd), copyNo, pv);
      G4ParameterisationTrdZ::ComputeDimensions(trd, copyNo, pv);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationTrdZ, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationTrdZ, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationTrdZ, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationTrdZ, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationTrdZ, GetMaterialScanner, );
   }
};

void export_G4ParameterisationTrd(py::module &m)
{
   py::class_<G4VParameterisationTrd, PyG4VParameterisationTrd, G4VDivisionParameterisation>(m,
                                                                                             "G4VParameterisationTrd")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4VParameterisationTrd &self) { return PyG4VParameterisationTrd(self); })

      .def("__deepcopy__",
           [](const PyG4VParameterisationTrd &self, py::dict) { return PyG4VParameterisationTrd(self); });

   py::class_<G4ParameterisationTrdX, PyG4ParameterisationTrdX, G4VParameterisationTrd>(m, "G4ParameterisationTrdX")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("width"), py::arg("offset"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationTrdX &self) { return PyG4ParameterisationTrdX(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationTrdX &self, py::dict) { return PyG4ParameterisationTrdX(self); })

      .def("GetMaxParameter", &G4ParameterisationTrdX::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationTrdX::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Trd &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationTrdX::ComputeDimensions, py::const_),
           py::arg("trd"), py::arg("copyNo"), py::arg("pv"))

      .def("ComputeDimensions",
           py::overload_cast<G4Trap &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationTrdX::ComputeDimensions, py::const_),
           py::arg("trd"), py::arg("copyNo"), py::arg("pv"))

      .def("ComputeSolid", &G4ParameterisationTrdX::ComputeSolid, py::return_value_policy::reference);

   py::class_<G4ParameterisationTrdY, PyG4ParameterisationTrdY, G4VParameterisationTrd>(m, "G4ParameterisationTrdY")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("width"), py::arg("offset"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationTrdY &self) { return PyG4ParameterisationTrdY(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationTrdY &self, py::dict) { return PyG4ParameterisationTrdY(self); })

      .def("GetMaxParameter", &G4ParameterisationTrdY::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationTrdY::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Trd &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationTrdY::ComputeDimensions, py::const_),
           py::arg("trd"), py::arg("copyNo"), py::arg("pv"));

   py::class_<G4ParameterisationTrdZ, PyG4ParameterisationTrdZ, G4VParameterisationTrd>(m, "G4ParameterisationTrdZ")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("width"), py::arg("offset"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationTrdZ &self) { return PyG4ParameterisationTrdZ(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationTrdZ &self, py::dict) { return PyG4ParameterisationTrdZ(self); })

      .def("GetMaxParameter", &G4ParameterisationTrdZ::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationTrdZ::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Trd &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationTrdZ::ComputeDimensions, py::const_),
           py::arg("trd"), py::arg("copyNo"), py::arg("pv"));
}

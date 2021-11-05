#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParameterisationPolycone.hh>
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
#include <G4Polyhedra.hh>
#include <G4Hype.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VGraphicsScene.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>
#include <G4SolidExtentList.hh>
#include <G4IntersectingCone.hh>
#include <G4AutoLock.hh>
#include <G4GeomSplitter.hh>
#include <G4VisAttributes.hh>
#include <G4EnclosingCylinder.hh>
#include <G4ReduciblePolygon.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VParameterisationPolycone : public G4VParameterisationPolycone, public py::trampoline_self_life_support {
public:
   using G4VParameterisationPolycone::G4VParameterisationPolycone;

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_PURE(void, G4VParameterisationPolycone, ComputeTransformation, copyNo, physVol);
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VParameterisationPolycone, GetMaxParameter, );
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4VParameterisationPolycone, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4VParameterisationPolycone, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4VParameterisationPolycone, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4VParameterisationPolycone, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4VParameterisationPolycone, GetMaterialScanner, );
   }

   void ComputeDimensions(G4Box &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Tubs &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trd &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Trap &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Cons &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Sphere &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Orb &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Ellipsoid &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Torus &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Para &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polycone &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Polyhedra &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }

   void ComputeDimensions(G4Hype &arg0, const G4int arg1, const G4VPhysicalVolume *arg2) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4VParameterisationPolycone, "ComputeDimensions", std::addressof(arg0), arg1, arg2);
      return G4VParameterisationPolycone::ComputeDimensions(arg0, arg1, arg2);
   }
};

class PyG4ParameterisationPolyconeRho : public G4ParameterisationPolyconeRho, public py::trampoline_self_life_support {
public:
   using G4ParameterisationPolyconeRho::G4ParameterisationPolyconeRho;

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationPolyconeRho, CheckParametersValidity, );
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationPolyconeRho, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationPolyconeRho, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Polycone &pcone, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationPolyconeRho, "ComputeDimensions", std::addressof(pcone), copyNo,
                             physVol);
      G4ParameterisationPolyconeRho::ComputeDimensions(pcone, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationPolyconeRho, ComputeSolid, arg0, arg1);
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationPolyconeRho, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationPolyconeRho, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationPolyconeRho, GetMaterialScanner, );
   }
};

class PyG4ParameterisationPolyconePhi : public G4ParameterisationPolyconePhi, public py::trampoline_self_life_support {
public:
   using G4ParameterisationPolyconePhi::G4ParameterisationPolyconePhi;

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationPolyconePhi, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationPolyconePhi, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Polycone &pcone, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationPolyconePhi, "ComputeDimensions", std::addressof(pcone), copyNo,
                             physVol);
      G4ParameterisationPolyconePhi::ComputeDimensions(pcone, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationPolyconePhi, ComputeSolid, arg0, arg1);
   }

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationPolyconePhi, CheckParametersValidity, );
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationPolyconePhi, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationPolyconePhi, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationPolyconePhi, GetMaterialScanner, );
   }
};

class PyG4ParameterisationPolyconeZ : public G4ParameterisationPolyconeZ, public py::trampoline_self_life_support {
public:
   using G4ParameterisationPolyconeZ::G4ParameterisationPolyconeZ;

   void CheckParametersValidity() override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationPolyconeZ, CheckParametersValidity, );
   }

   G4double GetMaxParameter() const override
   {
      PYBIND11_OVERRIDE(G4double, G4ParameterisationPolyconeZ, GetMaxParameter, );
   }

   void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE(void, G4ParameterisationPolyconeZ, ComputeTransformation, copyNo, physVol);
   }

   void ComputeDimensions(G4Polycone &pcone, const G4int copyNo, const G4VPhysicalVolume *physVol) const override
   {
      PYBIND11_OVERRIDE_IMPL(void, G4ParameterisationPolyconeZ, "ComputeDimensions", std::addressof(pcone), copyNo,
                             physVol);
      G4ParameterisationPolyconeZ::ComputeDimensions(pcone, copyNo, physVol);
   }

   G4VSolid *ComputeSolid(const G4int arg0, G4VPhysicalVolume *arg1) override
   {
      PYBIND11_OVERRIDE(G4VSolid *, G4ParameterisationPolyconeZ, ComputeSolid, arg0, arg1);
   }

   G4Material *ComputeMaterial(const G4int repNo, G4VPhysicalVolume *currentVol,
                               const G4VTouchable *parentTouch) override
   {
      PYBIND11_OVERRIDE(G4Material *, G4ParameterisationPolyconeZ, ComputeMaterial, repNo, currentVol, parentTouch);
   }

   G4bool IsNested() const override { PYBIND11_OVERRIDE(G4bool, G4ParameterisationPolyconeZ, IsNested, ); }

   G4VVolumeMaterialScanner *GetMaterialScanner() override
   {
      PYBIND11_OVERRIDE(G4VVolumeMaterialScanner *, G4ParameterisationPolyconeZ, GetMaterialScanner, );
   }
};

void export_G4ParameterisationPolycone(py::module &m)
{
   py::class_<G4VParameterisationPolycone, PyG4VParameterisationPolycone, G4VDivisionParameterisation>(
      m, "G4VParameterisationPolycone")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("msolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4VParameterisationPolycone &self) { return PyG4VParameterisationPolycone(self); })

      .def("__deepcopy__",
           [](const PyG4VParameterisationPolycone &self, py::dict) { return PyG4VParameterisationPolycone(self); });

   py::class_<G4ParameterisationPolyconeRho, PyG4ParameterisationPolyconeRho, G4VParameterisationPolycone>(
      m, "G4ParameterisationPolyconeRho")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__",
           [](const PyG4ParameterisationPolyconeRho &self) { return PyG4ParameterisationPolyconeRho(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationPolyconeRho &self, py::dict) { return PyG4ParameterisationPolyconeRho(self); })

      .def("CheckParametersValidity", &G4ParameterisationPolyconeRho::CheckParametersValidity)
      .def("GetMaxParameter", &G4ParameterisationPolyconeRho::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationPolyconeRho::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Polycone &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationPolyconeRho::ComputeDimensions, py::const_),
           py::arg("pcone"), py::arg("copyNo"), py::arg("physVol"));

   py::class_<G4ParameterisationPolyconePhi, PyG4ParameterisationPolyconePhi, G4VParameterisationPolycone>(
      m, "G4ParameterisationPolyconePhi")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__",
           [](const PyG4ParameterisationPolyconePhi &self) { return PyG4ParameterisationPolyconePhi(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationPolyconePhi &self, py::dict) { return PyG4ParameterisationPolyconePhi(self); })

      .def("GetMaxParameter", &G4ParameterisationPolyconePhi::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationPolyconePhi::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Polycone &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationPolyconePhi::ComputeDimensions, py::const_),
           py::arg("pcone"), py::arg("copyNo"), py::arg("physVol"));

   py::class_<G4ParameterisationPolyconeZ, PyG4ParameterisationPolyconeZ, G4VParameterisationPolycone>(
      m, "G4ParameterisationPolyconeZ")

      .def(py::init<EAxis, G4int, G4double, G4double, G4VSolid *, DivisionType>(), py::arg("axis"), py::arg("nCopies"),
           py::arg("offset"), py::arg("step"), py::arg("motherSolid"), py::arg("divType"))

      .def("__copy__", [](const PyG4ParameterisationPolyconeZ &self) { return PyG4ParameterisationPolyconeZ(self); })

      .def("__deepcopy__",
           [](const PyG4ParameterisationPolyconeZ &self, py::dict) { return PyG4ParameterisationPolyconeZ(self); })

      .def("CheckParametersValidity", &G4ParameterisationPolyconeZ::CheckParametersValidity)
      .def("GetMaxParameter", &G4ParameterisationPolyconeZ::GetMaxParameter)
      .def("ComputeTransformation", &G4ParameterisationPolyconeZ::ComputeTransformation, py::arg("copyNo"),
           py::arg("physVol"))

      .def("ComputeDimensions",
           py::overload_cast<G4Polycone &, const G4int, const G4VPhysicalVolume *>(
              &G4ParameterisationPolyconeZ::ComputeDimensions, py::const_),
           py::arg("pcone"), py::arg("copyNo"), py::arg("physVol"));
}

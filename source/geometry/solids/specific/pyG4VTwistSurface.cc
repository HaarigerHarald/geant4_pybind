#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VTwistSurface.hh>
#include <G4AffineTransform.hh>
#include <G4VoxelLimits.hh>
#include <G4VPVParameterisation.hh>
#include <G4VPhysicalVolume.hh>
#include <G4VGraphicsScene.hh>
#include <G4Polyhedron.hh>
#include <G4VisExtent.hh>
#include <G4DisplacedSolid.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VTwistSurface : public G4VTwistSurface, public py::trampoline_self_life_support {
public:
   using G4VTwistSurface::G4VTwistSurface;

   G4int DistanceToSurface(const G4ThreeVector &gp, const G4ThreeVector &gv, G4ThreeVector *gxx, G4double *distance,
                           G4int *areacode, G4bool *isvalid, G4VTwistSurface::EValidate validate) override
   {
      PYBIND11_OVERRIDE_PURE(G4int, G4VTwistSurface, DistanceToSurface, gp, gv, gxx, distance, areacode, isvalid,
                             validate);
   }

   G4int DistanceToSurface(const G4ThreeVector &gp, G4ThreeVector *gxx, G4double *distance, G4int *areacode) override
   {
      PYBIND11_OVERRIDE_PURE(G4int, G4VTwistSurface, DistanceToSurface, gp, gxx, distance, areacode);
   }

   G4ThreeVector GetNormal(const G4ThreeVector &xx, G4bool isGlobal) override
   {
      PYBIND11_OVERRIDE_PURE(G4ThreeVector, G4VTwistSurface, GetNormal, xx, isGlobal);
   }

   G4ThreeVector SurfacePoint(G4double arg0, G4double arg1, G4bool isGlobal) override
   {
      PYBIND11_OVERRIDE_PURE(G4ThreeVector, G4VTwistSurface, SurfacePoint, arg0, arg1, isGlobal);
   }

   G4double GetBoundaryMin(G4double arg0) override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VTwistSurface, GetBoundaryMin, arg0);
   }

   G4double GetBoundaryMax(G4double arg0) override
   {
      PYBIND11_OVERRIDE_PURE(G4double, G4VTwistSurface, GetBoundaryMax, arg0);
   }

   G4double GetSurfaceArea() override { PYBIND11_OVERRIDE_PURE(G4double, G4VTwistSurface, GetSurfaceArea, ); }

   void GetFacets(G4int m, G4int n, G4double xyz[][3], G4int faces[][4], G4int iside) override
   {
      // PYBIND11_OVERRIDE_PURE(void, G4VTwistSurface, GetFacets, m, n, xyz, faces, iside);
   }

   G4int GetAreaCode(const G4ThreeVector &xx, G4bool withtol) override
   {
      PYBIND11_OVERRIDE_PURE(G4int, G4VTwistSurface, GetAreaCode, xx, withtol);
   }

   void SetBoundaries() override { PYBIND11_OVERRIDE_PURE(void, G4VTwistSurface, SetBoundaries, ); }

   virtual void SetCorners() override { PYBIND11_OVERRIDE_PURE(void, G4VTwistSurface, SetCorners, ); }

   G4int AmIOnLeftSide(const G4ThreeVector &me, const G4ThreeVector &vec, G4bool withTol) override
   {
      PYBIND11_OVERRIDE(G4int, G4VTwistSurface, AmIOnLeftSide, me, vec, withTol);
   }

   G4double DistanceToBoundary(G4int areacode, G4ThreeVector &xx, const G4ThreeVector &p) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4VTwistSurface, "DistanceToBoundary", areacode, std::addressof(xx), p);
      return G4VTwistSurface::DistanceToBoundary(areacode, xx, p);
   }

   G4double DistanceToIn(const G4ThreeVector &gp, const G4ThreeVector &gv, G4ThreeVector &gxxbest) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4VTwistSurface, "DistanceToIn", gp, gv, std::addressof(gxxbest));
      return G4VTwistSurface::DistanceToIn(gp, gv, gxxbest);
   }

   G4double DistanceToOut(const G4ThreeVector &gp, const G4ThreeVector &gv, G4ThreeVector &gxxbest) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4VTwistSurface, "DistanceToOut", gp, gv, std::addressof(gxxbest));
      return G4VTwistSurface::DistanceToOut(gp, gv, gxxbest);
   }

   G4double DistanceTo(const G4ThreeVector &gp, G4ThreeVector &gxx) override
   {
      PYBIND11_OVERRIDE_IMPL(G4double, G4VTwistSurface, "DistanceTo", gp, std::addressof(gxx));
      return G4VTwistSurface::DistanceTo(gp, gxx);
   }

   G4String GetName() const override { PYBIND11_OVERRIDE(G4String, G4VTwistSurface, GetName, ); }

   void GetBoundaryParameters(const G4int &areacode, G4ThreeVector &d, G4ThreeVector &x0,
                              G4int &boundarytype) const override
   {
      PYBIND11_OVERRIDE(void, G4VTwistSurface, GetBoundaryParameters, areacode, d, x0, boundarytype);
   }

   G4ThreeVector GetBoundaryAtPZ(G4int areacode, const G4ThreeVector &p) const override
   {
      PYBIND11_OVERRIDE(G4ThreeVector, G4VTwistSurface, GetBoundaryAtPZ, areacode, p);
   }

   void SetBoundary(const G4int &axiscode, const G4ThreeVector &direction, const G4ThreeVector &x0,
                    const G4int &boundarytype) override
   {
      PYBIND11_OVERRIDE(void, G4VTwistSurface, SetBoundary, axiscode, direction, x0, boundarytype);
   }
};

void export_G4VTwistSurface(py::module &m)
{
   py::class_<G4VTwistSurface, PyG4VTwistSurface> mG4VTwistSurface(m, "G4VTwistSurface");

   py::enum_<G4VTwistSurface::EValidate>(mG4VTwistSurface, "EValidate")
      .value("kDontValidate", G4VTwistSurface::kDontValidate)
      .value("kValidateWithTol", G4VTwistSurface::kValidateWithTol)
      .value("kValidateWithoutTol", G4VTwistSurface::kValidateWithoutTol)
      .value("kUninitialized", G4VTwistSurface::kUninitialized)
      .export_values();

   // py::class_<CurrentStatus>(mG4VTwistSurface, "CurrentStatus")

   //    .def(py::init<>())
   //    .def(py::init<const G4VTwistSurface::CurrentStatus &>())
   //    .def("GetXX", &CurrentStatus::GetXX, py::arg("i"))
   //    .def("GetDistance", &CurrentStatus::GetDistance, py::arg("i"))
   //    .def("GetAreacode", &CurrentStatus::GetAreacode, py::arg("i"))
   //    .def("GetNXX", &CurrentStatus::GetNXX)
   //    .def("IsDone", &CurrentStatus::IsDone)
   //    .def("IsValid", &CurrentStatus::IsValid, py::arg("i"))
   //    .def("SetCurrentStatus", &CurrentStatus::SetCurrentStatus, py::arg("i"), py::arg("xx"), py::arg("dist"),
   //         py::arg("areacode"), py::arg("isvalid"), py::arg("nxx"), py::arg("validate"), py::arg("p"),
   //         py::arg("v") = static_cast<const G4ThreeVector *>(nullptr))

   //    .def("ResetfDone", &CurrentStatus::ResetfDone, py::arg("validate"), py::arg("p"),
   //         py::arg("v") = static_cast<const G4ThreeVector *>(nullptr))

   //    .def("DebugPrint", &CurrentStatus::DebugPrint);

   // py::class_<Boundary>(mG4VTwistSurface, "Boundary")

   //    .def(py::init<>())
   //    .def(py::init<const G4VTwistSurface::Boundary &>())
   //    .def("SetFields", &Boundary::SetFields, py::arg("areacode"), py::arg("d"), py::arg("x0"),
   //    py::arg("boundarytype"))

   //    .def("IsEmpty", &Boundary::IsEmpty)
   //    .def("GetBoundaryParameters", &Boundary::GetBoundaryParameters, py::arg("areacode"), py::arg("d"),
   //    py::arg("x0"),
   //         py::arg("boundarytype"));

   // py::class_<G4SurfCurNormal>(mG4VTwistSurface, "G4SurfCurNormal")

   //    .def(py::init<const G4VTwistSurface::G4SurfCurNormal &>())
   //    .def(py::init<>())
   //    .def_readwrite("p", &G4SurfCurNormal::p)
   //    .def_readwrite("normal", &G4SurfCurNormal::normal);

   // py::class_<G4SurfSideQuery>(mG4VTwistSurface, "G4SurfSideQuery")

   //    .def(py::init<const G4VTwistSurface::G4SurfSideQuery &>())
   //    .def(py::init<>())
   //    .def_readwrite("me", &G4SurfSideQuery::me)
   //    .def_readwrite("vec", &G4SurfSideQuery::vec)
   //    .def_readwrite("withTol", &G4SurfSideQuery::withTol)
   //    .def_readwrite("amIOnLeftSide", &G4SurfSideQuery::amIOnLeftSide);

   py::class_<Intersection>(m, "Intersection")

      .def("__copy__", [](const Intersection &self) { return Intersection(self); })
      .def("__deepcopy__", [](const Intersection &self, py::dict) { return Intersection(self); })
      .def(py::init<>())
      .def_readwrite("phi", &Intersection::phi)
      .def_readwrite("u", &Intersection::u)
      .def_readwrite("xx", &Intersection::xx)
      .def_readwrite("distance", &Intersection::distance)
      .def_readwrite("areacode", &Intersection::areacode)
      .def_readwrite("isvalid", &Intersection::isvalid);

   mG4VTwistSurface.def(py::init<const G4String &>(), py::arg("name"))
      .def(py::init<const G4String &, const G4RotationMatrix &, const G4ThreeVector &, G4int, const EAxis, const EAxis,
                    G4double, G4double, G4double, G4double>(),
           py::arg("name"), py::arg("rot"), py::arg("tlate"), py::arg("handedness"), py::arg("axis1"), py::arg("axis2"),
           py::arg("axis0min") = -kInfinity, py::arg("axis1min") = -kInfinity, py::arg("axis0max") = kInfinity,
           py::arg("axis1max") = kInfinity)

      .def("__copy__", [](const PyG4VTwistSurface &self) { return PyG4VTwistSurface(self); })
      .def("__deepcopy__", [](const PyG4VTwistSurface &self, py::dict) { return PyG4VTwistSurface(self); })

      .def("AmIOnLeftSide", &G4VTwistSurface::AmIOnLeftSide, py::arg("me"), py::arg("vec"), py::arg("withTol") = true)
      .def("DistanceToBoundary", &G4VTwistSurface::DistanceToBoundary, py::arg("areacode"), py::arg("xx"), py::arg("p"))
      .def("DistanceToIn", &G4VTwistSurface::DistanceToIn, py::arg("gp"), py::arg("gv"), py::arg("gxxbest"))
      .def("DistanceToOut", &G4VTwistSurface::DistanceToOut, py::arg("gp"), py::arg("gv"), py::arg("gxxbest"))
      .def("DistanceTo", &G4VTwistSurface::DistanceTo, py::arg("gp"), py::arg("gxx"))
      .def("DistanceToSurface",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, G4ThreeVector *, G4double *, G4int *,
                             G4bool *, G4VTwistSurface::EValidate>(&G4VTwistSurface::DistanceToSurface),
           py::arg("gp"), py::arg("gv"), py::arg("gxx"), py::arg("distance"), py::arg("areacode"), py::arg("isvalid"),
           py::arg("validate") = G4VTwistSurface::kValidateWithTol)

      .def("DistanceToSurface",
           py::overload_cast<const G4ThreeVector &, G4ThreeVector *, G4double *, G4int *>(
              &G4VTwistSurface::DistanceToSurface),
           py::arg("gp"), py::arg("gxx"), py::arg("distance"), py::arg("areacode"))

      .def("DebugPrint", &G4VTwistSurface::DebugPrint)
      .def("GetNormal", &G4VTwistSurface::GetNormal, py::arg("xx"), py::arg("isGlobal"))
      .def("GetName", &G4VTwistSurface::GetName)
      .def("GetBoundaryParameters", &G4VTwistSurface::GetBoundaryParameters, py::arg("areacode"), py::arg("d"),
           py::arg("x0"), py::arg("boundarytype"))

      .def("GetBoundaryAtPZ", &G4VTwistSurface::GetBoundaryAtPZ, py::arg("areacode"), py::arg("p"))
      .def("DistanceToPlaneWithV", &G4VTwistSurface::DistanceToPlaneWithV, py::arg("p"), py::arg("v"), py::arg("x0"),
           py::arg("n0"), py::arg("xx"))

      .def("DistanceToPlane",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4ThreeVector &, G4ThreeVector &>(
              &G4VTwistSurface::DistanceToPlane),
           py::arg("p"), py::arg("x0"), py::arg("n0"), py::arg("xx"))

      .def("DistanceToPlane",
           py::overload_cast<const G4ThreeVector &, const G4ThreeVector &, const G4ThreeVector &, const G4ThreeVector &,
                             G4ThreeVector &, G4ThreeVector &>(&G4VTwistSurface::DistanceToPlane),
           py::arg("p"), py::arg("x0"), py::arg("t1"), py::arg("t2"), py::arg("xx"), py::arg("n"))

      .def("DistanceToLine", &G4VTwistSurface::DistanceToLine, py::arg("p"), py::arg("x0"), py::arg("d"), py::arg("xx"))
      .def("IsAxis0", &G4VTwistSurface::IsAxis0, py::arg("areacode"))
      .def("IsAxis1", &G4VTwistSurface::IsAxis1, py::arg("areacode"))
      .def("IsOutside", &G4VTwistSurface::IsOutside, py::arg("areacode"))
      .def("IsInside", &G4VTwistSurface::IsInside, py::arg("areacode"), py::arg("testbitmode") = false)
      .def("IsBoundary", &G4VTwistSurface::IsBoundary, py::arg("areacode"), py::arg("testbitmode") = false)
      .def("IsCorner", &G4VTwistSurface::IsCorner, py::arg("areacode"), py::arg("testbitmode") = false)
      .def("IsValidNorm", &G4VTwistSurface::IsValidNorm)
      .def("IsSameBoundary", &G4VTwistSurface::IsSameBoundary, py::arg("surface1"), py::arg("areacode1"),
           py::arg("surface2"), py::arg("areacode2"))

      .def("GetAxisType", &G4VTwistSurface::GetAxisType, py::arg("areacode"), py::arg("whichaxis"))
      .def("ComputeGlobalPoint", &G4VTwistSurface::ComputeGlobalPoint, py::arg("lp"))
      .def("ComputeLocalPoint", &G4VTwistSurface::ComputeLocalPoint, py::arg("gp"))
      .def("ComputeGlobalDirection", &G4VTwistSurface::ComputeGlobalDirection, py::arg("lp"))
      .def("ComputeLocalDirection", &G4VTwistSurface::ComputeLocalDirection, py::arg("gp"))
      .def("SetAxis", &G4VTwistSurface::SetAxis, py::arg("i"), py::arg("axis"))
      .def("SetNeighbours", &G4VTwistSurface::SetNeighbours, py::arg("ax0min"), py::arg("ax1min"), py::arg("ax0max"),
           py::arg("ax1max"))

      .def("SurfacePoint", &G4VTwistSurface::SurfacePoint, py::arg("arg0"), py::arg("arg1"),
           py::arg("isGlobal") = false)

      .def("GetBoundaryMin", &G4VTwistSurface::GetBoundaryMin)
      .def("GetBoundaryMax", &G4VTwistSurface::GetBoundaryMax)
      .def("GetSurfaceArea", &G4VTwistSurface::GetSurfaceArea)
      .def(
         "GetFacets",
         [](G4VTwistSurface &self, G4int m, G4int n, py::list pyXyz, py::list pyFaces, G4int iside) {
            G4double(*xyz)[3] = new G4double[pyXyz.size()][3];
            G4int(*faces)[4]  = new G4int[pyFaces.size()][4];

            for (size_t i = 0; i < pyXyz.size(); i++) {
               py::list innerList = pyXyz[i];
               for (size_t j = 0; j < 3; j++) {
                  xyz[i][j] = innerList[j].cast<G4double>();
               }
            }

            for (size_t i = 0; i < pyFaces.size(); i++) {
               py::list innerList = pyFaces[i];
               for (size_t j = 0; j < 4; j++) {
                  xyz[i][j] = innerList[j].cast<G4int>();
               }
            }

            self.GetFacets(m, n, xyz, faces, iside);

            delete[] xyz;
            delete[] faces;
         },
         py::arg("m"), py::arg("n"), py::arg("xyz"), py::arg("faces"), py::arg("iside"))

      .def("GetNode", &G4VTwistSurface::GetNode, py::arg("i"), py::arg("j"), py::arg("m"), py::arg("n"),
           py::arg("iside"))

      .def("GetFace", &G4VTwistSurface::GetFace, py::arg("i"), py::arg("j"), py::arg("m"), py::arg("n"),
           py::arg("iside"))

      .def("GetEdgeVisibility", &G4VTwistSurface::GetEdgeVisibility, py::arg("i"), py::arg("j"), py::arg("m"),
           py::arg("n"), py::arg("number"), py::arg("orientation"))

      .def_readonly_static("sOutside", &G4VTwistSurface::sOutside)
      .def_readonly_static("sInside", &G4VTwistSurface::sInside)
      .def_readonly_static("sBoundary", &G4VTwistSurface::sBoundary)
      .def_readonly_static("sCorner", &G4VTwistSurface::sCorner)
      .def_readonly_static("sC0Min1Min", &G4VTwistSurface::sC0Min1Min)
      .def_readonly_static("sC0Max1Min", &G4VTwistSurface::sC0Max1Min)
      .def_readonly_static("sC0Max1Max", &G4VTwistSurface::sC0Max1Max)
      .def_readonly_static("sC0Min1Max", &G4VTwistSurface::sC0Min1Max)
      .def_readonly_static("sAxisMin", &G4VTwistSurface::sAxisMin)
      .def_readonly_static("sAxisMax", &G4VTwistSurface::sAxisMax)
      .def_readonly_static("sAxisX", &G4VTwistSurface::sAxisX)
      .def_readonly_static("sAxisY", &G4VTwistSurface::sAxisY)
      .def_readonly_static("sAxisZ", &G4VTwistSurface::sAxisZ)
      .def_readonly_static("sAxisRho", &G4VTwistSurface::sAxisRho)
      .def_readonly_static("sAxisPhi", &G4VTwistSurface::sAxisPhi)
      .def_readonly_static("sAxis0", &G4VTwistSurface::sAxis0)
      .def_readonly_static("sAxis1", &G4VTwistSurface::sAxis1)
      .def_readonly_static("sSizeMask", &G4VTwistSurface::sSizeMask)
      .def_readonly_static("sAxisMask", &G4VTwistSurface::sAxisMask)
      .def_readonly_static("sAreaMask", &G4VTwistSurface::sAreaMask);
}

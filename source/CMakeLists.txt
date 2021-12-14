
file(GLOB_RECURSE SOURCE CONFIGURE_DEPENDS
  analysis/*.cc
  digits_hits/*.cc
  event/*.cc
  geometry/*.cc
  global/*.cc
  graphics_reps/*.cc
  intercoms/*.cc
  interface/*.cc
  materials/*.cc
  particles/*.cc
  persistency/*.cc
  physics_lists/*.cc
  processes/*.cc
  run/*.cc
  tasking/*.cc
  track/*.cc
  tracking/*.cc
  visualization/*.cc
)

pybind11_add_module(geant4_pybind
  ${SOURCE}
  geant4_pybind.cc
)

target_include_directories(geant4_pybind PRIVATE "${CMAKE_CURRENT_LIST_DIR}")

target_compile_definitions(geant4_pybind
  PRIVATE
    PYBIND11_USE_SMART_HOLDER_AS_DEFAULT
    $<$<BOOL:${Geant4_gdml_FOUND}>:G4_HAS_GDML>
    $<$<BOOL:${Geant4_ui_tcsh_FOUND}>:G4_HAS_TCSH>
    $<$<BOOL:${Geant4_vis_opengl_x11_FOUND}>:G4_HAS_OPENGLX>
    $<$<BOOL:${Geant4_vis_raytracer_x11_FOUND}>:G4_HAS_RAYTRACERX>
    $<$<BOOL:${Geant4_motif_FOUND}>:G4_HAS_OPENGLXM>
    $<$<BOOL:${Geant4_vis_opengl_win32_FOUND}>:G4_HAS_OPENGLWIN>
    $<$<BOOL:${Geant4_qt_FOUND}>:G4_HAS_QT>
)

target_link_libraries(geant4_pybind PRIVATE ${Geant4_LIBRARIES})

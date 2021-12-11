# Mostly copied from .github workflow
add_test(NAME test_B1 COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_B1.py)
add_test(NAME test_destruction COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_destruction.py)
add_test(NAME test_examples COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test_examples.py)

set_tests_properties(test_B1 test_destruction test_examples
  PROPERTIES ENVIRONMENT PYTHONPATH=$<TARGET_FILE_DIR:geant4_pybind>)
from geant4_pybind import *
import os
import sys


print(RandBit.shootBit())

print(G4RandGauss.shoot(5, 2))
print(G4RandGauss.shoot(5, 2))
print(G4RandGauss.shoot(5, 2))
print(G4RandGauss.shoot(5, 2))
print(G4RandGauss.shoot(5, 2))

print(G4VERSION_NUMBER)

timer = G4Timer()
timer.Start()
timer2 = timer

vector1 = G4TwoVector(3.2, 4)

print(vector1)

vector3 = G4TwoVector(vector1)
vector1 *= 2

print(vector3)

sVector = G4StringVector(["Hello", " ", "World", "!"])
iVector = G4intVector([1, 2, 3])

vVector = G4TwoVectorVector([vector1, vector3])

print(vVector)

print(sVector[3])
print(iVector[2])

elVector = G4ElementTable

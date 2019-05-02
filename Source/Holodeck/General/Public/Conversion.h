#pragma once

#include "Holodeck.h"

enum ConvertType {UEToClient, ClientToUE, NoScale};

FVector ConvertLinearVector(FVector Vector, ConvertType Type);


FVector ConvertAngularVector(FVector Vector, ConvertType Type);

FRotator ConvertAngularVector(FRotator Rotator, ConvertType);


FVector ConvertTorque(FVector Vector, ConvertType Type);
// FieldClasses.h
#ifndef FIELD_CLASSES_H
#define FIELD_CLASSES_H

#include "TFile.h"
#include "TGraph.h"
#include "TVector3.h"

#include "BasicFunctions/BasicFunctions.h"

namespace rad
{
  class FieldPoint
  {
  private:
    TVector3 antennaPoint;
    // Time series for field components
    TGraph* EField[3];
    TGraph* BField[3];

    TGraph* pos[3];
    TGraph* vel[3];
    TGraph* acc[3];

    TGraph* tPrime; // Relationship between time and retarded time
    
    void ResetFields();

    TGraph* MakeRetardedTimeGraph(const TGraph* grOriginal);
    
  public:
    enum Coord_t{
      kX, kY, kZ
    };
    FieldPoint();
    FieldPoint(const TVector3 inputAntenna);
    ~FieldPoint();
    
    void GenerateFields(const char* inputFile, const double maxTime);

    TGraph* GetEFieldTimeDomain(Coord_t coord, const bool kUseRetardedTime=false);
    TGraph* GetBFieldTimeDomain(Coord_t coord, const bool kUseRetardedTime=false);
   
    TGraph* GetEFieldMagTimeDomain(const bool kUseRetardedTime=false);
    TGraph* GetBFieldMagTimeDomain(const bool kUseRetardedTime=false);
    TGraph* GetPoyntingMagTimeDomain(const bool kUseRetardedTime=false);
    
    TGraph* GetEFieldPeriodogram(Coord_t coord, const bool kUseRetardedTime=false);
    TGraph* GetTotalEFieldPeriodogram(const bool kUseRetardedTime=false);

    // These have a normalisation such that they shouldn't be changed
    TGraph* GetEFieldPowerSpectrumNorm(Coord_t coord, const bool kUseRetardedTime=false);
    TGraph* GetTotalEFieldPowerSpectrumNorm(const bool kUseRetardedTime=false);
    
    TGraph* GetDipolePowerTimeDomain(const bool kUseRetardedTime=false);
  };

}

#endif

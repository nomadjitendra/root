/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id$
 * Authors:                                                                  *
 *   Kyle Cranmer
 *                                                                           *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_CHISQUARE
#define ROO_CHISQUARE

#include "RooAbsPdf.h"
#include "RooRealProxy.h"

class RooRealVar;
class RooArgList ;

class RooChiSquarePdf : public RooAbsPdf {
public:

  RooChiSquarePdf() ;
  RooChiSquarePdf(const char *name, const char *title,
               RooAbsReal& x,  RooAbsReal& ndof) ;

  RooChiSquarePdf(const RooChiSquarePdf& other, const char* name = 0);
  TObject* clone(const char* newname) const override { return new RooChiSquarePdf(*this, newname); }
  inline ~RooChiSquarePdf() override { }

  
  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const override ;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const override ;
  

private:

  RooRealProxy _x;
  RooRealProxy _ndof;

  Double_t evaluate() const override;
  void computeBatch(cudaStream_t*, double* output, size_t nEvents, RooBatchCompute::DataMap&) const override;
  inline bool canComputeBatchWithCuda() const override { return true; }

  ClassDefOverride(RooChiSquarePdf,1) // Chi Square distribution (eg. the PDF )
};

#endif

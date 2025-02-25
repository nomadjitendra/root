/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitCore                                                       *
 *    File: $Id$
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_PARAM_BINNING
#define ROO_PARAM_BINNING

#include "Rtypes.h"
#include "RooAbsBinning.h"
#include "RooRealVar.h"
#include "RooListProxy.h"
class TIterator ;

class RooParamBinning : public RooAbsBinning {
public:

  RooParamBinning(const char* name=0) ;
  RooParamBinning(RooAbsReal& xlo, RooAbsReal& xhi, Int_t nBins, const char* name=0) ;
  RooParamBinning(const RooParamBinning& other, const char* name=0) ;
  RooAbsBinning* clone(const char* name=0) const override { return new RooParamBinning(*this,name?name:GetName()) ; }
  ~RooParamBinning() override ;

  void setRange(Double_t xlo, Double_t xhi) override ;

  Int_t numBoundaries() const override { return _nbins + 1 ; }
  Int_t binNumber(Double_t x) const override  ;

  Double_t lowBound() const override { return xlo()->getVal() ; }
  Double_t highBound() const override { return xhi()->getVal() ; }

  Double_t binCenter(Int_t bin) const override ;
  Double_t binWidth(Int_t bin) const override ;
  Double_t binLow(Int_t bin) const override ;
  Double_t binHigh(Int_t bin) const override ;

  Double_t averageBinWidth() const override { return _binw ; }
  Double_t* array() const override ;

  void printMultiline(std::ostream &os, Int_t content, Bool_t verbose=kFALSE, TString indent="") const override ;

  void insertHook(RooAbsRealLValue&) const override  ;
  void removeHook(RooAbsRealLValue&) const override  ;

  Bool_t isShareable() const override { return kFALSE ; } // parameterized binning cannot be shared across instances
  Bool_t isParameterized() const override { return kTRUE ; } // binning is parameterized, range will need special handling in integration
  RooAbsReal* lowBoundFunc() const override { return xlo() ; }
  RooAbsReal* highBoundFunc() const override { return xhi() ; }

protected:

  mutable Double_t* _array ; //! do not persist
  mutable RooAbsReal* _xlo ; //!
  mutable RooAbsReal* _xhi ; //!
  Int_t    _nbins ;
  Double_t _binw ;
  mutable RooListProxy* _lp ; //
  mutable RooAbsArg* _owner ; //

  RooAbsReal* xlo() const { return _lp ? ((RooAbsReal*)_lp->at(0)) : _xlo ; }
  RooAbsReal* xhi() const { return _lp ? ((RooAbsReal*)_lp->at(1)) : _xhi ; }

  ClassDefOverride(RooParamBinning,2) // Binning specification with ranges parameterized by external RooAbsReal functions
};

#endif

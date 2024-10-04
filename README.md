# ClassicSVfit and FastMTT
Branch used for the `HH->bbtautau` analysis for `CLUB` and `NBA` frameworks.

Main changes:
 - Based on `LLRCMS/ClassicSVfit` (branch `bbtautau_LegacyRun2`) with the addition of `FastMTT` classes from `SVfit/ClassicSVfit` (branch `fastMTT_2024`)
 - Uncommented lines in destructor to prevent memory leaking in src/svFitHistogramAdapter.cc
 - Updated the 'roundToNdigits' function in src/svFitAuxFunctions.cc
 - Addition of FastMTT algorithm

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include "../interface/MeasuredTauLepton.h"
#include "../interface/ClassicSVfit.h"
#include "../interface/FastMTT.h"

#include "TMatrixT.h"  // Include the TMatrixT header

namespace py = pybind11;



PYBIND11_MODULE(pybind_wrapper, m) {
    py::class_<ClassicSVfit>(m, "ClassicSVfit")
        .def(py::init<int>())
        .def("addLogM_fixed", &ClassicSVfit::addLogM_fixed)
        .def("addLogM_dynamic", &ClassicSVfit::addLogM_dynamic)
        .def("setDiTauMassConstraint", &ClassicSVfit::setDiTauMassConstraint)
        .def("setVerbosity", &ClassicSVfit::setVerbosity)
        .def("setMaxObjFunctionCalls", &ClassicSVfit::setMaxObjFunctionCalls)
        .def("setLikelihoodFileName", &ClassicSVfit::setLikelihoodFileName)
        .def("setTreeFileName", &ClassicSVfit::setTreeFileName)
        .def("setHistogramAdapter", &ClassicSVfit::setHistogramAdapter)
        .def("getHistogramAdapter", &ClassicSVfit::getHistogramAdapter, py::return_value_policy::reference)
        .def("prepareIntegrand", &ClassicSVfit::prepareIntegrand)
        .def("prepareLeptonInput", &ClassicSVfit::prepareLeptonInput)
        // .def("addMETEstimate", &ClassicSVfit::addMETEstimate)
        .def("addMETEstimate", [](ClassicSVfit &self, double metx, double mety, const py::object &cppyy_matrix) {
            // Check if the provided object is indeed a TMatrixT<double>
            if (!cppyy_matrix || !PyObject_HasAttrString(cppyy_matrix.ptr(), "GetMatrixArray")) {
                throw std::runtime_error("Invalid input: not a TMatrixT<double> object");
            }

            // Get the size of the matrix
            const int nrows = py::getattr(cppyy_matrix, "GetNrows")().cast<int>();
            const int ncols = py::getattr(cppyy_matrix, "GetNcols")().cast<int>();

            // Create a TMatrixD with the same size
            TMatrixD matrix(nrows, ncols);

            // Extract data from the TMatrixT<double> object and fill the TMatrixD
            for (int i = 0; i < nrows; ++i) {
                for (int j = 0; j < ncols; ++j) {
                    // const double value = py::getattr(cppyy_matrix,"[][]")(i, j).cast<double>();
                    const double value = cppyy_matrix.attr("__getitem__")(i).attr("__getitem__")(j).cast<double>();
                    // const double value = cppyy_matrix[i][j].cast<double>();
                    matrix(i, j) = value;
                }
            }
                 // Call the addMETEstimate method with the TMatrixD
            self.addMETEstimate(metx, mety, matrix);
        }, py::arg("metx"), py::arg("mety"), py::arg("cppyy_matrix"))                  
        .def("clearMET", &ClassicSVfit::clearMET)
        // .def("integrate", &ClassicSVfit::integrate)
        .def("integrate", [](ClassicSVfit &self,
                             const std::vector<classic_svFit::MeasuredTauLepton>& leptons,
                             const double& arg1, const double& arg2,
                             const py::object &cppyy_matrix){
            // Check if the provided object is indeed a TMatrixT<double>
            if (!cppyy_matrix || !PyObject_HasAttrString(cppyy_matrix.ptr(), "GetMatrixArray")) {
                throw std::runtime_error("Invalid input: not a TMatrixT<double> object");
            }

            // Get the size of the matrix
            const int nrows = py::getattr(cppyy_matrix, "GetNrows")().cast<int>();
            const int ncols = py::getattr(cppyy_matrix, "GetNcols")().cast<int>();

            // Create a TMatrixD with the same size
            TMatrixD matrix(nrows, ncols);

            // Extract data from the TMatrixT<double> object and fill the TMatrixD
            for (int i = 0; i < nrows; ++i) {
                for (int j = 0; j < ncols; ++j) {
                    // const double value = py::getattr(cppyy_matrix,"[][]")(i, j).cast<double>();
                    const double value = cppyy_matrix.attr("__getitem__")(i).attr("__getitem__")(j).cast<double>();
                    // const double value = cppyy_matrix[i][j].cast<double>();
                    matrix(i, j) = value;
                }
            }
                 // Call the addMETEstimate method with the TMatrixD
            self.integrate(leptons, arg1, arg2, matrix);
        }, py::arg("leptons"), py::arg("arg1"),py::arg("arg1"), py::arg("cppyy_matrix"))
        .def("isValidSolution", &ClassicSVfit::isValidSolution)
        .def("getComputingTime_cpu", &ClassicSVfit::getComputingTime_cpu)
        .def("getComputingTime_real", &ClassicSVfit::getComputingTime_real);

    py::class_<classic_svFit::MeasuredTauLepton>(m, "MeasuredTauLepton")
        .def(py::init<>())
        .def(py::init<int, double, double, double, double, int>())
        .def(py::init<const classic_svFit::MeasuredTauLepton&>())
        .def("type", &classic_svFit::MeasuredTauLepton::type)
        .def("pt", &classic_svFit::MeasuredTauLepton::pt)
        .def("eta", &classic_svFit::MeasuredTauLepton::eta)
        .def("phi", &classic_svFit::MeasuredTauLepton::phi)
        .def("mass", &classic_svFit::MeasuredTauLepton::mass)
        .def("energy", &classic_svFit::MeasuredTauLepton::energy)
        .def("px", &classic_svFit::MeasuredTauLepton::px)
        .def("py", &classic_svFit::MeasuredTauLepton::py)
        .def("pz", &classic_svFit::MeasuredTauLepton::pz)
        .def("p", &classic_svFit::MeasuredTauLepton::p)
        .def("decayMode", &classic_svFit::MeasuredTauLepton::decayMode)
        .def("p4", &classic_svFit::MeasuredTauLepton::p4)
        .def("p3", &classic_svFit::MeasuredTauLepton::p3)
        .def("cosPhi_sinTheta", &classic_svFit::MeasuredTauLepton::cosPhi_sinTheta)
        .def("sinPhi_sinTheta", &classic_svFit::MeasuredTauLepton::sinPhi_sinTheta)
        .def("cosTheta", &classic_svFit::MeasuredTauLepton::cosTheta)
        .def("roundToNdigits", &classic_svFit::MeasuredTauLepton::roundToNdigits);

    py::class_<classic_svFit::HistogramAdapter>(m, "HistogramAdapter")
        .def(py::init<std::vector<classic_svFit::SVfitQuantity*> const&>())
        .def("setMeasurement", &classic_svFit::HistogramAdapter::setMeasurement)
        .def("setTau1And2P4", &classic_svFit::HistogramAdapter::setTau1And2P4)
        .def("registerQuantity", &classic_svFit::HistogramAdapter::registerQuantity)
        .def("getQuantity", &classic_svFit::HistogramAdapter::getQuantity)
        .def("getNQuantities", &classic_svFit::HistogramAdapter::getNQuantities)
        .def("bookHistograms", &classic_svFit::HistogramAdapter::bookHistograms)
        .def("writeHistograms", &classic_svFit::HistogramAdapter::writeHistograms)
        .def("extractValue", &classic_svFit::HistogramAdapter::extractValue)
        .def("extractUncertainty", &classic_svFit::HistogramAdapter::extractUncertainty)
        .def("extractLmax", &classic_svFit::HistogramAdapter::extractLmax)
        .def("extractValues", &classic_svFit::HistogramAdapter::extractValues)
        .def("extractUncertainties", &classic_svFit::HistogramAdapter::extractUncertainties)
        .def("extractLmaxima", &classic_svFit::HistogramAdapter::extractLmaxima)
        .def("isValidSolution", &classic_svFit::HistogramAdapter::isValidSolution);

    py::class_<classic_svFit::DiTauSystemHistogramAdapter, classic_svFit::HistogramAdapter>(m, "DiTauSystemHistogramAdapter")
        .def(py::init<std::vector<classic_svFit::SVfitQuantity*> const&>())
        .def("getPt", &classic_svFit::DiTauSystemHistogramAdapter::getPt)
        .def("getPtErr", &classic_svFit::DiTauSystemHistogramAdapter::getPtErr)
        .def("getPtLmax", &classic_svFit::DiTauSystemHistogramAdapter::getPtLmax)
        .def("getEta", &classic_svFit::DiTauSystemHistogramAdapter::getEta)
        .def("getEtaErr", &classic_svFit::DiTauSystemHistogramAdapter::getEtaErr)
        .def("getEtaLmax", &classic_svFit::DiTauSystemHistogramAdapter::getEtaLmax)
        .def("getPhi", &classic_svFit::DiTauSystemHistogramAdapter::getPhi)
        .def("getPhiErr", &classic_svFit::DiTauSystemHistogramAdapter::getPhiErr)
        .def("getPhiLmax", &classic_svFit::DiTauSystemHistogramAdapter::getPhiLmax)
        .def("getMass", &classic_svFit::DiTauSystemHistogramAdapter::getMass)
        .def("getMassErr", &classic_svFit::DiTauSystemHistogramAdapter::getMassErr)
        .def("getMassLmax", &classic_svFit::DiTauSystemHistogramAdapter::getMassLmax)
        .def("getTransverseMass", &classic_svFit::DiTauSystemHistogramAdapter::getTransverseMass)
        .def("getTransverseMassErr", &classic_svFit::DiTauSystemHistogramAdapter::getTransverseMassErr)
        .def("getTransverseMassLmax", &classic_svFit::DiTauSystemHistogramAdapter::getTransverseMassLmax);

    py::class_<classic_svFit::TauTauHistogramAdapter, classic_svFit::DiTauSystemHistogramAdapter>(m, "TauTauHistogramAdapter")
        .def(py::init<std::vector<classic_svFit::SVfitQuantity*> const&>())
        .def("GetFittedHiggsLV", &classic_svFit::TauTauHistogramAdapter::GetFittedHiggsLV)
        .def("GetFittedTau1LV", &classic_svFit::TauTauHistogramAdapter::GetFittedTau1LV)
        .def("GetFittedTau2LV", &classic_svFit::TauTauHistogramAdapter::GetFittedTau2LV);
    

    py::class_<FastMTT>(m, "FastMTT")
        .def(py::init<>())
        .def("initialize", &FastMTT::initialize)
        .def("run", [](FastMTT &self,
                       const std::vector<classic_svFit::MeasuredTauLepton>& leptons,
                       const double& arg1, const double& arg2,
                       const py::object &cppyy_matrix){
            // Check if the provided object is indeed a TMatrixD
            if (!cppyy_matrix || !PyObject_HasAttrString(cppyy_matrix.ptr(), "GetNrows")) {
                throw std::runtime_error("Invalid input: not a TMatrixD object");
            }

            // Get the size of the matrix
            const int nrows = py::getattr(cppyy_matrix, "GetNrows")().cast<int>();
            const int ncols = py::getattr(cppyy_matrix, "GetNcols")().cast<int>();
            // Create a TMatrixD with the same size
            TMatrixD matrix(nrows, ncols);
            // Extract data from the TMatrixD object and fill the TMatrixD
            for (int i = 0; i < nrows; ++i) {
                for (int j = 0; j < ncols; ++j) {
                    const double value = cppyy_matrix.attr("__getitem__")(i).attr("__getitem__")(j).cast<double>();
                    matrix(i, j) = value;
                }
            }
            // Call the run method with the TMatrixD
            self.run(leptons, arg1, arg2, matrix);
        }, py::arg("leptons"), py::arg("arg1"), py::arg("arg2"), py::arg("cppyy_matrix"))
        .def("setLikelihoodParams", [](FastMTT &self, const std::vector<double> &params) {
            if (params.size() < 2) {
                throw std::runtime_error("Invalid input: expected at least 2 parameters");
            }
            self.setLikelihoodParams(params);
        }, py::arg("params"))
        .def("enableComponent", &FastMTT::enableComponent)
        .def("disableComponent", &FastMTT::disableComponent)
        .def("getBestP4", &FastMTT::getBestP4)
        // .def("getTau1P4", &FastMTT::getTau1P4)
        .def("getTau1P4", [](FastMTT &self) {
            py::object tau1P4_py = py::module::import("ROOT").attr("TLorentzVector")(self.getTau1P4().Px(), self.getTau1P4().Py(), self.getTau1P4().Pz(), self.getTau1P4().E());
            return tau1P4_py;
        })
        // .def("getTau2P4", &FastMTT::getTau2P4)
        .def("getTau2P4", [](FastMTT &self) {
            py::object tau2P4_py = py::module::import("ROOT").attr("TLorentzVector")(self.getTau2P4().Px(), self.getTau2P4().Py(), self.getTau2P4().Pz(), self.getTau2P4().E());
            return tau2P4_py;
        })
        .def("getBestX", &FastMTT::getBestX)
        .def("getBestLikelihood", &FastMTT::getBestLikelihood)
        .def("getCpuTime", &FastMTT::getCpuTime)
        .def("getRealTime", &FastMTT::getRealTime);
}

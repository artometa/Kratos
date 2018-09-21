//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Jordi Cotela
//


#if !defined(KRATOS_FLUID_DYNAMICS_APPLICATION_VARIABLES_H_INCLUDED )
#define  KRATOS_FLUID_DYNAMICS_APPLICATION_VARIABLES_H_INCLUDED

// System includes

// External includes


// Project includes
#include "includes/define.h"
#include "includes/kratos_application.h"
#include "includes/variables.h"
#include "includes/dem_variables.h"  //TODO: must be removed eventually
#include "includes/legacy_structural_app_vars.h"  //TODO: must be removed eventually

namespace Kratos
{
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, int,PATCH_INDEX)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,TAUONE)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,TAUTWO)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,PRESSURE_MASSMATRIX_COEFFICIENT)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,SUBSCALE_PRESSURE)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,C_DES)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,CHARACTERISTIC_VELOCITY)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, SUBSCALE_VELOCITY)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, COARSE_VELOCITY)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,FIC_BETA)

// Non-Newtonian constitutive relations
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, REGULARIZATION_COEFFICIENT)

// To be removed
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, BINGHAM_SMOOTHER)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, GEL_STRENGTH)

// Q-Criterion (for vortex visualization)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,Q_VALUE)

// Vorticity
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double,VORTICITY_MAGNITUDE)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS(FLUID_DYNAMICS_APPLICATION, RECOVERED_PRESSURE_GRADIENT)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, Vector,NODAL_WEIGHTS)

// Embedded fluid variables
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, int, EMBEDDED_IS_ACTIVE)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, EMBEDDED_WET_PRESSURE)
KRATOS_DEFINE_3D_APPLICATION_VARIABLE_WITH_COMPONENTS( FLUID_DYNAMICS_APPLICATION, EMBEDDED_WET_VELOCITY)

// Compressible fluid variable
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, HEAT_CAPACITY_RATIO)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, REACTION_DENSITY)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, REACTION_ENERGY)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, double, MACH)

// Transient adjoint stabilization variable
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, Matrix, VMS_STEADY_TERM_PRIMAL_GRADIENT_MATRIX)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, Matrix, VMS_ADJOINT_ENERGY_GENERATION_RATE_MATRIX)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, Matrix, ARTIFICIAL_DIFFUSION_MATRIX)
KRATOS_DEFINE_APPLICATION_VARIABLE( FLUID_DYNAMICS_APPLICATION, Matrix, VMS_VELOCITY_GRADIENT_TENSOR)
KRATOS_DEFINE_VARIABLE( double, ARTIFICIAL_DIFFUSION)
KRATOS_DEFINE_VARIABLE( double ,ADJOINT_ENERGY)
KRATOS_DEFINE_VARIABLE( double ,DIFFUSION_ENERGY)

// ------------------- Testing Variables --------------------
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_1_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_2_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_3_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_4_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_5_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_6_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_7_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_8_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_9_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_10_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_11_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_12_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_13_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_14_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_15_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_16_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_17_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_18_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_19_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_20_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_21_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_22_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_23_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_24_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_25_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_26_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_27_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_28_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_29_EIGEN_MIN)

KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_1_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_2_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_3_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_4_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_5_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_6_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_7_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_8_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_9_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_10_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_11_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_12_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_13_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_14_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_15_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_16_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_17_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_18_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_19_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_20_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_21_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_22_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_23_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_24_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_25_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_26_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_27_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_28_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_29_EIGEN_MAX)

KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_1_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_2_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_3_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_4_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_5_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_6_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_7_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_8_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_9_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_10_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_11_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_12_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_13_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_14_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_15_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_16_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_17_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_18_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_19_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_20_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_21_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_22_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_23_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_24_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_25_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_26_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_27_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_28_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_29_ENERGY)

KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_LHS_BEFORE_STABILIZATION_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_LHS_BEFORE_STABILIZATION_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_LHS_BEFORE_STABILIZATION_EIGEN_MAX)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_LHS_AFTER_STABILIZATION_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_LHS_AFTER_STABILIZATION_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_LHS_AFTER_STABILIZATION_EIGEN_MAX)

KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_PRIMAL_GRADIENT_OF_VMS_STEADY_TERM_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_PRIMAL_GRADIENT_OF_VMS_STEADY_TERM_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_PRIMAL_GRADIENT_OF_VMS_STEADY_TERM_EIGEN_MAX)

KRATOS_DEFINE_VARIABLE(Matrix, STABILIZATION_ANALYSIS_MATRIX_CUSTOM)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_CUSTOM_ENERGY)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_CUSTOM_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE( double, STABILIZATION_ANALYSIS_MATRIX_CUSTOM_EIGEN_MAX)

KRATOS_DEFINE_VARIABLE(Matrix, STABILIZATION_ANALYSIS_MATRIX_DIFFUSION)
KRATOS_DEFINE_VARIABLE(double, STABILIZATION_ANALYSIS_MATRIX_DIFFUSION_ENERGY)
KRATOS_DEFINE_VARIABLE(double, STABILIZATION_ANALYSIS_MATRIX_DIFFUSION_EIGEN_MIN)
KRATOS_DEFINE_VARIABLE(double, STABILIZATION_ANALYSIS_MATRIX_DIFFUSION_EIGEN_MAX)

KRATOS_DEFINE_VARIABLE(Matrix, STABILIZATION_ANALYSIS_MATRIX_PURE_DIFFUSION)
KRATOS_DEFINE_VARIABLE(Vector, STABILIZATION_ANALYSIS_MATRIX_ADJOINT_VECTOR)
KRATOS_DEFINE_VARIABLE(double, STABILIZATION_ANALYSIS_MATRIX_GAUSS_POINT_INTEGRATION_WEIGHT);

KRATOS_DEFINE_VARIABLE(Matrix, STABILIZATION_ANALYSIS_MATRIX_24)
KRATOS_DEFINE_VARIABLE(Matrix, STABILIZATION_ANALYSIS_MATRIX_29)
KRATOS_DEFINE_VARIABLE(Matrix, STABILIZATION_ANALYSIS_MATRICES)
KRATOS_DEFINE_VARIABLE(Matrix, STABILIZATION_ANALYSIS_MATRIX_LHS_BEFORE_STABILIZATION)
KRATOS_DEFINE_VARIABLE(Matrix, STABILIZATION_ANALYSIS_MATRIX_LHS_AFTER_STABILIZATION)

}

#endif	/* KRATOS_FLUID_DYNAMICS_APPLICATION_VARIABLES_H_INCLUDED */

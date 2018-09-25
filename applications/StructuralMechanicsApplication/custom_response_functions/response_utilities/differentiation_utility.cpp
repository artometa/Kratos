//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Martin Fusseder, https://github.com/MFusseder
//


// System includes

// External includes

// Project includes
#include "differentiation_utility.h"
#include "structural_mechanics_application_variables.h"

namespace Kratos
{
    void DifferentiationUtility::CalculateRigthHandSideDerivative(Element& rElement,
                                                const Variable<double>& rDesignVariable,
                                                Matrix& rOutput,
                                                const ProcessInfo& rCurrentProcessInfo)
    {
        KRATOS_TRY;

        if ( rElement.GetProperties().Has(rDesignVariable) )
        {
            // define working variables
            Vector RHS_unperturbed;
            Vector RHS_perturbed;

            ProcessInfo copy_process_info = rCurrentProcessInfo;

            // Get perturbation size
            const double delta = DifferentiationUtility::GetPerturbationSize(rDesignVariable);

            // Compute RHS before perturbion
            rElement.CalculateRightHandSide(RHS_unperturbed, copy_process_info);

            if ( (rOutput.size1() != 1) || (rOutput.size2() != RHS_unperturbed.size() ) )
                rOutput.resize(1, RHS_unperturbed.size());

            // Save property pointer
            Properties::Pointer p_global_properties = rElement.pGetProperties();

            // Create new property and assign it to the element
            Properties::Pointer p_local_property(Kratos::make_shared<Properties>(Properties(*p_global_properties)));
            rElement.SetProperties(p_local_property);

            // perturb the design variable
            const double current_property_value = rElement.GetProperties()[rDesignVariable];
            p_local_property->SetValue(rDesignVariable, (current_property_value + delta));

            // Compute RHS after perturbation
            rElement.CalculateRightHandSide(RHS_perturbed, copy_process_info);

            // Compute derivative of RHS w.r.t. design variable with finite differences
            for(IndexType i = 0; i < RHS_perturbed.size(); ++i)
                rOutput(0, i) = (RHS_perturbed[i] - RHS_unperturbed[i]) / delta;

            // Give element original properties back
            rElement.SetProperties(p_global_properties);

            //call one last time to make sure everything is as it was before TODO improve this..
            rElement.CalculateRightHandSide(RHS_perturbed, copy_process_info);
        }
        else
            if ( (rOutput.size1() != 0) || (rOutput.size2() != 0) )
                rOutput.resize(0,0,false);

        KRATOS_CATCH("");
    }

    void DifferentiationUtility::CalculateRigthHandSideDerivative(Element& rElement,
                                                const Variable<array_1d<double,3>>& rDesignVariable,
                                                Matrix& rOutput,
                                                const ProcessInfo& rCurrentProcessInfo)
    {
        KRATOS_TRY;

        #ifdef _OPENMP
            KRATOS_ERROR_IF(omp_get_thread_num() > 0) <<
                "DifferentiationUtility::CalculateRigthHandSideDerivative " <<
                "is not thread safe for shape derivatives!" << omp_get_thread_num();
        #endif

        if(rDesignVariable == SHAPE)
        {
            // define working variables
            Vector RHS_unperturbed;
            Vector RHS_perturbed;
            ProcessInfo copy_process_info = rCurrentProcessInfo;

            // Get perturbation size
            const double delta = DifferentiationUtility::GetPerturbationSize(rDesignVariable);

            const SizeType number_of_nodes = rElement.GetGeometry().PointsNumber();
            const SizeType dimension = rCurrentProcessInfo.GetValue(DOMAIN_SIZE);
            const SizeType num_dofs_per_node = 6; //(mHasRotationDofs) ?  2 * dimension : dimension; TODO
            const SizeType local_size = number_of_nodes * num_dofs_per_node;

            if ( (rOutput.size1() != dimension * number_of_nodes) || (rOutput.size2() != local_size ) )
                rOutput.resize(dimension * number_of_nodes, local_size);

            // compute RHS before perturbion
            rElement.CalculateRightHandSide(RHS_unperturbed, copy_process_info);

            IndexType index = 0;
            for(auto& node_i : rElement.GetGeometry())
            {
                for(IndexType coord_dir_i = 0; coord_dir_i < dimension; ++coord_dir_i)
                {
                    // perturb the design variable
                    node_i.GetInitialPosition()[coord_dir_i] += delta;
                    node_i[coord_dir_i] += delta;

                    // compute RHS after perturbation
                    rElement.CalculateRightHandSide(RHS_perturbed, copy_process_info);

                    //compute derivative of RHS w.r.t. design variable with finite differences
                    for(IndexType i = 0; i < RHS_perturbed.size(); ++i)
                        rOutput( (coord_dir_i + index*dimension), i) = (RHS_perturbed[i]-RHS_unperturbed[i])/delta;

                    // Reset perturbed vector
                    noalias(RHS_perturbed) = ZeroVector(RHS_perturbed.size());

                    // unperturb the design variable
                    node_i.GetInitialPosition()[coord_dir_i] -= delta;
                    node_i[coord_dir_i] -= delta;

                }
                index++;

                //call one last time to make sure everything is as it was before TODO improve this..
                rElement.CalculateRightHandSide(RHS_perturbed, copy_process_info);

            }// end loop over element nodes
        }
        else
        {
            KRATOS_WARNING("DifferentiationUtility") << "Unsupported nodal design variable: " << rDesignVariable << std::endl;
            if ( (rOutput.size1() != 0) || (rOutput.size2() != 0) )
                rOutput.resize(0,0,false);
        }

        KRATOS_CATCH("");
    }

    double DifferentiationUtility::GetPerturbationSize(const Variable<double>& rDesignVariable)
    {
        const double delta = 1.0e-5; //TODO modify this
        return delta;
    }

    double DifferentiationUtility::GetPerturbationSize(const Variable<array_1d<double,3>>& rDesignVariable)
    {
        const double delta = 1.0e-5; //TODO modify this
        return delta;
    }

}  // namespace Kratos.

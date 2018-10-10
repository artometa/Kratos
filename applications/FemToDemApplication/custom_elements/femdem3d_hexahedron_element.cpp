//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ \.
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics FemDem Application
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Alejandro Cornejo Velázquez
//

#include "includes/define.h"
#include "femdem3d_hexahedron_element.hpp"
#include "includes/element.h"
#include "includes/node.h"
#include "fem_to_dem_application_variables.h"
#include "includes/kratos_flags.h"
#include "containers/flags.h"
#include "solid_mechanics_application_variables.h"
#include "processes/find_nodal_neighbours_process.h"

namespace Kratos
{
//***********************DEFAULT CONSTRUCTOR******************************************
//************************************************************************************

FemDem3DHexahedronElement::FemDem3DHexahedronElement(IndexType NewId, GeometryType::Pointer pGeometry)
	: FemDem3DElement(NewId, pGeometry)
{
	//DO NOT ADD DOFS HERE!!!
}
//******************************CONSTRUCTOR*******************************************
//************************************************************************************

FemDem3DHexahedronElement::FemDem3DHexahedronElement(IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties)
	: FemDem3DElement(NewId, pGeometry, pProperties)
{
	//BY DEFAULT, THE GEOMETRY WILL DEFINE THE INTEGRATION METHOD
	mThisIntegrationMethod = GetGeometry().GetDefaultIntegrationMethod();
}

//******************************COPY CONSTRUCTOR**************************************
//************************************************************************************

FemDem3DHexahedronElement::FemDem3DHexahedronElement(FemDem3DHexahedronElement const &rOther)
	: FemDem3DElement(rOther)
{
	//ALL MEMBER VARIABLES THAT MUST BE KEPT AFTER COPYING AN ELEMENT HAVE TO BE DEFINED HERE
	//IF NO ASSIGMENT OPERATOR IS DEFINED THE COPY CONSTRUCTOR WILL DEFINE IT BY DEFFAULT
}

//*******************************ASSIGMENT OPERATOR***********************************
//************************************************************************************

FemDem3DHexahedronElement &FemDem3DHexahedronElement::operator=(FemDem3DHexahedronElement const &rOther)
{
	//ALL MEMBER VARIABLES THAT MUST BE KEPT IN AN "=" OPERATION NEEDS TO BE COPIED HERE

	FemDem3DElement::operator=(rOther);
	return *this;
}

//*********************************OPERATIONS*****************************************
//************************************************************************************

Element::Pointer FemDem3DHexahedronElement::Create(IndexType NewId, NodesArrayType const &rThisNodes, PropertiesType::Pointer pProperties) const
{
	//NEEDED TO CREATE AN ELEMENT
	return Element::Pointer(new FemDem3DHexahedronElement(NewId, GetGeometry().Create(rThisNodes), pProperties));
}

//************************************CLONE*******************************************
//************************************************************************************

Element::Pointer FemDem3DHexahedronElement::Clone(IndexType NewId, NodesArrayType const &rThisNodes) const
{

	//YOU CREATE A NEW ELEMENT CLONING THEIR VARIABLES
	//ALL MEMBER VARIABLES THAT MUST BE CLONED HAVE TO BE DEFINED HERE

	FemDem3DHexahedronElement NewElement(NewId, GetGeometry().Create(rThisNodes), pGetProperties());

	return Element::Pointer(new FemDem3DHexahedronElement(NewElement));
}

//*******************************DESTRUCTOR*******************************************
//************************************************************************************

FemDem3DHexahedronElement::~FemDem3DHexahedronElement()
{
}


void FemDem3DHexahedronElement::CalculateLocalSystem(
	MatrixType &rLeftHandSideMatrix,
	VectorType &rRightHandSideVector,
	ProcessInfo &rCurrentProcessInfo)
{
	// provisional elastic
	KRATOS_TRY

	const unsigned int number_of_nodes = GetGeometry().size();
	const unsigned int dimension = GetGeometry().WorkingSpaceDimension();
	unsigned int voigt_size = dimension * (dimension + 1) / 2;

	const GeometryType::IntegrationPointsArrayType &integration_points = GetGeometry().IntegrationPoints(mThisIntegrationMethod);
	unsigned int system_size = number_of_nodes * dimension;
	if (rLeftHandSideMatrix.size1() != system_size)
		rLeftHandSideMatrix.resize(system_size, system_size, false);
	noalias(rLeftHandSideMatrix) = ZeroMatrix(system_size, system_size);

	if (rRightHandSideVector.size() != system_size)
		rRightHandSideVector.resize(system_size, false);
	noalias(rRightHandSideVector) = ZeroVector(system_size);

	Matrix DeltaPosition(number_of_nodes, dimension);
	noalias(DeltaPosition) = ZeroMatrix(number_of_nodes, dimension);
	DeltaPosition = this->CalculateDeltaPosition(DeltaPosition);

	GeometryType::JacobiansType J;
	J.resize(1, false);
	J[0].resize(dimension, dimension, false);
	noalias(J[0]) = ZeroMatrix(dimension, dimension);
	J = GetGeometry().Jacobian(J, mThisIntegrationMethod, DeltaPosition);

	for (unsigned int PointNumber = 0; PointNumber < integration_points.size(); PointNumber++) {
		const Matrix &Ncontainer = GetGeometry().ShapeFunctionsValues(mThisIntegrationMethod);
		Vector N = row(Ncontainer, PointNumber);

		double detJ = 0;
		Matrix InvJ(dimension, dimension);
		noalias(InvJ) = ZeroMatrix(dimension, dimension);
		MathUtils<double>::InvertMatrix(J[PointNumber], InvJ, detJ);

		double IntegrationWeight = integration_points[PointNumber].Weight() * detJ;
		const Matrix &B = this->GetBMatrix();
		const Vector &StressVector = this->GetValue(STRESS_VECTOR);

		Matrix ConstitutiveMatrix = ZeroMatrix(voigt_size, voigt_size);
		const double E = this->GetProperties()[YOUNG_MODULUS];
		const double nu = this->GetProperties()[POISSON_RATIO];
		this->CalculateConstitutiveMatrix(ConstitutiveMatrix, E, nu);

		noalias(rLeftHandSideMatrix) += prod(trans(B), IntegrationWeight * Matrix(prod(ConstitutiveMatrix, B))); // LHS

		Vector VolumeForce = ZeroVector(dimension);
		VolumeForce = this->CalculateVolumeForce(VolumeForce, N);

		// RHS
		for (unsigned int i = 0; i < number_of_nodes; i++) {
			int index = dimension * i;
			for (unsigned int j = 0; j < dimension; j++) {
				rRightHandSideVector[index + j] += IntegrationWeight * N[i] * VolumeForce[j];
			}
		}

		//compute and add internal forces (RHS = rRightHandSideVector = Fext - Fint)
		noalias(rRightHandSideVector) -= IntegrationWeight * prod(trans(B), StressVector);

	}
	KRATOS_CATCH("")
}

void FemDem3DHexahedronElement::FinalizeSolutionStep(ProcessInfo &rCurrentProcessInfo)
{
}


// Double values
void FemDem3DHexahedronElement::GetValueOnIntegrationPoints(
	const Variable<double> &rVariable,
	std::vector<double> &rValues,
	const ProcessInfo &rCurrentProcessInfo)
{
	if (rVariable == DAMAGE_ELEMENT || rVariable == IS_DAMAGED || rVariable == STRESS_THRESHOLD) {
		CalculateOnIntegrationPoints(rVariable, rValues, rCurrentProcessInfo);
	}
}

// Vector Values
void FemDem3DHexahedronElement::GetValueOnIntegrationPoints(
	const Variable<Vector> &rVariable,
	std::vector<Vector> &rValues,
	const ProcessInfo &rCurrentProcessInfo)
{
	if (rVariable == STRAIN_VECTOR) {
		CalculateOnIntegrationPoints(rVariable, rValues, rCurrentProcessInfo);
	} else if (rVariable == STRESS_VECTOR) {
		CalculateOnIntegrationPoints(rVariable, rValues, rCurrentProcessInfo);
	} else if (rVariable == STRESS_VECTOR_INTEGRATED) {
		CalculateOnIntegrationPoints(rVariable, rValues, rCurrentProcessInfo);
	}
}

// Tensor variables
void FemDem3DHexahedronElement::GetValueOnIntegrationPoints(
	const Variable<Matrix> &rVariable,
	std::vector<Matrix> &rValues,
	const ProcessInfo &rCurrentProcessInfo)
{
	if (rVariable == STRAIN_TENSOR) {
		CalculateOnIntegrationPoints(rVariable, rValues, rCurrentProcessInfo);
	} else if (rVariable == STRESS_TENSOR) {
		CalculateOnIntegrationPoints(rVariable, rValues, rCurrentProcessInfo);
	} else if (rVariable == STRESS_TENSOR_INTEGRATED) {
		CalculateOnIntegrationPoints(rVariable, rValues, rCurrentProcessInfo);
	}
}

// double variables
void FemDem3DHexahedronElement::CalculateOnIntegrationPoints(
	const Variable<double> &rVariable,
	std::vector<double> &rOutput,
	const ProcessInfo &rCurrentProcessInfo)
{
    const GeometryType::IntegrationPointsArrayType &integration_points = GetGeometry().IntegrationPoints(this->GetIntegrationMethod());
	if (rOutput.size() != integration_points.size())
		rOutput.resize(integration_points.size());

	if (rVariable == DAMAGE_ELEMENT) {
		for (unsigned int PointNumber = 0; PointNumber < integration_points.size(); PointNumber++) {
			rOutput[PointNumber] = double(this->GetValue(DAMAGE_ELEMENT));
		}
	} else if (rVariable == IS_DAMAGED) {
		for (unsigned int PointNumber = 0; PointNumber < integration_points.size(); PointNumber++) {
			rOutput[PointNumber] = double(this->GetValue(IS_DAMAGED));
		}
	} else if (rVariable == STRESS_THRESHOLD) {
		for (unsigned int PointNumber = 0; PointNumber < integration_points.size(); PointNumber++) {
			rOutput[PointNumber] = double(this->GetValue(STRESS_THRESHOLD));
		}
	}
}

// 	VECTOR VARIABLES
void FemDem3DHexahedronElement::CalculateOnIntegrationPoints(
	const Variable<Vector> &rVariable,
	std::vector<Vector> &rOutput,
	const ProcessInfo &rCurrentProcessInfo)
{
    const GeometryType::IntegrationPointsArrayType &integration_points = GetGeometry().IntegrationPoints(this->GetIntegrationMethod());
	if (rOutput.size() != integration_points.size())
		rOutput.resize(integration_points.size());

	if (rVariable == STRESS_VECTOR) {
		for (unsigned int PointNumber = 0; PointNumber < integration_points.size(); PointNumber++) {
			rOutput[PointNumber] = this->GetValue(STRESS_VECTOR);
		}
	} else if (rVariable == STRAIN_VECTOR) {
		for (unsigned int PointNumber = 0; PointNumber < integration_points.size(); PointNumber++) {
			rOutput[PointNumber] = this->GetValue(STRAIN_VECTOR);
		}
	} else if (rVariable == STRESS_VECTOR_INTEGRATED) {
		for (unsigned int PointNumber = 0; PointNumber < integration_points.size(); PointNumber++) {
			rOutput[PointNumber] = this->GetValue(STRESS_VECTOR_INTEGRATED);
		}
	}
}

// 	TENSOR VARIABLES
void FemDem3DHexahedronElement::CalculateOnIntegrationPoints(
	const Variable<Matrix> &rVariable,
	std::vector<Matrix> &rOutput,
	const ProcessInfo &rCurrentProcessInfo)
{
    const GeometryType::IntegrationPointsArrayType &integration_points = GetGeometry().IntegrationPoints(this->GetIntegrationMethod());
	if (rOutput.size() != integration_points.size())
		rOutput.resize(integration_points.size());
	const unsigned int dimension = GetGeometry().WorkingSpaceDimension();

	if (rVariable == STRESS_TENSOR) {
		for (unsigned int PointNumber = 0; PointNumber < integration_points.size(); PointNumber++) {
			if (rOutput[PointNumber].size2() != dimension)
				rOutput[PointNumber].resize(dimension, dimension, false);
			rOutput[PointNumber] = MathUtils<double>::StressVectorToTensor(this->GetValue(STRESS_VECTOR));
		}
	} else if (rVariable == STRAIN_TENSOR) {
		for (unsigned int PointNumber = 0; PointNumber < integration_points.size(); PointNumber++) {
			if (rOutput[PointNumber].size2() != dimension)
				rOutput[PointNumber].resize(dimension, dimension, false);
			rOutput[PointNumber] = MathUtils<double>::StrainVectorToTensor(this->GetValue(STRAIN_VECTOR));
		}
	} else if (rVariable == STRESS_TENSOR_INTEGRATED) {
		for (unsigned int PointNumber = 0; PointNumber < integration_points.size(); PointNumber++) {
			if (rOutput[PointNumber].size2() != dimension)
				rOutput[PointNumber].resize(dimension, dimension, false);
			rOutput[PointNumber] = MathUtils<double>::StressVectorToTensor(this->GetIntegratedStressVector());
		}
	}
}

} // namespace Kratos
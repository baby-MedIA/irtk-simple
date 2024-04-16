/*=========================================================================
 
 Date      : $Date: 29.04.2010$
 Changes   : $Authors: Laurent Risser, Francois-Xavier Vialard$
 
 =========================================================================*/

#ifndef _IRTKLARGEDEFORMATIONGRADIENTLAGRANGE_H
#define _IRTKLARGEDEFORMATIONGRADIENTLAGRANGE_H

#include <irtkLargeDeformationSciCalcPack.h>


/**
 * Class for Large Deformation registration using Beg 05's technique
 */

class LargeDefGradLagrange{
private:
	
protected:
	/// Function to launch the default calculations
	virtual void Run_Default();
	
	/// Measure of the inverse typical amplitude of the deformations
	virtual float Run_MeasureTypicalAmplitude();
	
	
	/// functions to perform the registration
	virtual void AllocateAllVariables();
	virtual void ReadAndTreatInputImages();
	virtual void ComputeEnergyGradient(int,int);
	virtual float UpdateVelocityField(int);
	virtual void SaveResultGradientDescent();
	
	///functions to save and load various structures
	virtual void LoadVelocityFields(char *);
	virtual void SaveVelocityFields(VectorField *, char *);
	virtual void LoadSplittedVelocityFields(char *);
	virtual void SaveSplittedVelocityFields(char *);
	virtual void SaveDeformations(char *);
	virtual void SaveSplittedDeformations(char *);
	virtual void SaveFlowLength(VectorField *,VectorField *,char *,char *);
	virtual void SaveEvoFlowLength(VectorField *,VectorField *,char *,char *);
	virtual void SaveVecDeformation(char *);
	virtual void SaveInvVecDeformation(char *);
	virtual void SaveInitMomentum(char *);
	virtual void SaveGlobalFlowLength(char *);
	virtual void SaveSplittedVecDeformation(char *);
	virtual void SaveSplittedFlowLength(char *);
	virtual void SaveDetJacobian(char *);
	virtual void SaveSplittedDetJacobian(char *);
	
	/// Protected parameters
	//scalar and vector fields
	ScalarField * ImTemplate;   //3D image  * [nb channels]
	ScalarField * ImTarget;     //3D image  * [nb channels]
	ScalarField J0;           //projection of 'ImTemplate' at a time between 0 and 1
	ScalarField J1;           //projection of 'ImTarget' at a time between 0 and 1
	ScalarField InitialMomentum;
	ScalarField GradInitialMomentum;
	VectorField GradJ;
	ScalarField DetJacobians;
	VectorField ForwardMapping;
	VectorField BackwardMapping;
	VectorField MappingFromT05;
	VectorField VelocityField;
	VectorField * SplittedVelocityField;  //only allocated and used when the contribution of each kernel is measured
	VectorField GradE;
	VectorField * SplittedGradE;  //only allocated and used when the contribution of each kernel is measured
	VectorField MappingSrcImag;
	VectorField MappingTrgImag;
	VectorField MappingId;
	
	//gray level changes
	float MinGrayLevel;
	float MaxGrayLevel;
	
	//size of the fields
	int NX;
	int NY;
	int NZ;
	int NT;
	
	//fft convolver (to smooth the images)
	FFTconvolver3D FFTconvolver;
	
public:
	
	/// Constructor
	LargeDefGradLagrange();
	
	/// Destructor
	virtual ~LargeDefGradLagrange();
	
	/// Run  Large Deformation registration
	virtual void Run();
	
	
	/// public Parameters
	int iteration_nb;              //number of iterations 
	float epsilon;                 //Threshold on the energy gradient convergence
	int NbTimeSubdiv;              //Number of subdivision of virtual time steps
	float MaxVelocityUpdate;       //Maximum allowed velocity update at each subdivision and iteration (in voxels)
	float RefMaxGrad;              //Reference update gradient (typically the value of MaxGrad at the 1st iteration)
	float DeltaTimeSubdiv;         //time step between two subdivision
	int Margin;                    //Margin of the image in voxels where the calculations are reduced
	float weight1,sigmaX1,sigmaY1,sigmaZ1; //std. dev. of the 1st Gaussian kernel in direction x,y,z
	float weight2,sigmaX2,sigmaY2,sigmaZ2; //std. dev. of the 2nd Gaussian kernel in direction x,y,z (only used if >0)
	float weight3,sigmaX3,sigmaY3,sigmaZ3; //std. dev. of the 3rd Gaussian kernel in direction x,y,z (only used if >0)
	float weight4,sigmaX4,sigmaY4,sigmaZ4; //std. dev. of the 4th Gaussian kernel in direction x,y,z (only used if >0)
	float weight5,sigmaX5,sigmaY5,sigmaZ5; //std. dev. of the 5th Gaussian kernel in direction x,y,z (only used if >0)
	float weight6,sigmaX6,sigmaY6,sigmaZ6; //std. dev. of the 6th Gaussian kernel in direction x,y,z (only used if >0)
	float weight7,sigmaX7,sigmaY7,sigmaZ7; //std. dev. of the 7th Gaussian kernel in direction x,y,z (only used if >0)
	int NbKernels;
	int SplitKernels;
	int symmetric;
	int NbChannels;
	int MeasureTypicAmp;
	float weightChannel[100];       //weight on each channel
	int GreyLevAlign;              //Grey level linear alignment of each channel if !=0
	float GLA_Padding_Src;         //if grey level alignment: padding value for the source image
	float GLA_Padding_Trg;         //if grey level alignment: padding value for the target image
	float WghtVelField;            //Weight of the velocity field in the energy
	int FlowLength;                //Save Length of the deformation flow from each voxel if .==1
	int DetJacobian;               //Save Determinant of the Jacobian at each voxel if .==1
	int FinalDefVec;               //Save Vector field of the estimated deformation from [Source] to [Target] if .==1
	int FinalDefInvVec;            //Save Vector field of the estimated deformation from [Target] to [Source] if .==1
	int CptInitMomentum;              //Save the initial momentum if .==1
	int ShowSSD;                   //Show the evolution of the Sum of Squared Differences at t=1
	char PrefixInputs[256];        //Prefix of the files containing an initial velocity field
	char PrefixOutputs[256];       //Prefix of the files containing the final velocity field
	char SourceFiles[100][256];     //name of the file containing the source images (up to 100 channels)
	char TargetFiles[100][256];     //name of the file containing the target images (up to 100 channels)
	char MaskFile[256];            //name of the file containing the mask on the images
	char MappingSrc[256];          //name of the file containing the mapping on (X, Y, Z) of the input source images
	char MappingTrg[256];          //name of the file containing the mapping on (X, Y, Z) of the input target images
	
};


#endif

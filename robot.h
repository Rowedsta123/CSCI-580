#include "matrix.h"
#ifndef ROBOT
#define ROBOT
enum input{	NONE = 0,
						E = 1,
						W = 2,
						WE = 3,
						S = 4,
						SE = 5,
						SW = 6,
						SWE = 7,
						N = 8,
						NE = 9,
						NW = 10,
						NWE = 11,
						NS = 12,
						NSE = 13,
						NSW = 14,
						NSWE = 15};

class Robot
{
	public:
	//CONSTRUCTOR:
		Robot(int mapcols, int maprows, input* array, long double error);
	//DESTRUCTOR
		~Robot();
	//Functions

		/*
		**Matrix* CalcJointPredictProb();
		**void CalcJointProb(Matrix* jpp);
		**void MakeObservation(input sensor);
		**long double CalcEstProb();
		**bool printlikelystates(long double maxprob);
		**void print();
		**/

	  /*\ CalcJointPredictProb
	  \*\   Takes( nothing )
	  \*\   Retruns( pointer to matrix )
 		\*\ Creates a matrix of joint prediction probabilities.
	  \*/
		Matrix* CalcJointPredictProb();

		/*\ CalcJointProb
	  \*\   Takes( pointer to joint prediction matrix )
	  \*\   Retruns( nothing )
	  \*\ Creates a matrix of joint probabilities.
	  \*/
		void CalcJointProb(Matrix* jpp);

	  /*\ MakeObservation
	  \*\   Takes( input enum from sensors )
	  \*\   Retruns( returns pointer to matrix of observations )
	  \*\ Creates a matrix of observation probabilities based on observations..
	  \*/
		void MakeObservation(input sensor);
 
	  /*\ CalcEstProb
	  \*\   Takes( Matrix* joint probabilities )
	  \*\   Retruns( returns max probability )
	  \*\ Fills member matrix with current probabilities of robot location, 
	  \*\      Then, returns the highest probability.
	  \*/
		long double CalcEstProb();//(JPP)joint prediction prob.

  	/*\ printlikelystates
  	\*\   Takes( long double Max Probability )
  	\*\   Retruns( Nothing )
  	\*\ prints list of states that the robot is most likely in.
  	\*/
		bool printlikelystates(long double maxprob);

		/*\ print
		\*\		Takes( Nothing )
		\*\		Retruns( Nothing )
		\*\ prints All matricies.
		\*/
		void print();

	private:
		Matrix* m_Startpos;
		Matrix* m_EstProb;
		Matrix* m_Transition;
		Matrix* m_Observation;
		Matrix* m_map;
		input* m_Expectedobs;
		int m_FS; //Total number of NON-OBSTICAL states.	
		int m_TS; //Total number of states.
		long double m_PError;
};

#endif

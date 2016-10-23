#include<iostream>
#include<cstdio>
#include"robot.h"
using namespace std;

	//CONSTRUCTOR:
Robot::Robot(int mapcols, int maprows, input* array, long double error)
{
	m_PError = error;
	m_map = new Matrix(mapcols, maprows);
	int NTransitions[mapcols*maprows];
	m_TS = mapcols*maprows; //total number of states
	m_FS = 0;								//number of non-obsticle states
	int N_trans_from_state;	
	for(int i = 0; i < m_TS; ++i)
	{
		if(*(array+i) == NSWE)
		{
			m_map->set(i%mapcols, i/mapcols, 0);
			NTransitions[i] = 0;
		}
		else
		{
			++m_FS;
			m_map->set(i%mapcols, i/mapcols, i+1);
			N_trans_from_state = 0;
			if(!(*(array+i) & N))
			{
				++N_trans_from_state;
			}
			if(!(*(array+i) & S))
			{
				++N_trans_from_state;
			}
			if(!(*(array+i) & W))
			{
				++N_trans_from_state;
			}
			if(!(*(array+i) & E))
			{
				++N_trans_from_state;
			}
			NTransitions[i] = N_trans_from_state;
		}
	}
	m_Startpos = new Matrix(1,m_TS);
	m_EstProb = new Matrix(1,m_TS);
	m_Transition = new Matrix(m_TS, m_TS);
	m_Observation = new Matrix(m_TS, m_TS);
	for(int i = 0; i < m_TS; ++i)//row
	{
		if((int)m_map->get(i%mapcols, i/mapcols))
		{
			m_Startpos->set(0,i,(1.0/m_FS));	//equal prob of starting in any state.
		}
		else
		{
			m_Startpos->set(0,i,0);	//0 chance of starting in obsticle state.
		}
		m_EstProb->set(0,i,0);
		for(int j = 0; j < m_TS; ++j)//column
		{
			m_Transition->set(j,i,0); // SET all elements in transition to 0.
			m_Observation->set(j,i,0); // SET all elements in observation to 0.
		} 
	}
	int North;
	int South;
	int West;
	int East;
	int state1 = 0;  
	int state2 = 0;  
	
	//Initialize possible transitions with probabilities.
	//Remember offset between name of state, and index into transition matrix.
	//							IE(state :: 1 == Matrix Index :: 0)
	//							  (state :: 2 == Matrix Index :: 1)
	for(int i = 0; i < maprows; ++i)
	{
		for(int j = 0; j < mapcols; ++j)
		{
			North = i - 1;
			South = i + 1;
			West  = j - 1;
			East  = j + 1;
			if(state1 = (int)m_map->get(j,i))//Current state on map is not a block.
			{
				if(North >=0 && North < maprows)//InBounds state North of current.
				{
					if(state2 = (int)m_map->get(j,North))//North of current is not a block.
					{
						//Push transition from State 2 to 1 into trasition matrix.
						m_Transition->set((state2-1),(state1-1),(1.0/NTransitions[state2-1]));
					}
				}
				if(South >=0 && South < maprows)//Unblocked state South of current.
				{
					if(state2 = (int)m_map->get(j,South))//South of current is not a block.
					{
						//Push transition from State 2 to 1 into trasition matrix.
						m_Transition->set((state2-1),(state1-1),(1.0/NTransitions[state2-1]));
					}
				}
				if(West  >=0 && West  < mapcols)//Unblocked state West  of current.
				{
					if(state2 = (int)m_map->get(West,i))//West  of current is not a block.
					{
						//Push transition from State 2 to 1 into trasition matrix.
						m_Transition->set((state2-1),(state1-1),(1.0/NTransitions[state2-1]));
					}
				}
				if(East  >= 0 && East  < mapcols)//Unblocked state East  of current.
				{
					if(state2 = (int)m_map->get(East,i))//East  of current is not a block.
					{
						//Push transition from State 2 to 1 into trasition matrix.
						m_Transition->set((state2-1),(state1-1),(1.0/NTransitions[state2-1]));
					}
				}
			} // END if current state is a block. 
		} // END for m_map cols
	}// END for m_map rows
	m_Expectedobs = new input[m_TS];
	for(int i = 0; i < m_TS; ++i)
	{
		m_Expectedobs[i] = *(array+i);
	}
}

	//DESTRUCTOR
Robot::~Robot()
{
	delete m_Startpos;
	delete m_EstProb;
	delete m_Transition;
	delete m_Observation;
	delete m_map;
	delete m_Expectedobs;
}

	//Functions


	/*\ CalcJointPredictProb
	\*\		Takes( nothing )
	\*\		Retruns( pointer to matrix )
	\*\ Creates a matrix of joint prediction probabilities.
	\*/
Matrix* Robot::CalcJointPredictProb()
{
	return m_Transition->product(*m_Startpos);
}
	
/*\ CalcJointProb
	\*\		Takes( pointer to joint prediction matrix )
	\*\		Retruns( nothing )
	\*\ Creates a matrix of joint probabilities.
	\*/
void Robot::CalcJointProb(Matrix* jpp)
{
	delete m_Startpos;
	m_Startpos = m_Observation->product(*jpp);
	delete jpp;
}

	/*\ MakeObservation
	\*\		Takes( input enum from sensors )
	\*\		Retruns( nothing )
	\*\ Creates a matrix of observation probabilities based on observations..
	\*/
void Robot::MakeObservation(input sensor)
{
	long double ProbOfGivenState;
	int match;
	for(int i = 0; i < m_TS; ++i)
	{
		if(m_Expectedobs[i] == NSWE)
		{
			ProbOfGivenState = 0;
		}
		else
		{
			ProbOfGivenState = 1;
			match = ~(m_Expectedobs[i] ^ sensor);
			if(match & N)
			{
				ProbOfGivenState *= (1-m_PError);
			}
			else
			{
				ProbOfGivenState *= m_PError;
			}
			if(match & S)
			{
				ProbOfGivenState *= (1-m_PError);
			}
			else
			{
				ProbOfGivenState *= m_PError;
			}
			if(match & W)
			{
				ProbOfGivenState *= (1-m_PError);
			}
			else
			{
				ProbOfGivenState *= m_PError;
			}
			if(match & E)
			{
				ProbOfGivenState *= (1-m_PError);
			}
			else
			{
				ProbOfGivenState *= m_PError;
			}
		}
		m_Observation->set(i,i,ProbOfGivenState);
	}
}

	/*\ CalcEstProb
	\*\		Takes( Matrix* joint probabilities )
	\*\		Retruns( returns max probability )
	\*\ Fills member matrix with current probabilities of robot location, 
	\*\      Then, returns the highest probability.
	\*/
long double Robot::CalcEstProb()//joint prediction prob.
{
	long double sum = 0;
	for(int i = 0; i < m_TS; ++i)
	{
		sum += m_Startpos->get(0,i);
	}
	long double max = 0;
	for(int i = 0; i < m_TS; ++i)
	{
		if(m_Startpos->get(0,i)/sum > max)
		{
			max = m_Startpos->get(0,i)/sum;
		}
		m_EstProb->set(0,i,(m_Startpos->get(0,i)/sum));
	}
	return max;
}

	/*\ printlikelystates
	\*\		Takes( long double Max Probability )
	\*\		Retruns( Nothing )
	\*\ prints list of states that the robot is most likely in.
	\*/
bool Robot::printlikelystates(long double maxprob)
{
	for(int i = 0; i < m_TS; ++i)
	{
		if(m_EstProb->get(0,i) > maxprob)
		{
			return false;
		}
		if(m_EstProb->get(0,i) == maxprob)
		{
			printf("%d ", i+1);
		}
	}
	cout<<endl;
	return true;	
}

	/*\ print
	\*\		Takes( Nothing )
	\*\		Retruns( Nothing )
	\*\ prints All matricies.
	\*/
void Robot::print()
{
	cout<<"STARTPOS"<<endl;
	m_Startpos->print();
	cout<<"EstProb"<<endl;
	m_EstProb->print();
	cout<<"Transition"<<endl;
	m_Transition->print();
	cout<<"OBSERVATION"<<endl;
	m_Observation->print();
	cout<<"MAP"<<endl;
	m_map->print();
}

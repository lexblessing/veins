#ifndef BREAKPOINTPATHLOSSMODEL_H_
#define BREAKPOINTPATHLOSSMODEL_H_

#include "AnalogueModel.h"
#include "Mapping.h"
#include "BaseWorldUtility.h"
//#include "SimplePathlossModel.h"
#include <cstdlib>

//class BreakpointPathlossModel;

/**
 * @brief Basic implementation of a BreakpointPathlossModel.
 * This class can be used to implement the ieee802154 path loss model.
 *
 * @ingroup analogueModels
 */
class BreakpointPathlossModel : public AnalogueModel
{
protected:

//	/** @brief Model to use for distances below breakpoint distance */
//	SimplePathlossModel closeRangeModel;
//	/** @brief Model to use for distances larger than the breakpoint distance */
//	SimplePathlossModel farRangeModel;


    /** @brief initial path loss in dB */
    double PL01, PL02;
    /** @brief initial path loss */
    double PL01_real, PL02_real;

    /** @brief pathloss exponents */
    double alpha1, alpha2;

    /** @brief Breakpoint distance squared. */
    double breakpointDistance;

    /** @brief Carrier frequency in Hz */
    double carrierFrequency;

    /** @brief stores my Move pattern */
    const Move& myMove;

	/** @brief Information needed about the playground */
	const bool useTorus;

	/** @brief The size of the playground.*/
	const Coord& playgroundSize;

	/** @brief Whether debug messages should be displayed. */
	bool debug;

	/** logs computed pathlosses. */
    cOutVector pathlosses;

public:
	/**
	 * @brief Initializes the analogue model. myMove and playgroundSize
	 * need to be valid as long as this instance exists.
	 *
	 * The constructor needs some specific knowledge in order to create
	 * its mapping properly:
	 *
	 * @param alpha the coefficient alpha (specified e.g. in config.xml and passed
	 *    			in constructor call)
	 * @param carrierFrequency the carrier frequency
	 * @param myMove a pointer to the hosts move pattern
	 * @param useTorus information about the playground the host is moving in
	 * @param playgroundSize information about the playground the host is moving in
	 * @param debug display debug messages?
	 */
	BreakpointPathlossModel(double L01, double L02, double alpha1, double alpha2, double breakpointDistance,
					double carrierFrequency, const Move* myMove,
					bool useTorus, const Coord& playgroundSize, bool debug):
//		closeRangeModel(L01, alpha1, carrierFrequency, myMove, useTorus, playgroundSize, debug),
//		farRangeModel(L02, alpha2, carrierFrequency, myMove, useTorus, playgroundSize, debug),
//		breakpointDistance2(breakpointDistance*breakpointDistance),
		PL01(L01), PL02(L02), alpha1(alpha1), alpha2(alpha2), breakpointDistance(breakpointDistance),
		carrierFrequency(carrierFrequency),
		myMove(*myMove),
		useTorus(useTorus),
		playgroundSize(playgroundSize),
		debug(debug)
	{
		PL01_real =  pow(10, PL01/10);
		PL02_real =  pow(10, PL02/10);
		pathlosses.setName("pathlosses");
	}

	/**
	 * @brief Filters a specified Signal by adding an attenuation
	 * over time to the Signal.
	 */
	virtual void filterSignal(Signal& s);

	virtual bool isActiveAtDestination() { return true; }

	virtual bool isActiveAtOrigin() { return false; }

};

#endif /*BREAKPOINTPATHLOSSMODEL_H_*/
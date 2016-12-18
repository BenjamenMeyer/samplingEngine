#ifndef SAMPLE_ENGINE_STATE_TESTING_FAKE_ENGINE_H__
#define SAMPLE_ENGINE_STATE_TESTING_FAKE_ENGINE_H__

#include <samplingEngine/engine.h>

//! fakeSampleEngine is an object for testing interface compliance
/*!
 fakeEngine is a simplified instantiable version of the coreSamplingEngine
 that is used for testing the interface complaince of the coreSamplingEngine class
 since it is a pure virtual (aka interface) class. It only exists for the testing
 capabilities.
 */

class fakeSampleEngine : public samplingEngine::samplingEngine
{
	public:
		static bool constructor_called;
		static bool destructor_called;

		fakeSampleEngine() : samplingEngine::samplingEngine()
			{
			fakeSampleEngine::constructor_called = true;
			}
		~fakeSampleEngine()
			{
			fakeSampleEngine::destructor_called = true;
			}

		//! (internal access) set the state
		/*!
		 internally accessible function to set the state of the samplingEngine system
		 /param samplingEngine::samplingEngine::sampleEngineState state bit-map to set
		 */
		void setState(samplingEngine::samplingEngine::sampleEngineState _state_bit) { samplingEngine::samplingEngine::setState(_state_bit); }
		//! (internal access) enable a specific state
		/*!
		 Activate a specific state by setting its bitmap value
		 /param samplingEngine::samplingEngine::sampleEngineState state bit-map to set
		 */
		void enableState(samplingEngine::samplingEngine::sampleEngineState _state_bit) { samplingEngine::samplingEngine::enableState(_state_bit); }
		//! (internal access) disable a specific state
		/*!
		 Deactivate (or clear) a specific state by setting its bitmap value
		 /param samplingEngine::samplingEngine::sampleEngineState state bit-map to set
		 */
		void disableState(samplingEngine::samplingEngine::sampleEngineState _state_bit) { samplingEngine::samplingEngine::disableState(_state_bit); }
		//! (internal access) check state status
		/*!
		 Determine if a given state's bitmap entry is set to activate
		 /param samplingEngine::samplingEngine::sampleEngineState state bit-map to set
		 /returns true if set, otherwise false
		 */
		bool isStateSet(sampleEngineState _state_bit) const { return samplingEngine::samplingEngine::isStateSet(_state_bit); }
};

#endif //SAMPLE_ENGINE_STATE_TESTING_FAKE_ENGINE_H__
